#ifndef __WaveMng_FB_h__
#define __WaveMng_FB_h__

#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>

#include <stdlib.h>



/*@CLASS_C WaveMngIx_FB @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**This class provides only the index for all arrays for all waves with the same length.  
 * The index counts from 0 to size-1.
 * @simulink no-bus
 */
typedef struct WaveMngIx_FB_t
{
  /**Check of correctness of the instance. */
  ObjectJc obj;
  
  /**Size of all data fields for wave buffers which are aggregated with this. */
  int32 zBuffer;

  /**This index refers that element where the newest value was written in after [[fillIn_WaveData_FB(...)]]. */
	int ixNew;

} WaveMngIx_FB;

typedef WaveMngIx_FB* P_WaveMngIx_FB; 

extern_C struct ClassJc_t const refl_WaveMngIx_FB;


/**Constructs with given instance.
 * @param size the size (number of elements) of the arrays for buffering. 
 * @simulink ctor
 */
void ctor_WaveMngIx_FB(WaveMngIx_FB* thiz, int identObj, int32 size, float Tstep);





/**Counts the index, should be called in any step time. 
 * @param step this is only to determine the order if calculation, after calculation of the step value.
 *    The step time is the time of the step signal in Simulink. 
 *    Because step is not used in the operation's body, and this routine is inlined, it will be removed from compiler and does not need calculation time.
 *    It will be removed especially in the targets machine code (via optimizing compiler).
 * @simulink Object-FB, step-out, no-thizStep.
 */ 
inline void step_WaveMngIx_FB(WaveMngIx_FB* thiz){
  if(++thiz->ixNew >= thiz->zBuffer){
    thiz->ixNew = 0;
  }
}




/*@CLASS_C WaveMngCint_FB @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**This class provides the indices to access wave data for a constant average or past size.
 * @simulink no-bus
 */
typedef struct WaveMngCint_FB_t
{
  /**Check of correctness of the instance. */
  ObjectJc obj;

  /**Size of the allocated buffer. This value was copied from the aggregated [[FB:WaveMngIx_FB]].
   * It is set by constructor and constant after them. The value is copied to fasten access. */
  int zBuffer;

  /**Number of values for the average or access to past. */
  int nrofValues;

  /**Factor 1/nrofValues. */
  float nVal;

  /**This index refers that element where the newest value was written in. 
   * It is copied from the associated [[FB:WaveMnxIx_FB]] after [[step_WaveMngCint_FB(...)]]. */
	int ixNew;

  /**This index refers that element where the latest value was stored which should be subtract to build the average. */
	int ixLast;

  WaveMngIx_FB* waveIx;

} WaveMngCint_FB;

typedef WaveMngCint_FB* P_WaveMngCint_FB; 
extern_C struct ClassJc_t const refl_WaveMngCint_FB;

/**Constructs.
 * @param waveIx Aggregated Instance to provide the Index which is used for the [[FB:WaveData_FB]] too.
 * @param size the nrofValues to build an average or access to past values. 
 * @simulink ctor
 */
WaveMngCint_FB* ctor_WaveMngCint_FB(WaveMngCint_FB* thiz, int identObj, int nrofValues);

/**Sets aggreagation.
 * @param waveIx Aggregated Instance to provide the Index which is used for the [[FB:WaveData_FB]] too.
 * @param size the nrofValues to build an average or access to past values. 
 * @simulink init
 */
inline bool init_WaveMngCint_FB(WaveMngCint_FB* thiz, WaveMngIx_FB* waveIx) {
  if(isInitialized_ObjectJc(&thiz->obj) ==0 && waveIx !=null) {
    thiz->waveIx = waveIx;
    thiz->zBuffer = waveIx->zBuffer;
    setInitialized_ObjectJc(&thiz->obj);
  }
  return true;
}

/**Steps the WaveMng. It gets the ixNew from its associated [[FB:WaveMngIx_FB]] and calculates the indices
 * and part factors.  
 * @param nrofValues Number of values for the average or access to this wave manager.
 *  If that number is out of range, it is set to 1 or its maximum.
 * @simulink Object-FB, step-in, step-out, no-thizStep.
 */
inline void step_WaveMngCint_FB(WaveMngCint_FB* thiz){
  thiz->ixNew = thiz->waveIx->ixNew;
  thiz->ixLast = thiz->ixNew - thiz->nrofValues; 
  if(thiz->ixLast < 0){ thiz->ixLast += thiz->zBuffer; } //range 0..zBuffer
}






/*@CLASS_C WaveMng_FB @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**This class provides the indices to access wave data for a variable average or past size.
 * @simulink no-bus
 */
