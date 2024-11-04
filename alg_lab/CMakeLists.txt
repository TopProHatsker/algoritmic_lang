cmake_minimum_required(VERSION 3.16)

project(alg_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(alg_lab
    main.cpp
    station.h
    pipe.h
    func.h
    func.cpp
    new_menu.cpp
    new_menu.h
    res.pages
    gt_system.h
    gt_system.cpp
    station.cpp
    pipe.cpp
    graph.cpp
    graph.h
    )

include(GNUInstallDirs)
install(TARGETS alg_lab
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
