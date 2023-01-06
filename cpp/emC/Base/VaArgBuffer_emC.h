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
 */
#ifndef __VaArgBuffer_h__
#define __VaArgBuffer_h__
#include <applstdef_emC.h>
//#include "emC/Base/LogMessage_emC.h" //only because Va_listFW, TODO
#include <emC/Base/MemC_emC.h>
#include <emC/Base/Va_list_emC.h>

/*@CLASS_C VaArgBuffer_Data_s @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**It is an own struct because exactly this .*/
typedef struct VaArgBuffer_Data_t
{
  int32 v[17]; 
}VaArgBuffer_Data_s;

/*@CLASS_C VaArgBuffer @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
typedef struct VaArgBuffer_t
{
  /**type string, '?' if the argument types are unknown here. 
   * Use the same type chars such in ...
   */
  char sType[16];
  VaArgBuffer_Data_s data;
  //TODO later:
  //union Data_VaArgBuffer{ int32 v[17]; char* c[4*17]; } data;
}VaArgBuffer;

METHOD_C VaArgBuffer* ctorM_VaArgBuffer(MemC mthis, int size, ThCxt* _thCxt);


/**Copies given arguments from stack in a VaArgBuffer. 
 * @param formatText the format text if the variable argument list doesn't contain type informations.
 * @param src variable argument list
 */
METHOD_C void copyFrom_VaArgBuffer(VaArgBuffer* ythis, char const* formatText, Va_listFW src, ThCxt* _thCxt);

METHOD_C void clean_VaArgBuffer(VaArgBuffer* ythis, ThCxt* _thCxt);

METHOD_C Va_listFW get_va_list_VaArgBuffer(VaArgBuffer* ythis, ThCxt* _thCxt);

METHOD_C void setArg_VaArgBuffer(VaArgBuffer* thiz, int32_t ix, int32_t val, ThCxt* _thCxt);


#endif //__VaArgBuffer_h__

