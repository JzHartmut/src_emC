#ifndef HGUARD_specific_OSemC
#define HGUARD_specific_OSemC

struct Thread_OSemC_T;

//tag::Mutex[]
typedef struct Mutex_OSemC_T{
  /**The system use usually a handle. It is 32 or 64 bit (on 64-bit-Windows-Version).
   * In the Win environment a HANDLE is defined as void*, this is standard C and also used here.
   * The name need be osHandleMutex for compatibility.
   */
  void* osHandleMutex;
  void* attr;
  const char* name;
  /**null then the mutex is not locked. Else: handle of the locking thread. */
  struct Thread_OSemC_T const* lockingThread;
  /**Number of lock calls of the mutex in the SAME thread. Reentrant lock should be supported. */
  int ctLock;
}Mutex_OSemC_s;
//end::Mutex[]




#endif //HGUARD_specific_OSemC
