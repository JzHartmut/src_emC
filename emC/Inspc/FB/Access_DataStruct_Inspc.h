#ifndef __Access_DataStruct_Inspc_h__
#define __Access_DataStruct_Inspc_h__
#include <applstdef_emC.h>
#include <emC/base/DefPortTypes_emC.h>
#include <emC/Inspc/FB/DataStruct_Inspc.h>
#include <string.h>


struct DefPortTypes_emC_t;


/**Structure of one access to DataStruct. */
typedef struct Access_DataStruct_Inspc_t
{
  union{ ObjectJc object; } base;
  
  /**The output properties for Simulink, used for code generation. */
  Entry_DefPortType_emC portProps;

  /**Result of the parsed typeName_param on init_....(...), prevent multiple parsing. */
  VariableParam_DataStruct_Inspc_s typenameinfo;
  
  /**Information about the block in the simulink model. Set in ctor from properties of the model.
   * Either the input0 for set or the output0 for get is used to complete type information 
   * if there are not given in typenameinfo.
   */
  struct DefPortTypes_emC_t const* fblockInfo;

  /**null if ok, elsewhere the error message from init_...(...)*/
  char const* err;
  
  /**Number of bytes to copy to output. */
  int32 zBytes;

  int32 ctRepeatInit;

  /**The ready to use memory address of the data. */
  void* addr;
  
  /**Info for code generation. It is one field from InputValues_Inspc*/
  FieldJc const* field;

} Access_DataStruct_Inspc_s;

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Access_DataStruct_Inspc;
#endif

/**It is emmpty. */
void dtor_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s const* thiz);


/**Common init.
 * @param portProps to know Port information
 * @param bSet for using for the set_Access_DataStruct_Inspc(...)
 * @param typeName_param from parameter field name. 
 * @param typeDataIn_param used for Simulink coder to define the access type. Checked here. It may be a superType.
 * @param datapath_param used for getData_Access_DataStruct_Inspc(...)
 * @param data the input in the Tinit time for the Sfunction
 */
bool init_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s* thiz
  , Entry_DefPortType_emC const* portProps
  , bool bSet
  , StringJc typeName_param 
  , struct UserHead_DataStructMng_Inspc_t* data
  , uint32* handle_y);


/**
 * @param header_param not used, only for tlc
 * @simulink ctor.
 */
Access_DataStruct_Inspc_s* ctorTinit_Access_DataStruct_Inspc(ObjectJc* othiz, StringJc header_param, struct DefPortTypes_emC_t const* fblockInfo);


/**Initializes with given parameter and accesses in the Tinit time, because it is an init value. 
 * @param typeName
 * @simulink init.
 */
inline bool initTinit_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s* thiz, StringJc typeName_param, struct UserHead_DataStructMng_Inspc_t* data, uint32* handle_y) {
  return init_Access_DataStruct_Inspc(thiz, &thiz->fblockInfo->entries[thiz->fblockInfo->ixOutputStep], false, typeName_param, data, handle_y);
}



/**Routine to determine type all parameter for code generation for the tlc file. 
* @param keys_tlcParam array will be filled with some key names as const literals.
* @param values_tlcParams array will be filled with the char const char* reference to the value inside buffer_tlcParam
* @param buffer_tlcParam char[] as buffer for all param values, the buffer will be filled tight, with 0 between the items.
* @param typeName_param the combined parameter for the type and name
* @return number of chars used in buffer_tlcParam.
* @simulink defTlcParam_excl.
*/
int defTlcParams_TinitAccess_DataStruct_Inspc(DefPortTypes_emC* portInfo_tlcParam
	, char const* keys_tlcParam[5], void const* values_tlcParam[5]
	, char buffer_tlcParam[500], int zBuffer_tlcParam
  , char header_param[200], StringJc typeName_param
	);



/**
 * @simulink Object-FB, no-thizInit, no-thizStep.
 */
inline void getTinit_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s* thiz) {  }





/**
 * @param header_param only used for tlc file.
 * @param Tstep only used for Simulink to determine the step time
 * @param fblockInfo should be allocated before call using os_allocMem(...). It is freed in dtor. 
 * @simulink ctor.
 */
Access_DataStruct_Inspc_s* ctor_Access_DataStruct_Inspc(ObjectJc* othiz, StringJc header_param
  , float Tstep
  , struct DefPortTypes_emC_t const* fblockInfo);





/**Routine determines port properties
* @param defPortTypes contains array reference and length of array.
*    It is filled with the given port properties on call. Because of type the information are complemented.
*    With the complemented information the port initialization is done in mdlInizializeSizes
* @param typeName_param determines the type of the output. If "Type*" then the type is a handle.
* @simulink defPortTypes.
*/
char const* definePortType_Access_DataStruct_Inspc(DefPortTypes_emC* defPortTypes, EDefPortTypes_emC cause, StringJc typeName_param);



/**Initializes to get access. Due to typeName_param the source is searched and tested.
 * @param typeName_param String contain type, possible access path and variable name.
 *        Syntax see [[DataStructBase_Inspc.h:analyzeLineDef_DataStruct_Inspc(...)]]  
 * @simulink init.
 */
