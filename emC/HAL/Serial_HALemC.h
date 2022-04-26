#ifndef HGUARD_Serial_HALemC
#define HGUARD_Serial_HALemC
#include <applstdef_emC.h>
//#include <emC/Base/Object_emC.h>



/*@CLASS_C Com_HALemC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 *
 * Common pattern for the interface to communication
 */

/**Base data of a communication. */
typedef struct Com_HALemC_T {
  union{ ObjectJc object;} base;
  /**It is an internal used handle to detect which functionality should be used, 
   * contains for example also a channel number. 
   * The meaning depends on the implemenation, only used internally. 
   */
  int _handle_;
} Com_HALemC_s;


#define INIZ_Com_HALemC(OBJ, REFL, ID) { { INIZ_ObjectJc(OBJ, REFL, ID) }, 0 }


/**Initializes a pre-defined communication channel.
* The application does not determine the kind of the serial communication (async, sync etc),
* that is determined by using a defined channel.
* The hardware has some channels, due to its capabilities.
* This channels are used inf there are initialized here.
*
* For example channel = 0 is the only one UART, channel 2 is SPI, channel 1 is not existing.
* @return 0 if ok, else an internal error number (using in debug).
*    If an existing channel is used, the 0 as return is expected.
*/
extern_C int open_Com_HALemC ( Com_HALemC_s* ithiz);


/**Sends some non packed characters. The character are stored one after another in the memory.
* The int* pointer addresses the memory in is nature.
* Depending on the characteristic of the channel it may be that one memory word is only one character.
* But usual characters are stored in packed form.
* @param text non packed characters
* @return 0: Nothing done, transmit is not possible yet. >= number of set words.
*/
extern_C int txChars_Com_HALemC ( Com_HALemC_s* thiz, char const* const text
                               , int const fromCharPos, int const zChars, bool bCont);


/**Sends memory content.
* @param zChars Number of 8-bit-portions to send (character-count, bytes).
* If a memory location is 16 or 32 bit, mulitply the sizeof() of the location with 2 or 4.
* If a memory location contains packed characters, this is the number of characters.
* @return number of pending bytes which are not sent in this call.
*         It is especially for embedded hardware with limmited FIFO on hardware or limited DMA buffer size.
* See [[step_TxSerial_HALemC(...)]]
*/
extern_C int txData_Com_HALemC ( Com_HALemC_s* thiz, void const* data
                               , int fromBytePos, int zBytes, bool bCont);


/**Cares to sending pending data.
* @return 0 nothing still pending. >0 number of data still pending, <0 any error, value for debugging, unexpected.
*/
extern_C int stepTx_Com_HALemC ( Com_HALemC_s* thiz);


/**Handles received chars and returns the number of available chars.
* It is problem of the implementation whether and how many characters are buffered,
* but the application should call this routine in a proper cycle matched to the buffer size.
* It is adequate stepTx...().
*/
extern_C int stepRx_Com_HALemC ( Com_HALemC_s* thiz);


/**Reads one char or received word if it is available. Returns -1 if nothing is available.
* Depending on a buffer (FIFO) this routine can be called one after another so long characters are buffered.
*/
extern_C int getChar_Com_HALemC ( Com_HALemC_s* thiz);


/**Reads the received data and stores it to the given dst in memory as data words.
* If lesser data are available the routine returns with the number of copied bytes.
* It should be invoked later again with the same dst and the number of read bytes before as fromByte.
* @arg dst the buffer to store
* @arg fromByte It is a byte position, not a memory index. Usual 0, >0 if some bytes were received before
*      and the receiving should be continued.
*      The difference index vs byte position is: Some embedded processors (not X86 series)
*      addresses the memory word-wise in 16 or 32 bit.
*      Then sizeof(int) ==1 usual, and a byte data definition in memory is not possible.
* @arg zDst sizeof(*dst). It is not the number of expected character, it is the maximum of the memory.
*      But if only a part of characters should be evaluated, this value can be used to reduce
*      the number of copied bytes.
*      Note: The number of copied bytes is at max BYTE_in_Memword * this value.
* @return number of copied bytes to dst. 0 if no data are available.
*      Note: It is possible that a word in memory is not completed, for 16- or 32-bit memory addressing
*      and on an odd return value. But this value is proper for the 'fromByte' argument of the next call.
*/
extern_C int getData_Com_HALemC ( Com_HALemC_s* thiz, void* dst, int fromByteInDst, int zDst);


