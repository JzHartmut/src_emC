#ifndef HGUARD_emC_Base__Atomic_emC
#define HGUARD_emC_Base__Atomic_emC
#include <applstdef_emC.h>

#ifndef DEF_compareAndSwap_Atomic  //maybe already defined as macro or inline in HAL adaption or OSAL

/**Set a reference with update if it contains the expect value, returns the up to now current value.
 * The operation is performed if return == expect. 
 * @param reference the reference to set
 * @param expect the exepected value there
 * @parem update the value to update, only if expect is given on the reference
 * @return the value what is found before update. It is the expect if update was done. 
 */
extern_C void* compareAndSwap_AtomicRef(void* volatile* reference, void* expect, void* update);

/**Set an integer with update if it contains the expect value, returns the up to now current value.
 * The operation is performed if return == expect.
 * Note: The width of an integer depends on the capability of the CPU. If int as data type is used,
 * it means the optimized bit width for the platform, at least 16.
 * Usage of the int type is recommended (instead determined bit width)
 * if memory space is not expensive but the atomic access should be optimized in access time.
 * Compare comments to compareAndSwap_AtomicInt16(...).
 */
extern_C int compareAndSwap_AtomicInt(int volatile* reference, int expect, int update);

/**Set an int16 with update if it contains the expect value, returns the up to now current value.
 * The operation is performed if return == expect.
 * Note: If the CPU does only allow a 32 bit access, this operation checks also the unvulnerability of the other bits.
 * It means it is not optimized in any case. Use an int variable instead.
 * Compare comments to compareAndSwap_AtomicInt16(...).
 */
extern_C int16 compareAndSwap_AtomicInt16(int16 volatile* reference, int16 expect, int16 update);

/**Set an int32 with update if it contains the expect value, returns the up to now current value.
 * The operation is performed if return == expect.
 */
extern_C int32 compareAndSwap_AtomicInt32(int32 volatile* reference, int32 expect, int32 update);

/**Set an int32 with update if it contains the expect value, returns the current value.
 * The operation is performened if current == expect.
 */
extern_C int64 compareAndSwap_AtomicInt64(int64 volatile* reference, int64 expect, int64 update);





#endif //DEF_compareAndSwap_Atomic 


/**Simple and a value to a given variable. */
static inline void andInt_Atomic_emC(int volatile* addr, int val) {
  int ctAbort = 1000;
  int valueLast = *addr;
  int valueExpect;
  do {
    valueExpect = valueLast;
    int valueNew = valueLast & val;
    valueLast = compareAndSwap_AtomicInt(addr, valueExpect, valueNew);
  } while( valueLast != valueExpect && --ctAbort >=0); 
  ASSERT_emC(ctAbort >=0, "addInt_Atomic_emC faulty", (int)(intPTR)addr, val);
} 


/**Simple add a value to a given variable. */
static inline void addInt_Atomic_emC(int volatile* addr, int val) {
  int ctAbort = 1000;
  int valueLast = *addr;
  int valueExpect;
  do {
    valueExpect = valueLast;
    int valueNew = valueLast + val;
    valueLast = compareAndSwap_AtomicInt(addr, valueExpect, valueNew);
  } while( valueLast != valueExpect && --ctAbort >=0); 
  ASSERT_emC(ctAbort >=0, "addInt_Atomic_emC faulty", (int)(intPTR)addr, val);
} 


/**Simple add a value to a given variable. */
static inline void addInt16_Atomic_emC(int16 volatile* addr, int16 val) {
  int ctAbort = 1000;
  int16 valueLast = *addr;
  int16 valueExpect;
  do {
    valueExpect = valueLast;
    int valueNew = valueLast + val;
    valueLast = compareAndSwap_AtomicInt16(addr, valueExpect, valueNew);
  } while( valueLast != valueExpect && --ctAbort >=0); 
  ASSERT_emC(ctAbort >=0, "addInt16_Atomic_emC faulty", (int)(intPTR)addr, val);
} 


#endif //HGUARD_emC_Base__Atomic_emC
