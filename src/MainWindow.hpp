#pragma once

#include <gtkmm.h>
#include "NetClient.hpp"
#include "ModelColumns.hpp"
#include "gtkmm/treeiter.h"

namespace DownloadManager {

class AddUrlWindow;
class DownloadEntry;
class MainWindow : public Gtk::Window {
   public:
    MainWindow();
    virtual ~MainWindow();
    Gtk::TreeRow add_entry();
    Gtk::TreeRow add_entry(DownloadEntry&);
    NetClient& get_net_client();

   protected:
    // Signal handlers:
    void on_button_quit();
    void on_add_entry();
    void on_del_entry();
    void on_start_entry();
    void on_stop_entry();
    void select_entry(const Gtk::ListStore::Path&, Gtk::TreeViewColumn*);
    void on_my_row_deleted(const Gtk::TreeModel::Path&);
    // Tree model columns:

    ModelColumns m_columns;

    // Child widgets:
    Gtk::ButtonBox m_top_hbox;
    Gtk::Box m_vbox;

    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::TreeView m_TreeView;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
    Gtk::ButtonBox m_ButtonBox;
    Gtk::Button m_add_btn, m_del_btn, m_start_btn, m_stop_btn, m_btn_quit;
    AddUrlWindow* add_url_window;
    Gtk::TreeModel::Row selected_row;
    NetClient net_client;
};
}  // namespace DownloadManager