inline bool initGet_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s* thiz, StringJc typeName_param/*, StringJc typeDataIn_param, StringJc datapath_param*/, struct UserHead_DataStructMng_Inspc_t* data) {
  return init_Access_DataStruct_Inspc(thiz, &thiz->fblockInfo->entries[thiz->fblockInfo->ixOutputStep], false, typeName_param, /*typeDataIn_param, datapath_param, */data, null);
}


/**Routine to determine type and arraysize of the output port. The parameter should be with same name as on ctor.
 * @param dst The environment (simulink) should deliver an array of entries. Maybe as stack variable.
 * @param keys_tlcParam array will be filled with some key names as const literals. 
 *        [0] Will be set with "typeData_param" for the output type.
 * @param values_tlcParams array will be filled with the char const* reference to the value inside buffer_tlcParam
 *        [0] will be set with the type name if typeOut_param contains an "*" on end. 
 *        [0] will be set emtpy if typeOut_param does not contain a Reference type.
 * @param buffer_tlcParam char[] as buffer for all param values, the buffer will be filled tight, with 0 between the items. 
 * @param typeName_param it is the parameter for type Name of the Sfunction with its specified syntax.
 * @return number of chars used in buffer_tlcParam.
 * @simulink defTlcParam_excl.
 */
int defTlcParams_Access_DataStruct_Inspc(DefPortTypes_emC* portInfo_tlcParam
  , char const* keys_tlcParam[5], void const* values_tlcParam[5]
  , char buffer_tlcParam[500], int zBuffer_tlcParam
  , char header_param[200]
  , StringJc typeName_param
);




/**Accesses the prepared data.
 * Thiz contains the given address and number of bytes. 
 * Both is set and tested in [[initGet_Access_DataStruct_Inspc(...)]].
 * Hence only a simple memcpy is neccesary to set the output data
 * The parameter determines the type and size of the outport.
 * The simulation engine checks whether the output type is proper to the wired connection in the model.
 * @param y_y address to the output data, type and size is proper checked on init and by the model. 
 * @simulink Object-FB, no-thizInit, no-thizStep.
 */
inline void get_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s* thiz, void* y_y) { 
  memcpy(y_y, thiz->addr, thiz->zBytes); 
}




/**TODO
 * @simulink init.
 */
inline bool initSet_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s* thiz, StringJc typeName_param, struct UserHead_DataStructMng_Inspc_t* data) {
  return init_Access_DataStruct_Inspc(thiz, &thiz->fblockInfo->entries[thiz->fblockInfo->ixInputStep], true, typeName_param, data, null);
}

/**TODO
 * @simulink Object-FB, no-thizInit, no-thizStep.
 */
inline void set_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s* thiz, void const* x) { memcpy(thiz->addr, x, thiz->zBytes); }




/**For Object-FB for the triggered operations. ctor without type.
 * @simulink ctor.
 */
inline Access_DataStruct_Inspc_s* ctorTrg_Access_DataStruct_Inspc(ObjectJc* othiz, float Tstep, struct DefPortTypes_emC_t const* fblockInfo) {
  return ctor_Access_DataStruct_Inspc(othiz, null_StringJc, Tstep, fblockInfo);
}

/**For Object-FB for the triggered operations. Type should be a int16[2]. Port types are not significant for that.
 * @simulink init.
 */
inline bool initTrg_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s* thiz, StringJc typeName_param, StringJc typeDataIn_param, StringJc datapath_param, struct UserHead_DataStructMng_Inspc_t* data) {
  #ifndef __ignoreInCheader_zbnf__
  Entry_DefPortType_emC typeOfVar = { 'S', 2, 0, 1,{ 2 } }; //type of the variable instead port type. It is int16[2]
  return init_Access_DataStruct_Inspc(thiz, &typeOfVar, false, typeName_param, data, null);
  #endif//__ignoreInCheader_zbnf__
}

/**The callFn increments the var[0] by 4 to notify execution of trgFn if shouldCall.
 * The var[0].bit1 mirrors the shouldCall state.  If var[0].bit0 ==1, it is positive-edge-triggered.
 * By viewing the var[0] it can be estimate how often the trigger is given (it counts by 4).
 * @simulink Object-FB, no-thizInit, no-thizStep.
 */
inline void callFn_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s* thiz, bool shouldCall) {
  int16* var = (int16*)thiz->addr;
  if (shouldCall && (var[0] & 0x3) !=0x3) {   //either rising edge detect: 01, or state quest: 10, 00 
    var[0] = var[0] + 4;
    var[0] |= 2;          //set flag to detect rising edge. Result in Bit10== 11 on edge control. 
  }
  if (!shouldCall) {
    var[0] &= ~2;   //clear mirror.
  }
}



/**The trgFn checks if var[0] was incremented by 4.
 * It sets var[1] with var[0] to trigger only one time on changed var[0].
 * @simulink Object-FB, no-thizInit, no-thizStep, fnCallTrg.
 */
inline bool trgFn_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s* thiz) {
  int16* var = (int16*)thiz->addr;
  if ((var[0] & ~0x3) != (var[1] & ~0x3)) {
    var[1] = var[0];       //executes only 1 time on more as one call invocations too.
    return true;  //executes a function call in simulink
  }
  else {
    return false;
  }
}






#endif // __Access_DataStruct_Inspc_h__
