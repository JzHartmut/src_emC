#ifndef __analyzeLine_Inspc_h__
#define __analyzeLine_Inspc_h__
#include <applstdef_emC.h>
#include <emC/base/DefPortTypes_emC.h>

struct StringPartScanJc_t;

/* @ CLASS_C Param_DataStruct_Insplc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**The basic data common also for TimeSignals_Inspc. */
typedef struct DataStructBase_Inspc_t {

  union { ObjectJc object; } base;

  /**Information about the block in the simulink model. */
  struct DefPortTypes_emC_t const* fBlockInfo;

  /**in heap, persistent buffer for properties of the variable. 
   * It is filled with analyzeVariableDef(...) and used in evalNamesCreateFields(...) */
  struct VariableParam_DataStruct_Inspc_t* varParams;

  /**If sharedMem is used, this is the name. 0 if not used. */
  char nameSharedMem[16];
  
  /**Nr of entries in params. It is the number of assigend variables. */
  int16 zVariable;

  int16 __d[3];

  /**Ref to allocated param information. */
  struct VariableParam_DataStruct_Inspc_Array_t* varParams_debugView;



} DataStructBase_Inspc_s;

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_DataStructBase_Inspc;
#endif





/**Constructor of the common data of TimeSignals_Inspc, DataStruct_Inspc
 * @param ixPort The index in fbInfo for the port where the variable is associated.
 *        It this value is > fbInfo->nrofInputs then it is for output.
 */
void ctor_DataStructBase_Inspc(DataStructBase_Inspc_s* thiz, DefPortTypes_emC* fbInfo, int ixPort
  , int zVariable
  , char const* inputDefinition
);


void dtor_DataStructBase_Inspc(DataStructBase_Inspc_s* thiz);

/**Returns the nrof values necessary fot his given configuration. 
 * Initialized:
 * * thiz->varParams[ixArg].ixField
 * * thiz->varParams[ixArg].nrofBytesValue
 * @return nrof elements int32 for data
 */
int32 evalSizes_DataStructBase_Inspc(DataStructBase_Inspc_s* thiz);


/**Store info in fields. 
 * The FieldJc::offsFieldInStruct is not initialized here because the data arrangement is not known in this operation.
 * reads:
 * * thiz->zVariable: for(ixArg = 0 ... zVariable), used number of thiz->varParams, written fields[ixArg]
 * * thiz->varParams[ixArg + ixPortStart].ePort: Port information
 * * thiz->varParams[ixArg].typeRef: Handle output with that type, used for fields
 * * thiz->varParams[ixArg].accessRights: Used for fields
 * * 
 * writes:
 * * thiz->varParams[ixArg].ixField
 * * thiz->varParams[ixArg].nrofBytesValue
 *  
 * @param ixPortStart The start index of port inside thiz->fBlockInfo.entries which are used as input or output for the variables.
 * @param fields the instance have to be created with at least (ixFieldStart + thiz->zVariable) element. It is filled with the here created fields.
 * @param ixFieldStart first created field position in fields.
 */
void evalNamesCreateFields_DataStructBase_Inspc(DataStructBase_Inspc_s* thiz, FieldJcArray* fields, int ixFieldStart, ThCxt* _thCxt);



/**One Parameter of a variable in the DataStruct_Inspc
 */
typedef struct VariableParam_DataStruct_Inspc_t
{
  int8 accessRights;

  /**The index of the field in the reflection data. Up to 255 fields, no more. */
  uint8 ixField;

  /**For access: Used number of indices for array access. 
   * 0 on scalar or full array. 1 for element access to 1-dim array.*/
  uint8 dimensionUsed;
  
  int8 __d1;

  /**Number of the bytes for the value storing. It is the type size * array size. */
  int16 nrofBytesValue;

  int16 ixInVal;

  Entry_DefPortType_emC* ePort;

  //int16 dimensions;
  //int16 arraySizes[5]; 

  /**Storage for types from calling args (Simulink parameter), but persistent.
  * If "" (typeRef[0]==0) then it is not a reference but a primitive type.
  */
  char typeRef[32];

  /**Storage for names from calling args (Simulink parameter), but persistent. */
  char name[32];

  char structType[32];

} VariableParam_DataStruct_Inspc_s;


