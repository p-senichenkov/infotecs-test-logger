file(GLOB test_sources CONFIGURE_DEPENDS "*.cpp")

add_executable(Tests ${test_sources})

target_include_directories(Tests PRIVATE ".")

target_link_libraries(Tests LoggerLib)
