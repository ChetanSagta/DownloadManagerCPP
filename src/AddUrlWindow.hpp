#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/window.h>

namespace DownloadManager {

class AddUrlWindow : public Gtk::Window {
   public:
    AddUrlWindow();
    ~AddUrlWindow();

   private:
    Gtk::Button m_ok, m_cancel;
    Gtk::Entry m_url;
    Gtk::Label m_text;
    Gtk::Box m_box, m_button_box, m_text_box;

protected:
  void on_ok();
  void on_cancel();
};

}  // namespace DownloadManager
