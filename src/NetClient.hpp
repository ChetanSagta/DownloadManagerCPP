#pragma once
#include <curl/curl.h>
#include <gtkmm/treeview.h>
#include <map>

#include <string>
#include "gtkmm/treeiter.h"

namespace DownloadManager {

class NetClient {
   public:
    NetClient();
    ~NetClient();
    void add_download(const std::string url, const Gtk::TreeRow);
    void pause_download();
    void run();
    CURL* get_curl_handle(const std::string key);
    CURL* selected_handle;

   private:
    std::string url;
    std::string fileName;
    std::string contentType;
    int port, still_running;
    CURLM *cm;
    CURLMsg *msg;
    std::map<std::string,CURL*> download_tasks;
    std::string get_file_name();
    static size_t write_to_file(char* ptr, size_t size, size_t nmemb, void* f);
    static size_t header_callback(char* buffer, unsigned long size,
                                  unsigned long nitems, void* userdata);
    std::string get_file_name(std::string, std::string);
    int static progress_callback(void*, double, double, double, double);
    const long MAX_PARALLEL = 10;
};

}  // namespace DownloadManager
