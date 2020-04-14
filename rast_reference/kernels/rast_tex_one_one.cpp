#include "../kernel.h"

#define DEPTH_CMP   _mm_cmple_ps
#define SRC_BLEND   GL_ONE
#define DST_BLEND   GL_ONE
#define KERNEL_NAME rast_tex_one_one

#include "template.h"
