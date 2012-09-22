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
 * @content Definition of memory access routines. 
 * This routines are implemented in a operation system specific way. 
 *
 * @author Hartmut Schorrig
 * @version sf-0.83
 * 2012-09-08: Hartmut creation 
 *
 ************************************************************************************************/
#ifndef __fw_StateM_h__
#define __fw_StateM_h__

#include <os_types_def.h>

/**It is a template: 
typedef struct StateNAME_Fwc_t
{
  struct SuperState_t* enclState;
  int stateId;
} StateBase;



typedef struct StateBase_FwcX_t{
  struct StateComboBase_FwcX_t* enclState;
  int stateId;
} StateBase_FwcX;

*/

#define consumed_StateBase_Fwc 0x1
#define runToComplete_StateBase_Fwc 0x2
#define stateError_StateBase_Fwc 0x80


#define INIT_StateBase_Fwc(enclState, stateId, env) {enclState, stateId, env}
//(enclState)->super.env

/**Entry in the given state. This method can only be used for simple...*/
#define entry_StateBase_Fwc(THIZ, CONT) ( (THIZ)->enclState->super.stateAct = (THIZ)->stateId, CONT )


#define exit_StateBase_Fwc(THIZ) ((THIZ)->enclState)

/**empty macro for log, may be redefined. */
#define logStateSwitch_StateComboBase_Fwc(THIZ, EVENT)


#define logErrorState__StateComboBase_Fwc(THIZ, faultState)
        
#define logErrorRun__StateComboBase_Fwc(THIZ)
        
#define trans_StateTop(EVENT) 0


/**The composition state process routine.
 * It calls switchState_TYPEstate() for the given state.
 * @param RET int-variable which stores the return value. 
 *   It contains the bits [[consumed_StateBase_Fwc]] or [[runToComplete_StateBase_Fwc]]
 *   or [[stateError_StateBase_Fwc]] as result of the inside called trans(Event) method
 *   and the called {@link #entry(int)} method. 
 * @param TYPEstate same parameter as TYPEstate of the [[TYPEDEF_StateTopBase_Fwc(...)]]
 *   or [[TYPEDEF_StateComboBase_Fwc]] definition of the state types. 
 *   It determines the name of the trans_##TYPEstate(...) and the switchState_##TYPEstate(...)
 *   routine which is called intern.
 * @param THIZ reference to the state 
 */
#define PROCESS_StateComboBase_Fwc(RET, TYPEstate, THIZ, EVENT) { \
  int _CONT_;  \
  int catastrophicalCount =  (THIZ)->super.maxStateSwitchesInLoop;   \
  do{ \
    logStateSwitch_StateComboBase_Fwc((THIZ).super, EVENT); \
    _CONT_ = switchState_##TYPEstate(THIZ, EVENT);  \
    if((_CONT_ & consumed_StateBase_Fwc) != 0){ \
      EVENT = null; \
    } \
    if((_CONT_ & stateError_StateBase_Fwc) != 0){ \
      int faultState = (THIZ)->super.stateAct; \
      (THIZ)->super.stateAct = 0;  /*prevent hang forever.*/ \
      logErrorState__StateComboBase_Fwc(THIZ, faultState); \
    } \
  } while((_CONT_ & runToComplete_StateBase_Fwc) !=0 && --catastrophicalCount >=0);\
  if(catastrophicalCount <0) { \
    logErrorRun__StateComboBase_Fwc(THIZ); \
  }\
  _CONT_ = trans_##TYPEstate(EVENT); /*evTrans is null if it was consumed in inner transitions.*/ \
  RET = _CONT_;  /*runToComplete.bit may be set. */ \
}



#define entry_StateComboBase(StateBase, THIZ) { (THIZ)->enclState->stateNr = (THIZ)->stateId; }

/*
typedef struct StateComboBase_FwcX_t{
  struct StateBase_FwcX_t super;
  int stateAct;
}StateComboBase_FwcX;
*/

#define STRUCT_StateBase_Fwc(ComboState, EnumState, Environment) \
  struct ComboState##_t* enclState; \
  EnumState stateId;  \
  struct Environment##_t* env; \
  int32_t ctEntry;\
  int32_t dateLastEntry;\
  int32_t durationLast

