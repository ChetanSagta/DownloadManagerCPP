#include "NetClient.hpp"

#include <bits/types/FILE.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/multi.h>
#include <glibmm/base64.h>
#include <gtkmm/treeview.h>
#include <math.h>
#include <stddef.h>

#include <cstdio>
#include <exception>
#include <fstream>
#include <iostream>
#include "ModelColumns.hpp"

namespace DownloadManager {

NetClient::NetClient() {
    curl_global_init(CURL_GLOBAL_ALL);
    cm = curl_multi_init();
    curl_multi_setopt(cm, CURLMOPT_MAXCONNECTS, MAX_PARALLEL);
}

void NetClient::add_download(const std::string url, const Gtk::TreeRow row){
    CURL* easy_handle = curl_easy_init();
    ModelColumns m_columns;
    if(easy_handle == nullptr){
        return ;
    }
    curl_easy_setopt(easy_handle, CURLOPT_URL, url.c_str());
    /*std::fstream file;*/
    /*file.open("file.dat", std::ios::out | std::ios::in);*/
    FILE* a_file = fopen(Glib::Base64::encode(url).c_str(), "w");
    if (a_file == nullptr) {
        perror("File Not Found");
        return;
    }
    curl_easy_setopt(easy_handle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, a_file);
    curl_easy_setopt(easy_handle, CURLOPT_XFERINFODATA, row[m_columns.m_col_percentage]);
    curl_easy_setopt(easy_handle, CURLOPT_XFERINFOFUNCTION, progress_callback);
    curl_easy_setopt(easy_handle, CURLOPT_NOPROGRESS, 0);
    curl_easy_setopt(easy_handle, CURLOPT_HEADERDATA, this);
    curl_easy_setopt(easy_handle, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_setopt(easy_handle, CURLOPT_PRIVATE, &row);
    this->fileName = get_file_name(url, this->contentType);
    std::fstream file(this->fileName, std::ios::out);
}

void NetClient::run() { curl_multi_perform(cm, &still_running); }

NetClient::~NetClient() {
    curl_global_cleanup();
    curl_multi_cleanup(cm);
}

size_t NetClient::write_to_file(char* ptr, size_t size, size_t nmemb, void* f) {
    // TODO: Makesure to keep Thread safety here
    // some form of mutex or monitor
    FILE* file = (FILE*)f;
    std::cout << "file write" << std::endl;
    return fwrite(ptr, size, nmemb, file);
}

std::string NetClient::get_file_name(std::string url, std::string contentType) {
    if (int beginIndex = url.rfind('/')) {
        // Url maycontain filename
        std::string fileSubString = url.substr(beginIndex);
        if (int endIndex = fileSubString.find('&')) {
            // "&" maybe inside url and not a part of the file
            // maybe & is part of the file and in that case it wont work
            std::string fileName = fileSubString.substr(0, endIndex);
            return fileName;
        }

    } else {
        // URL Doesn't contain getFileName
        std::string fileName = "file";
        int index = contentType.find_first_of('/');
        std::string extension = contentType.substr(0, index);
        return fileName + "." + extension;
    }
    return nullptr;
}

int NetClient::progress_callback(void* clientp, double dltotal, double dlnow,
                                double ultotal, double ulnow) {
    /*std::cout<<"dltotal: "<<dltotal<<"dlnow: "<<dlnow<<"ultotal:
     * "<<ultotal<<"ulnow: "<<ulnow<<std::endl;*/
    double progress = (dlnow / dltotal) * 100;
    float percent = floorf(progress * 100) / 100;
    *(int*)clientp = percent;
    return 0;
};

void NetClient::pause_download() {
//    curl_easy_pause(easy_handle, CURL_READFUNC_PAUSE | CURL_WRITEFUNC_PAUSE);
}

auto NetClient::header_callback(char* buffer, size_t size, size_t items,
                               void* userdata) -> size_t {
    std::cout << "Buffer: " << buffer << " Size: " << size
              << " Items : " << items << " UserData: " << userdata << std::endl;
    std::string s(buffer, size * items);  // buffer is not null
                                          /* terminated*/
    /*std::cout << "==============================" << std::endl;*/
    /*std::cout << s << std::endl;*/
    if (s.find("Content-Type:") != std::string::npos) {
        int index = s.find(':');
        static_cast<NetClient*>(userdata)->contentType = s.substr(index + 1);
    }
    /*std::cout << "==============================" << std::endl;*/
    return size * items;
}

CURL* NetClient::get_curl_handle(const std::string key){
    auto task = download_tasks.find(key);
    if(task == download_tasks.end()){
        return nullptr;
    }
    return task->second;
}


}  // namespace DownloadManager
