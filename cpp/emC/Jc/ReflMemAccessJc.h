/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this source the LGPL Lesser General Public License,
 * published by the Free Software Foundation is valid.
 * It means:
 * 1) You can use this source without any restriction for any desired purpose.
 * 2) You can redistribute copies of this source to everybody.
 * 3) Every user of this source, also the user of redistribute copies
 *    with or without payment, must accept this license for further using.
 * 4) But the LPGL ist not appropriate for a whole software product,
 *    if this source is only a part of them. It means, the user
 *    must publish this part of source,
 *    but don't need to publish the whole source of the own product.
 * 5) You can study and modify (improve) this source
 *    for own using or for redistribution, but you have to license the
 *    modified sources likewise under this LGPL Lesser General Public License.
 *    You mustn't delete this Copyright/Copyleft inscription in this source file.
 *
 * This source may be used also with another licence, if the author 
 * and all other here named co-authors have agreed to this contract.
 * Especially a company can use a copy of this sources in its products without publishing.
 * The user should have a underwritten contract therefore.
 *
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 *
 * @version 0.92
 * @content Interface for Reflection memory access
 * The implementation of this methods may be implemented specially for embedded hardware,
 * which regards memory areas and access rights.
 * All accesses to memory locations with maybe unknown addresses, especially from symbolic accesses via reflection,
 * should be executed using this methods. It may be possible, that a adress in a reference
 * in the users software is faulty. Than a fault access will be executed. That situation should be catched here.
 * This methods may support an access to external memory locations too, at example a signal processor in a host environment.
 * It depends from the implementation there.
 *
 * @author Hartmut Schorrig www.vishia.org
 * list of changes:
 * 2010-07-13 Hartmut new: MemAccessDebugJc, for debugging the path to an external CPU
 * 2010-01-16 Hartmut created, expandation of memory access for Reflection
 *
 ****************************************************************************/
#ifndef __ReflMemAccessJc_h__
#define __ReflMemAccessJc_h__

//#include <emC/InspcTargetSimple/IfcTargetProxy_Inspc.h>
#include <emC/Base/MemC_emC.h>

/*@CLASS_C RemoteCpuJcJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**This class contains all definitions to access a remote cpu. 
 * Only static methods and constants are present.
 */
typedef struct RemoteCpuJc_t{  //only defined for documentation generation
	int dummy;
}RemoteCpuJc;


/**This is a ghost type which is used to typing addresses, which are addresses from a remote CPU.
 * It is a non-defined struct (ghost), to prevent access to the own memory.
 * TODO it is a faulty assumption that the pointer type in this proxy is the same as in target.
 * use instead RemoteAddress_Inspc_emC;
 * The it is clarified that the target has 32 bit addresses. The communication use 32 bit.
 * The target address definition is independent of the proxy address width!
 */
/**It presents a 32-bit-address in any target system. */
typedef struct { uint32 addrTarget; } RemoteAddress_Inspc_emC;

#define INIZ_RemoteAddress_Inspc_emC(ADDR) { ADDR }

extern_C RemoteAddress_Inspc_emC null_RemoteAddress_Inspc_emC;

/*@DEFINE_C MemSegmJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**MemSegmJc: It is a OS_PtrValue, see emC/Base/Object_emC.h. Itcontains a untyped address and a segment number.
 * The representation will be implemented in the same way as a OS_PtrValue, 
 * defined at OS-Adaption (OSAL), see <os_types_def.h>.
 */

 
typedef struct MemSegmJc_T {

  /**It can be an address in the 64-bit-application, or an address in the target, may be 32 bit.*/
  union Addr_MemSegmJc_T {void* a; uint32 a32;  } addr;

  /**Segment number, 0 is own. */
  int32 segm;

} MemSegmJc;



#define INIZ_MemSegmJc(PTR, SEGM) { (Addr8_emC*)(PTR), SEGM }

