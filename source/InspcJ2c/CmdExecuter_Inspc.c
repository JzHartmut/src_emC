/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#include "InspcJ2c/CmdExecuter_Inspc.h"
#include <string.h>  //because using memset()
#include <Jc/ReflectionJc.h>   //Reflection concept 
#include <Fwc/fw_Exception.h>  //basic stacktrace concept
#include "InspcJ2c/CmdConsumer_ifc_Inspc.h"  //reference-association: cmdConsumerMtbl
#include "InspcJ2c/Comm_Inspc.h"  //reference-association: comm
#include "Jc/ArraysJc.h"  //reference-association: ArraysJc
#include "Jc/PrintStreamJc.h"  //reference-association: err
#include "Jc/StringJc.h"  //embedded type in class data
#include "Jc/SystemJc.h"  //reference-association: SystemJc


/* J2C: Forward declaration of struct ***********************************************/


/* J2C: Method-table-references *********************************************************/
#ifndef CmdConsumer_ifc_InspcMTBDEF
  #define CmdConsumer_ifc_InspcMTBDEF
  typedef struct CmdConsumer_ifc_InspcMTB_t { struct Mtbl_CmdConsumer_ifc_Inspc_t const* mtbl; struct CmdConsumer_ifc_Inspc_t* ref; } CmdConsumer_ifc_InspcMTB;
#endif



const char sign_Mtbl_CmdExecuter_Inspc[] = "CmdExecuter_Inspc"; //to mark method tables of all implementations

typedef struct MtblDef_CmdExecuter_Inspc_t { Mtbl_CmdExecuter_Inspc mtbl; MtblHeadJc end; } MtblDef_CmdExecuter_Inspc;
 extern MtblDef_CmdExecuter_Inspc const mtblCmdExecuter_Inspc;
StringJc version_CmdExecuter_Inspc = CONST_z_StringJc("2015-08-05"); //J2C:static StringJc

/*Constructor */
struct CmdExecuter_Inspc_t* ctorO_CmdExecuter_Inspc(ObjectJc* othis, struct CmdConsumer_ifc_Inspc_t* commandConsumer, ThCxt* _thCxt)
{ CmdExecuter_Inspc_s* thiz = (CmdExecuter_Inspc_s*)othis;  //upcasting to the real class.
  STACKTRC_TENTRY("ctorO_CmdExecuter_Inspc");
  checkConsistence_ObjectJc(othis, sizeof(CmdExecuter_Inspc_s), null, _thCxt);  
  setReflection_ObjectJc(othis, &reflection_CmdExecuter_Inspc_s, sizeof(CmdExecuter_Inspc_s));  
  //j2c: Initialize all class variables:
  {
    //J2C: constructor for embedded element-MemC
      ctorM_InspcDatagram_InspcDataExchangeAccess_Inspc(/*J2C:static method call*/build_MemC(&thiz->datagramCmd, sizeof(thiz->datagramCmd)), _thCxt);
    //J2C: constructor for embedded element-MemC
      ctorM_Inspcitem_InspcDataExchangeAccess_Inspc(/*J2C:static method call*/build_MemC(&thiz->infoCmd, sizeof(thiz->infoCmd)), _thCxt);
    thiz->maxNrofAnswerBytes = 1400;
    init0_MemC(build_MemC(&thiz->data_bufferAnswerData, 1400 * sizeof(int8))); //J2C: init the embedded simple array;
    thiz->bufferAnswerData.ref = & thiz->data_bufferAnswerData[0]; thiz->bufferAnswerData.val = sizeof( thiz->data_bufferAnswerData) / sizeof(thiz->data_bufferAnswerData[0]);
    //J2C: constructor for embedded element-MemC
      ctorM_iY_InspcDatagram_InspcDataExchangeAccess_Inspc(/*J2C:static method call*/build_MemC(&thiz->myAnswerData, sizeof(thiz->myAnswerData)), thiz->bufferAnswerData, _thCxt);
  }
  { 
    
    thiz->cmdConsumer = commandConsumer;
  }
  STACKTRC_LEAVE;
  return thiz;
}


