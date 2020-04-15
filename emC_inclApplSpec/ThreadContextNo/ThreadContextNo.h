#define ADDR_IN_STACK_ThreadContext_emC(ptr) false


typedef struct StacktraceThreadContext_emC_t
{
  uint32 zEntries; //nrofEntriesStacktraceBuffer;
  
} StacktraceThreadContext_emC_s;



typedef struct ThreadContext_emC_t
{
  /**It is the heap, where block heap allocations are provided in this thread. */
  struct BlockHeap_emC_T* blockHeap;
  StacktraceThreadContext_emC_s stacktrc;

} ThreadContext_emC;

METHOD_C MemC getUserBuffer_ThreadContext_emC(int size, char const* sign, struct ThreadContext_emC_t* _thCxt);
INLINE_emC bool releaseUserBuffer_ThreadContext_emC(void const* data, struct ThreadContext_emC_t* _thCxt){ return true; }
METHOD_C void reduceLastUserBuffer_ThreadContext_emC(void* ptr, int size, struct ThreadContext_emC_t* _thCxt);
METHOD_C char const* getCallingMethodName_StacktraceThreadContext_emC(struct StacktraceThreadContext_emC_t* ythis, int level);

