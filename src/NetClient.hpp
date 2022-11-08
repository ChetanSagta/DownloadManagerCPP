#include <curl/curl.h>
#include <gtkmm/treeview.h>

#include <string>

namespace DownloadManager {

class NetClient {
   public:
    NetClient(const Glib::RefPtr<Gtk::TreeModel>& );
    ~NetClient();

    void setUrl(std::string url);
    void pauseDownload();
    void run();

   private:
    std::string url;
    std::string fileName;
    std::string contentType;
    int port;
    CURL* easy_handle;
    Gtk::TreeView m_tree_view;
    std::string getFileName();
    static size_t writeToFile(char* ptr, size_t size, size_t nmemb, void* f);
    static size_t header_callback(char* buffer, unsigned long size,
                                  unsigned long nitems, void* userdata);
    std::string getFileName(std::string, std::string);
    int static progressCallBack(void*, double, double, double, double);
    static size_t headerCallBack(char*, size_t, size_t,void*);
};

}  // namespace DownloadManager