typedef struct WaveMng_FB_t
{
	/**Check of correctness of the instance. */
  ObjectJc obj;

  /**Size of the allocated buffer. This value was copied from the aggregated [[FB:WaveMngIx_FB]].
   * It is set by constructor and constant after them. The value is copied to fasten access. */
  int zBuffer;

  /**Number of values for the average or access to past after the step method. */
  float nrofValues;

  /**This index refers that element where the newest value was written in. 
   * It is copied from the associated [[FB:WaveMnxIx_FB]] after [[step_WaveMngCint_FB(...)]]. */
	int ixNew;

  /**This index refers that element where the latest value was stored which should be subtract to build the average. */
	int ixLast;

  /**This index refers the next element after ixLast to get a part of old value, see [[nLast]]. */
	int ixLast1;
  
  /**This index refers the next element after ixLast1 to get a part of old value, only necessary if the nrofValues decreases. */
  int ixLast0;

  /**Factors which parts of ixLast should be used. TODO exact description. */
  float nLast, nLast1, nLast2;

  /**Letzte benutzte Länge für die Mittelwertbildung. */
  //float lenAvg1;

  /**Anteil des ältesten Wertes in der Summe. Diese Information wird benötigt wenn sich die Mittelwert-Länge verkleinert. 
   * Es darf dann nicht mehr vom ältesten Wert subtrahiert werden, als bei der letzten Subtraktion stehengeblieben ist.
   */
  float nPastPart;
  
  /**Multiplicator for each operation. 
   * It is 1/nrofValues
   */
  float nVal;

  /*Faktor bei ändernder nrofValues, ist 1.0 wenn nrofValues konstant ist. */
  //float XXXnSum;

  WaveMngIx_FB* waveIx;

} WaveMng_FB;

typedef WaveMng_FB* P_WaveMng_FB; 

extern_C struct ClassJc_t const refl_WaveMng_FB;


/**Constructs with given instance.
 * @param waveIx Aggregated Instance to provide the Index which is used for the [[FB:WaveData_FB]] too.
 * @simulink ctor
 */
void ctor_WaveMng_FB(WaveMng_FB* thiz, int identObj);

/**Sets aggregation.
 * @param waveIx Aggregated Instance to provide the Index which is used for the [[FB:WaveData_FB]] too.
 * @simulink init
 */
bool init_WaveMng_FB(WaveMng_FB* thiz, WaveMngIx_FB* waveIx);


/**Steps the WaveMng. It gets the ixNew from its associated [[FB:WaveMngIx_FB]] and calculates the indices
 * and part factors.  
 * @param nrofValues Number of values for the average or access to this wave manager.
 *  If that number is out of range, it is set to 1 or its maximum.
 * @simulink Object-FB, step-in, step-out, no-thizStep.
 */
void step_WaveMng_FB(WaveMng_FB* thiz, float nrofValues);


/*@CLASS_C WaveData_FB @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This struct refers the buffer for wave data.
 * It contains the sum of data from index 0.
 * @simulink no-bus
 */ 
typedef struct WaveData_FB_t
{
  /**Check of correctness of the instance. */
  ObjectJc obj;

  /**The last filled value, respecitvely the value to fillIn before calling [[step_WaveData_FB(...)]]. */
  float X;

  /**The sum from element data[0] to the current one data[waveIx->ixNew]. */
  float sum0;

  /**Association to the index source of all waves with the same length. */
  WaveMngIx_FB* waveIx;

  //#define sizeMin_WaveData_FB 40

  /**Reference to the data array. Its length is [[WaveMngIx_FB.zBuffer]] tested in constructor by given parameter. */
  float* data;

  /**The size of data are here as information. The waveIx.[[WaveMngIx_IB.sizeData]] are used for indexing. 
   * If sizeData is negativ, it will be set with an given instance. It it is positive, it is allocatated. */ 
  int32 sizeDataAllocPos;
} WaveData_FB;

typedef WaveData_FB* P_WaveData_FB; 


extern_C struct ClassJc_t const refl_WaveData_FB;


/**Initializes the WaveData with the associated data array and checks the correctness of sizes.
 * If the sizedata does not match the [[WaveMngIx_FB.zBuffer]] then an ,,ASSERT,, is invoked.
 * This assertion stops the program execution while testing on PC, but does nothing in the DSP target system.
 * The behavior of ,,ASSERT,, depends on its definition in the special header file for PC and DSP.
 * The check of length is essential to prevent data errors. 
 * Because all is tested on PC-Simulation and the constructor is called in any case, it is sufficient to test it
 * on PC-simulation. 
 * @param data the data array
 * @param sizedata number of elements in data. It should be calculated with ,,(sizeof(data)/sizeof(data[0]),,
 *   or the macro ,,ARRAYLEN_SimpleC(data),, should be used.
 * @XXXsimulink no-Sfunc
 */
