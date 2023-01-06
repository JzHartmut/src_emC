#ifndef HGUARD_Spi_HALemC
#define HGUARD_Spi_HALemC


#include <emC/HAL/Serial_HALemC.h>

struct SPI_Com_HALemC_T;

struct TargetSpec_SPI_Com_HALemC_T;    //Target specific structure with Port addresses

/**Initializes the SPI communication.
 * It is as a factory pattern, returns the instance.
 * @param target const describes which hardware resource is used.
 * @param baud the clock rate in Hz (1/s). Use 10000000 for 10 MHz
 * @param slave true then init as slave
 */
extern_C Com_HALemC_s* initSPI_Com_HALemC( Com_HALemC_s* thiz, struct TargetSpec_SPI_Com_HALemC_T const* target, int32 baud, bool slave );


/**Sets the transmission channel to master or slave.
 * If the transmission is master, SPICLK is output. On Slave it is input.
 * Adequate for SPIMOSI and SPISOMI
 */
extern_C bool setMaster_Com_HALemC(Com_HALemC_s* ithiz, bool bMaster);



/**Prepares the data to transmit, initialize one transmission.
 * This routine is adequate the pattern of txData_Com_HALemC(...) in emC/HAL/Serial_HALemC.h
 */
extern_C int txDataSPI_Com_HALemC(Com_HALemC_s* ithiz, void const* data, int fromBytePos, int zBytes, bool bCont, bool slave);

/**Cares to sending pending data.
 * This routine is adequate the pattern of stepTx_Com_HALemC(...) in emC/HAL/Serial_HALemC.h
 * @return 0 nothing still pending. >0 number of data still pending, <0 any error, value for debugging, unexpected.
 */
extern_C int stepTx_SPI_Com_HALemC ( Com_HALemC_s* thiz);

extern_C int test_SPI_Com_HALemC ( Com_HALemC_s* thiz);




/**Prepares destination of the data to receive.
 * This routine is adequate the pattern of getData_Com_HALemC(...) in emC/HAL/Serial_HALemC.h
 * @param zDst max nr of bytes in dst. Note: it is not sizeof(), the real the number of bytes.
 *   See MemUnit and BYTE_IN_MemUnit
 */
extern_C int rxData_SPI_Com_HALemC ( Com_HALemC_s* thiz, void* dst, int fromByteInDst, int zDst);


/**Handles received data and returns the number of available bytes from this request after calling rxData..(...).
 * This routine is adequate the pattern of stepRx_Com_HALemC(...) in emC/HAL/Serial_HALemC.h
 */
extern_C int stepRx_SPI_Com_HALemC ( Com_HALemC_s* thiz);



#endif //HGUARD_Spi_HALemC
