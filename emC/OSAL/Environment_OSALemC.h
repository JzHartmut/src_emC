#ifndef HGUARD_emC_OSAL__Environment_OSALemC
#define HGUARD_emC_OSAL__Environment_OSALemC
#include <compl_adaption.h>

extern_C char const* getEnvironment_OSALemC(char const* name);

/**Replaces $NAME in src with the value of this environment variable in dst.
 * This routine is not OS-specific, but it calls getEnvironment_OSALemC(...)
 * @param dst a buffer
 * @param zdst space in buffer. The buffer can be filled to its end with character, then a \0 is not appended.
 * @param src
 * @return number of written chars in dst. Note: A \0 is written, but not if return == zdst.
 */
extern_C int replace_Environment_OSALemC(char* dst, int zdst, char const* src);

#endif //HGUARD_emC_OSAL__Environment_OSALemC
