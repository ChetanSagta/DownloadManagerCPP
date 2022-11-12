#include "AddUrlWindow.hpp"

#include <gtkmm/entry.h>
#include <gtkmm/enums.h>
#include <sigc++/functors/mem_fun.h>

#include <iostream>

#include "DownloadEntry.hpp"
#include "MainWindow.hpp"
#include "NetClient.hpp"
#include "StringUtil.cpp"

namespace DownloadManager {

AddUrlWindow::AddUrlWindow(MainWindow* window)
    : m_ok("OK"),
      m_cancel("CANCEL"),
      m_url(),
      m_text("URL: "),
      m_box(Gtk::ORIENTATION_VERTICAL),
      m_button_box(Gtk::ORIENTATION_HORIZONTAL),
      m_text_box(Gtk::Orientation::ORIENTATION_HORIZONTAL),
      m_window(window) {
    add(m_box);

    set_position(Gtk::WIN_POS_CENTER);

    m_ok.signal_clicked().connect(sigc::mem_fun(*this, &AddUrlWindow::on_ok));
    m_cancel.signal_clicked().connect(
        sigc::mem_fun(*this, &AddUrlWindow::on_cancel));

    m_button_box.pack_start(m_ok);
    m_button_box.pack_start(m_cancel);

    m_text_box.pack_start(m_text);
    m_text_box.pack_start(m_url);

    m_box.pack_start(m_text_box);
    m_box.pack_start(m_button_box);
    show_all_children();
}

AddUrlWindow::~AddUrlWindow() {}

void AddUrlWindow::on_ok() {
    std::string url = m_url.get_buffer()->get_text();
    if (url.empty()) {
        std::cout << "Url is blank. Hence returning" << std::endl;
        return;
    }
    url = StringUtil::trim(url);

    /*NetClient net_client{url};*/

    m_window->add_entry();
}

void AddUrlWindow::on_cancel() {
    this->m_url.set_text("");
    this->hide();
}

}  // namespace DownloadManager