void completeConstruction_CmdExecuter_Inspc_F(CmdExecuter_Inspc_s* thiz, struct Comm_Inspc_t* comm, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("completeConstruction_CmdExecuter_Inspc_F");
  
  { 
    
    thiz->comm = comm;
  }
  STACKTRC_LEAVE;
}

/*J2C: dynamic call variant of the override-able method: */
void completeConstruction_CmdExecuter_Inspc(CmdExecuter_Inspc_s* thiz, struct Comm_Inspc_t* comm, ThCxt* _thCxt)
{ Mtbl_CmdExecuter_Inspc const* mtbl = (Mtbl_CmdExecuter_Inspc const*)getMtbl_ObjectJc(&thiz->base.object, sign_Mtbl_CmdExecuter_Inspc);
  mtbl->completeConstruction(thiz, comm, _thCxt);
}


/**Executes the given command received with this datagram (J2C:wmDef)*/
bool executeCmd_CmdExecuter_Inspc_F(CmdExecuter_Inspc_s* thiz, PtrVal_int8 buffer, int32 nrofBytesReceived, ThCxt* _thCxt)
{ Mtbl_CmdExecuter_Inspc const* mtthis = (Mtbl_CmdExecuter_Inspc const*)getMtbl_ObjectJc(&thiz->base.object, sign_Mtbl_CmdExecuter_Inspc);
  
  STACKTRC_TENTRY("executeCmd_CmdExecuter_Inspc_F");
  
  { 
    
    assignDatagram_InspcDatagram_InspcDataExchangeAccess_Inspc(& (thiz->datagramCmd), buffer, nrofBytesReceived);
    
    int32  nEntrant = getEntrant_InspcDatagram_InspcDataExchangeAccess_Inspc(& (thiz->datagramCmd));
    
    bool  bOk = true;
    
    int32  nrofBytesTelg;/*no initvalue*/
    
    int32  partLength;/*no initvalue*/
    
    int32  maxNrofBytesAnswerPart;/*no initvalue*/
    thiz->nrofBytesAnswer = 0;
    
    CmdConsumer_ifc_InspcMTB cmdConsumerMtbl ; SETMTBJc(cmdConsumerMtbl, thiz->cmdConsumer, CmdConsumer_ifc_Inspc);
    removeChildren_ByteDataAccessBaseJc(& ((thiz->myAnswerData).base/*J2C_super:*/.super));
    fill_mB_ArraysJc(/*J2C:static method call*/thiz->bufferAnswerData, 0, thiz->bufferAnswerData.val, (int8 /*J2C_cast*/)0, _thCxt);/*String test = myAnswerData.toString();*/
    
    if(nEntrant < 0) 
    { /*:a negative number: It is an entrant, the telegram has the common head.*/
      
      
      nrofBytesTelg = getLengthDatagram_InspcDatagram_InspcDataExchangeAccess_Inspc(& (thiz->datagramCmd));
      
      int32  nrofBytesAccess = getLengthTotal_ByteDataAccessBaseJc(& ((thiz->datagramCmd).base/*J2C_super:*/.super), _thCxt);
      ASSERT(/*J2C:static method call*/nrofBytesTelg == nrofBytesReceived);
      ASSERT(/*J2C:static method call*/nrofBytesTelg == nrofBytesAccess);/*nrofBytesProcessed = datagramCmd.sizeofHead;*/
      
      thiz->useTelgHead = true;/**/
      
      
      int32  seqNr = getSeqnr_InspcDatagram_InspcDataExchangeAccess_Inspc(& (thiz->datagramCmd));
      
      int32  encryption = getEncryption_InspcDatagram_InspcDataExchangeAccess_Inspc(& (thiz->datagramCmd));
      setHeadAnswer_InspcDatagram_InspcDataExchangeAccess_Inspc(& (thiz->myAnswerData), nEntrant, seqNr, encryption, _thCxt);
      thiz->nrofBytesAnswer = sizeofHead_InspcDatagram_InspcDataExchangeAccess_Inspc;
      
      while(bOk && sufficingBytesForNextChild_ByteDataAccessBaseJc(& ((thiz->datagramCmd).base/*J2C_super:*/.super), sizeofHead_Inspcitem_InspcDataExchangeAccess_Inspc, _thCxt))
        { /*:nrofBytesTelg >= (nrofBytesProcessed + InspcDataExchangeAccess.Inspcitem.sizeofHead)){*/
          /*:The next telg Part will be found after the processed part.*/
          
          
          addChild_XX_ByteDataAccessBaseJc(& ((thiz->datagramCmd).base/*J2C_super:*/.super), & ((thiz->infoCmd).base/*J2C_super:*/.super), _thCxt);
          partLength = getLenInfo_Inspcitem_InspcDataExchangeAccess_Inspc(& (thiz->infoCmd));
          if(partLength >= sizeofHead_Inspcitem_InspcDataExchangeAccess_Inspc && checkLengthElement_ByteDataAccessBaseJc(& ((thiz->infoCmd).base/*J2C_super:*/.super), partLength, _thCxt)) 
          { /*:partLength <= (nrofBytesTelg - nrofBytesProcessed)){*/
            /*:valid head data.*/
            
            
            setLengthElement_ByteDataAccessBaseJc(& ((thiz->infoCmd).base/*J2C_super:*/.super), partLength);/*this child has the given length.*/
            
            maxNrofBytesAnswerPart = thiz->maxNrofAnswerBytes - thiz->nrofBytesAnswer;/*execute:*/
            
            TRY
            { 
              
              cmdConsumerMtbl.mtbl->executeMonitorCmd(&(( (cmdConsumerMtbl.ref))->base.object), & (thiz->infoCmd), & (thiz->myAnswerData), maxNrofBytesAnswerPart, _thCxt);
            }_TRY
            CATCH(IllegalArgumentException, exc)
            
              { 
                
                println_z_PrintStreamJc(REFJc (err_SystemJc), "CmdExecuter - Exception", _thCxt);/*TODO send a nack*/
                
              }
            CATCH(UnsupportedEncodingException, exc)
            
              { 
                
                println_z_PrintStreamJc(REFJc (err_SystemJc), "CmdExecuter - Exception2", _thCxt);/*TODO send a nack*/
                
              }
            END_TRY
          }
          else 
          { /*:invalid head data*/
            
            
            bOk = false;
            thiz->ctFailedTelgPart += 1;
          }/*nrofBytesProcessed += partLength;*/
          
        }
      
      int32  nrofAnswer = getLengthTotal_ByteDataAccessBaseJc(& ((thiz->myAnswerData).base/*J2C_super:*/.super), _thCxt);
      if(nrofAnswer > sizeofHead_InspcDatagram_InspcDataExchangeAccess_Inspc) 
      { /*:more as the head:*/
        
        
        mtthis->AnswerComm_ifc_Inspc.txAnswer(&((& ((* (thiz)).base/*J2C:ifc*/.AnswerComm_ifc_Inspc))->base.object), nrofAnswer, true, _thCxt);
      }
    }
    else 
    { /*:a positive number: The telegram hasn't the commmon head ,,DataExchangeTelgHead_Inspc,,, it is one command.*/
      /*:It is the old style of communication, exclusively used until 2010-0216.*/
      
      
      thiz->useTelgHead = false;/*dummy head with 2 empty information units.*/
      
      setHeadAnswer_InspcDatagram_InspcDataExchangeAccess_Inspc(& (thiz->myAnswerData), 0, 0x80000, 0, _thCxt);
      setLengthDatagram_InspcDatagram_InspcDataExchangeAccess_Inspc(& (thiz->myAnswerData), 8);
      assign_iYi_ByteDataAccessBaseJc(& ((thiz->infoCmd).base/*J2C_super:*/.super), buffer, nrofBytesReceived);
      setBigEndian_ByteDataAccessBaseJc(& ((thiz->infoCmd).base/*J2C_super:*/.super), true);
      maxNrofBytesAnswerPart = 1400;
      TRY
      { 
        
        cmdConsumerMtbl.mtbl->executeMonitorCmd(&(( (cmdConsumerMtbl.ref))->base.object), & (thiz->infoCmd), & (thiz->myAnswerData), maxNrofBytesAnswerPart, _thCxt);
      }_TRY
      CATCH(IllegalArgumentException, exc)
      
        { /*:TODO send a nack*/
          
          
          
        }
      CATCH(UnsupportedEncodingException, exc)
      
        { /*:TODO send a nack*/
          
          
          
        }
      END_TRY
      
      int32  nrofAnswer = getLengthTotal_ByteDataAccessBaseJc(& ((thiz->myAnswerData).base/*J2C_super:*/.super), _thCxt);
      if(nrofAnswer > sizeofHead_InspcDatagram_InspcDataExchangeAccess_Inspc) 
      { /*:more as the head:*/
        
        
        mtthis->AnswerComm_ifc_Inspc.txAnswer(&((& ((* (thiz)).base/*J2C:ifc*/.AnswerComm_ifc_Inspc))->base.object), nrofAnswer, true, _thCxt);
      }
    }
    { STACKTRC_LEAVE;
      return bOk;
    }
  }
  STACKTRC_LEAVE;
}

