

#include <emC/HAL/Serial_HALemC.h>
#include <emC/Base/StringBase_emC.h>


#include <msp430.h>


int open_Serial_HALemC ( int channel, Direction_Serial_HALemC dir
  , int32 baud, ParityStop_Serial_HALemC bytePattern){


  // Configure UART pins
  P1SEL0 |= 0x03;            // set P1.0 = TxD, P1.1 = RxD to the second function,

  UCA0CTLW0 |= 0x0001;       // UCSWRST Put eUSCI in reset
  UCA0CTLW0 |= ( 2 << 6);    // UCSSEL clock source: 3=UCSSEL__SMCLK UM-pg 539
  // ------------------------// Baud Rate calculation
  UCA0BRW = 6;               // 12000000 / 16 / 115200 = 6.5104 12 MHz with 16 * oversampling
  UCA0MCTLW = (0x20 <<8)     // UCBRSx value
            | (0x8  <<4)     // UCBRFx value see table UM-pg 590
            | (  1  <<0);    // UCOS16 1= Oversampling enable
  //-------------------------
  UCA0CTLW0 &= ~0x0001;      // UCSWRST = 0 remove reset, Initialize eUSCI
  UCA0IE |= 0x0001;          // UCRXIE Enable USCI_A0 RX interrupt


  return 0;
}


static struct SerialData_MSP430_T {
  char* rxChars;
  char const* txChars;
  uint8 zRxChars;       //size of rxChars;
  uint8 ixRxChar;       //index chars received also for interrupt in rxChars
  uint8 nrRxChar;       //nr of chars received in rxChars, returned the last time.
  uint8 zTxChars;       //nr of chars to transmit from txChars buffer
  uint8 ixTxChar;       //current index to the next char to transmit
  uint8 dummy;
} serialData_MSP430 = {0};




int getData_Serial_HALemC ( int channel, void* dst, int fromByteInDst, int zRxChars ) {
  if(serialData_MSP430.rxChars != dst) {
    serialData_MSP430.ixRxChar = fromByteInDst;      // new buffer, fill from start.
    serialData_MSP430.rxChars = (char*) dst;      // The rx buffer in user space.
  } else {
    // unchanged buffer, don't touch ixRxChar.
  }
  serialData_MSP430.zRxChars = zRxChars;
  return serialData_MSP430.nrRxChar = serialData_MSP430.ixRxChar;
}

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_Interrupt(void) {
  uint8 ix = serialData_MSP430.ixRxChar;
  if(  serialData_MSP430.rxChars !=null
    && ix < serialData_MSP430.zRxChars  ) {          // else: ignore received chars
    char cc = UCA0RXBUF;
    if(cc == 0x08 || cc==0x7f) {  //back space or DEL
      if(ix >0){ ix -=2; }  // will be incremented again
    } else {
      serialData_MSP430.rxChars[ix] = cc;  // store received byte
    }
    serialData_MSP430.ixRxChar = (uint8)(ix+1);
  }
}



int txChars_Serial_HALemC ( int const channel, char const* const text, int const fromCharPos, int const zChars) {
  int nrChars = zChars;
  if(zChars <0) {
    nrChars = strnlen_emC(text, 1000);  //till '\0'
  }
  serialData_MSP430.zTxChars = nrChars;
  serialData_MSP430.ixTxChar = fromCharPos;
  serialData_MSP430.txChars = text;
  return stepTx_Serial_HALemC(channel);          // initial forcing tx, next comes with empty buffer
}



int stepTx_Serial_HALemC ( int channel) {
  if(serialData_MSP430.txChars ==null) {           // pointer given?
    return 0;
  } else {
    int nrPending = serialData_MSP430.zTxChars - serialData_MSP430.ixTxChar;  //pending after this tx
    if(  (UCA0IFG & UCTXIFG) !=0                   // tx buffer in hardware UART is empty
      && nrPending >0                             // at least one character is pending
      ) {
      UCA0TXBUF = serialData_MSP430.txChars[serialData_MSP430.ixTxChar++];
      nrPending -=1;
    }
    if(nrPending <=0) {
      serialData_MSP430.txChars = null;
    }
    return nrPending;
  }
}



int busyTx_Serial_HAL_emC ( int channel) {
  if(serialData_MSP430.txChars ==null) {           // pointer given?
    return 0;
  } else {
    int nrPending = serialData_MSP430.zTxChars - serialData_MSP430.ixTxChar;  //pending after this tx
    return nrPending;
  }
}




int stepRx_Serial_HALemC ( int channel) {
  //can be left empty because work is done in interrupt
  return 0;
}
