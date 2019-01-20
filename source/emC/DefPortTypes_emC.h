#ifndef __emC__DefPortTypes_emC_h__
#define __emC__DefPortTypes_emC_h__
#include <applstdef_emC.h>

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
  #define newDefined_Entry_DefPortType_emC 0x80
  #define mPortKind_Entry_DefPortType_emC 0x7f
  uint8 newDefined_Tstep_Tinit;

  /**0=scalar. 1 ..5: size of dimension in [[sizeArray+Entry_QueryPortType_emC]].
  * If >5 then sizeArray contains a pointer to a uint32 [...], cast necessary:
  * -1 then DYNAMICALLY_SIZED
  */
  uint8 dimensions;


  /**sizes for up to 5 dimensionens. If more as 5 dimensions are need, store it after this struct
  * as enhancement of this array. 0= Dimension not existing. */
  uint16 sizeArray[6];

  /**The step time (sample time) of the input. */
  float Tstep;

  /**The index of the sample time related to the Sfn step times.*/
  int32 ixTstepSfn;


  char const* sType;
  char const* sName;

} Entry_DefPortType_emC;  //Note: size=6*4




typedef enum EPortType_Entry_DefPortType_emC_t {
  mOutputFnCall_Entry_DefPortType_emC = 0x40
, mOutputThiz_Entry_DefPortType_emC = 0x20
, mOutputStep_Entry_DefPortType_emC = 0x10
, mOutputInit_Entry_DefPortType_emC = 0x08
, mInputStep_Entry_DefPortType_emC =  0x04
, mInputUpd_Entry_DefPortType_emC =   0x02
, mInputInit_Entry_DefPortType_emC =  0x01
, mNotForC_Entry_DefPortType_emC =    0
} EPortType_Entry_DefPortType_emC;



/**Parses the type or name string to detect a type.
 * * If the type is emtpy (NULL_StringJc) then the name till a ':' is used to parsed. 
 * * A character D F J I S B designates double, float, int64, int32, int16, int8. That are the same type chars as in Java usual used. 
 * * A character U W V is the unsigned form of uint32, uint16, uint8
 * * A character d f j i s b is the complex variant of double, float, int64, int32, int16, int8. 
 * * A character C Z is char8 and boolean as int8, same as in Java
 * * If TYPENAME* is found, the type is returned as 'U', a handle for simulink. 
 * * Not supported yet 2018-10: z for zero-terminated char*, s for StringJc, c for char16
 * * An array designation can be written as [12,23], as [12][23], as [12[23, as 12,23 or as 12[23. 
 * All of that is admissible because the [ , ] will be skipped, only the number is relevant.
 * Up to 5 array dimensions. 
 * * The type can start with array dimensions or with the type char. A mix is admissible too.
 * * For example "3F" and "F3", both it is a float[3]. "3F2" is a float[3][2].
 *
 * * @param type can be NULL_StringJc, then name till ':' is used. Elsewhere the type designation.
 * * @param name only used if type is NULL_StringJc
 * * @param posStartName null is admissible. If not null, set to position after ':' in name, if type is NULL_StringJc, elsewhere set to 0. 
 * * @return an error message on format error. Elsewhere null.
 */
char const* parse_Entry_DefPortType_emC  ( Entry_DefPortType_emC* thiz, StringJc typeName, ThCxt* _thCxt);


bool checkType_Entry_DefPortType_emC(Entry_DefPortType_emC* thiz, ClassJc const* reflectionType);



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
  int8 ixInputStep, ixInputStepVarg, nrInputStepVarg, ixInputThiz;
  int8 ixInputInit, ixInputInitVarg, nrInputInitVarg, __dInit;
  int8 ixInputUpd, ixInputUpdVarg, nrInputUpdVarg, __dUpd;
  int8 ixInputStep2, ixInputStep2Varg, nrInputStep2Varg, __dStep2;
  
  int8 ixOutputStep, ixOutputStep2, ixOutputInit, ixOutputThiz;

  int32 mInputStep, mInputUpd, mInputInit, mOutputStep, mOutputInit;

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



void ctor_DefPortTypes_emC(DefPortTypes_emC* thiz, int nrofAdditionalElements);


inline void set_DefPortTypes_emC(DefPortTypes_emC* thiz, int ix, char cType, char const* sName, char const* sType, int zArray, EPortType_Entry_DefPortType_emC io) {
  thiz->entries[ix].type = cType;
  if(zArray <0){ thiz->entries[ix].dimensions = -1; }
  else if(zArray ==0){ thiz->entries[ix].dimensions = 1; thiz->entries[ix].sizeArray[0] = 1; }
  else { thiz->entries[ix].dimensions = 1; thiz->entries[ix].sizeArray[0] = zArray; }
  switch (io) {
  case mOutputInit_Entry_DefPortType_emC: thiz->mOutputInit |=1; break;
  case mOutputStep_Entry_DefPortType_emC: thiz->mOutputStep |=1; break;
  case mInputInit_Entry_DefPortType_emC:  thiz->mInputInit |=1; break;
  case mInputUpd_Entry_DefPortType_emC:   thiz->mInputUpd |=1; break;
  case mInputStep_Entry_DefPortType_emC:  thiz->mInputStep |=1; break;
  }
  thiz->entries[ix].newDefined_Tstep_Tinit |= io;
  thiz->entries[ix].sName = sName;
  thiz->entries[ix].sType = sType;

}



/**
 * The name is the last identifier string in the name_param after any other designation
 */
StringJc extractName_TypeName_emC(StringJc name_param, ThCxt* _thCxt);


/**
 * Syntax of name: [{-###|!}:] [F:|U:|I:|...|TYPE*[:]] (StructType*)datpath->name 
 * The type is the string after any -19!: as identifier
*/
StringJc extractType_TypeName_emC(StringJc name_param, ThCxt* _thCxt);

/**
* Syntax of name: [{-###|!}:] [F:|U:|I:|...|TYPE*[:]] (StructType*)datpath->name
* The type is the string after any -19!: as identifier
*/
StringJc extractStructType_TypeName_emC(StringJc name_param, ThCxt* _thCxt);

/**
* Syntax of name: [{-###|!}:] [F:|U:|I:|...|TYPE*[:]] (StructType*)datpath->name
* The type is the string after any -19!: as identifier
*/
StringJc extractAccessPath_TypeName_emC(StringJc name_param, ThCxt* _thCxt);

/**Returns 'i' for an Tinit handle in an DataStruct_Inspc SFblock. Then a ! TYPE*  is found.
 * returns '!' for an init value without type.
 * return ' ' for a non-initial-only value.
 * Syntax of name: [{-###|!}:] [F:|U:|I:|...|TYPE*[:]] (StructType*)datpath->name
 *
 */
char extractInitialize_TypeName_emC(StringJc name_param, ThCxt* _thCxt);



int extractAccessRights_TypeName_emC(StringJc name_param, ThCxt* _thCxt);




#endif  // __emC__DefPortTypes_emC_h__

