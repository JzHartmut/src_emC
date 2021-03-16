#ifndef __DataStruct_Inspc_h__
#define __DataStruct_Inspc_h__
#include <applstdef_emC.h>
#include <emC/Inspc/FB/DataStructBase_Inspc.h>
#include <emC/Base/Object_emC.h>
#include <emC/Base/DefPortTypes_emC.h>
#include <emC/Jc/ReflectionJc.h>
#include <emC/OSAL/os_file.h>
#include <emC/base/MemC_emC.h>
#include <string.h> //memcpy

struct DataStruct_Inspc_t;
struct DefPortTypes_emC_t;
struct UserHead_DataStructMng_Inspc_t;


struct Access_DataStruct_Inspc_t;

struct DataStructMng_Inspc_t;



/* @ CLASS_C UserHead_DataStructMng_Inspc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This is the super class of all generated DataStruct.
* The first attribute thiz1 refers to the Mng data only for developer debug, it is visible wiht password only.
*/
typedef struct UserHead_DataStructMng_Inspc_t
{ /**The ObjectJc base is part of the user Data. */
  union { ObjectJc object; } base;

  struct DataStructMng_Inspc_t* thiz1;

} UserHead_DataStructMng_Inspc;

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_UserHead_DataStructMng_Inspc;
#endif



/**This is the head struct for the users data.
* After this struct some more int32 fields are allocated for any number of user data.
*/
typedef struct UserData_DataStructMng_Inspc_t
{ /**The ObjectJc base is part of the user Data. */
  union { UserHead_DataStructMng_Inspc super; ObjectJc object; } base;

#define zBaseVal_UserData_DataStructMng_Inspc 20

  /**Input buffer for at least 12 different value (cluster), maybe a single float, or a float_comlex, or a vector etc.
  * Correct view organized in the reflection.
  */
  int32 val[zBaseVal_UserData_DataStructMng_Inspc];
} UserData_DataStructMng_Inspc;


#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_UserData_DataStructMng_Inspc;
#endif



/* @ CLASS_C DataStruct_Inspc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


typedef struct Mem_UserData_DataStructMng_Inspc_t { UserData_DataStructMng_Inspc* addr; intptr_t val; } Mem_UserData_DataStructMng_Inspc;

//typedef STRUCT_MemC(UserData_DataStructMng_Inspc) Mem_UserData_DataStructMng_Inspc;


/**This is the core block for an input block of any values which are accessible via the inspector engine.

*/
typedef struct DataStruct_Inspc_t
{
  /**It is the ObjectJc base necessary for Sfunction. */
  union { DataStructBase_Inspc_s super; ObjectJc object; } base;

  int32 errorPort;

  /**ct dn from first init. For Mng: Wait for setting baseDataMng from a base.*/
  int32 ctInit;

  /**Reference to the data to get and set, derived from the mng at userDataBlock->data */
  Mem_UserData_DataStructMng_Inspc userData;

  /**Reference to the fields of the DataStructMng_Inspc */
  ClassJc const* clazz;

  /**The name of the chain member*/
  char subName[16];

  /**Boolean, 1 = super Input exists as input after zInputsData. */
  uint32 mBitInheritInput;

  /**Boolean, 1 = chain Input exists as input after super Input or zInputsData. */
  uint32 mBitChainInput;



  struct DataStruct_Inspc_t* prevChain;
  


} DataStruct_Inspc;

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_DataStruct_Inspc;
#endif



/**Constructs and completes the instance of a chained DataStruct (extension)
 * @simulink ctor
 */
void ctor_DataStruct_Inspc(DataStruct_Inspc* thiz, DefPortTypes_emC* fblockInfo
  , StringJc subName_param
  , char const inputDefinition[500]
  );



/**Constructs and completes the instance.
 * @simulink dtor
 */
void dtor_DataStruct_Inspc(DataStruct_Inspc* thiz);





/**Routine determines port properties
* @param defPortTypes contains array reference and length of array.
*    It is filled with the given port properties on call. Because of type the information are complemented.
*    With the complemented information the port initialization is done in mdlInizializeSizes
* @param typeName_param determines the type of the output. If "Type*" then the type is a handle.
* @simulink defPortTypes.
*/
char const* definePortType_DataStruct_Inspc(DefPortTypes_emC* defPortTypes, EDefPortTypes_emC cause
  , char const inputDefinition[500]
);



