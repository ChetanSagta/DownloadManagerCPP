#include "DownloadEntry.hpp"

#include <iostream>

namespace DownloadManager {
int DownloadEntry::get_sno(){return this->m_sno;}
Glib::ustring DownloadEntry::get_title() { return this->m_title; }
Glib::ustring DownloadEntry::get_url() { return this->m_url; }
Glib::ustring DownloadEntry::get_file_size() { return this->m_file_size; }
Glib::ustring DownloadEntry::get_local_size() { return this->m_local_size; }
Glib::ustring DownloadEntry::get_file_location() { return this->m_file_location; }
Glib::ustring DownloadEntry::get_percentage() { return this->m_percentage; }

}  // namespace DownloadManager