#ifndef __Inspc__IfcTargetProxy_Inspc_h__
#define __Inspc__IfcTargetProxy_Inspc_h__
#include <applstdef_emC.h>
#include <OSAL/os_endian.h>  //supports both big endian conversion and access to even address on memory.



/**This enum defines some contants for commands to access to a remote CPU with one call.
 */
typedef enum Cmd_InspcTargetProxy_t
{
  /**Returns the address of the root object. Input: 0*/
  getRootInstance_InspcTargetProxy = 1

  /**Returns the index of the type of root object. Input: 0*/ 
, getRootType_InspcTargetProxy = 2

  /**Returns the index of any type of root object, if there is a class information,
   * or 0, if there isn't any information (the type is the type of reference, not derived).
   * Input: address of instance. 
   */
, getType_InspcTargetProxy = 3


  /**Returns the offset and array-length of a field of any type.
   * Note: The offset informations are able to build only from the affiliated compiler of the remote CPU-system.
   * Input: ixtype | ixarray
   * Return: length | offset
   */
, getOffsetLength_InspcTargetProxy = 4

  /**Returns the current really length of an array of pointers.
   * Input: The static length. 
   * @return really length, it is the index of the first reference, which is and after them all references are null, or length itself.
   */
, getRealLengthStaticArray_InspcTargetProxy = 5

  /**Returns an int32-value. Input: address.*/
, getByte_InspcTargetProxy = 0x10
, getInt16_InspcTargetProxy = 0x11
, getInt32_InspcTargetProxy = 0x12
, getInt64_InspcTargetProxy = 0x13
, getFloat_InspcTargetProxy = 0x14
, getDouble_InspcTargetProxy = 0x15
, getRef_InspcTargetProxy = 0x16
, getBitfield_InspcTargetProxy = 0x17

, setByte_InspcTargetProxy = 0x18
, setInt16_InspcTargetProxy = 0x19
, setInt32_InspcTargetProxy = 0x1a
, setInt64_InspcTargetProxy = 0x1b
, setFloat_InspcTargetProxy = 0x1c
, setDouble_InspcTargetProxy = 0x1d
, setRef_InspcTargetProxy = 0x1e
  /**Sets 1 bit or some bits in an integer. It should be an extra call
	 * because it have to be done thread-safe in the external CPU.
	 * In opposite: The reading of bits is done with getByte_InspcTargetProxy ..getInt32_InspcTargetProxy
	 */
, setBitfield_InspcTargetProxy = 0x1f

}Cmd_InspcTargetProxy_e;





#define bitPosBitsInBitfieldAccess_InspcTargetProxy 0
/**Mask for the bit position in a bitfield. With this 12 bits at least 4096 bits are able to address,
 * That is 128 int32-words. */
#define mPosBitsInBitfieldAccess_InspcTargetProxy 0xfff

/**The bit position where the 'nrofBits' information is stored in the bitfield. */
#define bitNrofBitsInBitfieldAccess_InspcTargetProxy 12

/**Mask for the nrofBits. With this 4 bits at least 16 bits are able to read as a bitfield member.
 * 16 is coded with 0. 
 */
#define mNrofBitsInBitfieldAccess_InspcTargetProxy 0xf000

#define kBitValueInBitfieldAccess_InspcTargetProxy 16
#define mValueInBitfieldAccess_InspcTargetProxy 0xffff0000



/**This operation is used inside the sources of the Service_Inspc, especially in ReflMemAccessJc.c. 
 * It should be implemented in a proxy if the communication to target should be used.
 * This operation is used only if a pointer initialized with a less negative number (-1, -2 till -100) was found.
 * That is the pointer to a remote target, used as device value (the positive value).
 * Via this pointer the data of a remote target are shown via inspector access.
 * The rest of the data path from this pointer are searched in the binary reflection and communicate via this operation.
 */
int32 accessTarget_Inspc(Cmd_InspcTargetProxy_e cmd, int device, struct RemoteAddressJc* address, int32 input);

int64 accessTarget64_Inspc(Cmd_InspcTargetProxy_e cmd, int device, struct RemoteAddressJc* address, int64 input);




/**This struct describes one item in the telegram from the proxy to the target. It based on the Inspector telegram definition for items. 
 * The first 2 bytes should be the length, after them 2 bytes are the command.
 * But all data are arranged as 32 bit values. Therewith it is possible to define this data struct in an Dual Port Memory of as subsequence of 32-bit-Registers
 * in an memory range of an FPGA to exchange the data between two processors on the same hardware board.
 * The endianess is important for serial communication usual via Ethernet which is organzized bytewise (really done bitwise).
 * For 32 bit data exchange the endianess has no matter because an int32 location is an int32 location itself. 
 * All other bytes are special defined here.
 */