/*J2C: dynamic call variant of the override-able method: */
bool executeCmd_CmdExecuter_Inspc(CmdExecuter_Inspc_s* thiz, PtrVal_int8 buffer, int32 nrofBytesReceived, ThCxt* _thCxt)
{ Mtbl_CmdExecuter_Inspc const* mtbl = (Mtbl_CmdExecuter_Inspc const*)getMtbl_ObjectJc(&thiz->base.object, sign_Mtbl_CmdExecuter_Inspc);
  return mtbl->executeCmd(thiz, buffer, nrofBytesReceived, _thCxt);
}


/**Send the current answer datagram as answer. Firstly the {@link InspcDataExchangeAccess.InspcDatagram#incrAnswerNr()} (J2C:wmDef)*/
int32 txAnswer_ib_CmdExecuter_Inspc_F(ObjectJc* ithis, int32 nrofAnswerBytesPart, bool bLastTelg, ThCxt* _thCxt)
{ CmdExecuter_Inspc_s* thiz = (CmdExecuter_Inspc_s*)ithis;
  
  STACKTRC_TENTRY("txAnswer_ib_CmdExecuter_Inspc_F");
  
  { 
    
    
    int32  ret;/*no initvalue*/
    if(thiz->useTelgHead) 
    { 
      
      incrAnswerNr_InspcDatagram_InspcDataExchangeAccess_Inspc(& (thiz->myAnswerData), _thCxt);/*start answer from 1*/
      
      setLengthDatagram_InspcDatagram_InspcDataExchangeAccess_Inspc(& (thiz->myAnswerData), nrofAnswerBytesPart);
    }/*ythis->answer.nrofSentBytes = txAnswerRawData_Comm_Inspc(ythis, &ythis->answer.myAnswerData, ythis->answer.nrofAnswerBytes, &ythis->myAnswerAddress);*/
    
    thiz->nrofBytesAnswer = nrofAnswerBytesPart;
    if(!thiz->useTelgHead || thiz->nrofBytesAnswer > sizeofHead_InspcDatagram_InspcDataExchangeAccess_Inspc) 
    { 
      
      if(bLastTelg && thiz->useTelgHead) 
      { 
        
        markAnswerNrLast_InspcDatagram_InspcDataExchangeAccess_Inspc(& (thiz->myAnswerData), _thCxt);/*mark as last telg*/
        
      }/*send.*/
      
      sendAnswer_Comm_Inspc(thiz->comm, thiz->bufferAnswerData, thiz->nrofBytesAnswer, _thCxt);/**/
      
      if(bLastTelg) 
      { 
        
        ret = 0;
      }
      else 
      { /*:prepare the next telg:*/
        
        
        thiz->nrofBytesAnswer = sizeofHead_InspcDatagram_InspcDataExchangeAccess_Inspc;
        ret = sizeofHead_InspcDatagram_InspcDataExchangeAccess_Inspc - thiz->nrofBytesAnswer;
      }
    }
    else 
    { /*:nothing to sent.*/
      
      
      ret = sizeofHead_InspcDatagram_InspcDataExchangeAccess_Inspc - thiz->nrofBytesAnswer;
    }
    { STACKTRC_LEAVE;
      return ret;
    }
  }
  STACKTRC_LEAVE;
}

