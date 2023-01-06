#ifndef HGUARD_emC_Base__RingBuffer_emC
#define HGUARD_emC_Base__RingBuffer_emC
#include <applstdef_emC.h>
#include <emC/Base/Atomic_emC.h> //implementations for lockfree mutex

//#define bitsInt  (sizeof(int) * BYTE_IN_MemUnit * 8) //a const compiler calculated.


//left empty only set in a test routine. 
#ifndef TEST_INTR1_RingBuffer_emC
#define TEST_INTR1_RingBuffer_emC
#define TEST_INTR2_RingBuffer_emC
#define TEST_INTR3_RingBuffer_emC
#endif


/**A universal index management for a ring buffer (circular buffer) to store any data.
 * The buffer itself with any specific type for the entries is located outside, extra, not here.
 * This class manages only the indices for reading and writing, currently from 0 till the max value, 
 * as the index to access the array for the data used as ring buffer information.
 * <br>
 * This management functionality can be used either for exactly one writing source, using addSingle_RingBuffer_emC(...)
 * or from more as one thread or interrupt which writes data, using add_RingBuffer_emC(...).
 * This last operation works with atomic compare and swap, also applicable for simple controller, 
 * see www.vishia/emc/html/Base/Intr_vsRTOS.html
 * With this second variant it is possible for example for an message queue for event processing
 * to write events in different interrupts as also in the back loop, or of course using a RTOS with multi threading. 
 * <br>
 * But the reading source should be only one thread. This is typically for a message queue which can be written 
 * from different sources but processed from only one thread. It is also typically for and data processing,
 * if the data comes from several sources (several interrupts or threads) and should be processed even
 * in exactly one thread or in the back loop for an interrupt using system without RTOS.    
 * <br>
 * The following property is recommended: An active entry in the array for the RingBuffer data 
 * should be marked as "valid" or not "valid". This is necessary because for multi threading for writing. 
 * Only with this rule atomic compare and swap can be used because it needs one operation to set.
 * It is also more simple for a single writing thread or interrupt.
 * Elsewhere a second index for 'available data' will be necessary.
 * <br>
 * The writing thread gets the next free entry, and immediately this entry is marked as used 
 * in this ringbuffer structure because the writing index is incremented. 
 * That is important because the next access can get immediately the next writing position.
 *
 * Now, on read access, the location is marked as "written" from the view point of this index management structure. 
 * But the data may not be written till now if the read access is executed immediately.
 * In a system: Writing in interrupt, process in the back loop, of course the writing may be done 
 * completely in the interrupt before finish the interrupt and switch to the back loop. Then it is not a problem.
 * But if multiple threads access and the read access may be higher prior, or the writing needs more time,
 * for example more as one interrupt cycle, then this problem is present.
 * That's why firstly the data for the entry should be written in its intrinsic timing. 
 * The last action of writing should be: declare the data as valid. 
 *
 * Then a read access get the index, to read, but detect, there are not valid data. 
 * This is to do in the using algorithm, for example even in the message queue functionality. 
 * Then the read access should try get data later.
 * That's why getting the read index is divided in two operations:
 *
 * * next_RingBuffer_emC(...) to get the next read index.
 * * ... test the location whether the data are valid
 * * ... set the processed data as 'invalid' for a next usage.
 * * quitNext_RingBuffer_emC(...) to advertise that the postion was used, only if data were valid. 
 *
 * In that manner the next call of next_RingBuffer_emC(...) returns the same position again 
 * to test for valid data if quitNext_RingBuffer_emC(...) was not invoked. 
 * <br>
 * The simplest possibility to mark invalid is a null pointer in the ring buffer (pointer) array. 
 * If the ring buffer array is a array of embedded struct members, then the validy should be marked 
 * in a special kind clarified by usage. 
 */  //tag::RingBuffer_emC[]
