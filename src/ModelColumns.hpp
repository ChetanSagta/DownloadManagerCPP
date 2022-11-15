#pragma once

#include<gtkmm.h>

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
