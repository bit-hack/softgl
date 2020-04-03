file(GLOB C_FILES *.cpp)
file(GLOB H_FILES *.h)

add_library(
    softgl_rast_fasterizer
    SHARED
    ${C_FILES} ${H_FILES})
