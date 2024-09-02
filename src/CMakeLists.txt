file(GLOB_RECURSE SRC ./*.cpp)
add_library(${PROJECT_NAME} ${SRC} ${version_file})
target_include_directories(${PROJECT_NAME} PUBLIC .)
