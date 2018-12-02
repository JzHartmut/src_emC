#ifndef __SystemInit_emC_h__
#define __SystemInit_emC_h__
typedef struct SystemInit_emC_t {
  
  int32 ctCycle;

  int32 initDone;

} SystemInit_emC;


/**A static instance to manage initialization. Singleton. */
extern SystemInit_emC* systemInit_emC;

#endif __SystemInit_emC_h__
