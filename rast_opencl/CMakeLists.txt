file(GLOB C_FILES *.cpp)
file(GLOB H_FILES *.h)

find_package(OPENCL)

if (${OpenCL_FOUND})

add_library(
    softgl_rast_opencl
    SHARED
    ${C_FILES} ${H_FILES})

target_include_directories(
    softgl_rast_opencl
    PUBLIC
    ${OpenCL_INCLUDE_DIRS})

target_link_libraries(
    softgl_rast_opencl
    ${OpenCL_LIBRARIES})

else()
    
endif()