/**Deactivates usage of the channel. */
extern_C void close_Com_HALemC ( Com_HALemC_s* thiz);

#if defined(__cplusplus) && defined(DEF_cplusplus_emC)
/**Definition of an common class for C++ which can be used as interface. 
 * The inline called C routines need not be existent if the routines are not called
 * instead the routines are overridden as virtual ones.
 */
class Com_HALemC  {
  private: Com_HALemC_s* const thiz;

  public:
  Com_HALemC(Com_HALemC_s* thizP) : thiz(thizP) {}

  VIRTUAL_emC int open ( ) { return open_Com_HALemC(thiz); }

  VIRTUAL_emC int txChars ( char const* text, int fromCharPos, int zChars, bool bCont) {
    return txChars_Com_HALemC(thiz, text, fromCharPos, zChars, bCont);
  }

  VIRTUAL_emC int txData ( void const* data, int fromCharPos, int zChars, bool bCont) {
    return txData_Com_HALemC(thiz, data, fromCharPos, zChars, bCont);
  }

  VIRTUAL_emC int stepTx() { return stepTx_Com_HALemC(thiz); }

  VIRTUAL_emC int stepRx() { return stepRx_Com_HALemC(thiz); }

  VIRTUAL_emC int  getChar() { return getChar_Com_HALemC(thiz); }

  VIRTUAL_emC int getData(void* dst, int fromByteInDst, int zDst) {
    return getData_Com_HALemC(thiz, dst, fromByteInDst, zDst);
  }

  VIRTUAL_emC void close ( ) { close_Com_HALemC(thiz); }
}; //class Com_HALemC
#endif //#if defined(__cplusplus) && defined(DEF_cplusplus_emC)



/*@CLASS_C Serial_HALemC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*
* Definition of serial communication according to the common pattern
*/

typedef enum Direction_Serial_HALemC_T {
  toRead_Serial_HALemC = 1    //Note can be used as mask for int too.
, toWrite_Serial_HALemC = 2
, toReadWrite_Serial_HALemC = 3  //contains 1 and 2 as mask.
} Direction_Serial_HALemC;

typedef enum ParityStop_Serial_HALemC_T {
  ParityOddStop1_Serial_HALemC = 2    //Note can be used as mask for int too.
, ParityOddStop2_Serial_HALemC = 3
, ParityEvenStop1_Serial_HALemC = 4    //Note can be used as mask for int too.
, ParityEvenStop2_Serial_HALemC = 5
, ParityNoStop1_Serial_HALemC = 0
, ParityNoStop2_Serial_HALemC = 1  //Note can be used as mask for int too.
} ParityStop_Serial_HALemC;

typedef struct Serial_HALemC_T {
  union{ Com_HALemC_s comm_HAL_emC; ObjectJc object;} base;
  int channel; 
  enum Direction_Serial_HALemC_T dir;
  uint32 baud; 
  ParityStop_Serial_HALemC bytePattern;
} Serial_HALemC_s;

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Serial_HALemC;
#endif

#ifndef ID_refl_Serial_HALemC          //may be defined in *.reflOffs.h
#define ID_refl_Serial_HALemC 0x0FD1
#endif

#define INIZ_Serial_HALemC(OBJ, ID, CHANNEL) { \
  { INIZ_Com_HALemC(OBJ, refl_Serial_HALemC, ID) }, CHANNEL  \
}

