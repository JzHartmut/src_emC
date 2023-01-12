#ifndef HGUARD_specific_OSemC
#define HGUARD_specific_OSemC

//tag::Mutex[]
typedef struct Mutex_OSemC_T {
  /**The name is only interesting for debug. */
  char const* name;

  /**The system use usually a handle. It is 32 or 64 bit (on 64-bit-Windows-Version).
   * In the Win environment a HANDLE is defined as void*, this is standard C and also used here.
   * The name need be osHandleMutex for compatibility.
   */
  void* osHandleMutex;

  struct Thread_OSemC_T* lockingThread;

  int32 ctLock;
} Mutex_OSemC_s;
//end::Mutex[]




#endif //HGUARD_specific_OSemC