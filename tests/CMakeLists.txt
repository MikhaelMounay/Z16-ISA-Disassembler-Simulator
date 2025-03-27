
file(GLOB_RECURSE TESTS *.cpp *.h)

add_executable(Z16SimulatorTests ${TESTS})

target_link_libraries(Z16SimulatorTests gtest gtest_main APP_SRC)
