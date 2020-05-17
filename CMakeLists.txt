cmake_minimum_required(VERSION 3.16)
project(projekt C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(structs)

add_executable(projekt
        structs/Event.h
        structs/Node.h
        structs/Options.h
        structs/Snake.h
        main.c
        utils.c
        utils.h)

find_package(Curses REQUIRED )
include_directories(${CURSES_INCLUDE_DIRS} )
target_link_libraries(projekt ${CURSES_LIBRARIES} )