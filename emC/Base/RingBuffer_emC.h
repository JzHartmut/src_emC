#ifndef HGUARD_emC_Base__RingBuffer_emC
#define HGUARD_emC_Base__RingBuffer_emC
#include <emC/Base/Object_emC.h>
#include <emC/Base/Atomic_emC.h> //implementations for lockfree mutex

//#define bitsInt  (sizeof(int) * BYTE_IN_MemUnit * 8) //a const compiler calculated.


//left empty only set in a test routine. 
#ifndef TEST_INTR1_RingBuffer_emC
#define TEST_INTR1_RingBuffer_emC
#define TEST_INTR2_RingBuffer_emC
#define TEST_INTR3_RingBuffer_emC
#endif



/**A universal ring buffer (circular buffer) to store any data.
 * Important property: An active entry of the RingBuffer must not have 0 in the first 32 bit. 
 * An entry with 0 is designated as free. If an entry consist of a pointer, a null pointer is not admissible.
 *
 */
typedef struct RingBuffer_emC_T {

  union { ObjectJc obj; } base;

  uint16 nrofEntries;

  int volatile ctModify;
  


  /**Index to read from queue.a[thiz->ixRd].
   * ** If ixRd==ixWr, then the queue is empty.
   * ** If queue.a[thiz->ixRd].evIdent ==0 a write is pending on this position, the queue is empty yet at the moment.
   * ** If ixRd!=ixWr and queue.a[thiz->ixRd].evIdent !=0, it is the current entry.
   * ** ixRd can be increment without lock.
   */
  int volatile ixRd;  //use signed because difference building.

  /**Index of the next write position.
   * ** if (ixWr+1) modulo sizeQueue == ixRd, then the queue is full. Add will be prevented.
   * **+ It means the last position in queue.a[..] will be never used. 
   * ** ixWr is firstly incremented with atomicAccess to get a reservation for this position in ixWrCurr
   * ** after them the position is filled, but queue.a[ixWrCurrent].evIdent = x is set at last to confirm the completion.
   * ** The width is int32 for 32-bit-Systems and 16 for 16-bit-Systems to use atomic access to memory.
   */
  int volatile ixWr; //+rd and wr-pointer

  /**Only for debug, statistic runtime analyse, max repeat count of compareAndSwap loop. */
  int repeatCtMax;

} RingBuffer_emC_s;


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




/**Adds an entry to the ring buffer with atomic lockfree mutex.
 * This operation can be invoked from any thread or interrupt.
 * It works with atomic cmpAndSwap to access.
 * It returns the current ixWr if a new ixWr position is possible.
 * A new ixWr position is possible if the new ixWr position does not touch the ixRd position. 
 * It means the buffer cannot be filled with its whole capacity, on element remains empty. 
 * The incremenation of ixWr for the new position os only done 
 * if the position before is not change by a concurrent call of this routine. 
 * This is assured by the cmpAndSwap mechanism. 
 * The access to get the last position and write the next position is repeated
 * till it can be done successfully. It can be done successfully in any case
 * if another thread or interrupt does not interrupt this procedure.
 *
 * @return -1 if no more space in queue. pointer to the free entry on success.
 *     else return the index to write in the application definied ring buffer array.
 */
static inline int add_RingBuffer_emC ( RingBuffer_emC_s* thiz ) {
  #ifndef NO_PARSE_ZbnfCheader
  #ifdef DISABLE_INTR_POSSIBLE_emC
    disable_interrupt_emC();
    int ixWr = addSingle_RingBuffer_emC();
    enable_interrupt_emC();
    return ixWr;
  #else
  int repeatCt = 0;
  int volatile* ptr = &thiz->ixWr; //address of the ixWr
  int ixWrLast = thiz->ixWr; //The position where the event should be written to the queue.
  int ixWrExpect;  //to compare
  do {
    ixWrExpect = ixWrLast;
    int ixWrNext = ixWrLast + 1;
    if(ixWrNext >= thiz->nrofEntries) { ixWrNext =0; } //modulo
    if(ixWrNext == thiz->ixRd) { 
      return -1;    //RETURN: no more space in queue
    }
    TEST_INTR1_RingBuffer_emC
    ixWrLast = compareAndSwap_AtomicInt(ptr, ixWrExpect, ixWrNext); //set for next access.
  } while( ixWrLast != ixWrExpect && ++repeatCt < 100); //repeat if another thread has changed thiz->ixWr.
  if(repeatCt >=100) {
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




#if defined(USE_cplusplus_emC) && defined(__cplusplus)
class RingBuffer_emC: private RingBuffer_emC_s {
  
  public: RingBuffer_emC(int nrofEntries, int id) {
    CTOR_ObjectJc(&this->base.obj, this, sizeof(*this), refl_RingBuffer_emC, id);
    ctor_RingBuffer_emC(&this->base.obj, nrofEntries);
  }

  protected: RingBuffer_emC(ObjectJc* othiz, int size) {
  }

  public: int addSingle() { addSingle_RingBuffer_emC(this); }
  
  public: int add() { return add_RingBuffer_emC(this); }

  public: int next() { return next_RingBuffer_emC(this); }

  public: void quitNext(int ixRd) { quitNext_RingBuffer_emC(this, ixRd); }

};
#endif //USE_cplusplus_emC  

#endif //HGUARD_emC_Base__RingBuffer_emC
