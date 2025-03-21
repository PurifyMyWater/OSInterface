cmake_minimum_required(VERSION 3.16)

Project(OSInterface)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (ESP_PLATFORM)
    set(EXPECTED_IDF_VERSION "5.4.0")
    if (NOT $ENV{IDF_VERSION} STREQUAL ${EXPECTED_IDF_VERSION})
        message(WARNING "This project mirrors the logging behavior of ESP-IDF ${EXPECTED_IDF_VERSION}, but you are using a different version of ESP-IDF ($ENV{IDF_VERSION}). Please ensure that the logging behavior is consistent with your version. Check out the differences between 'OSInterfaceLogLevel' and https://github.com/espressif/esp-idf/blob/master/components/log/include/esp_log_level.h")
    endif ()
endif ()

add_subdirectory(include)
add_subdirectory(lintHelper)