typedef struct TelgProxy2Target_Inspc_t
{
  /**The length is always 16 because that is the fix length.
   * One of the Cmd_InspcTargetProxy_e. */
  int32BigEndian length_seq_cmd;
  
#define mLength_TelgProxy2Target_Inspc 0xffff0000
#define kBitLength_TelgProxy2Target_Inspc 16
#define mSeqnr_TelgProxy2Target_Inspc_s 0x0000ff00
#define kBitSeqnr_TelgProxy2Target_Inspc 8
#define mCmd_TelgProxy2Target_Inspc 0x000000ff
#define kBitCmd_TelgProxy2Target_Inspc 0


  /**First info. */
  int32BigEndian address;

  /**value to set or address bit fields. */
  int32BigEndian valueHi;

  /**value to set or address bit fields. */
  int32BigEndian value;


} TelgProxy2Target_Inspc_s;


inline int getSeqnr_TelgProxy2Target_Inspc(TelgProxy2Target_Inspc_s const* thiz) {
  int32 v = (getInt32BigEndian(&thiz->length_seq_cmd) & mSeqnr_TelgProxy2Target_Inspc_s) >> kBitSeqnr_TelgProxy2Target_Inspc;
  return (int)v;
}

inline Cmd_InspcTargetProxy_e getCmd_TelgProxy2Target_Inspc(TelgProxy2Target_Inspc_s const* thiz) {
  int32 v = (getInt32BigEndian(&thiz->length_seq_cmd) & mCmd_TelgProxy2Target_Inspc) >> kBitCmd_TelgProxy2Target_Inspc;
  return (Cmd_InspcTargetProxy_e)v;
}


inline void setCmdSeqnr_TelgProxy2Target_Inspc(TelgProxy2Target_Inspc_s* thiz, Cmd_InspcTargetProxy_e cmd, int seqnr) {
  int32 v = (((int32)sizeof(TelgProxy2Target_Inspc_s)) << kBitLength_TelgProxy2Target_Inspc) 
          | (cmd & mCmd_TelgProxy2Target_Inspc) 
          | ((seqnr << kBitSeqnr_TelgProxy2Target_Inspc) & mSeqnr_TelgProxy2Target_Inspc_s);
  setInt32BigEndian(&thiz->length_seq_cmd, v);
}



/**This is the prototype for processing the inspector commands in an target.
* It uses the generated ...ReflOffset...c.
*
* The user should programm the access to the communication in a proper way for the target sensitivities (conditions).
* @param cmd the command of type Cmd_InspcTargetProxy_e
* @param address The address value. It is a 32 bit value usually. A Processor with a 64-bit-Address space may not need this routine.
* @param inputVal depends from the command. For bitfield access it is the bit number and length, see [[mPosBitsInBitfieldAccess_InspcTargetProxy]] etc.
*    for setFloat and setDouble it is a float value (present in integer image).
* @param mainData The address of the root of all data. That is the only one address which should be known for access.
* @param reflectionOffset_MainData Pointer to the const array of offsets which describes the mainData structure,
*    from the generated ...ReflOffset...c-File.
* @param reflectionOffsetArrays pointer to the 'Array of all offsets' from the generated ...ReflOffset...c-File.
* @return for set and get operations the current value, gotten or after set. It is a int image of a float value on get/set double and float.
*/
int32 processInspcCmdOnTarget_Inspc(Cmd_InspcTargetProxy_e const cmd, int32 address, int32 inputVal, void const* mainData
  , int32 const* reflectionOffset_MainData, int32 const* const* reflectionOffsetArrays);




/**This struct describes one item in the telegram from the target or the data for shared memory data exchange. 
 * It is big endian because usual for telegram communication. 
 * It is aligned to 32 bit because simple processors supports only 32 bit access to memory or FPGA.
 * It is alligned to 8 Byte for the whole struct because proper for 64-Bit-Systems (PC).
 * The first 16bit in big endian are the length, to be compatible with simple Inspc telegrams (checks first 2 Bytes).
 */
