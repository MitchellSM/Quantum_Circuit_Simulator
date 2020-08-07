include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(cnot 
    cnot.cpp    
    ../functions.cpp
)
target_link_libraries(cnot)