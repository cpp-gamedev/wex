add_executable(wex-sample)
target_sources(wex-sample PRIVATE "main.cpp")
target_link_libraries(wex-sample wex::wex)
target_compile_options(wex-sample PRIVATE "-Wall" "-Wextra" "-Werror")
