#pragma once
#include <string>

class StringUtil {
   public:
    static std::string trim(std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

      static std::string getFileSizeStr(long bytes) {
        long tempContentLength = bytes;
        if ((tempContentLength = bytes / 1024) < 1024) {
            return std::to_string(tempContentLength) + "KB";
        } else if ((tempContentLength = bytes / (1024 * 1024)) < 1024) {
            return std::to_string(tempContentLength) + "MB";
        } else if ((tempContentLength = bytes / (1024 * 1024 * 1024)) < 1024) {
            return std::to_string(tempContentLength) + "GB";
        } else
            return std::to_string(bytes) + "B";
    }
};
