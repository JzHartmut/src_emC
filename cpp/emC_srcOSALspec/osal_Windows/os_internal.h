#ifndef HGUARD_os_internal
#define HGUARD_os_internal
//tag::start[]
#include <applstdef_emC.h>

#undef BOOL
#undef PBOOL
#undef boolean
#undef INT32
#undef UINT32
#undef int64
//#undef uint64

#include <wtypes.h>
#include <Winbase.h>


/**Informations about the current thread, more as an simple id. */
//struct OS_ThreadContext_t* getCurrent_OS_ThreadContext();
//end::start[]




#endif //HGUARD_os_internal
