#include "NetClient.hpp"

#include <bits/types/FILE.h>
#include <curlpp/Exception.hpp>
#include <stddef.h>
#include <cstdio>
#include <fstream>
#include <iostream>

namespace DownloadManager {

NetClient::NetClient(std::string url) {
  try {
    curlpp::initialize();
    std::cout << "URL: " << url << std::endl;
    easyHandle.setOpt<curlpp::Options::Url>(url);
    easyHandle.setOpt<curlpp::Options::FollowLocation>(true);
    /*easyHandle.setOpt<curlpp::Options::WriteFile>(&file);*/
    /*curlpp::OptionTrait<void*, CURLOPT_WRITEDATA> myData(&input);*/
    /*file.write(input, 2048);*/
    easyHandle.setOpt(new curlpp::options::HeaderFunction(
        [this](char *buffer, size_t size, size_t items) -> size_t {
          std::string s(buffer,
                        size * items); // buffer is not null
                                       /* terminated*/
          std::cout << "==============================" <<
          std::endl; std::cout << s << std::endl;
          if (s.find("Content-Type") != std::string::npos) {
            int index = s.find(':');
            this->contentType = s.substr(index);
          }
          std::cout << "==============================" <<
          std::endl;
          return size * items;
        }));
    this->fileName = getFileName(url, this->contentType);
    std::fstream file(this->fileName, std::ios::out);
    easyHandle.setOpt<curlpp::Options::WriteStream>(&file);
    easyHandle.perform();
    /*std::cout<<"================================"<<input;*/
    file.close();
  } catch (curlpp::LibcurlRuntimeError &err) {
    if (err.whatCode() == 3) {
      std::cout << "bad/ illegal format or missing URL. Please check the link";
    } else {
      std::cout << " Error Code: " << err.whatCode()
                << " Error Message: " << err.what() << std::endl;
    }
  }
    std::cout << "#########################################" << std::endl;
    std::cout << "Content-Type : " << this->contentType
              << "FileName : " << this->fileName << std::endl;
    std::cout << "#########################################" << std::endl;
}

NetClient::~NetClient() { curlpp::terminate(); }

size_t NetClient::writeToFile(char *ptr, size_t size, size_t nmemb, void *f) {
  // TODO: Makesure to keep Thread safety here
  // some form of mutex or monitor
  FILE *file = (FILE *)f;
  std::cout << "file write" << std::endl;
  return fwrite(ptr, size, nmemb, file);
}
size_t NetClient::header_callback(char *buffer, size_t size, size_t nitems,
                                  void *userdata) {
  std::string *headers = (std::string *)userdata;
  headers->append(buffer, nitems * size);
  return nitems * size;
}

std::string NetClient::getFileName(std::string url, std::string contentType) {
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

} // namespace DownloadManager
