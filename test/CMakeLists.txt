find_package(Catch2 3 REQUIRED)
file(GLOB_RECURSE TST ./*.cpp)

set(UNITTEST "${PROJECT_NAME}_unit_tests")
add_executable(${UNITTEST} ${TST})
target_include_directories(${UNITTEST} PRIVATE src)
target_include_directories(${UNITTEST} PRIVATE test)
target_include_directories(${UNITTEST} PRIVATE ${CATCH_INCLUDE_PATH})
target_link_libraries(${UNITTEST} ${PROJECT_NAME} Catch2::Catch2WithMain)

add_test(NAME unittest COMMAND ${UNITTEST})
