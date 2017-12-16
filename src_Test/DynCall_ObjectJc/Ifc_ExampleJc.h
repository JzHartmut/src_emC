#ifndef __Ifc_ExampleJc_h__
#define __Ifc_ExampleJc_h__
#include <applstdefJc.h>
#include <Jc/ObjectJc.h>




/**The table of dynamic linked routines - virtual routines - of the class DynCall_ExampleJc.
 * @noReflection
 */
typedef struct Vtbl_Ifc_ExampleJc_t
{ /**It starts always with a head. */
  MtblHeadJc head;            

  /**A virtual routine of this class. */
  void (*execute)(ObjectJc* thiz, int arg);
  //MT_execute_DynCall_ExampleJc* execute;
  
  /**Virtual table of the super class of this class. It is only ObjectJc*/
  Mtbl_ObjectJc ObjectJc;

} Vtbl_Ifc_ExampleJc;

extern char const* sign_Vtbl_Ifc_ExampleJc;



#endif  //__DynCall_ObjectJc_h__
