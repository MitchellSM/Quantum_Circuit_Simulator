include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(deutsch 
    deutsch.cpp    
    ../functions.cpp
)
target_link_libraries(deutsch)