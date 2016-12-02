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





#define bitPosBitsInBitfieldAccess_InspcTargetProxyTelg 0
/**Mask for the bit position in a bitfield. With this 12 bits at least 4096 bits are able to address,
 * That is 128 int32-words. */
#define mPosBitsInBitfieldAccess_InspcTargetProxyTelg 0xfff

/**The bit position where the 'nrofBits' information is stored in the bitfield. */
#define bitNrofBitsInBitfieldAccess_InspcTargetProxyTelg 12

/**Mask for the nrofBits. With this 4 bits at least 16 bits are able to read as a bitfield member.
 * 16 is coded with 0. 
 */
#define mNrofBitsInBitfieldAccess_InspcTargetProxyTelg 0xf000

#define kBitValueInBitfieldAccess_InspcTargetProxyTelg 16
#define mValueInBitfieldAccess_InspcTargetProxyTelg 0xffff0000







/**This struct describes one item in the telegram from the proxy. It based on the Inspector telegram definition for items. 
 * The first 2 bytes should be the length, after them 2 bytes are the command.
 * All other bytes are special defined here.
 */
typedef struct TelgProxy2Target_Inspc_t
{
  /**The length is always 12 because that is the fix length. */
  int16BigEndian length;
  
  /**One of the Cmd_InspcTargetProxyTelg_e. */
  int16BigEndian cmd;

  int32BigEndian seqnr;

  /**First info. */
  int32BigEndian address;

  /**value to set or address bit fields. */
  int32BigEndian value;


} TelgProxy2Target_Inspc_s;


/**This struct describes one item in the telegram from the target. */
typedef struct TelgTarget2Proxy_Inspc_s_t
{
  /**The length is always 8 because that is the fix length. */
  int16BigEndian length;
  
  int16BigEndian cmd;

  int32BigEndian seqnr;

  int32BigEndian retValue;

} TelgTarget2Proxy_Inspc_s;




/**This const array is defined by the reflection generator in the ReflOffset.c file. */
extern_C const int32* const reflectionOffsetArrays[];



/**This is the prototype for processing the inspector commands in an target.
 * It uses the generated ...ReflOffset...c.
 *
 * The user should programm the access to the communication in a proper way for the target sensitivities (conditions).
 * @param cmd the command of type Cmd_InspcTargetProxyTelg_e
 * @param address The address value. It is a 32 bit value usually. A Processor with a 64-bit-Address space may not need this routine.
 * @param inputVal depends from the command. For bitfield access it is the bit number and length, see [[mPosBitsInBitfieldAccess_InspcTargetProxyTelg]] etc.
 *    for setFloat and setDouble it is a float value (present in integer image). 
 * @param mainData The address of the root of all data. That is the only one address which should be known for access.
 * @param reflectionOffset_MainData Pointer to the const array of offsets which describes the mainData structure, 
 *    from the generated ...ReflOffset...c-File.
 * @param reflectionOffsetArrays pointer to the 'Array of all offsets' from the generated ...ReflOffset...c-File.
 * @return for set and get operations the current value, gotten or after set. It is a int image of a float value on get/set double and float.  
 */
int32 processInspcCmdOnTarget_Inspc(Cmd_InspcTargetProxyTelg_e const cmd, int32 address, int32 inputVal, void const* mainData
, int32 const* reflectionOffset_MainData, int32 const* const* reflectionOffsetArrays);


#endif //__InspcTargetProxyTelg_h__
