cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -Wall -pedantic -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
project(DownloadManager)
# Search pkg-config utility first
find_package(PkgConfig REQUIRED)
find_package(spdlog REQUIRED)
find_package(CURL REQUIRED)


# Then use pkg-config for locate specific package
pkg_check_modules(LIBXMLXX REQUIRED IMPORTED_TARGET libxml++-2.6)
# pkg_check_modules(CURLPP REQUIRED curlpp)
pkg_check_modules(GTKMM gtkmm-3.0)

# FetchContent_Declare(ftxui
#   GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
#   GIT_TAG v3.0.0
# )
#
# FetchContent_GetProperties(ftxui)
# if(NOT ftxui_POPULATED)
#   FetchContent_Populate(ftxui)
#   add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} src/main.cpp src/MainWindow.cpp src/MainWindow.hpp src/DownloadEntry.cpp src/DownloadEntry.hpp src/FSClient.cpp src/FSClient.cpp src/NetClient.cpp src/NetClient.cpp src/AddUrlWindow.hpp src/AddUrlWindow.cpp src/StringUtil.cpp)

# Link with the IMPORTED target created by 'pkg_check_modules'
# That target contains both include directories and actual libraries for link.
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::LIBXMLXX)
# target_link_libraries(${PROJECT_NAME} PRIVATE ${CURLPP_LDFLAGS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES})
# target_link_libraries(${PROJECT_NAME} PRIVATE ftxui::screen ftxui::dom ftxui::component) 
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTKMM_LIBRARIES}  )
