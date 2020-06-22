cmake_minimum_required(VERSION 3.14)
project(bitsy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

IF(APPLE)
	# Fix linking on 10.14+. See https://stackoverflow.com/questions/54068035
	LINK_DIRECTORIES(/usr/local/lib)
	INCLUDE_DIRECTORIES(/usr/local/include)
ENDIF()

if (WIN32)
	add_definitions(-DSDL_MAIN_HANDLED)
endif()

file(GLOB SRC "src/*.h" "src/*.cpp" "src/*.hpp")

find_package(SDL2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
