#ifndef HGUARD_specific_OSemC
#define HGUARD_specific_OSemC

struct Thread_OSemC_T;

//tag::Mutex[]
typedef struct Mutex_OSemC_T{
  const char* name;
  /**This refers OS-internal data for MUTEX allocated on createMutex and removed on deleteMutex_OSemC.
   * The internal type for pthread usage is defined in os_internals.h,
   * included only in the implementation file (os_mutex.h)
   * because OS-specific files should not be part of the user sources.
   */
  void* osHandleMutex;
  void* attr;

  /**null then the mutex is not locked. Else: handle of the locking thread. */
  struct Thread_OSemC_T const* lockingThread;

  /**Number of lock calls of the mutex in the SAME thread. Reentrant lock should be supported. */
  int32 ctLock;

  /**Time of the last access.*/
  int32 millisecLock;
} Mutex_OSemC_s;
//end::Mutex[]




#endif //HGUARD_specific_OSemC
