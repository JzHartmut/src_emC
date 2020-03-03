#ifndef DEF_StateFnCall_StateM_emC
#define DEF_StateFnCall_StateM_emC
#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>

struct StateFnCall_StateM_emC_T;
struct StateMnTopFnCall_State_emC_T;
struct StateMPartFnCall_StateM_emC_T;


/*@CLASS_C StateFnCall_StateM_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@q*/


/**Function prototype as type for entry action. 
 * @arg thiz it is the const state, it may be known in the implementation, given here to enabling an significance check
 * @arg stmn the Statemachine. stmn[thiz->ixStmn] is set with the state.
 * @arg idEvent a given event, from 0, or -1 if no event is given.
 * @arg dataEvent possible data of the event.
 * @arg dataClass the reference of the data of the class of any type. 
 */
typedef void DoEntry_StateFnCall_StateM_emC(struct StateFnCall_StateM_emC_T const* thiz 
  , struct StateMnTopFnCall_State_emC_T* stmn
  , int32 const idEvent, ObjectJc* const dataEvent, ObjectJc* const dataClass);


/**Function prototype as type for exit action. 
 * @arg thiz it is the const state, it may be known in the implementation, given here to enabling an significance check
 * @arg stmn the Statemachine. stmn[thiz->ixStmn] maybe marked as inactive.
 * @arg idEvent a given event, from 0, or -1 if no event is given.
 * @arg dataEvent possible data of the event.
 * @arg dataClass the reference of the data of the class of any type. 
 */
typedef void DoExit_StateFnCall_StateM_emC(struct StateFnCall_StateM_emC_T const* thiz 
  , struct StateMnTopFnCall_State_emC_T* stmn
  , int32 const idEvent, ObjectJc* const dataEvent, ObjectJc* const dataClass);


/**Function prototype as type for one transition and its action. 
 * @arg stmn The base class of the whole state machine to access all sub statemachines,
 *    the index of the sub statemachines are stored as const in the used state const data.
 * @arg idEvent Is is an inout-argument: set to -1 if the event was used.
 * @arg dataEvent The data to the event also valid for RunToCompletion cycles only with conditions
 * @arg dataClass The data of the appropriate class (C-struct) where the statechart is member on.
 */
typedef  struct StateFnCall_StateM_emC_T const* CheckTrans_StateFnCall_StateM_emC (
  struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn, 
  int32* idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass);



/**One per state as const data refers the operations for the state.*/
typedef struct StateFnCall_StateM_emC_T {

  char const* name;

  /**Any id able to use for user, not used for statemachine framework. 
   * Recommention: Only the end states have an id, all composite state have id==0 
   * All parallel states should have an id in an extra bit range.
   */
  int id;

  /**The index of the StateMPartFnCall_StateM_emC array where this state is member of.*/
  int ixStmn;

  /**The index of the StateMPartFnCall_StateM_emC array where nested states are stored.
   * If the state has zParallelStmn >0 this is the index of the first parallel state.*/
  int ixNestedStmn;

  /**0 or the number of parallel nested sub-statemachines (number of orthogonal regions) */
  int zParallelStmn;

  struct StateFnCall_StateM_emC_T const* parentState;

  /**A possible entry action. left null if no special entry action is need.*/
  DoEntry_StateFnCall_StateM_emC* doEntry;

  /**A possible exit action. left null if no special exit action is need.*/
  DoExit_StateFnCall_StateM_emC* doExit;

  /**A possible trans action. Left null if the state has no transitions.*/
  CheckTrans_StateFnCall_StateM_emC* checkTrans;

} StateFnCall_StateM_emC;



/**At least necessary action on entry: set the state as active.
 * This routine should be called firstly in a users entry after them special entry actions. 
 * This routine is delivered as inline for calctime-optimized code.
 */
inline StateFnCall_StateM_emC const*  doEntry_StateMFnCall_emC(struct StateFnCall_StateM_emC_T const* thiz 
  , int kindHistory, struct StateMnTopFnCall_State_emC_T* stmn
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass);


/**Set the partial state machine as inactive. 
* This routine should be called firstly in a users trans action 
* starting from the own inner non-composite state, 
* then for all necessary leaved composite states. 
* The exit-Action references as function pointer in the adequate states will be executed. 
* This routine is delivered as inline for calctime-optimized code.
*/
inline void doExit_StateMFnCall_emC(struct StateFnCall_StateM_emC_T const* thiz 
  , struct StateMnTopFnCall_State_emC_T* stmn
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass);

/**Set the partial and composite state machine as inactive. 
 * This routine should be called firstly in a users trans action 
 * starting from the known inner composite state, 
 * if the transition source is a composite state. 
 * All inner and parallel states will be exited.
 * Do not call this routine if the inner state are guaranteed exited already.
 * Then its exit actions will be executed faultily a second time.
 * The exit-Action references as function pointer in the adequate states will be executed. 
 */
void doExitComposite_StateMFnCall_emC(struct StateFnCall_StateM_emC_T const* thiz 
  , struct StateMnTopFnCall_State_emC_T* stmn
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass);




/**Default trans operation if the state has not a transition, it returns false. */
CheckTrans_StateFnCall_StateM_emC checktransDefault_StateFnCall_emC;



