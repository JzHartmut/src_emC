#ifndef __Inspc__Target2Proxy_Inspc_h__
#define __Inspc__Target2Proxy_Inspc_h__
#include <emC/InspcTargetSimple/IfcTargetProxy_Inspc.h>


/**Data used for the target handling for Inspector access with Target Proxy.
 *
 */
typedef struct Target2Proxy_Inspc_T
{
  ObjectJc object;

  /**Reference to the exchange data range. It may be located in a Dual Port Memory for immediately access,
   * in a buffer for serial interface or Socket communication etc. Given by the constructor. */
  TelgTarget2Proxy_Inspc_s* target2proxy;

  /**Reference to the exchange data range. It may be located in a Dual Port Memory for immediately access,
   * in a buffer for serial interface or Socket communication etc. Given by the constructor. */
  TelgProxy2Target_Inspc_s const* proxy2target;

  /**The last sequence number of a command. If the seqnr in the telg is changed, a new command was received.
  * Note: The trigger for new data is not related to any event, but with polling the seqnr.
  * That approach is more simple, needs less organization effort.
  */
  int16 seqnrLast;

  int16 errorMsg;

  int16 lifeCt;


} Target2Proxy_Inspc_s;



extern_C Target2Proxy_Inspc_s* ctor_Target2Proxy_Inspc ( ObjectJc* othiz
    , TelgProxy2Target_Inspc_s const* proxy2target, TelgTarget2Proxy_Inspc_s* target2proxy);



/**In the user space the following array should be defined. It holds the reference to all offset arrays.
* Such an array is generated via the zbnfjax/jzTc/Cheader2Refl.jztxt.cmd reflection generator.
* The label is defined here to clarify the type especially for C++ compilation, both should have the same declaration.
*/
extern_C ClassJc const* const reflectionOffsetArrays[];


/**This routine should be used to evaluate middle-cyclically accesses from the InspcTargetProxy
 * to read or change data. 
 *  
 */
extern_C void step_Target2Proxy_Inspc(Target2Proxy_Inspc_s* thiz, void const* mainData
  , int32 const* reflectionOffset_MainData, ClassJc const* const* reflectionOffsetArrays);



#endif //__Inspc__Target2Proxy_Inspc_h__
