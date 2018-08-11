/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#include "InspcJ2c/CmdConsumer_ifc_Inspc.h"
#include <string.h>  //because using memset()
#include <Jc/ReflectionJc.h>   //Reflection concept 
#include <emC/Exception_emC.h>  //basic stacktrace concept


/* J2C: Forward declaration of struct ***********************************************/


const char sign_Mtbl_CmdConsumer_ifc_Inspc[] = "CmdConsumer_ifc_Inspc"; //to mark method tables of all implementations


/**Executes a command, writes the answer in the answer datagram.*/
/*J2C: dynamic call variant of the override-able method: */
int32 executeMonitorCmd_CmdConsumer_ifc_Inspc(ObjectJc* ithis, struct Inspcitem_InspcDataExchangeAccess_Inspc_t* cmd, struct InspcDatagram_InspcDataExchangeAccess_Inspc_t* answer, int32 maxNrofAnswerBytes, ThCxt* _thCxt)
{ Mtbl_CmdConsumer_ifc_Inspc const* mtbl = (Mtbl_CmdConsumer_ifc_Inspc const*)getMtbl_ObjectJc(ithis, sign_Mtbl_CmdConsumer_ifc_Inspc);
  return mtbl->executeMonitorCmd(ithis, cmd, answer, maxNrofAnswerBytes, _thCxt);
}


/**Sets the aggregation for the answer.*/
/*J2C: dynamic call variant of the override-able method: */
void setAnswerComm_CmdConsumer_ifc_Inspc(ObjectJc* ithis, struct AnswerComm_ifc_Inspc_t* answerComm, ThCxt* _thCxt)
{ Mtbl_CmdConsumer_ifc_Inspc const* mtbl = (Mtbl_CmdConsumer_ifc_Inspc const*)getMtbl_ObjectJc(ithis, sign_Mtbl_CmdConsumer_ifc_Inspc);
  mtbl->setAnswerComm(ithis, answerComm, _thCxt);
}

 extern_C struct ClassJc_t const reflection_ObjectJc;
 static struct superClasses_CmdConsumer_ifc_Inspc_s_t
 { ObjectArrayJc head;
   ClassOffset_idxMtblJc data[1];
 }superclasses_CmdConsumer_ifc_Inspc_s =
 { CONST_ObjectArrayJc(ClassOffset_idxMtblJc, 1, OBJTYPE_ClassOffset_idxMtblJc, null, null)
 , { {&reflection_ObjectJc, 0 /*J2C: no Mtbl*/ }
   }
 };

const ClassJc reflection_CmdConsumer_ifc_Inspc_s = 
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ObjectJc, &reflection_ClassJc) 
, "CmdConsumer_ifc_Inspc_s"
,  0 //position of ObjectJc
, sizeof(CmdConsumer_ifc_Inspc_s)
, null //attributes and associations
, null //method
, (ClassOffset_idxMtblJcARRAY*)&superclasses_CmdConsumer_ifc_Inspc_s //superclass
, null //interfaces
, 0    //modifiers
};
