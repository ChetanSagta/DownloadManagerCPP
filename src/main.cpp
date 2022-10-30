#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include "NetClient.hpp"
#include "MainWindow.hpp"
#include "gtkmm/application.h"

int main(int argc, char* argv[]) {
  /*std::string url ="https://repo.zenk-security.com/Magazine%20E-book/Hacking-%20The%20Art%20of%20Exploitation%20(2nd%20ed.%202008)%20-%20Erickson.pdf";*/
    auto app = Gtk::Application::create(argc, argv, "Download Manager");
    
    DownloadManager::MainWindow mainwindow;
    
    return app->run(mainwindow);
}
