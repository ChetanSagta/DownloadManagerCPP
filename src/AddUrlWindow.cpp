#include "AddUrlWindow.hpp"

#include <sigc++/functors/mem_fun.h>

#include <iostream>

#include "gtkmm/enums.h"

namespace DownloadManager {

AddUrlWindow::AddUrlWindow()
    : m_ok("OK"),
      m_cancel("CANCEL"),
      m_url(),
      m_text("URL: "),
      m_box(Gtk::ORIENTATION_VERTICAL),
      m_button_box(Gtk::ORIENTATION_HORIZONTAL),
      m_text_box(Gtk::Orientation::ORIENTATION_HORIZONTAL) {
    add(m_box);

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

void AddUrlWindow::on_ok() { std::cout << m_url.get_buffer()->get_text()<< std::endl; }

void AddUrlWindow::on_cancel() { std::cout << "CANCEL BTN" << std::endl; 
  this->hide();
}

}  // namespace DownloadManager
