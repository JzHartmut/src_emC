#include <emC_Ctrl/Ctrl/CalcExpr.h>
#include <emC_Ctrl/Ctrl/T1Blocks_FB.h>
#include <emC/OSAL/os_time.h>



void ctor_CalcExpr(CalcExpr* thiz, int stacksizeAdditional){
  memset(thiz, 0, sizeof(*thiz));
  thiz->ixStackMax = ARRAYLEN_emC(thiz->stack) + stacksizeAdditional;
}

void calc_CalcExpr(CalcExpr* thiz, Operation_CalcExpr* operations, int zOperations) {
  while(--zOperations >=0) { //no check of significance, should be executed in fast calc time!
    (*operations->oper)(thiz, operations->val);  //should be a valid function pointer !!!
    operations+=1;  //next pointer position
  }
}



void setF_CalcExpr(CalcExpr* thiz, void* input) {
  thiz->accu.accuF = *(float*)input;
  thiz->cType = 'F';
}

void setI_CalcExpr(CalcExpr* thiz, void* input) {
  thiz->accu.accuF = *(int32*)input;
  thiz->cType = 'I';
}

void setS_CalcExpr(CalcExpr* thiz, void* input) {
  thiz->accu.accuI = 0;  //note: set all bits of the union to 0
  thiz->accu.accuS = *(int16*)input;  //note: sign only in bit 15.
  thiz->cType = 'S';
}

void convSI_CalcExpr(CalcExpr* thiz, void* unused) {
  thiz->accu.accuI = thiz->accu.accuS;  //automatically casting to int32 sets all bits 31..16 to sigh bit
  thiz->cType = 'I';
}

void convSF_CalcExpr(CalcExpr* thiz, void* unused) {
  thiz->accu.accuF = thiz->accu.accuS;  //automatically casting to float
  thiz->cType = 'F';
}

void convIS_CalcExpr(CalcExpr* thiz, void* unused) {
  thiz->accu.accuS = (int16)thiz->accu.accuI;  //should explicitely cast, truncates higher bits.
  thiz->cType = 'S';
}

void convIF_CalcExpr(CalcExpr* thiz, void* unused) {
  thiz->accu.accuF = thiz->accu.accuI;  //automatically cast
  thiz->cType = 'F';
}

void convFI_CalcExpr(CalcExpr* thiz, void* unused) {
  thiz->accu.accuI = (int32)thiz->accu.accuF;  //should explicitely cast, truncates higher bits.
  thiz->cType = 'I';
}

void convFS_CalcExpr(CalcExpr* thiz, void* unused) {
  thiz->accu.accuI = ((int32)thiz->accu.accuF) & 0x0000ffff;  //should explicitely cast, sets bits 3..16 to 0
  thiz->cType = 'S';
}






void addF_CalcExpr(CalcExpr* thiz, void* input) {
  thiz->accu.accuF += *(float*)input;
}

void subF_CalcExpr(CalcExpr* thiz, void* input) {
  thiz->accu.accuF -= *(float*)input;
}

void mulF_CalcExpr(CalcExpr* thiz, void* input) {
  thiz->accu.accuF *= *(float*)input;
}

void divF_CalcExpr(CalcExpr* thiz, void* input) {
  thiz->accu.accuF /= *(float*)input;
}


void addFs_CalcExpr(CalcExpr* thiz, void* unused) {
  thiz->accu.accuF += thiz->stack[thiz->ixStack--].F;
}

void subFs_CalcExpr(CalcExpr* thiz, void* unused) {
  thiz->accu.accuF = thiz->stack[thiz->ixStack--].F - thiz->accu.accuF;
}

void mulFs_CalcExpr(CalcExpr* thiz, void* unused) {
  thiz->accu.accuF *= thiz->stack[thiz->ixStack--].F;
}

void divFs_CalcExpr(CalcExpr* thiz, void* unused) {
  thiz->accu.accuF = thiz->stack[thiz->ixStack--].F / thiz->accu.accuF;
}


void push_CalcExpr(CalcExpr* thiz, void* unused) {
  thiz->stack[++thiz->ixStack].I = thiz->accu.accuI; //Note: use float as int-pattern
}

void pop_CalcExpr(CalcExpr* thiz, void* levels) {
  thiz->ixStack -= (int32)(intptr_t)levels; 
}


void T1filterF_CalcExpr(CalcExpr* thiz, void* vfilter){
  T1_DF_FB* filter = (T1_DF_FB*)vfilter;
  thiz->accu.accuF = step_T1_DF_FB(filter, thiz->accu.accuF);
}


void sysclk_CalcExpr(CalcExpr* thiz, void* vfilter){
  
  thiz->accu.accuI = os_getClockCnt();
}