/*@CLASS_C StateMPartFnCall_StateM_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@q*/


/**This is a part of a statemachine, one composite state, one orthogonal area etc. */
typedef struct StateMPartFnCall_StateM_emC_T {

  /**The index of this sub stateMachine. It has to be match to the state->ixStmn. This variable is for safety check. */
  int16_t ixStmn;

  /**=1 then this Part of the state machine (for a composite state) is active. The state is valid.
   * =0 then the state remain stored to enable history re-enter.*/ 
  int16_t active;

  /**It is a debug counter, to check how often any state switch is done. */
  int ctEntry; //Note: regard packed memory. For 16 bit it is an int16. For 64 bis it fills up to 64 bit, 8-byte-alignment. 

               /**The state contains the trans function pointer, a name etc. */
  StateFnCall_StateM_emC const* state;  //Note: uses 8 Byte in 64 bit system, 4 Byte in 32-bit-System.    

                                        /**The state contains the trans function pointer, a name etc. */
  StateFnCall_StateM_emC const* initState;  //Note: uses 8 Byte in 64 bit system, 4 Byte in 32-bit-System.    

} StateMPartFnCall_StateM_emC;



inline StateFnCall_StateM_emC const* getState_StateMPartFnCall_StateM_emC ( StateMPartFnCall_StateM_emC const* thiz) {
  return thiz->active ? thiz->state : null;
}


/**Helper for const initializing with { ... }
 * @arg IX The index from 0 (for top state) in the stmnPart-array
 * @arg INITSTATE instance of the initial state (without dereferencing)
 */
#define INIZ_StateMPartFnCall_StateM_emC(IX, INITSTATE) { IX, 0, 0, &INITSTATE, &INITSTATE }


/*@CLASS_C StateMnTopFnCall_State_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@q*/


/**This is the top part of a statemachine */
typedef struct StateMnTopFnCall_State_emC_T {
  union { ObjectJc obj; } base;
  
  int nrofSubStmn;

  int _d1;

  StateMPartFnCall_StateM_emC substmn[1]; 
} StateMnTopFnCall_State_emC;

/**Helper for const initializing with { ... }
* @arg IX The index from 0 (for top state) in the stmnPart-array
* @arg INITSTATE instance of the initial state (without dereferencing)
*/
#define INIZ_StateMnTopFnCall_StateM_emC(OBJ, REFL, NRPARTS, INITSTATE) \
  { { INIZ_ObjectJc((OBJ), REFL, 0) } \
  , NRPARTS \
  , 0 \
  , { { 0, 0, 0, &INITSTATE, &INITSTATE } } \
  }





/**Initializes the state machine. */
void init_StateFnCall_StateM_emC(StateMnTopFnCall_State_emC* thiz, StateFnCall_StateM_emC const* stateInit);

inline StateFnCall_StateM_emC const* getState_StateMnTopFnCall_StateM_emC ( StateMnTopFnCall_State_emC const* thiz) {
  return getState_StateMPartFnCall_StateM_emC(&thiz->substmn[0]);
}


/**Central step routine for the whole statemachine. 
 * @arg thiz it refers the representant of the Statemachine with possible some sub statemachines.
 * @arg idEvent a given event, from 0, or -1 if no event is given.
 * @arg dataEvent possible data of the event.
 * @arg dataClass the reference of the data of the class of any type. 
 */
void step_StateFnCall_StateM_emC ( StateMnTopFnCall_State_emC* const thiz
  , int32 const idEvent, ObjectJc* const dataEvent, ObjectJc* const dataClass);


/*@INLINE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


StateFnCall_StateM_emC const* doEntryHistory_StateMFnCall_emC__(struct StateFnCall_StateM_emC_T const* thiz 
  , int kindHistory, struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
);



inline StateFnCall_StateM_emC const* doEntry_StateMFnCall_emC(struct StateFnCall_StateM_emC_T const* thiz 
  , int kindHistory, struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
) {
  StateFnCall_StateM_emC const* state = thiz;
  StateMPartFnCall_StateM_emC* substmn = &stmn->substmn[state->ixStmn];;
  substmn->state = state; 
  substmn->active = 1;
  substmn->ctEntry += 1;
  if(state->doEntry !=null) {
    state->doEntry(state, stmn, idEvent, dataEvent, dataClass);
  }
  if(kindHistory !=0 && state->ixNestedStmn >0) {
    state = doEntryHistory_StateMFnCall_emC__(thiz, kindHistory, stmn, idEvent, dataEvent, dataClass);
  }
  return state;
}

inline void XXXdoEntry_StateFnCall_emC(struct StateFnCall_StateM_emC_T const* thiz , struct StateMPartFnCall_StateM_emC_T* substmn ) {
  substmn->state = thiz;
  substmn->active = 1;
  substmn->ctEntry += 1;
}



inline void doExit_StateMFnCall_emC(struct StateFnCall_StateM_emC_T const* thiz 
  , struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
  ) {
  StateMPartFnCall_StateM_emC* substmn = &stmn->substmn[thiz->ixStmn]; 
  substmn->active = 0;
  if(thiz->doExit !=null) {
    thiz->doExit(thiz, stmn, idEvent, dataEvent, dataClass);
  }
}



#endif //DEF_StateFnCall_StateM_emC

