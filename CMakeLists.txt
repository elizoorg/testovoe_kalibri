cmake_minimum_required(VERSION 3.16)
project(QtTelecomApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опции сборки
option(BUILD_CLIENT "Build client application" ON)
option(BUILD_SERVER "Build server application" ON)

# Ищем Qt6 компоненты
find_package(Qt6 REQUIRED COMPONENTS Core Network)

if(BUILD_CLIENT)
    add_subdirectory(client)
endif()

if(BUILD_SERVER)
    add_subdirectory(server)
endif()

add_custom_target(all_apps DEPENDS)
if(BUILD_CLIENT)
    add_dependencies(all_apps QtTelecomClient)
endif()
if(BUILD_SERVER)
    add_dependencies(all_apps QtTelecomServer)
endif()