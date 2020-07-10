#include <emC/StateM/StateFnCall_StateM_emC.h>


void init_StateFnCall_StateM_emC(StateMnTopFnCall_State_emC* thiz, StateFnCall_StateM_emC const* stateInit){
  thiz->substmn[0].state = stateInit;
}


/**This operation will be called for the current sub statemachine in the main level
 * and for all parallel sub statemachines.
 * It calls all parallel sub statemachines. 
 * @arg subStmn it is the top of a parallel stmn or the top of all
 */
static void stepState_StateFnCall_StateM_emC(StateMnTopFnCall_State_emC* const thiz
  , StateMPartFnCall_StateM_emC* const subStmn
  , int32* idEvent, ObjectJc* const dataEvent, ObjectJc* const dataClass) {
  int32 idEvent1 = *idEvent;
  StateMPartFnCall_StateM_emC* nestedStmn = subStmn;
  StateFnCall_StateM_emC const* state;
  //
  //Search the inner state of a nested construct:
  int abortMaxNested = 100;
  while(--abortMaxNested >=0) { //break inside
    state = nestedStmn->state; //it may be a inner substate (for deep history)
    if(state->ixNestedStmn >0 && state->zParallelStmn ==0) {
      nestedStmn = &thiz->substmn[state->ixNestedStmn];
    } else {
      break;
    }
  } 
  ASSERT_emC(abortMaxNested >0, "nested loop error", 0, 0);
  //
  int32 maxRunToCompletionCycles = 100;
  if(idEvent1 == 3 || idEvent1 == 21)
    dbgstop_emC();
  do {
    //bool bTrans = false;
    StateFnCall_StateM_emC const* newstate = null;
    do { 
      if(state->zParallelStmn >0) {
        int ixSubStmn = state->ixNestedStmn;
        int ix;
        bool bEventUsed = false;
        for(ix=0; ix < state->zParallelStmn; ++ix) {
          int32 idEventParallel = idEvent1;
          StateMPartFnCall_StateM_emC* stmnParallel = &thiz->substmn[ixSubStmn + ix];
          if(stmnParallel->active) { //possible to non active if join-transition of other parallel subStmn.
            stepState_StateFnCall_StateM_emC(thiz, stmnParallel, &idEventParallel, dataEvent, dataClass);
            if(idEventParallel == -1) { bEventUsed = true; }
          }
        }
        if(bEventUsed) {
          idEvent1 = -1;  //do not apply to the container state
        } //else: If the event is not used in any parallel stmn, it can be applied to the container statemachine. 
      }
      //
      //Check the container state of parallels, or the state itself:
      CheckTrans_StateFnCall_StateM_emC* transOp = state->checkTrans;
      if(transOp !=null) {
        newstate = transOp(state, thiz, &idEvent1, dataEvent, dataClass);
        if(newstate !=null) {
          state = newstate;
          idEvent1 = -1; //it is applied, -1 is an invalid ident
        }
      }     //note: state is the last valid state. From this get the parent.
    } while(newstate !=null && --maxRunToCompletionCycles >=0);  //Run to completion till no new state
  } while( (state = state->parentState) !=null);  //apply from inner to outer for nested states.
}




/**The only one step routine called from outside for the whole statemachine. 
 */
void step_StateFnCall_StateM_emC(StateMnTopFnCall_State_emC* const thiz
  , int32 const idEvent, ObjectJc* const dataEvent
  , ObjectJc* const dataClass) {
  StateMPartFnCall_StateM_emC* stmn1 = &thiz->substmn[0];
  int ixSubStmn = stmn1->state->ixStmn;
  if(ixSubStmn >0) {
    stmn1 = &thiz->substmn[ixSubStmn];
    //state = stmn1->state;
  }
  int32 idEvent1 = idEvent;
  stepState_StateFnCall_StateM_emC(thiz, stmn1, &idEvent1, dataEvent, dataClass);
}





/**Default trans operation if the state has not a transition, it returns false. 
 * Prototypedef: CheckTrans_StateFnCall_StateM_emC
 */
StateFnCall_StateM_emC const* checktransDefault_StateFnCall_emC  (
		struct StateFnCall_StateM_emC_T const* thiz , struct StateMnTopFnCall_State_emC_T* stmn
  , int32* idEvent, ObjectJc* dataEvent , ObjectJc* const dataClass ) {
  return null;
}

//CheckTrans_StateFnCall_StateM_emC checktransDefault_StateFnCall_emC() { return null; }


StateFnCall_StateM_emC const* doEntryHistory_StateMFnCall_emC__(struct StateFnCall_StateM_emC_T const* thiz 
  , int kindHistory, struct StateMnTopFnCall_State_emC_T* stmn 
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
  ) {

  StateFnCall_StateM_emC const* state = thiz;
  StateMPartFnCall_StateM_emC* substmn;
  while(state->ixNestedStmn >0) {

    //check history
    if(kindHistory >=1) {
      substmn = &stmn->substmn[state->ixNestedStmn]; //state maybe the parent
      if(state->zParallelStmn >0) {
        int ixParallel;
        for(ixParallel = state->ixNestedStmn; ixParallel < state->ixNestedStmn + state->zParallelStmn; ++ixParallel) {
          //recursively call of doEntry
          doEntry_StateMFnCall_emC(stmn->substmn[ixParallel].state, kindHistory, stmn, idEvent, dataEvent, dataClass);
        }
        break; //state remain.
      } else {
        state = substmn->state;
        substmn->active = 1;
        substmn->ctEntry += 1;
        if(state->doEntry !=null) {
          state->doEntry(state, stmn, idEvent, dataEvent, dataClass);
        }
      }
    } else {
      break;
    }

  } //while(true);  //break inside
  return state;
}



void doExitComposite_StateMFnCall_emC(struct StateFnCall_StateM_emC_T const* thiz 
  , struct StateMnTopFnCall_State_emC_T* stmn
  , int32 idEvent, ObjectJc* dataEvent, ObjectJc* const dataClass
  ) {
  StateFnCall_StateM_emC const* state = thiz;
  int ixNestedStmn;
  int ctNested = 1;
  while( (ixNestedStmn = state->ixNestedStmn) >0) { //break inside after exit parallel stateM
    if(state->zParallelStmn >0) {
      int ixParallel;
      for(ixParallel = ixNestedStmn; ixParallel < ixNestedStmn + state->zParallelStmn; ++ixParallel) {
        doExitComposite_StateMFnCall_emC(stmn->substmn[ixParallel].state, stmn, idEvent, dataEvent, dataClass);
      }
      break;
    } else {
      //search the most inner state:
      StateMPartFnCall_StateM_emC* stmnPart = &stmn->substmn[ixNestedStmn];
      ASSERTs_emC(stmnPart->state->parentState == state, "faulty parent-child-state",0,0);
      state = stmnPart->state; 
      ctNested +=1;  //counts the nested levels.
    }
  }
  while(--ctNested >=0) {
    if(CHECK_ASSERT_emC(state !=null, "invalied null state", 0,0)) {
      doExit_StateMFnCall_emC(state, stmn, idEvent, dataEvent, dataClass);
      state = state->parentState; //The parent state is the state of the container statemachinePart anytime.
    }
  }
}


