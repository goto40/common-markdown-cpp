file(GLOB EXAMPLES ./*.cpp)

foreach(CPPFILE ${EXAMPLES})
    get_filename_component(EXE_NAME ${CPPFILE} NAME_WLE)
    add_executable(${EXE_NAME} ${CPPFILE})
    target_include_directories(${PROJECT_NAME} PRIVATE src)
    target_link_libraries(${EXE_NAME} ${PROJECT_NAME})
endforeach()
