#if defined(CONFIG_MACH_CALLISTO)
#include "lcdc_s6d16a0x_callisto.c"
#elif defined(CONFIG_MACH_BENI)
#include "lcdc_s6d04h0a_beni.c"
#elif defined(CONFIG_MACH_TASS)
#include "lcdc_s6d04h0a_tass.c"
#elif defined(CONFIG_MACH_LUCAS)
#include "lcdc_s6d05a0_lucas.c"
#elif defined(CONFIG_MACH_COOPER)
#include "lcdc_s6d16a0x_cooper.c"
#elif defined(CONFIG_MACH_GIO)
#include "lcdc_s6d16a0x_gio.c"
#elif defined(CONFIG_FB_MSM_LCDC_S6D04M0_QVGA)
#include "lcdc_s6d04m0.c"
#elif defined(CONFIG_FB_MSM_LCDC_S6D04D1_WQVGA)
#include "lcdc_s6d04d1.c"
#endif
