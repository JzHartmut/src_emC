#ifndef __InputValues_Inspc_h__
#define __InputValues_Inspc_h__
#include <applstdef_emC.h>
#include <emC/Object_emC.h>
//#include <Jc/ObjectJc.h>
#include <Jc/ReflectionJc.h>
//#include <emC/String_emC.h>

struct DataNode_Inspc_t;





/**This is the core block for an input block of any values which are accessible via the inspector engine. 

 */
typedef struct InputValues_Inspc_t
{ ObjectJc base;
  
  
  /**Input buffer for at least 12 different value (cluster), maybe a single float, or a float_comlex, or a vector etc.
   * Correct view organized in the reflection. 
   */
  int32 val[240];

  /**Size of 1 element internally. The x[240] is x[12][20] really. Use 1 dimension to inspect. */
  #define kSizeX_InputValues_Inspc 20

  /**Zähler falls irgendwas in config-File nicht stimmt, sollte auf 0 stehen. */
  int32 errorCfg;

  int32 bReflRegistered;

  /**Instance name in Reflection Node Tree. */
  char nameRefl[32];

  int32 nrofElements[12];

  int8 dataType[16];

  int32 dataTypeSmlk[12];

  /**Parametrized signal identifier. */
  char names[12][32];

  int32 nrofbytesType[12];

  #ifndef refl
    //don't generate reflection for this block.

    ClassJc clazz;

    FieldJc_Y fields;

    FieldJc _fields[17 - zFieldsInHead_FieldJc_Y];
  #endif//refl

} InputValues_Inspc;

/**Allocate and construct. */
InputValues_Inspc* create_InputValues_Inspc();

void ctorXXX_InputValues_Inspc(InputValues_Inspc* thiz);


/**Constructs and completes the instance. 
 * @simulink ctor
 */
void ctor_InputValues_Inspc(InputValues_Inspc* thiz);

/**Initializes. It stores the given port types. 
 * @simulink init
 */
char const* init_InputValues_Inspc(InputValues_Inspc* thiz, struct DataNode_Inspc_t* dataNode
  , StringJc nameRefl_param
  , StringJc n1_param, StringJc n2_param, StringJc n3_param, StringJc n4_param, StringJc n5_param, StringJc n6_param
  , StringJc n7_param, StringJc n8_param, StringJc n9_param, StringJc n10_param, StringJc n11_param, StringJc n12_param
  , Entry_DefPortTypeJc* portTypes);

/**Stores the given values from inputs. The type of inputs are determined by [[init_InputValues_Inspc(...)]].
 * @simulink Object-FB, no-thizInit, no-thizStep
 */
void step_InputValues_Inspc(InputValues_Inspc* thiz
     , void const* x1, void const* x2, void const* x3, void const* x4, void const* x5, void const* x6
     , void const* x7, void const* x8, void const* x9, void const* x10, void const* x11, void const* x12
     );


/**Register it in a DataNode_Inspc, invoke one time after create. */
bool registerReflection_InputValues_Inspc(InputValues_Inspc* thiz, struct DataNode_Inspc_t* reflNode);



void free_InputValues_Inspc(InputValues_Inspc* thiz);



#endif //__InputValues_Inspc_h__
