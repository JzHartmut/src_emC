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
  */
  char type;

  /**Size of the type in byte.
  */
  uint8 sizeType;

  /**If this value is not 0, then the port should be set newly with the given information. */
  uint8 newDefined;

  /**0=scalar. 1 ..5: size of dimension in [[sizeArray+Entry_QueryPortType_emC]].
  * If >5 then sizeArray contains a pointer to a uint32 [...], cast necessary:
  */
  uint8 dimensions;


  /**sizes for up to 5 dimensionens. If more as 5 dimensions are need, store it after this struct
  * as enhancement of this array. 0= Dimension not existing. */
  uint32 sizeArray[5];

  /**The step time (sample time) of the input. */
  float Tstep;

  /**The index of the sample time related to the Sfn step times.*/
  int32 ixTstepSfn;

} Entry_DefPortType_emC;  //Note: size=6*4


/**Parses the type or name string to detect a type.
 * * If the type is emtpy (NULL_StringJc) then the name till a ':' is used to parsed. 
 * * A character D F J I S B designates double, float, int64, int32, int16, int8. That are the same type chars as in Java usual used. 
 * * A character U W V is the unsigned form of uint32, uint16, uint8
 * * A character d f j i s b is the complex variant of double, float, int64, int32, int16, int8. 
 * * A character C Z is char8 and boolean as int8, same as in Java
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
char const* parse_Entry_DefPortType_emC  ( Entry_DefPortType_emC* thiz, StringJc type, StringJc name, int* posStartName, ThCxt* _thCxt);


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
  
  /**Number of that port which has the first minimal sample time. Negative: Output port.*/
  int16 ixInputStepMin;

  /**Index in the Sfn sample time indices of the fastest sample time. */
  int16 ixStepSfnMin;



  /**Indices of the ports in entries. */
  int16 ixInputStep, ixInputStep2, ixInputUpd, ixInputInit, nrofInputs;
  int16 ixOutputStep, ixOutputStep2, ixOutputInit, ixOutputThiz, nrofOutputs;  //Note: pos=8

  int32 bitsParamTunable;

                                                               /**The number of elements of entries. */
  int16 zEntries, _1_;

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
  , kRun_EPropagatePortTypes_emC = 5
} EDefPortTypes_emC;



void ctor_DefPortTypes_emC(DefPortTypes_emC* thiz, int nrofAdditionalElements);



#endif  // __emC__DefPortTypes_emC_h__

