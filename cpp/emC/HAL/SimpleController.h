#ifndef HGUARD_emCHAL_SimpleController
#define HGUARD_emCHAL_SimpleController
/**This file defines the interface to standard features of controllers in a well usable form.
 * The implementation should be done for any necessary controller in the proper way.
 */

#include <applstdef_emC.h>

/**Initialize for full speed clock*/
extern void initClockFast_SimpleController_HALemC(void);


/**This operation contains some specific operations which are valid for this Controller
 * in the Launchpad hardware, independent of the application.
 */
extern void initGeneralHw_SimpleController_HALemC(void);


/**This file should be implemented in the target- and application specific part of the software
 * proper to the application or application group.
 * Usual the programming of all port properties (Input, Output, Pullup, special usage) should be done
 * for the overall hardware proper to the application.
 */
extern void initPorts_SimpleController_HALemC ( void );


extern void initClockCnt_SimpleController_HALemC(void);

/**The timer is mapped to a memory address. The address is set as const value.
 * It can be used after timer initialization. This simple approach is proper for most of controller.
 * The definition of this const pointer is done beside the initTimer0...  implementation.
 * The associated getClockCnt_Time_emC() is contained in the compl_adaption.h because may be CPU-specific.  */
extern_C int volatile* const addrTimer0_TICPU;



/**Init the first timer on hardware, with a specific end value for counting and PWM values.
 * Which timer, which clock speed depends on the given hardware.
 * This is a common interface maybe fulfilled by some controller.
 * @param maxCt end value
 * @param ct1pwm first counter value for a PWM output depending on the capability of the timer
 * @param ct2pwm first counter value for a PWM output depending on the capability of the timer
 * */
extern void initTimer1_simpleController_HALemC ( int maxCt, int ct1pwm, int ct2pwm);



extern void setPulseWidth_PWM2_HALemC ( int value );


extern void initAdc_SimpleController_HALemC ( void);


extern void enableAdc_SimpleController_HALemC ( void);

extern bool isBusyAdc_SimpleController_HALemC ( );

extern void startAdc_SimpleController_HALemC ( int chn );



/**Get the value from the last measurement started with start_Adc_HAL(...)
 *
 */
extern int getValueAdc_SimpleController_HALemC ( int chn );

#endif //HGUARD_emCHAL_SimpleController
