#ifndef __SystemInit_emC_h__
#define __SystemInit_emC_h__




/**Helper of system structure for control initializing:
 * Intializing should be done in a loop till all modules have its aggregations.
 * One module should do anything because its object(s) (composites) are forwarded to other modules.
 * The other modules should know aggregations to success initializing. 
 * Deadlocks are possible, but that is a faulty in module build. The most of modules should unconditionally offer their data reference.  
 */
typedef struct SystemInit_emC_t {
  
  /**Counter for initializing cycles, the value after intializing shows how many cycles were need. Should be 1..2..10.
   * It is possible to abort the program if initializing does not success in a expected number of cycles.
   */
  int32 ctCycle;

  /**On start of each cycle this variable is set to 1. If any module cannot successed its initializing, it set initDone = 0. 
   * Therefore the initializing is repeated.
   */
  int32 initDone;

} SystemInit_emC;


/**A static reference to manage initialization. Singleton. The reference should be set in startup of main. */
extern SystemInit_emC* systemInit_emC;

#endif //__SystemInit_emC_h__
