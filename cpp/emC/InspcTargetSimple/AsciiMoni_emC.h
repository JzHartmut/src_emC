#ifndef HGUARD_emC_InspTS_AsciiMoniSimple    //respect max. 32 chars for older compiler
#define HGUARD_emC_InspTS_AsciiMoniSimple
#define HGUARD_emC__InspcTargetSimple__AsciiMoniSimple  //full qualified
#include <applstdef_emC.h>
#include <emC/Base/EventTask_emC.h>

typedef struct AsciiMoni_emC_T {
  union {ObjectJc obj; } base;

  union flags_AsciiMoni_emC_T {
    struct Values_AsciiMoni_emC_T{
      uint16 bitValue16;
      uint8 channel;
      uint8 ixRxChars;         // Number of character currently in rxBuffer
    } val;

    struct Bits_AsciiMoni_emC_T{
      uint16 bEcho : 1;      // if 1 then echo any character, depends on monitor on PC.
      uint16 bRxTxAnswer: 1; // answer given
      uint16 bTxState : 1;   // tx status info in 1 second step
      uint16 dummy:1;        // use 4 bits for this block
      uint16 nShowFormat: 4;           // 0-byte 1-word 2-quad 3-float 4..7 decimal 1..4 byte
      uint16 nShIncrMemAddr :2;        // 1=2 byte, 2=4 byte 3= 8 byte
      uint16 bIncrMemAddr: 1;          // + cmd given, next memory location
      uint16 bTxFirstNewline : 1;
    } bit;
  } flags;

  intPTR lastMemAddr;
  int nrofValuesToShow;
  int ixValuesToShow;

  /**Buffer for received characters may be immediately used in interrupt of serial driver
   * or written with stepRx_Serial_HALemC(...) depending on hardware adaption.
   */
  char rxBuffer[20];

  char txBuffer[20];

} AsciiMoni_emC_s;


extern_C void ctor_AsciiMoni_emC ( AsciiMoni_emC_s* thiz, int nrSerialChn);

/**It can/should be called cyclically with an alive message to detect that the serial comm is proper
 * and the system runs.
 * Should not transmit any what if Monitor communication is pending.
 */
extern_C void txStatus_AsciiMoni_emC ( AsciiMoni_emC_s* thiz, char const* text);

/**step should be called cyclically either in a lower prior interrupt
 * or in the back loop with a guaranteed maximal cycle.
 * That approach avoids the necessity of special interrupts which bedevils the system.
 * The calling cycle should be lesser than the expectable receive cycle of commands.
 * Because the commands comes usual from manual inputs, it is a long time (>100 ms).
 * If the input comes from an automate, it should be lesser. For example 2 ms for command length of 20 Bytes with 115200 Baud.
 */
extern_C void step_AsciiMoni_emC ( AsciiMoni_emC_s* thiz);


#endif //HGUARD_emC_InspTS_AsciiMoniSimple