#define TYPEDEF_StateTopBase_Fwc(TYPEstate, EnumState, Environment) \
  typedef struct TYPEstate##_ComboState_t {STRUCT_StateBase_Fwc(Unused, int, Environment); EnumState stateAct; int maxStateSwitchesInLoop; } TYPEstate##_ComboState; \
  typedef struct TYPEstate##_State_t { STRUCT_StateBase_Fwc(TYPEstate, EnumState, Environment); } TYPEstate##_State;
  
#define TYPEDEF_StateComboBase_Fwc(TYPEstate, EnumState, SuperState, EnumSuperState, Environment) \
  typedef struct TYPEstate##_ComboState_t { STRUCT_StateBase_Fwc(SuperState, EnumSuperState, Environment); EnumState stateAct; int maxStateSwitchesInLoop; } TYPEstate##_ComboState; \
  typedef struct TYPEstate##_State_t { STRUCT_StateBase_Fwc(TYPEstate, EnumState, Environment); } TYPEstate##_State;
  
  //TYPEDEF_StateBase_Fwc(TYPEstate, EnumState)

#define INIT_StateTopBase_Fwc(StateNull, env) { null, 0, env, 0, 0, 0, StateNull, 1000 }

#define INIT_StateComboBase_Fwc(enclState, stateId, StateNull, env) {enclState, stateId, env, 0, 0, 0, StateNull, 1000 }



#define entry_StateComboBase(StateBase, THIZ) { (THIZ)->enclState->stateNr = (THIZ)->stateId; }


TYPEDEF_StateTopBase_Fwc(StateTopBase_Fwc, int, void);


void faultState_StateComboBase_Fwc_(StateTopBase_Fwc_ComboState* thiz);

#define faultState_StateComboBase_Fwc(THIZ) faultState_StateComboBase_Fwc_((StateTopBase_Fwc_ComboState*)(THIZ))








#define STRUCT_StateBaseConst_Fwc(EnclosingState, StateData, EnumState, Environment) \
  struct StateData##_t* stateData; \
  struct EnclosingState##Const_t const* enclState; \
  EnumState CONSTMember_Fwc stateId;  \
  struct Environment##_t* env



#define STRUCT_StateBaseData_Fwc() \
  int32_t ctEntry;\
  int32_t dateLastEntry;\
  int32_t durationLast


#define TYPEDEF_StateTopBaseConst_Fwc(TYPEstate, EnumState, Environment) \
  typedef struct TYPEstate##_ComboStateConst_t {STRUCT_StateBaseConst_Fwc(Unused, TYPEstate##_StateComboData, int, Environment); EnumState stateAct; } TYPEstate##_ComboStateConst; \
  typedef struct TYPEstate##_StateConst_t { STRUCT_StateBaseConst_Fwc(TYPEstate, StateBaseData_Fwc, EnumState, Environment); } TYPEstate##_StateConst;
  
#define TYPEDEF_StateComboBaseConst_Fwc(TYPEstate, EnumState, SuperState, EnumSuperState, Environment) \
  typedef struct TYPEstate##_ComboStateConst_t { STRUCT_StateBaseConst_Fwc(SuperState, TYPEstate##_StateComboData, EnumSuperState, Environment); EnumState stateAct; } TYPEstate##_ComboStateConst; \
  typedef struct TYPEstate##_StateConst_t { STRUCT_StateBaseConst_Fwc(TYPEstate, StateBaseData_Fwc, EnumState, Environment); } TYPEstate##_StateConst;
  

#define CONST_StateTopBase_Fwc(stateData, env) { stateData, null, 0, env}

#define CONST_StateComboBase_Fwc(enclState, stateId, stateData, env) {stateData, enclState, stateId, env }

#define CONST_StateBase_Fwc(stateData, enclState, stateId, env) {stateData, enclState, stateId, env }


  


typedef struct StateBaseData_Fwc_t{ STRUCT_StateBaseData_Fwc(); } StateBaseData_Fwc;


//#define DATA_StateBaseData_Fwc(stateName) StateBaseData_Fwc stateName = {0 };

#define TYPEDEF_StateComboBaseData_Fwc(stateName, EnumState) typedef struct stateName##_StateComboData_t{ STRUCT_StateBaseData_Fwc(); EnumState stateAct; }  stateName##_StateComboData;

/**Entry in the given state. This method can only be used for simple...*/
#define entry_StateBaseConst_Fwc(THIZ, CONT) ( (THIZ)->enclState->super.stateData->stateAct = (THIZ)->stateId, CONT )




#endif  //__fw_StateM_h__