//typedef OS_PtrValue MemSegmJc;
//#define MemSegmJc OS_PtrValue



#define NULL_MemSegmJc { null, 0 }

#define INIT_null_MemSegmJc(THIS) setAddrSegm_MemSegmJc(THIS, null, 0)

#define INIT_MemSegmJc(THIS) setAddrSegm_MemSegmJc(THIS, null, 0)

#define INIT_Mem_MemSegmJc(THIS, SRC) SET_AddrVal_emC(THIS, (SRC).addr, (SRC).val)

#define INIT_AddrSegm_MemSegmJc(THIS, ADDR, SEGM) SETADDR_AddrVal_emC(THIS, ADDR, SEGM)

#define setNull_MemSegmJc(THIS) setAddrSegm_MemSegmJc(THIS, null, 0)

#define setAddrSegm_MemSegmJc(THIZ, ADDR, SEGM) (THIZ).addr.a = ADDR; (THIZ).segm = SEGM

#define setAddr32Segm_MemSegmJc(THIZ, ADDR, SEGM) (THIZ).addr.a32 = ADDR; (THIZ).segm = SEGM

#define segment_MemSegmJc(THIS) ((THIS).segm)

#define ADDR_MemSegmJc(THIS, TYPE) ((TYPE*)((THIS).addr.a))

#define obj_MemSegmJc(THIZ) ((THIZ).addr.a)


#define isNull_MemSegmJc(THIS) (ADDR_AddrVal_emC(THIS, void)==null)

#define CONST_MemSegmJc(ADDR, SEGM) INIZ_AddrVal_emC(ADDR, SEGM) 

#define setADDR_MemSegmJc(THIZ, ADDR) ((THIZ).addr.a = ADDR)

#define setADDR32_MemSegmJc(THIZ, ADDR) ((THIZ).addr.a32 = ADDR)

#define set_MemSegmJc(THIS, SRC) (THIS = SRC)

#define setSegmAddr_MemSegmJc(THIS, SEGM, ADDR) SET_AddrVal_emC(THIS, ADDR, SEGM)

 /**Instance with null-pointer. */
extern_C MemSegmJc null_MemSegmJc;


/*@CLASS_C MemAccessJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

int getRealLengthStaticArray_MemAccessJc(MemSegmJc instance, int length);

/**Sets an integer value.
 * @param pValue The pointer to an integer position. It may be a int8, int16, etc.
 *        Only that bytes will be read from the source, which are requested.
 *        The endian of the source memory layout will be respected.
 * @param nrofBytes The number of bytes, it should be a number between 1..8.
 */
int setValue_MemAccessJc(MemSegmJc addr, void const* pValue, int nrofBytes);

/**Sets some bits in an integer. 
 */
/**Sets some bits from in an integer value.
 * Implementation notes: The access to the own memory uses an 8-, 16- or 32-bit-access
 * depending on the bit position and the address alignment. 
 * For example An 32-bit-access will be only done on address able to divide by 4.
 * The bits in the byte or word are masked and set. The setting uses the AtomicAccess,
 * so it is thread-safe. It is proper to use on most of processors.
 * 
 * The access to a remote CPU is done calling [[getInfoDebug_RemoteCpuJc(...)]]
 * using the command setBitfield_RemoteCpuJc. It should be implemented in a proper way.
 * Especially thread-safety should be regarded. The simple way to do it is
 * read, set and write under interrupt-disable.
 * @param addr The address of the bitfield-base variable
 * @param bitVal The set value for this bits, from bit 0.. Maximal 16 bits are used. 
 *        The parameter is admissible as 16-bit-int too (for 16-bit-CPUs).
 * @param posBit The position of the bit at the location addr
 * @param nrofBit The number of bits in this bitfield.
 * @return the value of the bitfield after writing, from bit 0.., max 16 bit.
 */
int setBitfield_MemAccessJc(MemSegmJc addr, int bitVal, int posBit, int nrofBit );

