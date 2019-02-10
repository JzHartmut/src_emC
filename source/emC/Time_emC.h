/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this source the LGPL Lesser General Public License,
 * published by the Free Software Foundation is valid.
 * It means:
 * 1) You can use this source without any restriction for any desired purpose.
 * 2) You can redistribute copies of this source to everybody.
 * 3) Every user of this source, also the user of redistribute copies
 *    with or without payment, must accept this license for further using.
 * 4) But the LPGL ist not appropriate for a whole software product,
 *    if this source is only a part of them. It means, the user
 *    must publish this part of source,
 *    but don't need to publish the whole source of the own product.
 * 5) You can study and modify (improve) this source
 *    for own using or for redistribution, but you have to license the
 *    modified sources likewise under this LGPL Lesser General Public License.
 *    You mustn't delete this Copyright/Copyleft inscription in this source file.
 *
 * This source may be used also with another licence, if the author 
 * and all other here named co-authors have agreed to this contract.
 * Especially a company can use a copy of this sources in its products without publishing.
 * The user should have a underwritten contract therefore.
 *
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content Definition of memory access routines. 
 * This routines are implemented in a operation system specific way. 
 *
 * @author Hartmut Schorrig
 * @version sf-0.83
 * 2017-12-03: Hartmut creation from OSAL/os_time.h 
 *
 ************************************************************************************************/
#ifndef __emC_fw_Time_h__
#define __emC_fw_Time_h__
#include <applstdef_emC.h>
#include <emC/Object_emC.h>
#include <OSAL/os_time.h>

typedef struct SimTime_emC_t
{
  int32 timeShort;

  int32 spare1_8aligned;  //for 8-byte-Alignment.

  double timeSim;

} SimTime_emC;


extern_C ClassJc const reflection_SimTime_emC;




typedef struct Clock_MinMaxTime_emC_t {

  union { ObjectJc object; } base;

  float microSecondsPerClock;

  int32 nrofSlices;

  /**3 nested instances for time measurements in 3 time slots. More are possible. */
  MinMaxTime_emC times[3];
} Clock_MinMaxTime_emC;

extern_C ClassJc const reflection_Clock_MinMaxTime_emC;

void ctor_Clock_MinMaxTime_emC(Clock_MinMaxTime_emC* thiz, int nrofEntries);


void init_Clock_MinMaxTime_emC(Clock_MinMaxTime_emC* thiz);


/**
 * @simulink Operation-FB, step-in.
 */
void startTime_Clock_MinMaxTime(int slice_param, float* time_y);

/**
* @simulink Operation-FB, step-in.
*/
void measTime_Clock_MinMaxTime(int slice_param, float* time_y);






#endif  //Headerguard