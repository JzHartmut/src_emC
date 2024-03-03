#include "WaveMng_Ctrl_emC.h"

//#include <math.h>
#include <string.h>
#include <stdlib.h>  //alloc
#ifdef __OS_IS_DSP_AD__
  #define CTOR_ObjectJc(THIZ, ADDR, SIZE, REFL, ID)
#else
  #include "genRefl/WaveMng_Ctrl_emC.crefl"
#endif


//const ClassJc refl_WaveMngIx_FB = { CONST_ObjectJc(0, (ObjectJc*)&refl_WaveMngIx_FB.object, null), "WaveMngIx_FB", 0};


void ctor_WaveMngIx_FB(WaveMngIx_FB* thiz, int identObj, int32 size, float Tstep){
  memset(thiz, 0, sizeof(*thiz)); 
  CTOR_ObjectJc(&thiz->obj, thiz, sizeof(*thiz), refl_WaveMngIx_FB, identObj);
  setInitialized_ObjectJc(&thiz->obj);
  //thiz->check = check_WaveMngIx_FB;
  thiz->zBuffer = size;
  thiz->ixNew = 0;
}



//const ClassJc refl_WaveMng_FB = { CONST_ObjectJc(0, (ObjectJc*)&refl_WaveMng_FB.object, null), "WaveMng_FB", 0};


void ctor_WaveMng_FB(WaveMng_FB* thiz, int identObj){
  CTOR_ObjectJc(&thiz->obj, thiz, sizeof(*thiz), refl_WaveMng_FB, identObj);
}


bool init_WaveMng_FB(WaveMng_FB* thiz, WaveMngIx_FB* waveIx){
  if(isInitialized_ObjectJc(&thiz->obj) ==0 && waveIx !=null) {
    thiz->waveIx = waveIx;
    thiz->zBuffer = waveIx->zBuffer;
    thiz->nrofValues = 1.0f;
    setInitialized_ObjectJc(&thiz->obj);
  }
  return true;
}




//const ClassJc refl_WaveMngCint_FB = { CONST_ObjectJc(0, (ObjectJc*)&refl_WaveMngCint_FB.object, null), "WaveMngCint_FB", 0};

WaveMngCint_FB* ctor_WaveMngCint_FB(WaveMngCint_FB* thiz, int identObj, int nrofValues){
  memset(thiz, 0, sizeof(*thiz));
  CTOR_ObjectJc(&thiz->obj, thiz, sizeof(*thiz), refl_WaveMngCint_FB, identObj);
  //thiz->check = check_WaveMngCint_FB;
  thiz->nrofValues = nrofValues;
  thiz->nVal = 1.0f / nrofValues;
  return thiz;
}



//const ClassJc refl_WaveData_FB = { CONST_ObjectJc(0, (ObjectJc*)&refl_WaveData_FB.object, null), "WaveData_FB", 0};


void ctorData_WaveData_FB(WaveData_FB* thiz, int identObj, float* data, int sizedata) 
{
  memset(thiz, 0, sizeof(*thiz));
  CTOR_ObjectJc(&thiz->obj, thiz, sizeof(*thiz), refl_WaveData_FB, identObj);
  thiz->sizeDataAllocPos = - sizedata;
  thiz->data = data;
}


void ctor_WaveData_FB(WaveData_FB* thiz, int identObj, int sizedata)
{
  int zBytesData = sizedata * sizeof(float);
  memset(thiz, 0, sizeof(*thiz));
  CTOR_ObjectJc(&thiz->obj, thiz, sizeof(*thiz), refl_WaveData_FB, identObj);
  thiz->sizeDataAllocPos = sizedata;
  thiz->data = (float*)malloc(zBytesData);
  memset(thiz->data, 0, zBytesData);
}




void dtor_WaveData_FB(WaveData_FB* thiz)
{
  if(thiz !=null && thiz->sizeDataAllocPos > 0) {
    free(thiz->data);
  }
}