float setFloat_MemAccessJc(MemSegmJc addr, float value);

double setDouble_MemAccessJc(MemSegmJc addr, double pValue);



int32 getInt32_MemAccessJc(MemSegmJc addr);
#define getValue32_MemAccessJc(AADR) getInt32_MemAccessJc(ADDR) 

int16 getInt16_MemAccessJc(MemSegmJc addr);

int8 getByte_MemAccessJc(MemSegmJc addr);

int32 getValue32Ix_MemAccessJc(MemSegmJc addr, int ix);

/**Gets some bits from an integer. 
 * Implementation notes: The access to the own memory uses an 8-, 16- or 32-bit-access
 * depending on the bit position and the address alignment. 
 * For example An 32-bit-access will be only done on address able to divide by 4,
 * It is able to use on most of processors.
 * The access to a remote CPU is done calling [[getInfoDebug_RemoteCpuJc(...)]]
 * using a byte, 16-bit or 32-bit access in an adequate way.
 */
int16 getBitfield_MemAccessJc(MemSegmJc addr, int posBit, int nrofBit);

float getFloat_MemAccessJc(MemSegmJc addr);

double getDouble_MemAccessJc(MemSegmJc addr);

int64 getInt64_MemAccessJc(MemSegmJc addr);
#define getValue64_MemAccessJc(AADR) getInt64_MemAccessJc(ADDR) 

/**Gets the reference to the data.
 *  
 *  addr-->[reference--]-->[any ....]  
 *  return --------------->[....data]
 *
 * @param addr Address of a reference, which contains the reference to the data.
*/
MemSegmJc getRef_MemAccessJc(MemSegmJc addr);

/**Gets the reference to the data.
 *  
 *  addr-->[enhanced ref--]-->[any ....]  
 *  return ------------------>[....data]
 *
 * @param addr Address of a enhanced reference, which contains the reference to the data.
*/
MemSegmJc getEnhancedRef_MemAccessJc(MemSegmJc addr);




//typedef struct RemoteAddressJc_t* RemoteAddressJc;

#if 0
/**This enum defines some contants for commands to access to a remote CPU with one call.
 */
typedef enum Cmd_RemoteCpuJc_t
{
  /**Returns the address of the root object. Input: 0*/
  getRootInstance_RemoteCpuJc = 1

  /**Returns the index of the type of root object. Input: 0*/ 
, getRootType_RemoteCpuJc = 2

  /**Returns the index of any type of root object, if there is a class information,
   * or 0, if there isn't any information (the type is the type of reference, not derived).
   * Input: address of instance. 
   */
, getType_RemoteCpuJc = 3


  /**Returns the offset and array-length of a field of any type.
   * Note: The offset informations are able to build only from the affiliated compiler of the remote CPU-system.
   * Input: ixtype | ixarray
   * Return: length | offset
   */
, getOffsetLength_RemoteCpuJc = 4

  /**Returns the current really length of an array of pointers.
   * Input: The static length. 
   * @return really length, it is the index of the first reference, which is and after them all references are null, or length itself.
   */
, getRealLengthStaticArray_RemoteCpuJc = 5

  /**Returns an int32-value. Input: address.*/
, getByte_RemoteCpuJc = 0x10
, getInt16_RemoteCpuJc = 0x11
, getInt32_RemoteCpuJc = 0x12
, getInt64_RemoteCpuJc = 0x13
, getFloat_RemoteCpuJc = 0x14
, getDouble_RemoteCpuJc = 0x15
, getRef_RemoteCpuJc = 0x16
, getBitfield_RemoteCpuJc = 0x17

, setByte_RemoteCpuJc = 0x18
, setInt16_RemoteCpuJc = 0x19
, setInt32_RemoteCpuJc = 0x1a
, setInt64_RemoteCpuJc = 0x1b
, setFloat_RemoteCpuJc = 0x1c
, setDouble_RemoteCpuJc = 0x1d
, setRef_RemoteCpuJc = 0x1e
  /**Sets 1 bit or some bits in an integer. It should be an extra call
	 * because it have to be done thread-safe in the external CPU.
	 * In opposite: The reading of bits is done with getByte_RemoteCpuJc ..getInt32_RemoteCpuJc
	 */
, setBitfield_RemoteCpuJc = 0x1f

}Cmd_RemoteCpuJc_e;


