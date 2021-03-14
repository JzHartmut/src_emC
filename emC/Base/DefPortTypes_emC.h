#ifndef __emC__DefPortTypes_emC_h__
#define __emC__DefPortTypes_emC_h__
#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>

/*@CLASS_C DefPortType_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This struct can be filled by any static operation of a class to determine about numeric types and array sizes of ports.
*/
typedef struct Entry_DefPortType_emC_t
{
  /**The type. The type characters of Java are used: B1S2I4J8FD for int8, uint8, int16, uint16, int32, uint32,
  * int64, uint64, float double,
  * ZC for boolean and character (UTF16).
  * sifd (lower case) for adequate complex types.
  * if '?' then DYNAMICALLY_TYPED
  */
  char type;

  /**Size of the type in byte.
   * Maybe only set, never read.
  */
  uint8 sizeType;

  /**If this value is not 0, then the port should be set newly with the given information. */
  #define newDefined_Entry_DefPortType_emC 0x8000
  #define mPortKind_Entry_DefPortType_emC 0x7fff
  uint16 newDefined_Tstep_Tinit;

  /**isu for Input init, step, update
   * t for thiz-input
   * IS for Output Init, step
   * @ thiz-Output init
   * T thiz-Output step
   * 
   */




  /**0=scalar. 1 ..5: size of dimension in [[sizeArray+Entry_QueryPortType_emC]].
  * If >5 then sizeArray contains a pointer to a uint32 [...], cast necessary:
  * -1 then DYNAMICALLY_SIZED
  */
  int16 dimensions;


  /**sizes for up to 5 dimensionens. If more as 5 dimensions are need, store it after this struct
  * as enhancement of this array. 0= Dimension not existing. */
  uint16 sizeArray[5];

  /**The step time (sample time) of the input. */
  float Tstep;

  /**The index of the sample time related to the Sfn step times.*/
  int32 ixTstepSfn;

  /**It may be set by a string literal by initializing from arguments. 
   * It may be set by a reference inside VariableParam_DataStruct_Inspc_s::name for variable arguments. */
  char const* sName;

  /**It may be set by a string literal by initializing from arguments. 
   * It may be set by a reference inside VariableParam_DataStruct_Inspc_s::name for variable arguments. */
  char const* sType;

  /**If the type is given as bus, the reflection are necessary to check the arrangements of the elements in the bus and in the struct. 
   * Elsewhere this element is null.
   */
  ClassJc const* refl;

} Entry_DefPortType_emC;  //Note: size=6*4




typedef enum EPortType_Entry_DefPortType_emC_t {
  mStepOut_Entry_DefPortType_emC = 0x200
  , mStepIn_Entry_DefPortType_emC = 0x100
  , mOutputFnCall_Entry_DefPortType_emC = 0x80
  , mOutputThizInit_Entry_DefPortType_emC = 0x40
  , mOutputThizStep_Entry_DefPortType_emC = 0x20
  , mOutputStep_Entry_DefPortType_emC = 0x10
, mOutputInit_Entry_DefPortType_emC = 0x08
, mInputStep_Entry_DefPortType_emC =  0x04
, mInputUpd_Entry_DefPortType_emC =   0x02
, mInputInit_Entry_DefPortType_emC =  0x01
, XXXmNotForC_Entry_DefPortType_emC =    0
} EPortType_Entry_DefPortType_emC;


#define mInit_Entry_DefPortType_emC (mOutputThizInit_Entry_DefPortType_emC | mOutputInit_Entry_DefPortType_emC | mInputInit_Entry_DefPortType_emC)



/**This type is only used as pointer for reflection and debug viewing. 
 * It is never used to store something.
 * Reason: The content is not able to view in debugger and reflection if only 1 instance is used on 'DefPortTypes_emC#entries'
 */
typedef struct Entry_DefPortType_emC_20_t {
  Entry_DefPortType_emC e[20];
} Entry_DefPortType_emC_20_s;






/**Data definition for port properties, especially for Simulink Sfunctions.
 * This struct should included in the following definition:
 * ,,struct { DefPortTypes_emC head; Entry_DefPortType_emC __data__[<&return.nrofPorts>-1]; } __defPortTypes;
 * In this case the __data__ followes the element entries[1] immediately in the memory layout.
 * Note: The size of this struct is able to divide by 8. It is important for alignment.
 */
typedef struct DefPortTypes_emC_t
{ 
  /**The fastest sample time. */
  float TstepMin;
  
  /**Number of the first port which has the minimal sample time. Positive: Inport. Negative: Outport.*/
  int8 ixInOutTstep;

  /**Index in the Sfn sample time indices of the fastest sample time. */
  int8 ixStepSfnMin;
  int8 nrofInputs, nrofOutputs;

  /**Indices of the ports in entries. @pos:8*/
  int8 ixInputStep, ixInputStep2, ixInputInit, ixInputUpd, ixInputVarg, ixInputThiz;
  int8 ixOutputStep, ixOutputStep2, ixOutputInit, ixOutputVarg; 
  
  /**Index of the output pin for thiz. If -1 then no thiz output. Initial set from the arguments, 
   * may be modified by a @ simulink defPortTypes routine. 
   */
  int8 ixOutputThizInit, ixOutputThizStep;
  
  /**Either inputs or outputs are varg, nor both. */
  int8 nrofVargsInit, nrofVargsStep, _d1, _d2;

  /**Number of variable Inputs for Step, Upd etc. It should be adequate number of Bits in the Bit masks.*/
  //int8 nrVargInputStep, nrVargInputUpd, nrVargInputInit, nrVargOutputStep, nrVargOutputInit; 

  /**Mask for up to 32 pins as step, init etc. pins. */
  int32 mInputStep, mInputUpd, mInputInit, mOutputStep, mOutputInit;

  /**Especially only for DataStructMng: Data inputs in init, it does not contain the inherit and chain input. */
  int32 mInputDataInit;

  /**If variable arguments are used, it should be determine by a C routine. 
   * This mask bit shows which pins are for Init time and which are for step time.
   */ 
  int32 mInputVargInit, mInputVargStep, mOutputVargInit, mOutputVargStep;

  int32 bitsParamTunable;

                                                               /**The number of elements of entries. */
  int16 ctInit;
  int16 zEntries;

  /**The full path of the block in the model. */
  char pathBlock[512];

  Entry_DefPortType_emC_20_s* pEntries;

  /**Array of all entries following, use a struct definition to create the correct array length. */
  Entry_DefPortType_emC entries[1];
} DefPortTypes_emC;


typedef enum EDefPortTypes_emC_t
{
  kSetFromArg_EPropagatePortTypes_emC = 1
  , kSetType_EPropagatePortTypes_emC = 2
  , kSetSize_EPropagatePortTypes_emC = 3
  , kSetComplex_EPropagatePortTypes_emC = 4
  /**Set if the portinfo is read from the model. All ports are set. */
  , kRun_EPropagatePortTypes_emC = 5
} EDefPortTypes_emC;



void ctor_DefPortTypes_emC  (  DefPortTypes_emC* thiz, int nrofAdditionalElements);


/**Sets all information for one port. 
 * @param ix index in the entries. For outports it should be >= nrofInputs.
 * @param io: Note apply this routine to outputs only if all inputs are set.
 */
void set_DefPortTypes_emC  (  DefPortTypes_emC* thiz, int ix, char cType, char const* sName, ClassJc const* refl, char const* sType, int zArray, EPortType_Entry_DefPortType_emC io);







#endif  // __emC__DefPortTypes_emC_h__

