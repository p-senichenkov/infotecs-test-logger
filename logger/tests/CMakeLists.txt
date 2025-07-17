file(GLOB test_sources CONFIGURE_DEPENDS "*.cpp")

add_executable(LoggerTests ${test_sources})

target_include_directories(LoggerTests PRIVATE ".")

target_link_libraries(LoggerTests LoggerLib)
