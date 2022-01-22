cmake_minimum_required(VERSION 3.13)
project(wex)

add_subdirectory("ext/SFML")

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Select Build type [Debug/Release]")
endif()

# find the source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# TODO: set the wex engine to a static library, and link this exe
# to that library.
add_library(${PROJECT_NAME})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC "ext/SFML/headers")
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-window)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

if (NOT MSVC)
	set(COMPILER_FLAGS "-Wall" "-Wextra" "-Werror")
endif()
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILER_FLAGS})

# The sample game
option(WEX_BUILD_SAMPLE "Build a sample game" ON)
if (WEX_BUILD_SAMPLE)
	add_subdirectory(sample)
endif()
