#ifndef __fw_StateMachine_h__
#define __fw_StateMachine_h__

typedef enum ETrans_States_emC_t
{
  mEventConsumed_States_emC = 0x01
, mTransit_States_emC = 0x2
, mStateEntered_States_emC = 0x4
, mRunToComplete_States_emC = 0x10
} ETrans_States_emC;



#endif  //__fw_StateMachine_h__