include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(toffoli 
    toffoli.cpp    
    ../functions.cpp
)
target_link_libraries(toffoli)