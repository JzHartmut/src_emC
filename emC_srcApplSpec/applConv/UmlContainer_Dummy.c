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
 * list of changes:
 * 2007-03-01: JcHartmut www.vishia.org creation
 *
 ****************************************************************************/
/**This file supplies dummy implementations to access to special container associations of an UML tool
 * using reflection.
 */

#include "emC/Jc/ReflectionJc.h"




METHOD_C MemSegmJc getRefAddrUML_LinkedList_FieldJc(MemSegmJc container, char const* sVaargs, va_list vaargs, ThCxt* _thCxt)
{
  int idx = -1;
  if(idx < 0) return null_MemSegmJc;  //no quest to container content
  else
  { return null_MemSegmJc;
  }
}


METHOD_C MemSegmJc getRefAddrUML_ArrayList_FieldJc(MemSegmJc container, char const* sVaargs, va_list vaargs, ThCxt* _thCxt)
{
  int idx = -1;
  if(idx < 0) return null_MemSegmJc;  //no quest to container content
  else
  { return null_MemSegmJc;
  }
}


METHOD_C MemSegmJc getRefAddrUML_Map_FieldJc(MemSegmJc container, char const* sVaargs, va_list vaargs, ThCxt* _thCxt)
{
  int idx = -1;
  if(idx < 0) return null_MemSegmJc;  //no quest to container content
  else
  { return null_MemSegmJc;
  }
}



METHOD_C int getArraylengthUML_LinkedList_FieldJc(MemSegmJc address)
{
  return 0;
}


METHOD_C int getArraylengthUML_ArrayList_FieldJc(MemSegmJc address)
{
  return 0;
}


METHOD_C int getArraylengthUML_Map_FieldJc(MemSegmJc address)
{
  return 0;
}

