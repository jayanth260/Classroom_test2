find_package(OpenMP REQUIRED)


add_library(studentlib main.cpp)
target_include_directories(studentlib PUBLIC ${CMAKE_SOURCE_DIR}/include)

if(OpenMP_FOUND)
    target_link_libraries(studentlib PUBLIC OpenMP::OpenMP_CXX)
    target_compile_options(studentlib PRIVATE ${OpenMP_CXX_FLAGS})
endif()

target_compile_options(studentlib PRIVATE -Ofast  -march=native) 
