#include "../kernel.h"

#define DEPTH_TEST  1
#define DEPTH_WRITE 1
#define COLOR_WRITE 1
#define DEPTH_CMP   _mm_cmple_ps
#define SRC_BLEND   GL_ONE
#define DST_BLEND   GL_ONE
#define KERNEL_NAME rast_tex_one_one

#if USE_APROX_TEMPLATE
#include "template_aprox.h"
#else
#include "template.h"
#endif
