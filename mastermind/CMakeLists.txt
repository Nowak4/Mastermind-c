cmake_minimum_required(VERSION 3.16)

project(mastermind LANGUAGES C)

add_executable(mastermind
    ../src/mastermind.c ../src/players.c ../src/players.h)

include(GNUInstallDirs)
install(TARGETS mastermind
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
