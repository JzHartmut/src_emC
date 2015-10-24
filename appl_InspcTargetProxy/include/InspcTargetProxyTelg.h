#ifndef __InspcTargetProxyTelg_h__
#define __InspcTargetProxyTelg_h__
#include <os_types_def.h>
#include <os_endian.h>  //supports both big endian conversion and access to even address on memory.


/**This enum defines some contants for commands to access to a remote CPU with one call.
 */
typedef enum Cmd_InspcTargetProxyTelg_t
{
  /**Returns the address of the root object. Input: 0*/
  getRootInstance_InspcTargetProxyTelg = 1

  /**Returns the index of the type of root object. Input: 0*/ 
, getRootType_InspcTargetProxyTelg = 2

  /**Returns the index of any type of root object, if there is a class information,
   * or 0, if there isn't any information (the type is the type of reference, not derived).
   * Input: address of instance. 
   */
, getType_InspcTargetProxyTelg = 3


  /**Returns the offset and array-length of a field of any type.
   * Note: The offset informations are able to build only from the affiliated compiler of the remote CPU-system.
   * Input: ixtype | ixarray
   * Return: length | offset
   */
, getOffsetLength_InspcTargetProxyTelg = 4

  /**Returns the current really length of an array of pointers.
   * Input: The static length. 
   * @return really length, it is the index of the first reference, which is and after them all references are null, or length itself.
   */
, getRealLengthStaticArray_InspcTargetProxyTelg = 5

  /**Returns an int32-value. Input: address.*/
, getByte_InspcTargetProxyTelg = 0x10
, getInt16_InspcTargetProxyTelg = 0x11
, getInt32_InspcTargetProxyTelg = 0x12
, getInt64_InspcTargetProxyTelg = 0x13
, getFloat_InspcTargetProxyTelg = 0x14
, getDouble_InspcTargetProxyTelg = 0x15
, getRef_InspcTargetProxyTelg = 0x16
, getBitfield_InspcTargetProxyTelg = 0x17

, setByte_InspcTargetProxyTelg = 0x18
, setInt16_InspcTargetProxyTelg = 0x19
, setInt32_InspcTargetProxyTelg = 0x1a
, setInt64_InspcTargetProxyTelg = 0x1b
, setFloat_InspcTargetProxyTelg = 0x1c
, setDouble_InspcTargetProxyTelg = 0x1d
, setRef_InspcTargetProxyTelg = 0x1e
  /**Sets 1 bit or some bits in an integer. It should be an extra call
	 * because it have to be done thread-safe in the external CPU.
	 * In opposite: The reading of bits is done with getByte_InspcTargetProxyTelg ..getInt32_InspcTargetProxyTelg
	 */
, setBitfield_InspcTargetProxyTelg = 0x1f

}Cmd_InspcTargetProxyTelg_e;




/**This struct describes the common head of any telegram for inspector communication. 16 Byte. */
typedef struct InspcTelgHead_Inspc_t
{
  /**Nr of bytes of this telegram. */
  int16BigEndian nrofBytes;

  /**The command is a version identificator too. A new version uses new command constants. 
   * That is used as BOM (Byte Order Mark) too: 
   * * A big endian command sets its bit15 to 0 anyway. It means the bit 7 in the first byte is 0.
   * * A little endian command sets its bit 7 to 1. It means the bit 7 in the first byte is 1. 
   */
  int16BigEndian cmdTelg;

  #define mLittleEndianCmdTelg_Inspc 0x0080;

  /**A number to support an encryption. For future extensions. */
  int32BigEndian encryption;

  /**The sequence number of this telegram. The request and the answer have the same sequence number. */
  int32BigEndian seqnr;

  /**A answer number if the answer uses more as one telegram. */
  int16BigEndian answernr;

  /**Distinction if more as one service is used with the same port of communication. */ 
  int16BigEndian entrant;


} InspcTelgHead_Inspc_s;




/**This struct describes one item in the telegram from the proxy. It based on the Inspector telegram definition for items. 
 * The first 2 bytes should be the length, after them 2 bytes are the command.
 * All other bytes are special defined here.
 */
typedef struct ItemProxy2Target_Inspc_t
{
  /**The length is always 12 because that is the fix length. */
  int16BigEndian length;
  
  /**One of the Cmd_InspcTargetProxyTelg_e. */
  int16BigEndian cmd;

  /**First info. */
  int32BigEndian address;

  /**value to set. */
  int32BigEndian setValue;


} ItemProxy2Target_Inspc_s;


/**This struct describes one item in the telegram from the target. */
typedef struct ItemTarget2Proxy_Inspc_s_t
{
  int16BigEndian length;
  
  int16BigEndian cmd;

  int32BigEndian retValue;

} ItemTarget2Proxy_Inspc_s;



/**This struct describes the telegram from the proxy to the target to send commands. */
typedef struct TelgProxy2Target_Inspc_t
{
  InspcTelgHead_Inspc_s head;

  /**Up to 100 items with commands from Proxy to the target, often only 1 used. 
   * The max length of a telegram is 1216 with them. 
   */
  ItemProxy2Target_Inspc_s items[100];

} TelgProxy2Target_Inspc_s;


/**This struct describes the telegram from the target to the proxy to send answers. */
typedef struct TelgTarget2Proxy_Inspc_t
{
  InspcTelgHead_Inspc_s head;

  /**Up to 100 items with answers from target to the proxy, often only 1 used. 
   * The max length of a telegram is 816 with them. 
   */
  ItemTarget2Proxy_Inspc_s items[100];

} TelgTarget2Proxy_Inspc_s;


#endif //__InspcTargetProxyTelg_h__
