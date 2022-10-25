#include <glibmm/ustring.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/widget.h>

#include <cstddef>
#include <string>

#include "gtkmm/container.h"

namespace DownloadManager {

class DownloadEntry {
   public:
    DownloadEntry(Glib::ustring, Glib::ustring, Glib::ustring, Glib::ustring,
                  Glib::ustring, Glib::ustring);
    ~DownloadEntry();

    int get_sno();
    Glib::ustring get_title();
    Glib::ustring get_url();
    Glib::ustring get_file_size();
    Glib::ustring get_local_size();
    Glib::ustring get_file_location();
    Glib::ustring get_percentage();

   protected:
    void on_click();

   private:
    int m_sno;
    Glib::ustring m_title;
    Glib::ustring m_url;
    Glib::ustring m_file_size;
    Glib::ustring m_local_size;
    Glib::ustring m_file_location;
    Glib::ustring m_percentage;
    static inline int counter = 0;
};

}  // namespace DownloadManager
