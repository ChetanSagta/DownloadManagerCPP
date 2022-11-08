#include <string>

namespace DownloadManager {
class FSClient {
   private:
    bool is_file_present();
    std::string update_name();
};

}  // namespace DownloadManager