/**Routine to determine RTW param for tlc (Simulink Coder).
* @param keys_tlcParam array will be filled with some key names as const literals. 
*        [0] Will be set with "typeData_param" for the output type.
* @param values_tlcParams array will be filled with the char const* reference to the value inside buffer_tlcParam
*        [0] will be set with the type name if typeOut_param contains an "*" on end. 
*        [0] will be set emtpy if typeOut_param does not contain a Reference type.
* @param buffer_tlcParam char[] as buffer for all param values, the buffer will be filled tight, with 0 between the items. 
* @return number of chars used in buffer_tlcParam.
* @simulink defTlcParam_excl.
*/
int defTlcParams_DataStruct_Inspc(DefPortTypes_emC* portInfo_tlcParam
  , char const* keys_tlcParam[3], void const* values_tlcParam[3], char types_tlcParam[2]
  , char buffer_tlcParam[100], int zBuffer_tlcParam
  , char subName_param[10]
);



/**Initializes. It stores the given port types.
 * @param prevchain: For concatenation.
 * @param thiz_y  The thiz pointer should firstly offered if init is run the first time. no-thizInit on Object-FB.
 *                Note: this is only convinient if aggregations are not neccessary one another. Here it is ok.
 * @param ... void const* varg[12];
 * @simulink init.
 */
bool init_DataStruct_Inspc(DataStruct_Inspc* thiz 
  , DataStruct_Inspc** thizout_y
  , ...
  );



/**Stores the given values from inputs. The type of inputs are determined by [[init_DataStruct_Inspc(...)]].
* @param ... void const* varg[12];
* @simulink update.
*/
void update_DataStruct_Inspc(DataStruct_Inspc* thiz
//  , void const* const vport_x[32]
, ...
);



/**Stores the given values from inputs. The type of inputs are determined by [[init_DataStruct_Inspc(...)]].
* @simulink Object-FB, no-thizStep, no-thizInit.
*/
inline void step_DataStruct_Inspc(DataStruct_Inspc* thiz){} //empty.



/* @ CLASSC DataStructMng_Inspc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@q*/



//struct DataNode_Inspc_t;




/**This is the core block for an input block of any values which are accessible via the inspector engine. 

 */
typedef struct DataStructMng_Inspc_t
{ 
  /**It is the ObjectJc base necessary for Sfunction. */
  union { DataStruct_Inspc super; ObjectJc object; } base;

  /**The data which are created to store, determined by the parameter of init. 
   * If this element is null, it is not initialized yet or it is a base mng. 
   */
  Mem_UserData_DataStructMng_Inspc userDataBlock;

  uint32 hUserDataBlock;

  /**The mng of the super instance, null or ==thiz if is the ObjectJc-based class. */
  struct DataStructMng_Inspc_t* superTypeMng;

  /**The mng of the derived instance which contains the data. */
  struct DataStructMng_Inspc_t* subTypeMng_dbg;


  int32 nrofDataSuperMng;

  int32 ixDataLast;

  /**Zähler falls irgendwas in config-File nicht stimmt, sollte auf 0 stehen. */
  int32 errorCfg;

  int32 stateGen;

  /**It contains the path from parameter.  */
  FileDescription_OSAL filegen;

  int ctGenSrc;
  
  /**Registered Access_DataStruct_Inspc*/
  struct { 
    int zdata;
    struct Access_DataStruct_Inspc_t* data[100];
  } setData;

#ifndef refl
  //don't generate reflection for this block.

    ClassJc clazz;

    FieldJc_Y* fields;

    //FieldJc _fields[50 - zFieldsInHead_FieldJc_Y]; //TODO 13

    struct {
      ObjectArrayJc head;
      ClassOffset_idxVtblJc clazz;
    } superclass;



  #endif//refl

} DataStructMng_Inspc;

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_DataStructMng_Inspc;
#endif





/**Constructs and completes the instance.
 * @param fbockInfo it should be completely set, in Sfunctions in the mdlStart(...). There setPortInfo(...) from the Sfn-Wrapper was called.
 * @simulink ctor
 */
void ctor_DataStructMng_Inspc(DataStructMng_Inspc* thiz, DefPortTypes_emC* fblockInfo
, char const inputDefinition[500]
, int inherit_param, int chain_param
);

/**Constructs and completes the instance.
* @simulink dtor
*/
void dtor_DataStructMng_Inspc(DataStructMng_Inspc* thiz);

