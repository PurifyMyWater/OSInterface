add_library(OSInterface INTERFACE)

if (ESP_PLATFORM)
    target_compile_definitions(OSInterface INTERFACE ESP_DEFINED=1)
endif ()

target_include_directories(OSInterface INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