typedef struct RingBuffer_emC_T {

  union{ObjectJc obj; } base;

  /**Number of entries in the Ringbuffer struct, range of the index 0 till nrofEntries -1. 
   * Note: The size of the queue is limited to 65535 entries because of int16 usage, seems to be really enough.
   */
  uint16 nrofEntries;

  /**A counter to detect access. Incremented on any change. 
   * Also int16 because of a proper memory layout for alignment see www.vishia/emc/html/Base/int_pack_endian.html
   */ 
  int16 volatile ctModify;

  /**Index to read from queue.array[thiz->ixRd].
   * ** If ixRd==ixWr, then the queue is empty.
   * ** If queue.array[thiz->ixRd].evIdent ==0 (invalid), a write is pending on this position
   *    and the queue is empty yet at the moment.
   * ** If ixRd!=ixWr and queue.array[thiz->ixRd].evIdent !=0, it is the current entry.
   * ** ixRd can be increment without lock. 
   * But use the access operations next_RingBuffer_emC(...) and quitNext_RingBuffer_emC(...)  
   */
  int volatile ixRd;  //use signed because difference building.

  /**Index of the next write position.
   * ** if (ixWr+1) modulo sizeQueue == ixRd, then the queue is full. Add will be prevented.
   * **+ It conclusion, the last position in queue.array[..] will never be used, a really little disadvantage of this simple rule. 
   * ** ixWr is firstly incremented with atomicAccess to get a reservation for this position in ixWrCurr
   * ** after them the position should be filled and then marked as valid.
   * Note that the int data type for the indices is the platform-intrinsic type of memory access,
   * Usual better for compareAndSwap. The really used range is usual less, int16 may be sufficient. 
   */
  int volatile ixWr; //+rd and wr-pointer

  /**Only for debug, statistic runtime analyse, max repeat count of compareAndSwap loop. */
  int repeatCtMax;

} RingBuffer_emC_s;
//end::RingBuffer_emC[]


#define ID_refl_RingBuffer_emC 0x0fe4
#ifndef DEF_REFLECTION_NO 
  extern_C ClassJc const refl_RingBuffer_emC;
#endif


#define INIZ_RingBuffer_emC(OBJ, REFL, ID, NROFentries) { { INIZ_ObjectJc(OBJ, REFL, ID) }, NROFentries }


/**Constructs, it allocates memory for the entries.
 * @param nrofEntries size of the buffer, maximal number of entries able to store.
 * @param sizeEntry number of memory words for one entry. It is sizeof(void*) if pointer are stored.
 */
extern_C RingBuffer_emC_s* ctor_RingBuffer_emC ( ObjectJc* othiz, int nrofEntries );



/**A routine to view the status. It is especially for Modelling to see what's happen and to have a step routine.
 * @simulink Object-FB, no-thizStep.
 */
extern_C void status_RingBuffer_emC(RingBuffer_emC_s* thiz, int16* nrofEntries_y, int* ctModify_y);

extern_C int16 info_RingBuffer_emC(RingBuffer_emC_s* thiz, int16* ctEvents_y);

//tag::addSingle_RingBuffer_emC
/**Adds an entry to the ring buffer as only one (single) thread or interrupt.
 * It returns the current ixWr if a new ixWr position is possible.
 * A new ixWr position is possible if the new ixWr position does not touch the ixRd position. 
 * It means the buffer cannot be filled with its whole capacity, on element remains empty. 
 *
 * @return -1 if no more space in queue. pointer to the free entry on success.
 *     else return the index to write in the application definied ring buffer array.
 */
static inline int addSingle_RingBuffer_emC ( RingBuffer_emC_s* thiz ) {
  #ifndef NO_PARSE_ZbnfCheader
  int ixWrLast = thiz->ixWr;
  int ixWrNext = ixWrLast + 1;
  if(ixWrNext >= thiz->nrofEntries) { ixWrNext =0; } //modulo
  if(ixWrNext != thiz->ixRd) {
    thiz->ixWr = ixWrNext;  //is valid
    return ixWrLast;        //current write position.
  }
  else {
    return -1;  //no space to write
  }
  #endif//NO_PARSE_ZbnfCheader
}
//end::addSingle_RingBuffer_emC



//tag::add_RingBuffer_emC[]
/**Adds an entry to the ring buffer with atomic lockfree mutex.
 * This operation can be invoked from any thread or interrupt.
 * It works with atomic cmpAndSwap to access.
 * It returns the current ixWr if a new ixWr position is possible
 * but has set the new ixWr position for a next add access in another thread.
 *
 * @return the index to write in the application definied ring buffer array.
 *    or -1 if no more space is in the queue. 
 *    This is if the new ixWr position would touch the ixRd position 
 */
