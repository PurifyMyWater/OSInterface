add_library(OSInterface STATIC)

file(GLOB OSInterface_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(OSInterface PRIVATE ${OSInterface_SOURCES})
target_include_directories(OSInterface PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
