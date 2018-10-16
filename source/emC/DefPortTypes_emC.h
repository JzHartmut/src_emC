#ifndef __emC__DefPortTypes_emC_h__
#define __emC__DefPortTypes_emC_h__
#include <applstdef_emC.h>

/*@CLASS_C DefPortTypeJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This struct can be filled by any static operation of a class to determine about numeric types and array sizes of ports.
*/
typedef struct Entry_DefPortTypeJc_t
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

  /**0=scalar. 1 ..5: size of dimension in [[sizeArray+Entry_QueryPortTypeJc]].
  * If >5 then sizeArray contains a pointer to a uint32 [...], cast necessary:
  */
  uint8 dimensions;


  /**sizes for up to 5 dimensionens. If more as 5 dimensions are need, store it after this struct
  * as enhancement of this array. 0= Dimension not existing. */
  uint32 sizeArray[5];

} Entry_DefPortTypeJc;  //Note: size=6*4



                        /**Data definition for port properties, especially for Simulink Sfunctions.
                        * This struct should included in the following definition:
                        * ,,struct { DefPortTypesJc head; Entry_DefPortTypeJc __data__[<&return.nrofPorts>-1]; } __defPortTypes;
                        * In this case the __data__ followes the element entries[1] immediately in the memory layout.
                        * Note: The size of this struct is able to divide by 8. It is important for alignment.
                        */
typedef struct DefPortTypesJc_t
{ /**The number of elements of entries. */
  int16 size;
  /**Indices of the ports in entries. */
  int16 ixInputStep, ixOutputInit, ixOutputStep;  //Note: pos=8

                                                  /**Array of all entries following, use a struct definition to create the correct array length.
                                                  */
  Entry_DefPortTypeJc entries[1];
} DefPortTypesJc;


typedef enum EDefPortTypesJc_t
{
  kSetFromArg_EPropagatePortTypesJc = 1
  , kSetType_EPropagatePortTypesJc = 2
  , kSetSize_EPropagatePortTypesJc = 3
  , kSetComplex_EPropagatePortTypesJc = 4
  , kRun_EPropagatePortTypesJc = 5
} EDefPortTypesJc;


#endif  // __emC__DefPortTypes_emC_h__

