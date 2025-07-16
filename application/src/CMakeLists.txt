file(GLOB app_sources CONFIGURE_DEPENDS "*.cpp")

add_executable(DemoApplication ${app_sources})

target_link_libraries(DemoApplication LoggerLib)