typedef union XXXBitfieldInfo_RemoteCpuJc_t
{ int32 allBits;
  struct
	{ int32 posBits: 12;
    int32 nrofBits: 4;
	  int32 value: 16;
	}b;
}XXXBitfieldInfo_RemoteCpuJc;

#define bitPosBitsInBitfieldAccess_RemoteCpuJc 0
#define mPosBitsInBitfieldAccess_RemoteCpuJc 0xfff
#define bitNrofBitsInBitfieldAccess_RemoteCpuJc 12
#define mNrofBitsInBitfieldAccess_RemoteCpuJc 0xf000
#define kBitValueInBitfieldAccess_RemoteCpuJc 16
#define mValueInBitfieldAccess_RemoteCpuJc 0xffff0000

#endif


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




/**Gets any info from a remoteCPU, which has max. 4 byte return value. 
 * This method should be implemented by the special accessor to an external CPU in the target software.
 * It is not a part of the base software.
 * @param cmd the action to do.
 * @param device the remote device (it comes from a segment number in MemSegmentJc).
 * @param A address in the memory area in remote device. 
 *        The address is returned sometimes from other calls of this method and it is never changed.
 * @param input some additional parameter depends on cmd.
 */
//METHOD_C int32 accessTarget_Inspc(Cmd_RemoteCpuJc_e cmd, int device, RemoteAddress_Inspc_emC address, int32 input);


/**This is the internal called method. Some debug informations are captured too. 
 */
extern_C int32 getInfoDebug_InspcTargetProxy(Cmd_InspcTargetProxy_e cmd, int device, uint32 address, int32 input);


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
* @return depends on type of command. 
*/
extern_C int32 accessTarget_Inspc ( Cmd_InspcTargetProxy_e cmd, int device, uint32 address, int32 input);

extern_C int64 accessTarget64_Inspc ( Cmd_InspcTargetProxy_e cmd, int device, uint64 address, int64 input);





/**Gets any info from a remoteCPU, which has max. 8 byte return value. */
//METHOD_C int64 getInfoDebug64_InspcTargetProxy(Cmd_InspcTargetProxy_e cmd, int device, RemoteAddress_Inspc_emC address);


//METHOD_C void writeRemoteAccessDebug_MemAccessJc(int32 cmd, void* address, int32 input, int32 output);






/*@CLASS_C Access1TxData_ReflMemAccessJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This is an item to access data to the target for 1 access. 
 * In a DualPortRam or other interprocesscomm-Medium, there can be more as one such data. */
typedef struct Access1TxData_ReflMemAccessJc_t
{
  /**The cmd to the external CPU.*/ 
  int32 cmd;

  /**The value for the address to the external CPU, casted to int32.*/ 
  int32 address;

  /**The value for the input to the external CPU.*/ 
  int32 input;

}Access1TxData_ReflMemAccessJc;





/*@CLASS_C AccessTxData_ReflMemAccessJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This is an item to access data to the target for 1 access. 
 * In a DualPortRam or other interprocesscomm-Medium, there can be more as one such data. */
