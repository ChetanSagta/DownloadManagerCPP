#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include<string>

namespace DownloadManager {

class NetClient {
   public:
    NetClient(std::string url);
    ~NetClient();

   private:
    std::string url;
    std::string fileName;
    std::string contentType;
    int port;
    curlpp::Easy easyHandle;
    std::string getFileName();
    static size_t writeToFile(char* ptr, size_t size, size_t nmemb, void*f);
    static size_t header_callback(char* buffer, unsigned long size,
    unsigned long nitems, void* userdata);
    std::string getFileName(std::string, std::string);
};

}  // namespace DownloadManager
