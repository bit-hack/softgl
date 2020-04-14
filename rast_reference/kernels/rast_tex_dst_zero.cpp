#include "../kernel.h"

#define DEPTH_CMP   _mm_cmple_ps
#define SRC_BLEND   GL_DST_COLOR
#define DST_BLEND   GL_ZERO
#define KERNEL_NAME rast_tex_dst_zero

#include "template.h"