extern_C void ctorData_WaveData_FB(WaveData_FB* thiz, int identObj, float* data, int sizedata); 

/**Initializes the WaveData with the associated data array and checks the correctness of sizes.
 * If the sizedata does not match the [[WaveMngIx_FB.zBuffer]] then an ,,ASSERT,, is invoked.
 * This assertion stops the program execution while testing on PC, but does nothing in the DSP target system.
 * The behavior of ,,ASSERT,, depends on its definition in the special header file for PC and DSP.
 * The check of length is essential to prevent data errors. 
 * Because all is tested on PC-Simulation and the constructor is called in any case, it is sufficient to test it
 * on PC-simulation. 
 * @param sizedata number of elements in data. It should be calculated with ,,(sizeof(data)/sizeof(data[0]),,
 *   or the macro ,,ARRAYLEN_SimpleC(data),, should be used.
 * @simulink ctor
 */
extern_C void ctor_WaveData_FB(WaveData_FB* thiz, int indentObj, int sizedata); 

/**Destructs, especially an allocated data area will be freed. 
 * @simulink dtor
 */
extern_C void dtor_WaveData_FB(WaveData_FB* thiz);



/**Initializes the WaveData with the associated data array and checks the correctness of sizes.
 * @simulink init
 */
inline bool init_WaveData_FB(WaveData_FB* thiz, WaveMngIx_FB* waveIx) {
  if(isInitialized_ObjectJc(&thiz->obj) ==0 && waveIx !=null) {
    thiz->waveIx = waveIx;
    ASSERT(waveIx->zBuffer == thiz->sizeDataAllocPos || waveIx->zBuffer == -thiz->sizeDataAllocPos);
    setInitialized_ObjectJc(&thiz->obj);
  }
  return true;
} 



#define ctorD_WaveData_FB(THIZ, IX, DATA) { \
  ctorData_WaveData_FB(THIZ, 0, &(DATA)[0], ARRAYLEN_SimpleC(DATA)); \
  init_WaveData_FB(THIZ, IX); \
}

/**Operation outside simulink in pure C: thiz->X have to be set outside. 
 */
inline void stepC_WaveData_FB(WaveData_FB* thiz) 
{ thiz->data[thiz->waveIx->ixNew] = thiz->X;  /**Store this */ 
  if(thiz->waveIx->ixNew ==0) { 
    thiz->sum0 = thiz->X; /*start cummulate newly. */ 
  } else { 
    thiz->sum0 += thiz->X; /*cummulate*/ 
  } 
}



/**Fills the given value into the buffer and builds the average for constant buffer length. 
 * This method should be called one time in the step time of calculation.
 * The value should be store in thiz->X before. 
 * Note: That is more proper because the value is often calculated and can be viewed via Inspector. date:2016-0517
 * @simulink Object-FB, step-in.
 */
inline void step_WaveData_FB(WaveData_FB* thiz, float X) 
{ thiz->X = X;
  stepC_WaveData_FB(thiz);
}








inline float getPast_WaveData_FB(WaveData_FB* thiz, WaveMng_FB* mng) {
  float y;
  if(mng->nLast1 > 1.0f){
    float val0 = thiz->data[mng->ixNew]; 
    float val2 = thiz->data[mng->ixLast0] * (mng->nLast1 - 1.0f) + thiz->data[mng->ixLast1] + thiz->data[mng->ixLast] * mng->nLast2; 
    y = val0 - val2;
  } else {
    //normal case, subtract 2 parts
    float val0 = thiz->data[mng->ixNew]; 
    float val2 = thiz->data[mng->ixLast1] * mng->nLast1 + thiz->data[mng->ixLast] * mng->nLast2; 
    y = val0 - val2;
  }
  return y;
}


/**Gets a value from data buffer on that past point which is referred by the mng. 
 * @param mng manages the indices. 
 */
inline float getPastCint_WaveData_FB(WaveData_FB* thiz, WaveMngCint_FB* mng) {
  return thiz->data[mng->ixLast];
}


/**Gets a value from data buffer on that past point given by the index. 
 * @param ixPast 0 is the current value, 1 is the last past value etc.
 *        It should always >=0 and <zBuffer by invoking algorithm, not tested here.
 * @simulink Operation-FB
 *         
 */
