#ifndef HGUARD_serial_HALemC
#define HGUARD_serial_HALemC
#include <compl_adaption.h>


enum Direction_Serial_HALemC {
  toRead_Serial_HALemC = 1    //Note can be used as mask for int too.
, toWrite_Serial_HALemC = 2
, toReadWrite_Serial_HALemC = 3  //contains 1 and 2 as mask.
};

enum ParityStop_Serial_HALemC {
  ParityOddStop1_Serial_HALemC = 2    //Note can be used as mask for int too.
, ParityOddStop2_Serial_HALemC = 3
, ParityEvenStop1_Serial_HALemC = 4    //Note can be used as mask for int too.
, ParityEvenStop2_Serial_HALemC = 5
, ParityNoStop1_Serial_HALemC = 0
, ParityNoStop2_Serial_HALemC = 1  //Note can be used as mask for int too.
};


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
extern_C int open_Serial_HALemC ( int channel, Direction_Serial_HALemC dir
  , int32 baud, ParityStop_Serial_HALemC bytePattern);

/**Sends some non packed characters. The character are stored one after another in the memory.
 * The int* pointer addresses the memory in is nature.
 * Depending on the characteristic of the channel it may be that one memory word is only one character.
 * But usual characters are stored in packed form.
 * @param text non packed characters
 * @return 0: Nothing done, transmit is not possible yet. >= number of set words.
 */
extern_C int txChar_Serial_HALemC ( int const channel, char const* const text, int const fromCharPos, int const zChars);

/**Sends memory content.
 * @param zChars Number of 8-bit-portions to send (character-count, bytes).
 * If a memory location is 16 or 32 bit, mulitply the sizeof() of the location with 2 or 4.
 * If a memory location contains packed characters, this is the number of characters.
 * @return number of pending bytes which are not sent in this call.
 *         It is especially for embedded hardware with limmited FIFO on hardware or limited DMA buffer size.
 * See [[step_TxSerial_HALemC(...)]]
 */
extern_C int tx_Serial_HALemC ( int const channel, void const* const data, int const fromCharPos, int const zChars);


/**Cares to sending pending data.
 * @return 0 nothing still pending. >0 number of data still pending, <0 any error, value for debugging, unexpected.
 */
extern_C int stepTx_Serial_HALemC( int const channel);

/**Prepare an receive buffer for receiving data. Often DMA is used do fill the buffer.
 * The call of this operation clears the number of current received data words. [[See hasRx_HALemC(...)]].
 * The buffer content is valid only after quest of [[hasRxChars_HALemC(...)]] for the returned number of characters.
 * @param valueBuffer The address in memory of the valueBuffer. 
 * @param zBuffer The size of the buffer in memory words (result of sizeof(...). 
 * @param fromCurrent 0 for newly receiving. If the valueBuffer may contains ome received content
 *        which was not evaluated yet and this content should be preserved, 
 *        This is the byte index in the valueBuffer to copy the information. 
 *        Important: The memory words may organzized in 16 or 32 bit for some special processors. 
 *        This is not the index in memory but the byte index, because serial receive is organized in bytes.
 */
extern_C void prepareRx_Serial_HALemC ( int channel, void* valueBuffer, int zBuffer, int fromCurrent);


/**Returns the number of received character after calling [[prepareRxSerial_HALemC(...)]].
 * Note: A character is always understand as a 8-bit-entity. The memory buffer is filled in packed form
 * to support binary data.
 * If a memory location is greater than the character size, especially 16 bit (for example for Texas Instruments processors)
 * or 32 bit (typically for Analog Devices signal processors) then a memory location contains 2 or 4 characters.
 * This is independent of a word length for example for SPI communication (maybe 16), the word length is an internal topic.
 * But the communication word length of an UART communication is always 8 bit, also if 7 bits and a parity is transmitted.
 * It means the memory is always packed with data, also if the communication is character oriented.
 * With it character communication can transport also binary data without distinction on communication transmit and receive level.
 * @return number of 8-bit-portions in memory.
 * Note: If a MemUnit is 16 or 32 bit, divide this value (shift) to get the number of received memory locations.
 */
extern_C int hasRxChars_Serial_HALemC ( int channel );

/**Deactivates usage of the channel. */
extern_C void close_Serial_HAL_emC(int channel);


#endif //HGUARD_serial_HALemC
