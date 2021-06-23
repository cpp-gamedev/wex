cmake_minimum_required(VERSION 3.13)
project(wex)

add_subdirectory("ext/SFML")

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Select Build type [Debug/Release]" FORCE)
endif()

set(CFLAGS -Wall -Wextra -Werror)

# find the source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# TODO: set the wex engine to a static library, and link this exe
# to that library.
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE "ext/SFML/include")
target_include_directories(${PROJECT_NAME} PRIVATE "ext/SFML/headers")
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE ${CFLAGS})

