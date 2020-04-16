file(GLOB KERNELS
    kernels/*.cpp
    kernels/*.h)
add_library(
    softgl_rast_reference_kernels
    ${KERNELS})

file(GLOB SOURCE *.cpp *.h)
add_library(
    softgl_rast_reference
    SHARED
    ${SOURCE})

target_link_libraries(
    softgl_rast_reference
    softgl_rast_reference_kernels)

target_compile_definitions(
    softgl_rast_reference_kernels
    PUBLIC
    -DUSE_APROX_TEMPLATE)
