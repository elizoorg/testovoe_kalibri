cmake_minimum_required(VERSION 3.16)
project(QtTelecomServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets)

set(SERVER_SOURCES
    main.cpp
    network_server.cpp
    server_window.cpp
    settings_dialog.cpp
)

set(SERVER_HEADERS
    network_server.h
    server_window.h
    settings_dialog.h
)

qt_add_executable(QtTelecomServer ${SERVER_SOURCES} ${SERVER_HEADERS})
target_link_libraries(QtTelecomServer PRIVATE Qt6::Core Qt6::Network Qt6::Widgets)


install(TARGETS QtTelecomServer DESTINATION bin)