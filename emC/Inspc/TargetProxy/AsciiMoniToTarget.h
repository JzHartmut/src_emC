#ifndef HGUARD_emC_Inspc_AsciiMoniToTarget
#define HGUARD_emC_Inspc_AsciiMoniToTarget
#include <emC/AsciiMoni/AsciiMoni.h>


/**This is a specific 'Ascii Monitor'
 * receiving cmd from console or keyboard (CON)
 * to forward it to the target.
 */
class AsciiMoniToTarget_InspcTargetPrx_emC : public AsciiMoni_emC {

  /**Overridden variant of evalCmd. 
   * The cmd can be checked here. 
   */
  public: /*override*/ int evalCmd ( int zCmd );

};



#endif //HGUARD_emC_Inspc_AsciiMoniToTarget