/**Initializes a pre-defined serial channel.
* The application does not determine the kind of the serial communication (async, sync etc),
* that is determined by using a defined channel.
* The hardware has some channels, due to its capabilities.
* This channels are used inf there are initialized here.
*
* For example channel = 0 is the only one UART, channel 2 is SPI, channel 1 is not existing.
* @return 0 if ok, else an internal error number (using in debug).
*    If an existing channel is used, the 0 as return is expected.
*/
extern_C int open_Serial_HALemC ( int channel, enum Direction_Serial_HALemC_T dir
  , int32 baud, ParityStop_Serial_HALemC bytePattern);

/**Sends some non packed characters. The character are stored one after another in the memory.
 * The int* pointer addresses the memory in is nature.
 * Depending on the characteristic of the channel it may be that one memory word is only one character.
 * But usual characters are stored in packed form.
 * @param text non packed characters
 * @return 0: Nothing done, transmit is not possible yet. >= number of set words.
 */
extern_C int txChars_Serial_HALemC ( int const channel, char const* const text, int const fromCharPos, int const zChars);

/**Sends memory content.
* @param zChars Number of 8-bit-portions to send (character-count, bytes).
* If a memory location is 16 or 32 bit, mulitply the sizeof() of the location with 2 or 4.
* If a memory location contains packed characters, this is the number of characters.
* @return number of pending bytes which are not sent in this call.
*         It is especially for embedded hardware with limmited FIFO on hardware or limited DMA buffer size.
* See [[step_TxSerial_HALemC(...)]]
*/
extern_C int txData_Serial_HALemC ( int channel, void const* data, int fromBytePos, int zBytes);


/**Cares to sending pending data.
 * @return =0 nothing still pending. >0 number of data still pending, <0 any error, value for debugging, unexpected.
 */
extern_C int stepTx_Serial_HALemC ( int channel);

/**Checkes whether the transmission is busy or ready.
 * @return =0 nothing still pending. >0 number of data still pending, <0 any error, value for debugging, unexpected.
 */
extern_C int busyTx_Serial_HAL_emC ( int channel);

/**Handles received chars and returns the number of available chars.
* It is problem of the implementation whether and how many characters are buffered,
* but the application should call this routine in a proper cycle matched to the buffer size.
* It is adequate stepTx...().
*/
extern_C int stepRx_Serial_HALemC ( int channel );


/**Reads one char or received word if it is available. Returns -1 if nothing is available.
* Depending on a buffer (FIFO) this routine can be called one after another so long characters are buffered.
*/
extern_C int getChar_Serial_HALemC ( int channel );


/**Reads the received data and stores it to the given dst in memory as data words.
* If lesser data are available the routine returns with the number of copied bytes.
* It should be invoked later again with the same dst and the number of read bytes before as fromByte.
*
* For a simple controller this routine may force writing received chars on the fly immediately in this given dst buffer.
* In opposite in a system which has a separate kernel, this routine copies the data from the kernel where they are stored firstly.
* The difference should not be present in usage.
* It means after calling this routine an return a given number of chars it is possible that the dst will be filled furthermore.
* A second call then returns only the new number of available chars, without change the conditions for receiving.
* In that case the formByteInDst argument is usual equal or increased in comparison to the last call.
*
* A simple possibility to clean is, apply a null pointer to dst, and afterwards the (same) dst pointer.
* If the dst is different from one call to the next, a clean respectively set the new index is to be done anyway.
*
* @arg dst the buffer to store
* @arg fromByte It is a byte position, not a memory index. Usual 0, >0 if some bytes were received before
*      and the receiving should be continued.
*      The difference index vs byte position is: Some embedded processors (not X86 series)
*      addresses the memory word-wise in 16 or 32 bit.
*      Then sizeof(int) ==1 usual, and a byte data definition in memory is not possible.
* @arg zDst sizeof(*dst). It is not the number of expected character, it is the maximum of the memory.
*      But if only a part of characters should be evaluated, this value can be used to reduce
*      the number of copied bytes. This argument should any time applied also in cheap systems for immediately used buffer.
*      Note: The number of copied bytes is at max BYTE_in_Memword * this value.
* @return number of copied bytes to dst. 0 if no data are available.
*      Note: It is possible that a word in memory is not completed, for 16- or 32-bit memory addressing
*      and on an odd return value. But this value is proper for the 'fromByte' argument of the next call.
*/
extern_C int getData_Serial_HALemC ( int channel, void* dst, int fromByteInDst, int zDst );



