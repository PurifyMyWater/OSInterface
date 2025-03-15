add_executable(lintHelper lintHelper.cpp espLintHelper.cpp)

target_link_libraries(lintHelper PUBLIC OSInterface)