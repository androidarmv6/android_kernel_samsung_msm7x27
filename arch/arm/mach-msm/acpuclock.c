#if defined(CONFIG_MACH_COOPER)
#include "acpuclock_cooper.c"
#elif defined(CONFIG_MACH_GIO)
#include "acpuclock_cooper.c"
#else
#include "acpuclock_all.c"
#endif