typedef struct TelgTarget2Proxy_Inspc_s_t
{
  /**The length is sizeof(TelgTarget2Proxy_Inspc_s) == 16 because that is the fix length. */
  int32BigEndian length_seq_cmd;
#define mSeqnr_TelgTarget2Proxy_Inspc      0x0000ff00
#define kBitSeqnr_TelgTarget2Proxy_Inspc   8
#define mCmd_TelgTarget2Proxy_Inspc        0x000000ff
#define kBitCmd_TelgTarget2Proxy_Inspc     0
#define  kBitLength_TelgTarget2Proxy_Inspc  16

  /**The Seqnr will be changed (incremented) if a new information is given. 
   * That occurs only if a new Information was received. 
   * The Bit 15 mError_TelgTarget2Proxy_Inspc_s is set if the target has an initializing error
   * and the Inspector communication cannot be used. 
   * Then the bits for lifect stores an error code (target individual, manually evaluated)
   * The lifect is incremented in any polling cycle of the target. 
   * For serial or ethernet communication a telegram with this changed lifeCt is sent. 
   * It means the proxy receives telegrams cyclically. 
   * For simplex serial connection the communication level should send a request telegramm from the proxy
   * in a short cycle after receiving a telegram from target. 
   * The target should send (and poll) with a pause of at least the time-length of a telegram.
   */
  int32BigEndian error__lifeCt;

  #define mError_TelgTarget2Proxy_Inspc      0xffff0000
  #define mLifeCt_TelgTarget2Proxy_Inspc     0x00008fff
  #define kBitError_TelgTarget2Proxy_Inspc   16
  #define kBitLifeCt_TelgTarget2Proxy_Inspc   0

  /**This element is used to evaluate whether the target system runs or not. 
   * If it runs, the lifeCt should count in a positive range, maybe with 16 or 31 bit.
   * If the target system has had an initialization error, the error number (maybe negative) should be written here
   * to have a hint to the cause of the error.
   */
  int32BigEndian retValueHi;

  int32BigEndian retValue;

} TelgTarget2Proxy_Inspc_s;


inline int getSeqnr_TelgTarget2Proxy_Inspc  (  TelgTarget2Proxy_Inspc_s const* thiz) {  
  int32 v = ( getInt32BigEndian(&thiz->length_seq_cmd) & mSeqnr_TelgTarget2Proxy_Inspc ) >> kBitSeqnr_TelgTarget2Proxy_Inspc;
  return (int)v;
}


inline Cmd_InspcTargetProxy_e getCmd_TelgTarget2Proxy_Inspc(TelgTarget2Proxy_Inspc_s const* thiz) {
  int32 v = (getInt32BigEndian(&thiz->length_seq_cmd) & mCmd_TelgTarget2Proxy_Inspc) >> kBitCmd_TelgTarget2Proxy_Inspc;
  return (Cmd_InspcTargetProxy_e)v;
}


inline void setCmdSeqnr_TelgTarget2Proxy_Inspc(TelgTarget2Proxy_Inspc_s* thiz, Cmd_InspcTargetProxy_e cmd, int seqnr) {
  int32 v = (((int32)sizeof(TelgTarget2Proxy_Inspc_s)) << kBitLength_TelgTarget2Proxy_Inspc)
    | (cmd & mCmd_TelgProxy2Target_Inspc)
    | ((seqnr << kBitSeqnr_TelgTarget2Proxy_Inspc) & mSeqnr_TelgTarget2Proxy_Inspc);
  setInt32BigEndian(&thiz->length_seq_cmd, v);
}



/**Set the error information into the telegram structure. */
inline void setError_TelgTarget2Proxy_Inspc(TelgTarget2Proxy_Inspc_s* thiz, int error) {
  int32 v = getInt32BigEndian(&thiz->error__lifeCt);
  v = v & ~mLifeCt_TelgTarget2Proxy_Inspc 
    | (((int32)error << kBitError_TelgTarget2Proxy_Inspc) & mError_TelgTarget2Proxy_Inspc);
  setInt32BigEndian(&thiz->error__lifeCt, v);
}


/**Repaces the lifeCt bits with the given value. A stored error will be overwritten with the lifeCt.
 * This routine must not be called if a error code should be sent furthermore.
 */
inline void setLifeCt_TelgTarget2Proxy_Inspc(TelgTarget2Proxy_Inspc_s* thiz, int lifeCt) {
  int32 v = getInt32BigEndian(&thiz->error__lifeCt);
  v = v & ~mLifeCt_TelgTarget2Proxy_Inspc | (((int32)lifeCt << kBitLifeCt_TelgTarget2Proxy_Inspc) & mLifeCt_TelgTarget2Proxy_Inspc);
  setInt32BigEndian(&thiz->error__lifeCt, v);
}


#endif //__Inspc__IfcTargetProxy_Inspc_h__
