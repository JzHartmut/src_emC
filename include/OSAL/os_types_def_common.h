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
 * @content Definitions for basics, which maybe identical for all operation systems and compilers,
 * This file is include in <os_types_def.h>. Because that file is able to adjust in a project specific way,
 * the inclusion of this file can be changed. In that way the definitions in this file can be adapted.
 * Therefor it is not recommended to include this file directly in a users file. 
 *
 * @author Hartmut Schorrig
 */
#ifndef __os_types_def_common_h__


 //plattformunabhaengige Ergaenzungen
//folgende Typen sind besser schreib- und lesbar
#define ushort unsigned short int
#define uint unsigned int
#define ulong unsigned long int


 
 /**Macros for C-labeling in C++-compilation:
 * *extern_C replaces a simple 'extern' with 'extern "C"' for C++
 * *C_TYPE creates a 'extern "C"' in C++ but nothing in C, for example used for 'extern "C" typedef method()'
 * *METHOD_C is deprecated, used for METHOD prototype declaration. 
 * Both extern_C or C_TYPE can be used there because a 'extern' designation in C is optional there.
 * extern_C_BLOCK_ and _END_extern_C_BLOCK can be written at start and end of a header-block
 *
 * This macros can be set to the C-form in C++ too, then all labels are created in the C++-manner. 
 * Then all sources should be compiled with C++, use only C++-libraries. 
 */
#ifdef __cplusplus
  #define extern_C extern "C"
  #define C_TYPE extern "C"
  #define METHOD_C extern "C"
  #define extern_C_BLOCK_ extern "C" { 
  #define _END_extern_C_BLOCK } 
  //#define METHOD_C
#else
  #define extern_C extern
  #define C_TYPE
  #define METHOD_C
  #define extern_C_BLOCK_ 
  #define _END_extern_C_BLOCK 
#endif




/**An instance which contains null-values. */
extern_C OS_PtrValue null_OS_PtrValue;



#define __os_types_def_common_h__
#endif  // __os_types_def_common_h__
