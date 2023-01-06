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
 * @content
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 *
 * @version 0.83
 * @content: All declarations to use from user level to work with simple References
 *           and simple allocation. 
 * for References of ObjectJc and derivated classes for C-language.
 * The references are used for garbage collection and virtual methods in C.
 *
 * @author Hartmut Schorrig www.vishia.org
 *
 ****************************************************************************/
#ifndef __ObjectRefJc__h
#define __ObjectRefJc__h

/**NOTE: This file is also included in ObjectJc.h, but in this case the __ObjectJc__ is set.
 */
#ifndef HEADERGUARD_ObjectJc_h
  #include "ObjectJc.h"
#endif

/**Usage of the BlockHeap management or not and define the size of a block.
 * The size of a normal block in all BlockHeaps are the same. The size must be (!) a power of 2.
 */
#undef USE_BlockHeap_emC
#undef SIZEBLOCK_BlockHeap_emC
//#undef SIZEBLOCK_BlockHeap_emC

//#define NO_DYNAMICALLY_MEMORY

/**unused...TODO*/
//#define SMALL_DYNAMICALLY_MEMORY
//#define USE_DYNAMICALLY_MEMORY



/*@CLASS_C ObjectJcREF @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



#endif //__ObjectRefJc__h
