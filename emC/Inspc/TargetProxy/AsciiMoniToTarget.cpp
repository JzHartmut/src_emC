#include <emC/Inspc/TargetProxy/AsciiMoniToTarget.h>
#include <emC/HAL/Serial_HALemC.h>


/**Command from console to target.
 * any received cmd (from keyboard) should be forwarded without change.
 * zCmd does not contain any line end or RETURN.
 * The target needs RETURN ('\r'), this is appended.
 * It is possible to pre-filter the cmd here. 
 */
int AsciiMoniToTarget_InspcTargetPrx_emC::evalCmd ( int zCmd) {


  int comTarget = 7;                             //rx from Console forward to target.
  this->zPending = txChar_Serial_HALemC(comTarget, this->rxBuffer, 0, zCmd);
  this->zPending = txChar_Serial_HALemC(comTarget, "\r", 0, 1);   //The command should be terminated with RETURN
  return zCmd;
}
