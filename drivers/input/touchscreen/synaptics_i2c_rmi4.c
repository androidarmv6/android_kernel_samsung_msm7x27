#if defined(CONFIG_MACH_COOPER)
#include "synaptics_i2c_rmi4_cooper.c"
#elif defined(CONFIG_MACH_BENI)
#include "synaptics_i2c_rmi4_beni.c"
#elif defined(CONFIG_MACH_TASS)
#include "synaptics_i2c_rmi4_tass.c"
#elif defined(CONFIG_MACH_TASSDT)
#include "synaptics_i2c_rmi4_tassdt.c"
#elif defined(CONFIG_MACH_LUCAS)
#include "synaptics_i2c_rmi4_lucas.c"
#elif defined(CONFIG_MACH_GIO)
#include "synaptics_i2c_rmi4_gio.c"
#else
#endif
