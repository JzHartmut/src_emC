#ifndef HGUARD_SystemSettings_HALemC
#define HGUARD_SystemSettings_HALemC

#include <compl_adaption.h>

/**This struct contains some clock specifications
 * valid for the whole embedded system
 * specified as const
 * processed in the Hardware, CPU initialization
 * able to use in some parts of the application which should convert timings in number of counts
 * for example for a pulse width modulation.
 * <br/>
 * The used specifications are for a universal typical approaches in embedded targets.
 * If a specific target hardware does not support a specific clock or function
 * then let it unused. It needs only less bytes on const memory (Flash)
 * If a target cannot differ for some clocks or has specific ratio,
 * then the correct values should be used for that target specification.
 * The values itself are target specific. The structure is common.
 * Hence the structure definition is given in this common header file.
 *
 * The Hardware Abstraction Layer is common and equal for all targets.
 */
typedef struct SystemSettings_HwCpu_emC_T {
  int const clkCpu_ns;        //: CPU Clock in 100kHz, 2000 is 200 MHz
  int const clkSerial_ns;  //: same for serial peripheral components.
  int const clkPWM_ns;
} SystemSettings_HwCpu_emC;


//Note: this define may be a part of the specific target.
#define INIZ_fast_SystemSettings_HwCpu_emC(CPUCLK_ns) { \
 CPUCLK_ns, CPUCLK_ns, CPUCLK_ns *2 }

#define INIZ_CpuClk_SerClk_PwmClk_SystemSettings_HwCpu_emC(CPUCLK_ns, SERCLK_ns, PWMCLK_ns) { \
 CPUCLK_ns, SERCLK_ns, PWMCLK_ns }

//unfortunately Visual Studio 2015 cannot do so:
#if 0
  .clkCpu_ns = CPUCLK_ns \
, .clkSerial_ns = CPUCLK_ns \
, .clkPWM_ns = CPUCLK_ns *2 }
#endif

/**Access from outside only with const. Defining as constant. */
extern_C SystemSettings_HwCpu_emC const systemSettings_HwCpu_emC;

#endif //HGUARD_SystemSettings_HALemC
