#include "MainWindow.hpp"

#include <cstdlib>
#include <iostream>

#include "AddUrlWindow.hpp"
#include "DownloadEntry.hpp"
#include "StringUtil.cpp"
#include "gtkmm/box.h"
#include "gtkmm/enums.h"

namespace DownloadManager {
MainWindow::MainWindow()
    : m_top_hbox(Gtk::ORIENTATION_HORIZONTAL),
      m_vbox(Gtk::ORIENTATION_VERTICAL),
      m_add_btn("ADD"),
      m_del_btn("DELETE"),
      m_start_btn("START"),
      m_stop_btn("STOP"),
      m_btn_quit("Quit"),
      add_url_window() {


    set_title("Gtk::TreeView (ListStore) example");
    set_position(Gtk::WIN_POS_CENTER);
    set_border_width(5);
    set_default_size(900, 700);

    add(m_vbox);
    // Add the TreeView, inside a ScrolledWindow, with the button underneath:
    m_ScrolledWindow.add(m_TreeView);

    // Only show the scrollbars when they are necessary:
    m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    m_vbox.pack_start(m_top_hbox, Gtk::PACK_SHRINK);
    m_vbox.pack_start(m_ScrolledWindow);
    m_vbox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

    m_add_btn.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_add_entry));
    m_del_btn.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_del_entry));
    m_start_btn.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_start_entry));
    m_stop_btn.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_stop_entry));
    m_top_hbox.pack_start(m_add_btn, Gtk::PACK_SHRINK);
    m_top_hbox.pack_start(m_del_btn, Gtk::PACK_SHRINK);
    m_top_hbox.pack_start(m_start_btn, Gtk::PACK_SHRINK);
    m_top_hbox.pack_start(m_stop_btn, Gtk::PACK_SHRINK);

    m_ButtonBox.pack_start(m_btn_quit, Gtk::PACK_SHRINK);
    m_ButtonBox.set_border_width(5);
    m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
    m_btn_quit.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_button_quit));

    // Create the Tree model:
    m_refTreeModel = Gtk::ListStore::create(m_columns);
    m_TreeView.set_model(m_refTreeModel);
    m_TreeView.set_activate_on_single_click(true);
    m_TreeView.signal_row_activated().connect(
        sigc::mem_fun(*this, &MainWindow::select_entry));
    // Fill the TreeView's model
    /*add_entry();*/

    // Add the TreeView's view columns:
    // This number will be shown with the default numeric formatting.
    m_TreeView.append_column_numeric("S.No", m_columns.m_col_id, "%d");
    m_TreeView.append_column("Name", m_columns.m_col_title);

    m_TreeView.append_column("URL", m_columns.m_col_url);
    m_TreeView.append_column("FILE SIZE", m_columns.m_col_file_size);
    m_TreeView.append_column("LOCAL FILE SIZE",
                             m_columns.m_col_local_file_size);
    m_TreeView.append_column("FILE SIZE", m_columns.m_col_file_size);
    m_TreeView.append_column("LOCAL FILE SIZE",
                             m_columns.m_col_local_file_size);
    m_TreeView.append_column("FILE LOCATION", m_columns.m_col_file_location);
    auto cell = Gtk::make_managed<Gtk::CellRendererProgress>();
    int cols_count = m_TreeView.append_column("PERCENTAGE", *cell);
    auto pColumn = m_TreeView.get_column(cols_count - 1);
    if (pColumn) {
        pColumn->add_attribute(cell->property_value(),
                               m_columns.m_col_percentage);
    }

    // Make all the columns reorderable:
    // This is not necessary, but it's nice to show the feature.
    // You can use TreeView::set_column_drag_function() to more
    // finely control column drag and drop.
    for (guint i = 0; i < 2; i++) {
        auto column = m_TreeView.get_column(i);
        column->set_reorderable();
    }
    show_all_children();
}

MainWindow::~MainWindow() {}

void MainWindow::on_button_quit() { hide(); }
void MainWindow::on_add_entry() {
    if (add_url_window == nullptr) add_url_window = new AddUrlWindow(this);
    add_url_window->show();
}
void MainWindow::on_del_entry() {
    if (selected_row == nullptr) return;
    selected_row = *(m_refTreeModel->erase(selected_row));
    if (selected_row == nullptr) {
        auto selection = m_TreeView.get_selection();
        selected_row = *(selection->get_selected());
    }
}
void MainWindow::on_start_entry() {
    if (selected_row == nullptr) return;
    /*std::cout << selected_row.children()<< std::endl;*/
   selected_row.
}
void MainWindow::on_stop_entry() {
    if (selected_row == nullptr) return;
    std::cout << "ON STOP Entry" << std::endl;
}
void MainWindow::add_entry() {
    static int count = 0;
    Gtk::TreeModel::Row row = *(m_refTreeModel->append());
    row[m_columns.m_col_id] = ++count;
    ;
    row[m_columns.m_col_title] = "Billy Bob";
    row[m_columns.m_col_url] = "URL";
    row[m_columns.m_col_file_size] = "10MB";
    row[m_columns.m_col_local_file_size] = "1MB";
    row[m_columns.m_col_file_location] = "Downloads";
    row[m_columns.m_col_percentage] = 10;
}
void MainWindow::add_entry(DownloadEntry& entry) {
    Gtk::TreeModel::Row row = *(m_refTreeModel->append());
    row[m_columns.m_col_id] = entry.get_sno();
    row[m_columns.m_col_title] = entry.get_title();
    row[m_columns.m_col_url] = entry.get_url();
    row[m_columns.m_col_file_size] =
        StringUtil::getFileSizeStr(entry.get_file_size());
    row[m_columns.m_col_local_file_size] =
        StringUtil::getFileSizeStr(entry.get_local_size());
    row[m_columns.m_col_file_location] = entry.get_file_location();
    row[m_columns.m_col_percentage] = entry.get_percentage();
}

void MainWindow::select_entry(const Gtk::TreeModel::Path& path,
                              Gtk::TreeViewColumn* column) {
    /*Glib::RefPtr<Gtk::TreeSelection> selection = m_TreeView.get_selection();*/
    /*std::cout << selection.get() << std::endl;*/
    const auto iter = m_refTreeModel->get_iter(path);
    if (iter) {
        selected_row = *iter;
        const auto row = *iter;
        std::cout << "Row activated: ID= " << row[m_columns.m_col_id]
                  << ", Name= " << row[m_columns.m_col_title] << std::endl;
    }
}
}  // namespace DownloadManager