/**Deactivates usage of the channel. */
extern_C void close_Serial_HAL_emC(int channel);


#if defined(DEF_cplusplus_emC) && defined(__cplusplus)

/**It defines only the interface used in all comm classes. */
class Serial_HALemC : public Com_HALemC, private Serial_HALemC_s {
  public:
  Serial_HALemC ( ): Com_HALemC(&this->base.comm_HAL_emC) {}

  int openComm ( Direction_Serial_HALemC dir
  , int32 baud, ParityStop_Serial_HALemC bytePattern) {
    this->base.comm_HAL_emC._handle_ = channel;
    this->channel = channel;
    this->dir = dir;
    this->baud = baud;
    this->bytePattern = bytePattern;
    
    return open_Serial_HALemC(channel, dir, baud, bytePattern);
  }

  /**Activates ad hoc a sending process.
   * The sending may be done completely in the next future without additional software operation
   * (if it returns 0) or it needs cyclically step handling via txStep();
   * The first case is true if the controller has an hardware support such as FIFO or DMA.
   * Especially with DMA the whole message can be sent without software support.
   * @arg data any data, a mem address.
   * @arg fromBytePos usual 0, only for special cases.
   *      If the transmitting word length is not 8 bit, especially 16 bit,
   *      this value may/should be even, bit 0 =0, as special property of the implementation.
   * @arg zBytes The number of bytes to send. It is not sizeof(data) in any case:
   *      Note: sizeof(...) returns the number of address steps, not the number of bytes!
   *      For PC programming this is equal. But some processors have a 16- or 32-bit address step,
   *      in this case multiply sizeof(data) * BYTE_in_MemWord.
   *      If the transmitting word length is not 8 bit, especially 16 bit,
   *      this value may/should be even, bit 0 =0, as special property of the implementation.
   * @return number of bytes pending. If 0, the data will be sending complete
   *      only with the hardware of the controller (DMA, FIFO).
   *      If >0 then txStep() should be invoked.
   *      < 0 then an error, especially -1 for: pending transmission.
   */
  int txData ( void const* data, int fromBytePos, int zBytes) OVERRIDE_VIRTUAL_emC {
    return txData_Serial_HALemC(this->channel, data, fromBytePos, zBytes);
  }

  /**Activates a receiving order.
   * If DMA is used, this setups the DMA for receiving, so the data are stored
   * automatically on dst.
   * If DMA is not used, this stores only the order data to handle it in rxStep().
   */
  virtual int getData ( void* dst, int fromBytePos, int zBytes) OVERRIDE_VIRTUAL_emC {
    return getData_Serial_HALemC(this->channel, dst, fromBytePos, zBytes);
  }

  /**Processes and completes the receiving order
   * If DMA is not used, this reads one word / character or some words if FIFO is present
   * to the dst of the order. If DMA is used, this may read the last words
   * not regarded on burst DMA (to less words for burst).
   * @return sum of all bytes received.
   */
  virtual int stepRx ( )  OVERRIDE_VIRTUAL_emC;

};



/**It defines only the interface used in all comm classes. */
class Comm_HALemC {
public:
  virtual int openComm ( Direction_Serial_HALemC dir
  , int32 baud, ParityStop_Serial_HALemC bytePattern) =0;

