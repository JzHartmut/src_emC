#ifndef __DynCall_ObjectJc_h__
#define __DynCall_ObjectJc_h__
#include <applstdefJc.h>
#include <Jc/ObjectJc.h>


/**A struct which contains the data of this class
 * @vtbl vtbl_DynCall_ExampleJc. Name of the const virtual table for reflection generation.
 */
typedef struct DynCall_ExampleJc_t
{
  ObjectJc object;
  
  char buffer[100];
  
  int lengthBuffer;

  int val;

} DynCall_ExampleJc_s;

extern const ClassJc reflection_DynCall_ExampleJc_s;


//typedef void MT_execute_DynCall_ExampleJc(DynCall_ExampleJc* thiz, int arg); 









/**The table of dynamic linked routines - virtual routines - of the class DynCall_ExampleJc.
 * @noReflection
 */
typedef struct Vtbl_DynCall_ExampleJc_t
{ /**It starts always with a head. */
  MtblHeadJc head;            

  /**A virtual routine of this class. */
  void (*execute)(DynCall_ExampleJc_s* thiz, int arg);
  //MT_execute_DynCall_ExampleJc* execute;
  
  /**Virtual table of the super class of this class. It is only ObjectJc*/
  Mtbl_ObjectJc ObjectJc;

  /**Method table of interfaces. */
  Mtbl_CharSeqJc CharSeqJc;
} Vtbl_DynCall_ExampleJc;

extern char const* sign_Vtbl_DynCall_ExampleJc;




/**A struct with the data of the class ImplIfc_Example
 * which implements Ifc_ExampleJc 
 * @vtbl vtbl_ImplIfc_ExampleJc. Name of the const virtual table for reflection generation.
 */
typedef struct ImplIfc_ExampleJc_t
{
  ObjectJc object;
  
  int val;

} ImplIfc_ExampleJc_s;

extern const ClassJc reflection_ImplIfc_ExampleJc_s;




#endif  //__DynCall_ObjectJc_h__
