#ifndef HGUARD_AsciiMoni_emC
#define HGUARD_AsciiMoni_emC
#include <applstdef_emC.h>
#include <emC/InspcTargetSimple/IfcTargetProxy_Inspc.h>
#include <emC/InspcTargetSimple/Target2Proxy_Inspc.h>

/**The ascii monitor is only a simple functionality for an embedded system
 * to access with a simple terminal program like putty.
 * It has only basicly functionality.
 *
 * An important feature: The ascii monitor can work together with a specific binaray monitor.
 * If the received data are detect as binary information the specific routine ... TODO is invoked
 * to handle it. It should be implemented outside of this source, or implemented as empty.
 * The usage of virtual is avoided because .... safety.
 *
 */
class AsciiMoni_emC {

protected:
  int channelRx;    //:The serial channel which is used by the Monitor

  int channelTx;    //:The serial channel which is used by the Monitor

  int channelEcho;

  int ctEvalRx;     //:counter to view activity

  int32 timeLastRx; //:timestamp for re-init if nothing is received.

  int32 timeoutRx;  //:if after this nrof Clock no more is received, reset the buffer.

  int zRx;   //:Number of received chars yet.

  int ixInspcTelg;  //:if >=0 then an inspcTelg is receiving.

  int stateRxInspcTelg; //:1 then receives InspcTelg

  int ixCharEcho; //:Index in received data echoed.

  int ixCharChecked;  //index in receive data checked for 0x0d.

  int zCmd;           //: >=0 then execute cmd, ==0: only RETURN pressed.

  int zPendingTx;  //:Number of chars which are not transmitted from the last tx call.

  int test_txPendingAfterInspc;

  int test_timeoutInRx;  //:view in debug

  int test_esc;

  int test_newline;

  int bFirst;

  int32 memaddr;     //:the last used memaddr for repeat

  void const* const mainData;

  int32 const* const reflMainData;

  /**The buffer as one word per mem unit. It is because StringPacked is used.*/
public: TelgProxy2Target_Inspc_s rxInspc;
public: TelgTarget2Proxy_Inspc_s txInspc;

public: char rxBuffer[32];      //:used for ascii moni cmd

public: char txCharBuffer[85];  //:used for tx ascii moni cmd

public: Target2Proxy_Inspc_s inspcAccess;  //InspectorAccess

  uint32 w1;

public: AsciiMoni_emC (void const* mainDataArg, ClassJc const* refl );


  /**Initialize with given channel number.
   * The channel number should match to the implementation of the HAL level UART communication
   * for the used hardware. It is not a general property of the application, it depends on the target.
   * Hence it should be a parameter of the application.
   */
  public: void init ( int rxChannelRx, int channelTx, int channelEcho);

  /**step should be called cyclically either in a lower prior interrupt
   * or in the back loop with a guaranteed maximal cycle.
   * That approach avoids the necessity of special interrupts which bedevils the system.
   * The calling cycle should be lesser than the expectable receive cycle of commands.
   * Because the commands comes usual from manual inputs, it is a long time (>100 ms).
   * If the input comes from an automate, it should be lesser.
   * But this is not the approach of this simple monitor.
   */
  public: int step ( );

  public: int evalRx ( );

  private: virtual int evalCmd ( int zCmd );

  private: void initRx();
};

#endif //HGUARD_AsciiMoni_emC