  /**Activates ad hoc a sending process.
   * The sending may be done completely in the next future without additional software operation
   * (if it returns 0) or it needs cyclically step handling via txStep();
   * The first case is true if the controller has an hardware support such as FIFO or DMA.
   * Especially with DMA the whole message can be sent without software support.
   * @arg data any data, a mem address.
   * @arg fromBytePos usual 0, only for special cases.
   *      If the transmitting word length is not 8 bit, especially 16 bit,
   *      this value may/should be even, bit 0 =0, as special property of the implementation.
   * @arg zBytes The number of bytes to send. It is not sizeof(data) in any case:
   *      Note: sizeof(...) returns the number of address steps, not the number of bytes!
   *      For PC programming this is equal. But some processors have a 16- or 32-bit address step,
   *      in this case multiply sizeof(data) * BYTE_in_MemWord.
   *      If the transmitting word length is not 8 bit, especially 16 bit,
   *      this value may/should be even, bit 0 =0, as special property of the implementation.
   * @return number of bytes pending. If 0, the data will be sending complete
   *      only with the hardware of the controller (DMA, FIFO).
   *      If >0 then txStep() should be invoked.
   *      < 0 then an error, especially -1 for: pending transmission.
   */
  virtual int txData ( void const* data, int fromBytePos, int zBytes)=0;

  /**Activates a receiving order.
   * If DMA is used, this setups the DMA for receiving, so the data are stored
   * automatically on dst.
   * If DMA is not used, this stores only the order data to handle it in rxStep().
   */
  virtual int rxData ( void* dst, int fromBytePos, int zBytes)=0;

  /**Processes and completes the receiving order
   * If DMA is not used, this reads one word / character or some words if FIFO is present
   * to the dst of the order. If DMA is used, this may read the last words
   * not regarded on burst DMA (to less words for burst).
   * @return sum of all bytes received.
   */
  virtual int rxStep ( )=0;

  /**Reads one word (byte, character) in the given bit width from the hardware
   * or from an underlying buffer.
   * This operation can be used if the data kind are unknown, received words / character
   * should be separately checked before storing.
   * It is another approach than rxComm(...).
   * @return the character or -1 if the transmitter is empty.
   *     If the int width is equal the word width, -1 may be a received value.
   *     But: this routine is usual used for UART character communication.
   */
  virtual int getWord ( )=0;
};



/**This Comm classes can be present, used via forward declaration as reference in applications.
 * The application should not know and need not know the inner structure of this derived classes.
 */
class Comm_UART_HALemC;

class TargetSpec_Comm_SPI_HALemC;



/**Old solution, TODO remove*/
class Comm_SPI_HALemC //: public Comm_HALemC
{


  private: TargetSpec_Comm_SPI_HALemC* priv;


  MemUnit* rxDst;

  int zRxData;

  int ixRxData;

  /**Constructs a concretely SPI channel from this controller.
   * @arg spiRegs reference to the controllers SPI register
   * @arg dmaChnUsed reference to the used DMA channel. One of 6
   */
  public: Comm_SPI_HALemC ( TargetSpec_Comm_SPI_HALemC* privArg  );


  //it is final.
  public: int openComm ( Direction_Serial_HALemC dir
    , int32 baud, ParityStop_Serial_HALemC bytePattern);

  public: int txData ( void const* data, int fromBytePos, int zChars);

  /**Activates a receiving order.
   * If DMA is used, this setups the DMA for receiving, so the data are stored
   * automatically on dst.
   * If DMA is not used, this stores only the order data to handle it in rxStep().
   */
  public: int rxData ( void* dst, int fromBytePos, int zBytes);

  /**Processes and completes the receiving order
   * If DMA is not used, this reads one word / character or some words if FIFO is present
   * to the dst of the order. If DMA is used, this may read the last words
   * not regarded on burst DMA (to less words for burst).
   * @return sum of all bytes received.
   */
  public: int rxStep ( );

  private: int initDMA ( );
};


#endif //DEF_cplusplus_emC




#endif //HGUARD_Serial_HALemC