inline void getPastIx_WaveData_FB(WaveData_FB* thiz, int ixPast_param, float* dst_y) {
  int ix = thiz->waveIx->ixNew - ixPast_param;
  if(ix <0) { ix += thiz->waveIx->zBuffer; }
  *dst_y= thiz->data[ix];
}







/*@CLASS_C AvgWave_FB @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



/**Class to calculate any sliding averaging sum.
 * This class have an aggregation to a WaveBuffer_FB which stores the value.
 *
 * Dieser FB dient der Berechnung des Mittelwert ab dem aktuellen Wert in die Vergangenheit mit einer festen Länge von Werten. 
 * @simulink no-bus
 */
typedef struct AvgWave_FB_t
{ 
  ObjectJc obj;
  /**The average value. Return value of step(). */
  float Y;
  
  /**Adjusting factor. */
  float pNk;

  /**The sum of that values, which builds the average. */
  float sum_;

  WaveData_FB* data_;

  /**Association to the wave manager. */
  WaveMng_FB* wu_;
}AvgWave_FB;


typedef AvgWave_FB* P_AvgWave_FB; 


extern_C struct ClassJc_t const refl_AvgWave_FB;


/**Initializes with given association.
 * @param WaveBuffer This wave buffer is used to get the values.
 * @simulink ctor
 */
extern_C void ctor_AvgWave_FB(AvgWave_FB* thiz, int identObj);


/**Initializes with given association.
 * @param WaveBuffer This wave buffer is used to get the values.
 * @simulink init
 */
inline bool init_AvgWave_FB(AvgWave_FB* thiz, WaveMng_FB* wu, WaveData_FB* data) {
  if(isInitialized_ObjectJc(&thiz->obj) ==0 && wu !=null && data !=null) {
    thiz->data_ = data;
    thiz->wu_ = wu; 
    setInitialized_ObjectJc(&thiz->obj);
    ASSERT(wu->waveIx == data->waveIx);  //should be initialized already with same WaveMngIx_FB 
  }
  return true;
}


/**Returns the average value, core operation. */
extern_C float stepR_AvgWave_FB(AvgWave_FB* thiz);


/**Calculates the average from current value to deepness of aggregated WaveMng_FB
 * from aggregated data.
 * @param step only dummy for determine the step order.
 * @param avg_y Output the average.
 * @simulink Object-FB, step-in, no-thizStep.
 */
inline void step_AvgWave_FB(AvgWave_FB* thiz, float* avg_y)
{ *avg_y = stepR_AvgWave_FB(thiz); }




/*@CLASS_C AvgWaveCint_FB @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



/**Class to calculate any sliding averaging sum.
 * This class have an aggregation to a WaveBuffer_FB which stores the value.
 *
 * Dieser FB dient der Berechnung des Mittelwert ab dem aktuellen Wert in die Vergangenheit mit einer festen Länge von Werten. 
 */
typedef struct AvgWaveCint_FB_t
{ 
  ObjectJc obj;

  /**The average value. Return value of step(). */
  float Y;
  
  /**The sum of that values, which builds the average. */
  float sum_;

  WaveData_FB* data_;

  /**Association to the wave manager. */
  WaveMngCint_FB* wu_;

}AvgWaveCint_FB;


typedef AvgWaveCint_FB* P_AvgWaveCint_FB; 


extern_C struct ClassJc_t const refl_AvgWaveCint_FB;

/**Initializes with given association.
 * @param WaveBuffer This wave buffer is used to get the values.
 * @xxxsimulink xxxSfunc
 */
extern_C void ctor_AvgWaveCint_FB(AvgWaveCint_FB* thiz, WaveMngCint_FB* wu, WaveData_FB* data);



/**
 * @xxxsimulink xxxSfunc
 */
inline void step_AvgWaveCint_FB(AvgWaveCint_FB* thiz, float* avg_y)
{
  float const* data = thiz->data_->data;
  WaveMngCint_FB const* wu = thiz->wu_;
  float Y = thiz->Y;

  //if((wu->ixNew - wu->nrofValues) < 1 && (wu->ixNew - wu->nrofValues) >=1){ 
  if(wu->ixNew == wu->nrofValues-1){ // && wu->nrofValues >1){
    //take the absolute instead cummuative.
    thiz->sum_ = thiz->data_->sum0;  //use non corrected part!
  } else {
    thiz->sum_ += data[wu->ixNew] - data[wu->ixLast];
  }
  *avg_y = thiz->Y = thiz->sum_ * wu->nVal;
}









#endif  //__WaveMng_FB_h__
