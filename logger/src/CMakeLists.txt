file(GLOB_RECURSE lib_sources CONFIGURE_DEPENDS "*.cpp")

add_library(LoggerLib ${LIBRARY_TYPE} ${lib_sources})

target_include_directories(LoggerLib PUBLIC ".")
