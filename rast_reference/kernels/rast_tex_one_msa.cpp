#include "../kernel.h"

#define DEPTH_TEST  1
#define DEPTH_WRITE 1
#define COLOR_WRITE 1
#define DEPTH_CMP   _mm_cmple_ps
#define SRC_BLEND   GL_ONE
#define DST_BLEND   GL_ONE_MINUS_SRC_ALPHA
#define KERNEL_NAME rast_tex_one_msa

#include "template.h"
