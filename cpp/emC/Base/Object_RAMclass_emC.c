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
**copyright**************************************************************************************
*
* @content Routines which are necessary only if Reflection (ClassJc) are organized in the RAM, not as constants.
* For const reflection, the standard application, the INIZ-macros are given in Object_emC.h.
* This codes are only necessary in special cases. The operation declaration is in emC/Base/Object_emC.h
*
* @author Hartmut Schorrig www.vishia.org
* @version 0.82
* list of changes:
* 2018-10-12: Hartmut creation, 
*
****************************************************************************/
#include <emC/Base/Object_emC.h>
#include <emC/Base/String_emC.h>

#ifdef DEF_REFLECTION_FULL  //Note: this feature is not able to use for ObjectJc simple

void ctor_Fields_super_ClassJc ( ClassJc* thiz, StringJc name, int sizeType, ObjectArrayJc const* fields, ObjectArrayJc const* super) {
  memset(thiz, 0, sizeof(*thiz));
  iniz_ObjectJc(&thiz->object, thiz, sizeof(*thiz), &refl_ClassJc, ID_refl_ClassJc);
  copyToBuffer_StringJc(name, 0, -1, thiz->name, sizeof(thiz->name));
  thiz->nSize = sizeType;
  thiz->attributes = (struct FieldJc_Y_t const*)fields;  //TODO before casting: check type via reflection
  thiz->superClass_es.obj = &super->object; //TODO before casting: check type via reflection
}



void ctor_ClassOffset_idxVtblJc ( ClassOffset_idxVtblJc* thiz, ClassJc const* refl_super, int accessLevel, int ixVtbl)
{
  memset(thiz, 0, sizeof(*thiz));
  //thiz->clazz_super = refl_super;
  strncpy_emC(thiz->superfield.name, "super", sizeof(thiz->superfield.name));
  thiz->superfield.nrofArrayElementsOrBitfield_ = 0;
  thiz->superfield.type_ = refl_super;
  thiz->superfield.bitModifiers = kEmbeddedContainer_Modifier_reflectJc
                           | ((accessLevel << kBitAccessLevel_Modifier_FieldJc) & mAccessLevel_Modifier_FieldJc)
                           | (7 << kBitChangeLevel_Modifier_FieldJc);  //never change the super field
  thiz->superfield.offsetToObjectifcBase = 0;
  thiz->superfield.offsFieldInStruct = 0;  //usual 0
  thiz->idxVtbl = ixVtbl;
}



#endif //DEF_REFLECTION_FULL


