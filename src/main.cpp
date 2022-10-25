#include "MainWindow.hpp"
#include "gtkmm/application.h"

int main(int argc, char *argv[]) {

  auto app = Gtk::Application::create(argc, argv, "Download Manager");

  DownloadManager::MainWindow mainwindow;

  return app->run(mainwindow);
}
