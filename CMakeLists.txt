cmake_minimum_required(VERSION 3.16)
project(babyphone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Quick DBus)

add_executable(babyphone
    main.cpp
    babyphonedefines.h
    settings.cpp settings.h
    contact.cpp contact.h
    audiomonitor.cpp audiomonitor.h
    callmonitor.cpp callmonitor.h
    usernotifier.cpp usernotifier.h
    profileswitcher.cpp profileswitcher.h
    babyphone.cpp babyphone.h
    mainwindow.cpp mainwindow.h
    resources.qrc
)

target_link_libraries(babyphone PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Quick
    Qt6::DBus
)

target_compile_definitions(babyphone PRIVATE BABYPHONE_DESKTOP_BUILD)

install(TARGETS babyphone DESTINATION bin)
