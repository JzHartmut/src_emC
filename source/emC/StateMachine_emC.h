#ifndef __fw_StateMachine_h__
#define __fw_StateMachine_h__

typedef enum ETrans_States_Fwc_t
{
  mEventConsumed_States_Fwc = 0x01
, mTransit_States_Fwc = 0x2
, mStateEntered_States_Fwc = 0x4
, mRunToComplete_States_Fwc = 0x10
} ETrans_States_Fwc;



#endif  //__fw_StateMachine_h__