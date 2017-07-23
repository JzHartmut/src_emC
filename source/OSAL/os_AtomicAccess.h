/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this source the LGPL Lesser General Public License,
 * published by the Free Software Foundation is valid.
 * It means:
 * 1) You can use this source without any restriction for any desired purpose.
 * 2) You can redistribute copies of this source to everybody.
 * 3) Every user of this source, also the user of redistribute copies
 *    with or without payment, must accept this license for further using.
 * 4) But the LPGL ist not appropriate for a whole software product,
 *    if this source is only a part of them. It means, the user
 *    must publish this part of source,
 *    but don't need to publish the whole source of the own product.
 * 5) You can study and modify (improve) this source
 *    for own using or for redistribution, but you have to license the
 *    modified sources likewise under this LGPL Lesser General Public License.
 *    You mustn't delete this Copyright/Copyleft inscription in this source file.
 *
 * This source may be used also with another licence, if the author 
 * and all other here named co-authors have agreed to this contract.
 * Especially a company can use a copy of this sources in its products without publishing.
 * The user should have a underwritten contract therefore.
 *
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content Definition of atomic access routines. 
 * This routines are implemented at machine code level instruction appropriated to the CPU. 
 *
 * @author Hartmut Schorrig
 * @version sf-0.83
 * list of changes:
 * 2008-02-01: Hartmut creation 
 *
 ************************************************************************************************/
#ifndef __os_AtomicAccess_h__
#define __os_AtomicAccess_h__
#include <applstdefJc.h>
/*@CLASS_C AtomicReference @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

//#define AtomicReference struct AtomicReference_t*

//#define CONST_AtomicReference(VAL) { (struct AtomicReference_t*)&(VAL) }

//#define ATOMICREFERENCE ATOMICREFERENCE
#define ATOMICREFERENCE void* volatile*


#if defined(__CPLUSGEN) && defined(__cplusplus)

  #define CAST_AtomicReference(VARIABLE) ((ATOMICREFERENCE)(&(VARIABLE)))
#else
  //C: the cast to void* is accepted.
  #define CAST_AtomicReference(VARIABLE) ((ATOMICREFERENCE)(&(VARIABLE)))
#endif
/**Atomically sets the value to the given updated value if the current value == the expected value.
 * @param expect the expected value
 * @param update - the new value
 * @return true if successful. False return indicates that the actual value was not equal to the expected value.
 */
METHOD_C bool compareAndSet_AtomicReference(ATOMICREFERENCE reference, void* expect, void* update);



METHOD_C void* compareAndSwap_AtomicReference(ATOMICREFERENCE reference, void* expect, void* update);
//#define compareAndSet_AtomicReference(REF, EXPECT, UPDATE) compareAndSet_AtomicInteger((int32*)(REF), (int)(EXPECT), (int)(UPDATE))


/*@CLASS_C AtomicInteger @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Atomically sets the value to the given updated value if the current value == the expected value.
 * @param expect the expected value
 * @param update - the new value
 * @return the old value if or not successfull. False return indicates that the actual value was not equal to the expected value.
 */
METHOD_C bool compareAndSet_AtomicInteger(int32 volatile* reference, int32 expect, int32 update);

/**The compareAndSwap is nearer on the machine instruction. */
METHOD_C int32 compareAndSwap_AtomicInteger(int32 volatile* reference, int32 expect, int32 update);

/**The compareAndSwap is nearer on the machine instruction. */
METHOD_C int64 compareAndSwap_AtomicInteger64(int64 volatile* reference, int64 expect, int64 update);

/**Regard a special platform variant, which may define macros instead prototypes: */
#ifdef PLATFORM_os_AtomicAccess_h
#include "PLATFORM_os_AtomicAccess.h"
#endif


#endif //__os_AtomicAccess_h__