/**Routine determines port properties
* @param defPortTypes contains array reference and length of array.
*    It is filled with the given port properties on call. Because of type the information are complemented.
*    With the complemented information the port initialization is done in mdlInizializeSizes
* @param typeName_param determines the type of the output. If "Type*" then the type is a handle.
* @simulink defPortTypes.
*/
char const* definePortType_DataStructMng_Inspc(DefPortTypes_emC* defPortTypes, EDefPortTypes_emC cause
  , char const inputDefinition[500]
  , int inherit_param, int chain_param
);


/**Initializes. It stores the given port types.
 * @param x variable number of inputs.  
 * @param data_y: The data pointer in init time for aggregation. 
 * @param ... void const* varg[12];
 * @simulink init
 */
bool init_DataStructMng_Inspc(DataStructMng_Inspc* thiz
  //, DataStructMng_Inspc* subTypeMng, struct DataStruct_Inspc_t* prevChain
  , StringJc dirGenSource_param
  , StringJc typeData_param
  //, void const* const vport_x[32]
  , UserHead_DataStructMng_Inspc** data_y
  , ...
);



/**Routine to determine RTW param for tlc (Simulink Coder).
* @param keys_tlcParam array will be filled with some key names as const literals. 
*        [0] Will be set with "typeData_param" for the output type.
* @param values_tlcParams array will be filled with the char const* reference to the value inside buffer_tlcParam
*        [0] will be set with the type name if typeOut_param contains an "*" on end. 
*        [0] will be set emtpy if typeOut_param does not contain a Reference type.
* @param buffer_tlcParam char[] as buffer for all param values, the buffer will be filled tight, with 0 between the items. 
* @return number of chars used in buffer_tlcParam.
* @simulink defTlcParam_excl.
*/
int defTlcParams_DataStructMng_Inspc(DefPortTypes_emC* portInfo_tlcParam
  , char const* keys_tlcParam[3], void const* values_tlcParam[3], char types_tlcParam[2]
  , char buffer_tlcParam[100], int zBuffer_tlcParam
  , char const typeData_param[40]
  , int inherit_param, int chain_param
);






/**Stores the given values from inputs. The type of inputs are determined by [[init_DataStructMng_Inspc(...)]].
 * @param ... void const* varg[12];
 * @simulink update.
 */
void update_DataStructMng_Inspc(DataStructMng_Inspc* thiz
//  , void const* x1, void const* x2, void const* x3, void const* x4, void const* x5, void const* x6
//, void const* const vport_x[32]
  , ...
);


void genSourceContent_DataStructMng_Inspc(DataStructMng_Inspc* thiz);



/**Stores the given values from inputs. The type of inputs are determined by [[init_DataStructMng_Inspc(...)]].
* @simulink Object-FB, no-thizStep.
*/
inline void step_DataStructMng_Inspc(DataStructMng_Inspc* thiz) { //, int32* error_y){
  if (--thiz->ctGenSrc == 0) { //start only if >0 before.
    genSourceContent_DataStructMng_Inspc(thiz);
  }
  else if (thiz->ctGenSrc < 0) {
    thiz->ctGenSrc = -1;  //hold on -1/-2
  }
  //*error_y = thiz->errorPort;
}



/**Registeres an appended Access_DataStruct_Inspc. Note: It is inlined because prevented too much dependencies on linked time for usage. */
inline void registerSetData_DataStructMng_Inspc(DataStructMng_Inspc* thiz, struct Access_DataStruct_Inspc_t* data) {
  int ix = thiz->setData.zdata;
  if (ix < ARRAYLEN_emC(thiz->setData.data) - 1) {
    thiz->setData.zdata = ix + 1;  //maybe use atomic access
    thiz->setData.data[ix] = data;
  }
}



/**Works in Tinit
 * @param in pointer uint32-handle in Sfunction
 * @param typeData_param Used to check the in type. Used for generated code to include the header genSrcInspc/<&typeData_param> and to cast. 
 * @param header_param: Unused in this source for simulation, used in tlc-File and in Sfunction-Wrapper for generated code to include any header.
 * @param out_y Any reference based on ObjectJc
 * @XXXsimulink Operation-FB, try-catch.
 * 
 */
void checkAndCast_DataStructMng_Inspc(UserHead_DataStructMng_Inspc* in, StringJc typeData_param, StringJc header_param, UserHead_DataStructMng_Inspc** out_y);


#endif //__DataStruct_Inspc_h__