/*J2C: dynamic call variant of the override-able method: */
int32 txAnswer_ib_CmdExecuter_Inspc(ObjectJc* ithis, int32 nrofAnswerBytesPart, bool bLastTelg, ThCxt* _thCxt)
{ Mtbl_AnswerComm_ifc_Inspc const* mtbl = (Mtbl_AnswerComm_ifc_Inspc const*)getMtbl_ObjectJc(ithis, sign_Mtbl_AnswerComm_ifc_Inspc);
  return mtbl->txAnswer(ithis, nrofAnswerBytesPart, bLastTelg, _thCxt);
}



/**J2C: Reflections and Method-table *************************************************/
const MtblDef_CmdExecuter_Inspc mtblCmdExecuter_Inspc = {
{ { sign_Mtbl_CmdExecuter_Inspc //J2C: Head of methodtable of CmdExecuter_Inspc
  , (struct Size_Mtbl_t*)((2 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
  }
  //J2C: Dynamic methods of the class :CmdExecuter_Inspc:
, completeConstruction_CmdExecuter_Inspc_F //completeConstruction
, executeCmd_CmdExecuter_Inspc_F //executeCmd
  //J2C: The superclass's methodtable: 
, { { sign_Mtbl_ObjectJc //J2C: Head of methodtable of ObjectJc
    , (struct Size_Mtbl_t*)((5 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
    }
    //J2C: Dynamic methods of the class :ObjectJc:
  , clone_ObjectJc_F //clone
  , equals_ObjectJc_F //equals
  , finalize_ObjectJc_F //finalize
  , hashCode_ObjectJc_F //hashCode
  , toString_ObjectJc_F //toString
  }
  //J2C: The interface's methodtable: 
  //J2C: Mtbl-interfaces of :CmdExecuter_Inspc: */
, { { sign_Mtbl_AnswerComm_ifc_Inspc //J2C: Head of methodtable of AnswerComm_ifc_Inspc
    , (struct Size_Mtbl_t*)((1 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
    }
    //J2C: Dynamic methods of the class :AnswerComm_ifc_Inspc:
  , txAnswer_ib_CmdExecuter_Inspc_F //txAnswer
    //J2C: The superclass's methodtable: 
  , { { sign_Mtbl_ObjectJc //J2C: Head of methodtable of ObjectJc
      , (struct Size_Mtbl_t*)((5 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
      }
      //J2C: Dynamic methods of the class :ObjectJc:
    , clone_ObjectJc_F //clone
    , equals_ObjectJc_F //equals
    , finalize_ObjectJc_F //finalize
    , hashCode_ObjectJc_F //hashCode
    , toString_ObjectJc_F //toString
    }
  }
}, { signEnd_Mtbl_ObjectJc, null } }; //Mtbl


 extern_C struct ClassJc_t const reflection_ObjectJc;
 static struct superClasses_CmdExecuter_Inspc_s_t
 { ObjectArrayJc head;
   ClassOffset_idxMtblJc data[1];
 }superclasses_CmdExecuter_Inspc_s =
 { CONST_ObjectArrayJc(ClassOffset_idxMtblJc, 1, OBJTYPE_ClassOffset_idxMtblJc, null, null)
 , { {&reflection_ObjectJc, OFFSET_Mtbl(Mtbl_CmdExecuter_Inspc, ObjectJc) }
   }
 };

 extern_C struct ClassJc_t const reflection_AnswerComm_ifc_Inspc_s;
 static struct ifcClasses_CmdExecuter_Inspc_s_t
 { ObjectArrayJc head;
   ClassOffset_idxMtblJc data[1];
 }interfaces_CmdExecuter_Inspc_s =
 { CONST_ObjectArrayJc(ClassOffset_idxMtblJc, 1, OBJTYPE_ClassOffset_idxMtblJc, null, null)
, { {&reflection_AnswerComm_ifc_Inspc_s, OFFSET_Mtbl(Mtbl_CmdExecuter_Inspc, AnswerComm_ifc_Inspc) }
  }
};

extern_C struct ClassJc_t const reflection_CmdExecuter_Inspc_s;
extern_C struct ClassJc_t const reflection_CmdConsumer_ifc_Inspc_s;
extern_C struct ClassJc_t const reflection_Comm_Inspc_s;
extern_C struct ClassJc_t const reflection_InspcDatagram_InspcDataExchangeAccess_Inspc_s;
extern_C struct ClassJc_t const reflection_Inspcitem_InspcDataExchangeAccess_Inspc_s;
extern_C struct ClassJc_t const reflection_StringJc;
const struct Reflection_Fields_CmdExecuter_Inspc_s_t
{ ObjectArrayJc head; FieldJc data[13];
} reflection_Fields_CmdExecuter_Inspc_s =
{ CONST_ObjectArrayJc(FieldJc, 13, OBJTYPE_FieldJc, null, &reflection_Fields_CmdExecuter_Inspc_s)
, {
     { "datagramCmd"
    , 0 //nrofArrayElements
    , &reflection_InspcDatagram_InspcDataExchangeAccess_Inspc_s
    , kEmbedded_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((CmdExecuter_Inspc_s*)(0x1000))->datagramCmd) - (int32)(CmdExecuter_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_CmdExecuter_Inspc_s
    }
   , { "infoCmd"
    , 0 //nrofArrayElements
    , &reflection_Inspcitem_InspcDataExchangeAccess_Inspc_s
    , kEmbedded_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((CmdExecuter_Inspc_s*)(0x1000))->infoCmd) - (int32)(CmdExecuter_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_CmdExecuter_Inspc_s
    }
   , { "cmdConsumer"
    , 0 //nrofArrayElements
    , &reflection_CmdConsumer_ifc_Inspc_s
    , kReference_Modifier_reflectJc |mObjectJc_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((CmdExecuter_Inspc_s*)(0x1000))->cmdConsumer) - (int32)(CmdExecuter_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_CmdExecuter_Inspc_s
    }
   , { "maxNrofAnswerBytes"
    , 0 //nrofArrayElements
    , REFLECTION_int32
    , 4 << kBitPrimitiv_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((CmdExecuter_Inspc_s*)(0x1000))->maxNrofAnswerBytes) - (int32)(CmdExecuter_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_CmdExecuter_Inspc_s
    }
   , { "nrofBytesAnswer"
    , 0 //nrofArrayElements
    , REFLECTION_int32
    , 4 << kBitPrimitiv_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((CmdExecuter_Inspc_s*)(0x1000))->nrofBytesAnswer) - (int32)(CmdExecuter_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_CmdExecuter_Inspc_s
    }
   , { "nrofSentBytes"
    , 0 //nrofArrayElements
    , REFLECTION_int32
    , 4 << kBitPrimitiv_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((CmdExecuter_Inspc_s*)(0x1000))->nrofSentBytes) - (int32)(CmdExecuter_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_CmdExecuter_Inspc_s
    }
   , { "ctFailedTelgPart"
    , 0 //nrofArrayElements
    , REFLECTION_int32
    , 4 << kBitPrimitiv_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((CmdExecuter_Inspc_s*)(0x1000))->ctFailedTelgPart) - (int32)(CmdExecuter_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_CmdExecuter_Inspc_s
    }
   , { "comm"
    , 0 //nrofArrayElements
    , &reflection_Comm_Inspc_s
    , kReference_Modifier_reflectJc |mObjectJc_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((CmdExecuter_Inspc_s*)(0x1000))->comm) - (int32)(CmdExecuter_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_CmdExecuter_Inspc_s
    }
   , { "data_bufferAnswerData"
    , 1400 //nrofArrayElements
    , REFLECTION_int8
    , 1 << kBitPrimitiv_Modifier_reflectJc |kStaticArray_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((CmdExecuter_Inspc_s*)(0x1000))->data_bufferAnswerData) - (int32)(CmdExecuter_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_CmdExecuter_Inspc_s
    }
   , { "bufferAnswerData"
    , 0 //nrofArrayElements
    , REFLECTION_int8
    , 1 << kBitPrimitiv_Modifier_reflectJc |kObjectArrayJc_Modifier_reflectJc |kPtrVal_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((CmdExecuter_Inspc_s*)(0x1000))->bufferAnswerData) - (int32)(CmdExecuter_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_CmdExecuter_Inspc_s
    }
   , { "myAnswerData"
    , 0 //nrofArrayElements
    , &reflection_InspcDatagram_InspcDataExchangeAccess_Inspc_s
    , kEmbedded_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((CmdExecuter_Inspc_s*)(0x1000))->myAnswerData) - (int32)(CmdExecuter_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_CmdExecuter_Inspc_s
    }
   , { "useTelgHead"
    , 0 //nrofArrayElements
    , REFLECTION_bool
    , 4 << kBitPrimitiv_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((CmdExecuter_Inspc_s*)(0x1000))->useTelgHead) - (int32)(CmdExecuter_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_CmdExecuter_Inspc_s
    }
   , { "version"
    , 0 //nrofArrayElements
    , &reflection_StringJc
    , kEnhancedReference_Modifier_reflectJc /*t*/ |mSTATIC_Modifier_reflectJc //bitModifiers
    , 0 //compiler problem, not a constant,TODO: (int16)(&version_CmdExecuter_Inspc) //lo part of memory address of static member
    , 0 //compiler problem, not a constant,TODO: (int16)((int32)(&version_CmdExecuter_Inspc)>>16) //hi part of memory address of static member instead offsetToObjectifcBase, TRICKY because compatibilty.
    , &reflection_CmdExecuter_Inspc_s
    }
} };
const ClassJc reflection_CmdExecuter_Inspc_s = 
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ObjectJc, &reflection_ClassJc) 
, "CmdExecuter_Inspc_s"
, (int16)((int32)(&((CmdExecuter_Inspc_s*)(0x1000))->base.object) - (int32)(CmdExecuter_Inspc_s*)0x1000)
, sizeof(CmdExecuter_Inspc_s)
, (FieldJc_Y const*)&reflection_Fields_CmdExecuter_Inspc_s
, null //method
, (ClassOffset_idxMtblJcARRAY*)&superclasses_CmdExecuter_Inspc_s //superclass
, (ClassOffset_idxMtblJcARRAY*)&interfaces_CmdExecuter_Inspc_s //interfaces
, mObjectJc_Modifier_reflectJc
, &mtblCmdExecuter_Inspc.mtbl.head
};
