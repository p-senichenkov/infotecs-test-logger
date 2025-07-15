file(GLOB_RECURSE lib_sources CONFIGURE_DEPENDS "*.cpp")

message(${LIBRARY_TYPE})

add_library(${CMAKE_PROJECT_NAME} ${LIBRARY_TYPE} ${lib_sources})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ".")
