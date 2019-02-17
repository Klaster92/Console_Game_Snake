cmake_minimum_required (VERSION 2.8)

if (CMAKE_VERSION VERSION_LESS "3.1")
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
	endif ()
else ()
	set (CMAKE_CXX_STANDARD 11)
endif ()

project (Console_Game_Snake)

find_package(Threads)

add_executable(Console_Game_Snake
		src/game.cpp
		src/ConsoleGameBase.cpp
		src/ConsoleGameSnake.cpp
		src/ConsoleGamePong/ConsoleGamePong.cpp
		)
target_link_libraries(Console_Game_Snake ${CMAKE_THREAD_LIBS_INIT})
