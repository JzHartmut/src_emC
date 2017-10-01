#ifndef __InputValues_Inspc_h__
#define __InputValues_Inspc_h__
#include <os_types_def.h>
#include <Jc/ObjectJc.h>
#include <Jc/ReflectionJc.h>
#include <Fwc/fw_String.h>

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

  #ifndef refl
    //don't generate reflection for this block.

    ClassJc clazz;

    FieldJc_Y fields;

    FieldJc _fields[17 - zFieldsInHead_FieldJc_Y];
  #endif//refl

} InputValues_Inspc;

/**Allocate and construct. */
InputValues_Inspc* create_InputValues_Inspc();

/**Constructs and completes the instance. 
 * Some attributes should be set before:
 * TODO rename it to init_InputValues_Inspc, the ctor should do only basic initalizing.
 * * dataType
 */

void ctor_InputValues_Inspc(InputValues_Inspc* thiz);


/**Register it in a DataNode_Inspc, invoke one time after create. */
bool registerReflection_InputValues_Inspc(InputValues_Inspc* thiz, struct DataNode_Inspc_t* reflNode);



void free_InputValues_Inspc(InputValues_Inspc* thiz);



#endif //__InputValues_Inspc_h__
