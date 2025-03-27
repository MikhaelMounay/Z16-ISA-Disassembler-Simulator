
file(GLOB_RECURSE SRC *.cpp *.h)

add_library(APP_SRC ${SRC})

add_executable(Z16Simulator ${SRC})
