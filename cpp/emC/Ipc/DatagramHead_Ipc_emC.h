#ifndef HGUARD_DatagramHead_Ipc_emC
#define HGUARD_DatagramHead_Ipc_emC
#include <emC/Base/Endianness_emC.h>

/**This structur is the start of a datagram due to the Inspector-Communication defined in vishia Software.
 * see https://vishia.org/Inspc/html/InspcComm.html
 * Note that all data should transmit and receive in Big Endian. To reduce trouble with hton etc.
 * the Endianess_emC.h is used. With that system errors are prevented by obvious compiler error messages.
 * To set and read a value use set/getInt16BigEndian(...) etc.
 */
typedef struct DatagramHead_Ipc_emC_T {
  
  int16BigEndian nrofBytes;
  
  int16BigEndian cmd;
  
  int32BigEndian encryption;
  
  int32BigEndian seqnr;
  
  int16BigEndian answer;
  
  int16BigEndian entrant;

} DatagramHead_Ipc_emC_s;


/**One information item in the datagram should start with this 4 bytes.
 * After them any payload is possible.
 */
typedef struct DatagramItem_Ipc_emC_T {
  
  int16BigEndian nrofBytes;
  
  int16BigEndian cmd;
  
} DatagramItem_Ipc_emC_s;



#endif //HGUARD_DatagramHead_Ipc_emC
