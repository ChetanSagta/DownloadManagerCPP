#pragma once

#include <gtkmm.h>

#include "DownloadEntry.hpp"
namespace DownloadManager {

class AddUrlWindow;
class MainWindow : public Gtk::Window {
   public:
    MainWindow();
    virtual ~MainWindow();
    void add_entry();
    void add_entry(DownloadEntry&);

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
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
       public:
        ModelColumns() {
            add(m_col_id);
            add(m_col_title);
            add(m_col_url);
            add(m_col_file_size);
            add(m_col_local_file_size);
            add(m_col_file_location);
            add(m_col_percentage);
        }

        Gtk::TreeModelColumn<unsigned int> m_col_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_title;
        Gtk::TreeModelColumn<Glib::ustring> m_col_url;
        Gtk::TreeModelColumn<Glib::ustring> m_col_file_size;
        Gtk::TreeModelColumn<Glib::ustring> m_col_local_file_size;
        Gtk::TreeModelColumn<Glib::ustring> m_col_file_location;
        Gtk::TreeModelColumn<int> m_col_percentage;
    };

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
    Gtk::TreeRow selected_row;
    
};
}  // namespace DownloadManager
