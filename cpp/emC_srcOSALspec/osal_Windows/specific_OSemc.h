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
  /**Supports a timeout: If a timeout is necessary, an independent time order thread
   * should call DeleteCriticalSection and increment this value.
   * Note: Do not use a boolean variable, its size if not clarified. 
   */
  struct TimeOrder_emC_T* timeoutOrder;
//  int32 aborted_timeout;
} Mutex_OSemC_s;
//end::Mutex[]




#endif //HGUARD_specific_OSemC