cmake_minimum_required(VERSION 3.16)
project(fuz C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

find_package(Curses REQUIRED)

include_directories(
	src/core/matcher
	src/data_handler
	src/tui
	src/vector
	${CURSES_INCLUDE_DIR}
)

set(SOURCES
	src/main.c
	src/core/matcher/matcher.c
	src/data_handler/handler.c
	src/tui/tui.c
	src/vector/vector.c
)

if(NOT DEFINED EXECUTABLE_OUTPUT_DIR)
	set(EXECUTABLE_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_DIR})

add_executable(fuz ${SOURCES})

target_link_libraries(fuz ${CURSES_LIBRARIES})
