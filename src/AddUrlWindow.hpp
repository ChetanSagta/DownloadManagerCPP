#pragma once

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/window.h>
namespace DownloadManager {

class MainWindow;

class AddUrlWindow : public Gtk::Window {
   public:
    AddUrlWindow(MainWindow *window);
    ~AddUrlWindow();

   private:
    Gtk::Button m_ok, m_cancel;
    Gtk::Entry m_url;
    Gtk::Label m_text;
    Gtk::Box m_box, m_button_box, m_text_box;
    MainWindow* m_window;

protected:
  void on_ok();
  void on_cancel();
};

}  // namespace DownloadManager
