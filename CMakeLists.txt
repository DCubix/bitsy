cmake_minimum_required(VERSION 3.14)
project(bitsy)

if (WIN32)
	add_definitions(-DSDL_MAIN_HANDLED)
endif()

file(GLOB SRC "src/*.h" "src/*.cpp" "src/*.hpp")

find_package(SDL2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
