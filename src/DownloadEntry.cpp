#include "DownloadEntry.hpp"

namespace DownloadManager {
int DownloadEntry::get_sno(){return this->m_sno;}
Glib::ustring DownloadEntry::get_title() { return this->m_title; }
Glib::ustring DownloadEntry::get_url() { return this->m_url; }
long DownloadEntry::get_file_size() { return this->m_file_size; }
long  DownloadEntry::get_local_size() { return this->m_local_size; }
Glib::ustring DownloadEntry::get_file_location() { return this->m_file_location; }
int DownloadEntry::get_percentage() { return this->m_percentage; }

DownloadEntry::DownloadEntry(Glib::ustring url): m_sno{++counter}, m_url{url}, m_local_size{0}{}


}  // namespace DownloadManager
