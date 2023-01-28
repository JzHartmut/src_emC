//comment ...


#include <emC/HAL/SimpleController.h>
#include <applstdef_emC.h>
#include <msp430.h>



void initLCD_SimpleController_HALemC() {
  // Disable the GPIO power-on default high-impedance mode
  // to activate previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;// I/O Pins entsperren
  //0b = LPMx.5 configuration is not locked and defaults to its reset condition.
  //1b = LPMx.5 configuration remains locked. Pin state is held during LPMx.5 entry
  //and exit.

  // Configure LCD pins
  SYSCFG2 |= LCDPCTL;                                        // R13/R23/R33/LCDCAP0/LCDCAP1 pins selected

  LCDPCTL0 = 0xFFFF;
  LCDPCTL1 = 0x07FF;
  LCDPCTL2 = 0x00F0;                                         // L0~L26 & L36~L39 pins selected

  LCDCTL0 = LCDSSEL_0 | LCDDIV_7;                            // flcd ref freq is xtclk

  // LCD Operation - Mode 3, internal 3.08v, charge pump 256Hz
  LCDVCTL = LCDCPEN | LCDREFEN | VLCD_6 | (LCDCPFSEL0 | LCDCPFSEL1 | LCDCPFSEL2 | LCDCPFSEL3);

  LCDMEMCTL |= LCDCLRM;                                      // dfClear LCD memory

  LCDCSSEL0 = 0x000F;  //L0...L15                                        // Configure COMs and SEGs
  LCDCSSEL1 = 0x0000;   //L16..L31                                     // L0, L1, L2, L3: COM pins
  LCDCSSEL2 = 0x0000;   //L32..L47

  LCDM0 = 0x21;                                              // L0 = COM0, L1 = COM1
  LCDM1 = 0x84;                                              // L2 = COM2, L3 = COM3

  LCDCTL0 |= LCD4MUX | LCDON;                                // Turn on LCD, 4-mux selected

  PMMCTL0_H = PMMPW_H;                                       // Open PMM Registers for write
  PMMCTL0_L |= PMMREGOFF_L;                                  // and set PMMREGOFF

  //__bis_SR_register(LPM3_bits | GIE);                        // Enter LPM3.5

}



/*     ---7-------     Bitnumber per segment 15..0
 *    |\    |    /|
 *    | 15  14  / |      pos     pos   bit 10: Special segment,
 *    2  \  |  13 6      LCDM4W    1   leading -
 *    |   \ | /   |      LCDM6W    2   colon after 2. char (for hh:mm)
 *     -1--- ---0-       LCDM8W    3   Transmission symbol left
 *    |   / | \   |      LCDM10W   4   colon after 4. char
 *    3  /  |  9  5      LCDM2W    5   Grad symbol after 5. char
 *    | 11  12  \ |      LCDM18W   6   TX, instead decimal point
 *    |/    |    \|                    (bit 8): RX on transmission symbol
 *     ---4-------   o8
 *
 *   LCD8W.10  LCDM12W Bit:
 *       ___   0  2   3   1   8  5  9  6 10  8 11   4
 *        |    !  â?¤      â?²     (R)  [ XX XX XX XX XX XX ] |
 *      TX RX
 * Bit: 10  8  in LCDM18W
 *
 *
 * -                 :                  :        Â°   bit 10
 *
 *   LCDM4W   LCDM6W   LCDM8W   LCDM10W   LCDM2W   LCDM18W
 *
 *
 * LCDM12W  specials:
 * hexa
 * 0xf000 not used
 * 0x0800                      X
 * 0x0400                    X
 * 0x0200                  X
 * 0x0100                [       ]
 * 0x0080                     X
 * 0x0040                   X
 * 0x0020                 X
 * 0x0010                         |
 * 0x0008           â?²          (a clock)
 * 0x0004        â?¤                  (a hart)
 * 0x0002             (R)
 * 0x0001      !
 *
 * 0x0fe0                [XXXXXX]
 * 0x0ee0                 XXXXXX    see table charbar
 * 0x0e60                [XXXXX ]
 */



static const uint16 segmentCoding[] =  //index of table is ascii value frm 0x 30 =^`0`, content of table is segment pattern
{
    0x0000,    // " "
    0x01c0,    // "!"
    0x0000,    // """
    0x0000,    // "#"
    0x0000,    // "$"
    0xaa27,    // "%"
    0x0000,    // 0x26 "&"
    0x0000,    // 0x27 "'"
    0x0000,    // 0x28 "("
    0x0000,    // 0x29 ")"
    0xfa03,    // 0x2a *
    0x5003,    // 0x2b +
    0x0008,    //:0x2c ,
    0x0003,    //:0x2d -
    0x0100,    //:0x2e .
    0x0000,    //:0x2f /

    0xFC,    // "0"
    0x60,    // "1"
    0xDB,    // "2"
    0xF3,    // "3"
    0x67,    // "4"
    0xB7,    // "5"
    0xBF,    // "6"
    0xE4,    // "7"
    0xFF,    // "8"
    0xF7,    // "9"
    0x00,    //:0x3a: :
    0x00,    //:0x3b  ;
    0x00,    //:0x3c  <
    0x00,    //:0x3d  =
    0x00,    //:0x3e  >:
    0x00,    //:0x3f  ?
    0x00,    //0x40 @:
           //;
  //...
    0xef,    //0x41 A
    0x3f,    //B
    0x9c,    //C
    0x7b,    //D
    0x9f,    //E
    0x8f,    //F
    0x00BD   //G
    ,   0x6F    // H
    ,   0x5090  // I
    ,   0xF0    // J
    ,   0x220E  // K
    ,   0x1C    // L
    ,   0xA06C  // M
    ,   0x826C  // N
    ,   0xFC    // o
    ,   0xCF    // p
    ,   0xE7    // q
    ,   0xCC    // r
    ,   0xB7    // s
    ,   0x5080  // t
    ,   0x7C    // u
    ,   0x280C  // v
    ,   0x57    // w   0x57
    ,   0xAA00    // x   0x58
    ,   0x8061    // y   0x59
    ,   0x2890  // z
    ,   0xF7  // a
    ,   0x3F  // b
    ,   0x1B  // c
    //,   0x7B  // d
    ,   0xDF  // e
};


//positions of digits in LCDMEM
static int posAssociation[] = { 2, 3, 4, 5, 1, 9 }; //{ 4, 6, 8, 10, 2, 18 };




/**Set a character to the LCD display.
 * @param pos Position of the character at display, 0 = first position.
 * @param cc The character to present, only 0..9 admissible
 */
void setCharLCD_SimpleController_HALemC(int pos, char ccharacter){
  int ixSegmentCodingIndex = ((int)(ccharacter)) - (int)('0');       //table starts with '0'
  int ixLCDMEM = posAssociation[pos];
  LCDMEM[ixLCDMEM] = segmentCoding[ixSegmentCodingIndex];
}




void setTextLCD_SimpleController_HALemC(char const* text) {
  int ix = 0;
  char c1 = *text++;
  while(ix < 7 && c1 !=0) {
    char c2 = *text;
    uint16 segm = 0;
    if(c1 >= ' ' && c1 <= 'z') {
      segm = segmentCoding[((int)c1) - ((int)' ')];
    }
    if(c2 == '.') {
      segm |= 0x100;
      text +=1;
    }
    int ixLCDMEM = posAssociation[ix];
    (&LCDM0W)[ixLCDMEM] = segm;
    ix +=1;
    c1 = *text++;
  }
}

