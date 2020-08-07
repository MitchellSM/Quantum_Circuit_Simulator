include_directories(${PROJECT_SOURCE_DIR}/include)

set(CATCH_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/test})
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

add_library(funcs ${PROJECT_SOURCE_DIR}/src/functions.cpp)
add_executable(tests test.cpp)
target_link_libraries(tests funcs Catch)