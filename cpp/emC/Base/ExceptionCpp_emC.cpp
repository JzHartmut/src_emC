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
* @content Definition of throw routines only for C++ usage
*
* @author Hartmut Schorrig
* @version 2.0
* 2020-05-16: Hartmut creation 
*
************************************************************************************************/
#include <applstdef_emC.h>

#ifdef DEF_Exception_TRYCpp
  //Compile the next source as C++ though C-Compilation is used for C-files.
  #define DEF_ExceptionCpp_INCLUDED
  #include <emC/Base/Exception_emC.c>

#else
  //left emtpty, because Exception_emC.c is compiled immediately.
#endif

