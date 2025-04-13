#define DEBUG_PK
#ifdef DEBUG_PK
#include "SEGGER_RTT.h"
#define DEBUG_PRINTF(...) SEGGER_RTT_printf(0, __VA_ARGS__)
#else // DEBUG_PK
#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#endif // DEBUG_PK
