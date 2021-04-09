#ifndef __Inspc__IfcTargetProxy_Inspc_h__
#define __Inspc__IfcTargetProxy_Inspc_h__
#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>
#include <emC/Jc/ReflMemAccessJc.h>







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
  int32 length_seq_cmd;
  
#define mLength_TelgProxy2Target_Inspc 0xffff0000
#define kBitLength_TelgProxy2Target_Inspc 16
#define mSeqnr_TelgProxy2Target_Inspc_s 0x0000ff00
#define kBitSeqnr_TelgProxy2Target_Inspc 8
#define mCmd_TelgProxy2Target_Inspc 0x000000ff
#define kBitCmd_TelgProxy2Target_Inspc 0


  /**First info. */
  int32 address;

  /**value to set or address bit fields. */
  int32 valueHi;

  /**value to set or address bit fields. */
  int32 value;


} TelgProxy2Target_Inspc_s;


inline int getSeqnr_TelgProxy2Target_Inspc(TelgProxy2Target_Inspc_s const* thiz) {
  int32 v = (thiz->length_seq_cmd & mSeqnr_TelgProxy2Target_Inspc_s) >> kBitSeqnr_TelgProxy2Target_Inspc;
  return (int)v;
}

inline Cmd_InspcTargetProxy_e getCmd_TelgProxy2Target_Inspc(TelgProxy2Target_Inspc_s const* thiz) {
  int32 v = (thiz->length_seq_cmd & mCmd_TelgProxy2Target_Inspc) >> kBitCmd_TelgProxy2Target_Inspc;
  return (Cmd_InspcTargetProxy_e)v;
}


inline void setCmdSeqnr_TelgProxy2Target_Inspc(TelgProxy2Target_Inspc_s* thiz, Cmd_InspcTargetProxy_e cmd, int seqnr) {
  int32 v = (((int32)sizeof(TelgProxy2Target_Inspc_s) * BYTE_IN_MemUnit) << kBitLength_TelgProxy2Target_Inspc)
          | (cmd & mCmd_TelgProxy2Target_Inspc) 
          | ((seqnr << kBitSeqnr_TelgProxy2Target_Inspc) & mSeqnr_TelgProxy2Target_Inspc_s);
  thiz->length_seq_cmd = v;
}



/**This struct describes one item in the telegram from the target or the data for shared memory data exchange. 
 * It is big endian because usual for telegram communication. 
 * It is aligned to 32 bit because simple processors supports only 32 bit access to memory or FPGA.
 * It is alligned to 8 Byte for the whole struct because proper for 64-Bit-Systems (PC).
 * The first 16bit in big endian are the length, to be compatible with simple Inspc telegrams (checks first 2 Bytes).
 */
typedef struct TelgTarget2Proxy_Inspc_s_t
{
  /**The length is sizeof(TelgTarget2Proxy_Inspc_s) * BYTE_IN_MemUnit == 16 because that is the fix length. */
  int32 length_seq_cmd;
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
  int32 error__lifeCt;

  #define mError_TelgTarget2Proxy_Inspc      0xffff0000
  #define mLifeCt_TelgTarget2Proxy_Inspc     0x00008fff
  #define kBitError_TelgTarget2Proxy_Inspc   16
  #define kBitLifeCt_TelgTarget2Proxy_Inspc   0

  /**This element is used to evaluate whether the target system runs or not. 
   * If it runs, the lifeCt should count in a positive range, maybe with 16 or 31 bit.
   * If the target system has had an initialization error, the error number (maybe negative) should be written here
   * to have a hint to the cause of the error.
   */
  int32 retValueHi;

  int32 retValue;

} TelgTarget2Proxy_Inspc_s;


inline int getSeqnr_TelgTarget2Proxy_Inspc  (  TelgTarget2Proxy_Inspc_s const* thiz) {  
  int32 v = ( thiz->length_seq_cmd & mSeqnr_TelgTarget2Proxy_Inspc ) >> kBitSeqnr_TelgTarget2Proxy_Inspc;
  return (int)v;
}


inline Cmd_InspcTargetProxy_e getCmd_TelgTarget2Proxy_Inspc(TelgTarget2Proxy_Inspc_s const* thiz) {
  int32 v = (thiz->length_seq_cmd & mCmd_TelgTarget2Proxy_Inspc) >> kBitCmd_TelgTarget2Proxy_Inspc;
  return (Cmd_InspcTargetProxy_e)v;
}


inline void setCmdSeqnr_TelgTarget2Proxy_Inspc(TelgTarget2Proxy_Inspc_s* thiz, Cmd_InspcTargetProxy_e cmd, int seqnr) {
  int32 v = (((int32)sizeof(TelgTarget2Proxy_Inspc_s) * BYTE_IN_MemUnit) << kBitLength_TelgTarget2Proxy_Inspc)
    | (cmd & mCmd_TelgProxy2Target_Inspc)
    | ((seqnr << kBitSeqnr_TelgTarget2Proxy_Inspc) & mSeqnr_TelgTarget2Proxy_Inspc);
  thiz->length_seq_cmd = v;
}



/**Set the error information into the telegram structure. */
inline void setError_TelgTarget2Proxy_Inspc(TelgTarget2Proxy_Inspc_s* thiz, int error) {
  int32 v = thiz->error__lifeCt;
  v = (v & ~mLifeCt_TelgTarget2Proxy_Inspc) 
    | (((int32)error << kBitError_TelgTarget2Proxy_Inspc) & mError_TelgTarget2Proxy_Inspc);
  thiz->error__lifeCt = v;
}


/**Repaces the lifeCt bits with the given value. A stored error will be overwritten with the lifeCt.
 * This routine must not be called if a error code should be sent furthermore.
 */
inline void setLifeCt_TelgTarget2Proxy_Inspc(TelgTarget2Proxy_Inspc_s* thiz, int lifeCt) {
  int32 v = thiz->error__lifeCt;
  v = (v & ~mLifeCt_TelgTarget2Proxy_Inspc) | (((int32)lifeCt << kBitLifeCt_TelgTarget2Proxy_Inspc) & mLifeCt_TelgTarget2Proxy_Inspc);
  thiz->error__lifeCt = v;
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
int32 processInspcCmdOnTarget_Inspc(TelgProxy2Target_Inspc_s const* proxy2target, TelgTarget2Proxy_Inspc_s* target2proxy
      , void const* mainData
      , int32 const* reflectionOffset_MainData, ClassJc const* const* reflectionOffsetArrays);






#endif //__Inspc__IfcTargetProxy_Inspc_h__
