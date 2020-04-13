file(GLOB C_FILES *.cpp kernels/*.cpp)
file(GLOB H_FILES *.h)

add_library(
    softgl_rast_reference
    SHARED
    ${C_FILES} ${H_FILES})