typedef struct AccessTxData_ReflMemAccessJc_t
{
  /**This number should be incremented in any case. A telegramm can be sent with change heartbeat,
	 * but without changed seqNrofData. Then it isn't a new information, only a life msg.
	 */
  int32 heartBeat;

  /**An sequence number and the number of data in 1 4-Byte-word. It is increased, if new data are sent.
	 * The bits 31..24 contains the number of request blocks.
	 */ 
  int32 seqNrofData;

	/**Only the bits 31..24 are able to use for nrofData. */
  #define mSeq_AccessTxData_ReflMemAccessJc 0x0000ffff
	/**Only the bits 31..24 are able to use for nrofData. */
  #define mNrofData_AccessTxData_ReflMemAccessJc 0xff000000
  #define kBitNrofData_AccessTxData_ReflMemAccessJc 24

	/**The array of blocks. The size given here is for debug showing. 
	 * The real length of the array depends from the following space (memory allocation). 
	 */
  Access1TxData_ReflMemAccessJc data[10];


}AccessTxData_ReflMemAccessJc;


/*@CLASS_C Access1RxData_ReflMemAccessJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This is an item to access data to the target for 1 access. 
 * In a DualPortRam or other interprocesscomm-Medium, there can be more as one such data. */
typedef struct Access1RxData_ReflMemAccessJc_t
{
  int32 lo;

  int32 hi;

}Access1RxData_ReflMemAccessJc;






/*@CLASS_C AccessRxData_ReflMemAccessJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This is an item to access data to the target for 1 access. 
 * In a DualPortRam or other interprocesscomm-Medium, there can be more as one such data. */
typedef struct AccessRxData_ReflMemAccessJc_t
{
  /**This number should be incremented in any case. A telegramm can be sent with change heartbeat,
	 * but without changed seqNrofData. Then it isn't a new information, only a life msg.
	 */
  int32 heartBeat;

  /**An sequence number and the number of data in 1 4-Byte-word. It is increased, if new data are sent.
	 * The bits 31..24 contains the number of request blocks.
	 */ 
  int32 seqNrofData;

	/**Only the bits 31..24 are able to use for nrofData. */
  #define mNrofData_AccessRxData_ReflMemAccessJc 0xff000000

	/**The array of answer data. The size given here is for debug showing. 
	 * The real length of the array depends from the following space (memory allocation). 
	 */
  Access1RxData_ReflMemAccessJc data[10];


}AccessRxData_ReflMemAccessJc;





/*@CLASS_C MemAccessDebugJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This is an item to debug the external access. */
typedef struct MemAccessDebugJc_t
{
  /**The cmd to the external CPU.*/ 
  int32 cmd;

  /**The value for the address to the external CPU, casted to int32.*/ 
  uint32 address;

  /**The value for the input to the external CPU.*/ 
  int32 input;

  /**The value which is returned from external CPU.*/
  int32 output;

}MemAccessDebugJc;



/*@CLASS_C MemAccessArrayDebugJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This struct is filled on any external access. */
typedef struct MemAccessArrayDebugJc_t
{
  int ix;
  MemAccessDebugJc item[20];
}MemAccessArrayDebugJc;

/**Only this instance exists. It is a singleton, in this form it is lightweightly able to see in a debugger.
 * But all methods doesn't use this sigleton. They are able to instanciate multiple.
 */
extern MemAccessArrayDebugJc memAccessDebugJc;

/**Adds a request to an external CPU. 
 * If the cmd is getRootInstance_RemoteCpuJc, then the recording starts at 0.
 * Elsewhere it is incremented. On overflow any time the last element is used.
 * The Output will be set to 0xbad00bad to designate the missing output yet.
 */
METHOD_C void addRequest_MemAccessArrayDebugJc ( MemAccessArrayDebugJc* ythis, int32 cmd, uint32 addr, int32 input);


/**Sets the output form an external CPU. 
 * The position calculated in [[addRequest_MemAccessArrayDebugJc(...)]] is used.
 * Then the index is incremented.
 */
METHOD_C void setOutput_MemAccessArrayDebugJc(MemAccessArrayDebugJc* ythis, int32 output);


#define getSingleton_MemAccessArrayDebugJc() (&memAccessDebugJc)

#endif //__ReflMemAccessJc_h__
