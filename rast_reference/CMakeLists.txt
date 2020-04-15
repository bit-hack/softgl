file(GLOB KERNELS kernels/*.cpp)
add_library(
    softgl_rast_reference_kernels
    ${KERNELS})

file(GLOB C_FILES *.cpp)
file(GLOB H_FILES *.h)
add_library(
    softgl_rast_reference
    SHARED
    ${C_FILES} ${H_FILES})

target_link_libraries(
    softgl_rast_reference
    softgl_rast_reference_kernels)
