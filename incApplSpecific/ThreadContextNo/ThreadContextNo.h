#define ADDR_IN_STACK_ThreadContextFw(ptr) false


typedef struct StacktraceThreadContext_t
{
  uint32 zEntries; //nrofEntriesStacktraceBuffer;
  
} StacktraceThreadContext_s;



typedef struct ThreadContextFW_t
{
  /**It is the heap, where block heap allocations are provided in this thread. */
  struct BlockHeapJc_t* blockHeap;
  StacktraceThreadContext_s stacktrc;

} ThreadContextFW;

METHOD_C MemC getUserBuffer_ThreadContextFw(int size, char const* sign, struct ThreadContextFW_t* _thCxt);
INLINE_Fwc bool releaseUserBuffer_ThreadContextFw(void const* data, struct ThreadContextFW_t* _thCxt){ return true; }
METHOD_C void reduceLastUserBuffer_ThreadContextFw(void* ptr, int size, struct ThreadContextFW_t* _thCxt);
METHOD_C char const* getCallingMethodName_StacktraceThreadContext(struct StacktraceThreadContext_t* ythis, int level);