/**This type is used as reference type only, it is for debugging. It is only used as VariableParam_DataStruct_Inspc_s*.*/
typedef struct VariableParam_DataStruct_Inspc_Array_t { VariableParam_DataStruct_Inspc_s  d[10]; } VariableParam_DataStruct_Inspc_Array;



int XXXanalyzeLineDef_DataStruct_Inspc(struct StringPartScanJc_t* sscan, Entry_DefPortType_emC const* portInfo, VariableParam_DataStruct_Inspc_s* varInfo
  , char* bufferDataPath, int zBufferDatapath
  , EDefPortTypes_emC cause, ThCxt* _thCxt);

/**Analyzes the given parameter in the text area and sets port info about the signal inputs.
 * This routine is invoked for twice situations:
 * * Define the port properties. That is inside the [[definePortType_DataStruct_Inspc(...).]] There the varArray is null.
 * * Inside ctor. There informations about fields are stored in varArray. The fbInfo are not changed.
 * @param spSrc Input, content of the parameter text area with specified syntax. Points on a definition of a variable. 
 *   It is after a previous ',' or ';'.
 * @param portInfo signal, port definitions. It is read only if varInfo is not null. If varInfo==null, it is casted to not const.
 * @param varInfo destination for the signal properties. Can be null, especially for port initialization.
 *   If is not null, then portInfo is complete, really read only, it is not changed.
 * @param bufferDataPath if given the line can contain a datapath instead of variable name only:
 * @param zBufferDatapath its size, then 'path.to.name' is parsed and stored there..
 * @param cause portInfo is not changed in kRun_EPropagatePortTypes_emC
 * @return
 * On return the current position of spSrc is on the ',' or ';'. Can be checked outside, skip outside.
 */
int parseLineDef_DataStruct_Inspc  ( struct StringPartJc_t* spSrc
  , Entry_DefPortType_emC const* portInfo
  , VariableParam_DataStruct_Inspc_s* varInfo
  , char* bufferDataPath, int zBufferDatapath
  , EDefPortTypes_emC cause, ThCxt* _thCxt);

/**Analyzes the given input parameter text field, used yet for DataStructMng and for TimeSignals_Inspc. 
 * This routine is invoked for twice situations:
 * * Define the port properties. That is inside the [[definePortType_DataStruct_Inspc(...).]] There the varArray is null.
 * * Inside ctor. There informations about fields are stored in varArray. The fbInfo are not changed. 
 * @param sVarDef The content of the parameter text area with specified syntax.
 * @param varArray destination for the variable properties. Can be null.
 *   It is not null in the ctor of ctor_DataStructBase_Inspc(...). 
 *   Especially null for port initialization. Should have zVarArray Elements.
 *   If is not null, then fbInfo is complete and should not be changed. It is in ctor.
 *   If not null, then all elements will be initialized. The port from ixPortStart is associated to varArray[0].
 * @param zVarArray maximal number of slots for signals. At least one.
 * @param fbInfo destination for the signal, port definitions. If varArray not null, then the fbInfo is not changed but used.
 * @param ixPort start index in fbInfo for the ports which are determined by sVarDef. 
 *        Note that the input ports of the fblock starts with 0 and the output ports starts after the inputs, with fbInfo->nrofInputs
 * @param bOutput true then the variables are for output pins.
 * @param cause if kRun... then the fbInfo for port properties is not changed, but compared with the content. The ports are well defined.
 *        But the Entry_DefPortType_emC::name and sType is set, because it is not stored in fbInfo from the model level.
 */
int analyzeVariableDef( StringJc sVarDef
//, VariableParam_DataStruct_Inspc_s* const varArray
, DataStructBase_Inspc_s* dataStructBase_FB
//, int zVariables
, DefPortTypes_emC* fbInfo, int ixPortStart, bool bOutput
, EDefPortTypes_emC cause);

#endif //__analyzeLine_Inspc_h__