static inline int add_RingBuffer_emC ( RingBuffer_emC_s* thiz ) {
  #ifndef NO_PARSE_ZbnfCheader
  #ifdef DISABLE_INTR_POSSIBLE_emC
    disable_interrupt_emC();
    int ixWr = addSingle_RingBuffer_emC(thiz);
    enable_interrupt_emC();
    return ixWr;
  #else
  int repeatCt = 0;
  int volatile* ptr = &thiz->ixWr; //address of the ixWr
  int ixWrLast = thiz->ixWr;       //The position where the event should be written to the queue.
  int ixWrExpect;                  //to compare
  do {
    ixWrExpect = ixWrLast;
    int ixWrNext = ixWrLast + 1;
    if(ixWrNext >= thiz->nrofEntries) { ixWrNext =0; } //modulo
    if(ixWrNext == thiz->ixRd) { 
      return -1;                   //RETURN: no more space in queue
    }
    TEST_INTR1_RingBuffer_emC      //This macro is normally empty, only used for specific test to interrupt the access.
    ixWrLast = compareAndSwap_AtomicInt(ptr, ixWrExpect, ixWrNext); //set for next access.
  } while( ixWrLast != ixWrExpect && ++repeatCt < 1000); //repeat if another thread has changed thiz->ixWr.
  if(repeatCt >=1000) {
    //it is a problem of thread workload, compareAndSet does not work.
    THROW_s0n(IllegalStateException, "thread compareAndSwap problem", 0, 0);
    return -1; //RETURN for non-exception handling, THROW writes a log entry only.
  }
  if(thiz->repeatCtMax < repeatCt) { thiz->repeatCtMax = repeatCt; }
  #endif
  //the ixWrCurr is proper for this entry, another thread may incr thiz->ixWr meanwhile
  //but the other thread uses the position after.
  return ixWrLast;
  #endif//NO_PARSE_ZbnfCheader
}
//end::add_RingBuffer_emC[]






/**Returns the pointer to the current read entry or null if the queue is empty.
 * After evaluation of the referenced content the operation 
 * [[quitNext_RingBuffer_emC(...)]] has to be invoked to increment the read
 * position respectively to free the entry for writing on end of the queue.
 * @return null if buffer is empty, or the pointer to the current entry. 
 *         If the content on read position is 0, the position is not written yet,
 *         it means the buffer should be designated as empty.
 *         The getNext(...) should be repeated then, quitNext should not be called.
 */
static inline int next_RingBuffer_emC ( RingBuffer_emC_s* thiz) {
  if(thiz->ixRd == thiz->ixWr) {
    return -1;
  }
  else {
    return thiz->ixRd;  //0 in content is a not ready written entry.
  }
} 




static inline void quitNext_RingBuffer_emC ( RingBuffer_emC_s* thiz, int ixRd) {
  ASSERT_emC(thiz->ixRd != thiz->ixWr, "faulty quit", thiz->ixRd, thiz->ixWr);

  int32 ixRdNext = ixRd +1;
  if(ixRdNext >= thiz->nrofEntries){ ixRdNext = 0; } //wrapping
  thiz->ixRd = ixRdNext;
}


/**A routine to view the status. It is especially for Modelling to see what's happen and to have a step routine.
 * @simulink Object-FB, no-thizStep.
 */
extern_C void status_RingBuffer_emC(RingBuffer_emC_s* thiz, int16* nrofEntries_y, int* ctModify_y);




#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class RingBuffer_emC: private RingBuffer_emC_s {
  
  public: RingBuffer_emC(int nrofEntries, int id) {
    CTOR_ObjectJc(&this->base.obj, this, sizeof(*this), refl_RingBuffer_emC, id);
    ctor_RingBuffer_emC(&this->base.obj, nrofEntries);
  }

  protected: RingBuffer_emC(ObjectJc* othiz, int size) {
  }

  public: int addSingle() { return addSingle_RingBuffer_emC(this); }
  
  public: int add() { return add_RingBuffer_emC(this); }

  public: int next() { return next_RingBuffer_emC(this); }

  public: void quitNext(int ixRd) { quitNext_RingBuffer_emC(this, ixRd); }

};
#endif //DEF_cplusplus_emC  

#endif //HGUARD_emC_Base__RingBuffer_emC
