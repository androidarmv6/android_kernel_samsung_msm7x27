#if defined(CONFIG_MACH_CALLISTO)
#include "board-callisto.c"
#elif defined(CONFIG_MACH_EUROPA)
#include "board-europa.c"
#elif defined(CONFIG_MACH_COOPER)
#include "board-cooper.c"
#elif defined(CONFIG_MACH_BENI)
#include "board-beni.c"
#elif defined(CONFIG_MACH_TASS)
#include "board-tass.c"
#elif defined(CONFIG_MACH_TASSDT)
#include "board-tassdt.c"
#elif defined(CONFIG_MACH_LUCAS)
#include "board-lucas.c"
#elif defined(CONFIG_MACH_GIO)
#include "board-gio.c"
#else
#include "board-msm7x27_org.c"
#endif