void step_WaveMng_FB(WaveMng_FB* thiz, float nrofValues){
  //check faulty parameter
  if( nrofValues < 1.0f ){ nrofValues = 1.0f; }
  if( nrofValues >= thiz->zBuffer ){ nrofValues = (float)(thiz->zBuffer -1); }

  thiz->nVal = 1.0f / nrofValues;
  //thiz->nSum = thiz->lenAvg1 / nrofValues;
  { int ixNew = thiz->ixNew = thiz->waveIx->ixNew;
    int dPast2 = (int)(nrofValues);      //lesser distance of average period
	  int dPast3 = dPast2 +1;              //distance to oldest index 
	
	  //Set the indices of past values:
	  //if( (thiz->ixLast1 = ixNew - dPast2) < 2){ thiz->ixLast1 += thiz->zBuffer -2; }
	  //if( (thiz->ixLast = ixNew - dPast3) < 2){ thiz->ixLast += thiz->zBuffer -2; }
	  if(ixNew >= dPast3){ //both lesser
	    thiz->ixLast1 = ixNew - dPast2;  
	    thiz->ixLast = ixNew - dPast3;  
	  } else if(ixNew >= dPast2){ //one lesser ixNew - dPast2 >= startPos
	    thiz->ixLast1 = ixNew - dPast2;  
	    thiz->ixLast = ixNew - dPast3 + thiz->zBuffer;  
	  } else if(ixNew > 0){
	    thiz->ixLast1 = ixNew - dPast2 + thiz->zBuffer;  
	    thiz->ixLast = ixNew - dPast3 + thiz->zBuffer;  
	  } else { //ixNew == 2
	    thiz->ixLast1 = thiz->zBuffer - dPast2;  
	    thiz->ixLast = thiz->zBuffer - dPast3;  
	  }
	  thiz->ixLast0 = thiz->ixLast1 +1;
	  if(thiz->ixLast0 >= thiz->zBuffer){
	    thiz->ixLast0 = 0;
	  }
	
	  thiz->nLast2 = nrofValues - dPast2;  //distance
	  thiz->nLast1 = 1.0f - thiz->nLast2;
	  thiz->nLast = 0;        //for sum0
  }
  if(thiz->ixLast1 != 0) //not new Sum:
  {  
    if(nrofValues == 1.0f){
      //special case: Restart average
      //thiz->lenAvg1 = nrofValues;
      thiz->nPastPart = 0;
    } else {
      float nd = nrofValues - thiz->nrofValues;  //changing of nrofValues: >0 if more points, subtract less
      if(nd >= 0) {     //more points, subtract less from last values:
        thiz->nLast2 -= nd;    //subtract less of last last,    
        if(thiz->nLast2 < 0){
          thiz->nLast1 += thiz->nLast2;  //decrease thiz->nLast1, substract less because more points
          thiz->nLast2 = 0;
        }
      } else {          //nd < 0 less points, subtract more from last values:
        thiz->nLast2 -= nd;   //increases it. subtract more.
        if(thiz->nLast2 > thiz->nPastPart){  //thiz->nLast2, part to subtract should not be greater as its part in the sum from last summation.
          thiz->nLast1 += (thiz->nLast2 - thiz->nPastPart);  //increase thiz->nLast1 therefore, 
          thiz->nLast2 = thiz->nPastPart;
          //thiz->nLast1 may be > 1, handling see below
        }
      }

  

      if(thiz->ixLast1 == 0){
        thiz->nPastPart = 1.0f - thiz->nLast;
      } else {
        if(thiz->nLast1 > 1.0f){
          //special case, subtract 3 parts because average time is decreased.
          thiz->nPastPart = 2.0f - thiz->nLast1;
        } else {
          //normal case, subtract 2 parts
          thiz->nPastPart = 1.0f - thiz->nLast1;
        }
      }
    }
  }
  thiz->nrofValues = nrofValues;
}



#ifdef __Reflection_Simple__
const ClassJc refl_AvgWave_FB = { CONST_ObjectJc(0, (ObjectJc*)&refl_AvgWave_FB.object, null), "AvgWave_FB", 0};
#endif

void ctor_AvgWave_FB(AvgWave_FB* thiz, int identObj)
{ memset(thiz, 0, sizeof(*thiz)); 
  CTOR_ObjectJc(&thiz->obj, thiz, sizeof(*thiz), refl_AvgWave_FB, identObj);
  //thiz->check = 1;
  thiz->pNk = 1.0f; 
} 


void ctor_AvgWaveCint_FB(AvgWaveCint_FB* thiz, WaveMngCint_FB* wu, WaveData_FB* data)
{ memset(thiz, 0, sizeof(*thiz)); 
  thiz->wu_ = wu; 
  thiz->data_ = data;
  ASSERT(wu->waveIx == data->waveIx);  //should be initialized already with same WaveMngIx_FB 
} 





float step_AvgWave_FB(AvgWave_FB* thiz)
{
  float const* data = thiz->data_->data;
  WaveMng_FB const* wu = thiz->wu_;
  float Y = thiz->Y;

  if(wu->nrofValues == 1.0f){
    //special case: Restart average
    thiz->sum_ = data[wu->ixNew];
  } else {

    //if((wu->ixNew - wu->nrofValues) < 1 && (wu->ixNew - wu->nrofValues) >=1){ 
    if(wu->ixLast1 == 0){ // && wu->nrofValues >1){
      //take the absolute instead cummuative.
      thiz->sum_ = (thiz->data_->sum0 - data[0] * wu->nLast1);  //use non corrected part!
    } else {
      if(wu->nLast1 > 1.0f){
        float val0 = data[wu->ixNew]; 
        float val2 = data[wu->ixLast0] * (wu->nLast1 - 1.0f) + data[wu->ixLast1] + data[wu->ixLast] * wu->nLast2; 
        thiz->sum_ += val0 - val2;
      } else {
        //normal case, subtract 2 parts
        float val0 = data[wu->ixNew]; 
        float val2 = data[wu->ixLast1] * wu->nLast1 + data[wu->ixLast] * wu->nLast2; 
        thiz->sum_ += val0 - val2;
      }
    }
  }
  return thiz->Y = thiz->sum_ * thiz->pNk * wu->nVal;
}




