#include "../kernel.h"

#define DEPTH_CMP   _mm_cmple_ps
#define SRC_BLEND   GL_SRC_ALPHA
#define DST_BLEND   GL_ONE_MINUS_SRC_ALPHA
#define KERNEL_NAME rast_tex_sa_msa

#include "template.h"
