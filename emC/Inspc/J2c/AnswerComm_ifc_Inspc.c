/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#include <applstdef_emC.h>
#ifdef DEF_ClassJc_Vtbl
//NOTE: This file can only be used with full capability of emC, not for simple applications.
//      It is only necessary to full including the Inspc symbolic access on target

#include <emC/Inspc/J2c/AnswerComm_ifc_Inspc.h>
#include <string.h>  //because using memset()
#include <emC/Jc/ReflectionJc.h>   //Reflection concept 
  //basic stacktrace concept


const char sign_Vtbl_AnswerComm_ifc_Inspc[] = "AnswerComm_ifc_Inspc"; //to mark method tables of all implementations


/**Sends an answer. */
/*J2C: dynamic call variant of the override-able method: */
int32 txAnswer_AnswerComm_ifc_Inspc(ObjectJc* ithis, int32 nrofAnswerBytesPart, bool bLastTelg, ThCxt* _thCxt)
{ Vtbl_AnswerComm_ifc_Inspc const* mtbl = (Vtbl_AnswerComm_ifc_Inspc const*)getVtbl_ObjectJc(ithis, sign_Vtbl_AnswerComm_ifc_Inspc);
  return mtbl->txAnswer(ithis, nrofAnswerBytesPart, bLastTelg, _thCxt);
}

 extern_C struct ClassJc_t const refl_ObjectJc;
 static struct superClasses_AnswerComm_ifc_Inspc_s_t
 { ObjectArrayJc head;
   ClassOffset_idxVtblJc data[1];
 }superclasses_AnswerComm_ifc_Inspc_s =
 { CONST_ObjectArrayJc(ClassOffset_idxVtblJc, 1, OBJTYPE_ClassOffset_idxVtblJc, null, null)
 , { {&refl_ObjectJc, 0 /*J2C: no Vtbl*/ }
   }
 };

const ClassJc refl_AnswerComm_ifc_Inspc_s = 
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ObjectJc, &refl_ClassJc) 
, "AnswerComm_ifc_Inspc_s"
,  0 //position of ObjectJc
, sizeof(AnswerComm_ifc_Inspc_s)
, null //attributes and associations
, null //method
, &superclasses_AnswerComm_ifc_Inspc_s.head.object  //, &superclasses_AnswerComm_ifc_Inspc_s.head.object //superclass
, null //interfaces
, 0    //modifiers
};

#endif //def DEF_ClassJc_Vtbl
