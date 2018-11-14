cmake_minimum_required(VERSION 3.12)
project(NPuzzle)

set(CMAKE_CXX_STANDARD 14)

add_executable(NPuzzle sources/main.cpp sources/Board.cpp headers/Board.h sources/Solver.cpp headers/Solver.h sources/Logger.cpp headers/Logger.h sources/Parser.cpp headers/Parser.h headers/CommonHeader.h)


#set(CURSES_NEED_NCURSES TRUE)
#find_package(Curses REQUIRED)
#if (CURSES_FOUND AND CURSES_HAVE_NCURSES_H)
#    include_directories(${CURSES_INCLUDE_DIR})
#    target_link_libraries (NPuzzle ${CURSES_LIBRARIES})
#endif()