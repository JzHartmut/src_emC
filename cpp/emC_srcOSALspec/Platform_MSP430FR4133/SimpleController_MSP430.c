#include <emC/HAL/SimpleController.h>
#include <msp430.h>



// hint better writing style: It is better to use immediately constants -> lesser effort to look what's that.
// you can immediately compare this programming with the datasheet register description.
// UM-pg in User manual https://www.ti.com/lit/ug/slau445i/slau445i.pdf
// LP-pg in Launchpad https://www.ti.com/lit/ug/slau595b/slau595b.pdf
// CM-pg in Controller manual https://www.ti.com/lit/ds/symlink/msp430fr4133.pdf
// The compiler calculates in compile time the full const value as one machine code instruction!



void initGeneralHw_SimpleController_HALemC(void) {
   WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer
   PM5CTL0 = 0x0030;   //This is a specific Power Mode control register, see data sheet.

}


/**Initialize for full speed clock*/
void initClockFast_SimpleController_HALemC(void) {
  CSCTL1 = 0x3b;    // Select 16 MHz clock, modulation disabled.
  FRCTL0 = 0xa510;  //A5 is the password, 1 waitstate see datasheet slas865e, Dec-2019, page 15
  FRCTL0_H = 0;     //close access with wrong password
  CSCTL2 = 0 <<8    //FLLD = 0, fDCLCLK/1 divider
         | 0x1f;    //FLLN Multiplier bits (??)
  TA0CTL = 4;       // first clear all timer register
  TA0CTL = (2 <<8)  // SMCLK  See User Manual slau445i, page 384
         + (0 <<6)  // CLK divider 1
         + (2<<4)   // continuous mode
         + (0 <<2)  // no clear
         + (0 <<1)  // no interrupt
         + (0 <<0)  // clear flag
         ;          // with them the timer should count continous
}


void initTimer1_simpleController_HALemC(int maxCt, int ct1pwm, int ct2pwm) {
  TA1CTL |= 0x04;            // TACLR: set all register of this timer to zero
  TA1CCTL1 = OUTMOD_6;       // CCR1 reset/set  (UM-pg 478)
  TA1CCTL2 =       // Capture/Compare Control register (UM-pg 478)
      (0 << 14)    // CM capture mode 0=no, 1/2/3= rising/falling/both edge
    | (0 << 12)    // CCIS capture input 0=CCI2A = P8.3, 1=CCI2B (CM-pg 47)
    | (0 << 11)    // SCS 0=asyn input, 1=capture input with timer clk sync
    | (0 << 10)    // read here Latched compare input
    | (0 << 8)     // CAP 0=compare 1=capture mode
    | (6 << 5)     // OUTMOD 6 = reset/set, see UM-pg 470ff
    | (0 << 4)     // CCIE interrupt enable
    | (0 << 3)     // CCI read here CCIS input
    | (0 << 2)     // OUT value of the output immediately setable here
    | (0 << 1)     // COV capture overflow read and reset by software
    | (0 << 0)     // CCIFG interrupt flag read and reset by software
    ;
  TA1CCR0 = maxCt;        // counter end value for 16 MHz clock
  TA1CCR1 = ct1pwm;    // CCR1 PWM duty cycle
  TA1CCR2 = ct2pwm;    // CCR2 PWM duty cycle
  TA1CTL = (2 << 8)    // TASSEL_2, using SMCLK as input, the full system clock
         | (0 << 6)    // ID input divider for the clock = 1 (1, 2, 3 for 1:2, 1:4, 1:8)
         | (1 << 4)    // MC timer mode (0=stop, 1=up, 2=cont till 0xffff)
         | (0 << 2)    // TACLR was set above already
         | (1 << 1)    // TAIE Interrupt enable
         | (0 << 0);   // TAIFG Interrupt flag not to reset.
}


void setPulseWidth_PWM2_HALemC ( int value ) {
  //TA1CCR1 = value;  //Test it is output PWM 1 or 2
  TA1CCR2 = value;
  if(TA1R > value) {
    //reset output immediately because it is possible that TA1CCR2 is set too late.
    //With the last value it is not reset till now, with the new value it may be reset before.
    //Without this manually set this period may be faulty, which is a faulty output value.
    TA1CCTL2 &= ~(1<<2);     // produces a clear bit machine statement.
    //
  }
}



void initClockCnt_SimpleController_HALemC(void) {
  // Initializierung des Timer_A
  TA0CTL = 0x4;// set all register of Ta0CTL to zero
  TA0CCR0 = 0xFFFF; // not used
  TA0CTL = 0x2 << 8  //TASSEL = SMCLK
         | 0   << 6  //ID=0 input clock divider = 1
         | 2   << 4  //MC=2 continous mode
         | 0   << 0;  //no interrupt
}


//Necessary cast from unsigned to signed int. The type int is proper for this controller.
int volatile* const addrTimer0_TICPU = (int volatile*)&TA0R;

bool isBusyAdc_SimpleController_HALemC ( ) {
  return (ADCCTL1 & 0x01);       // Bit 0: ADCBUSY
}

void startAdc_SimpleController_HALemC ( int chn ) {
  ADCCTL0 |= 1; // Bit 0: ADCSC software trigger UM-pg 561
}


int getValueAdc_SimpleController_HALemC ( int chn ) {
  return ADCMEM0;
}



void enableAdc_SimpleController_HALemC(void) {
  ADCCTL0 |= 0x0002;  //Bit 1 ADCENC
}

