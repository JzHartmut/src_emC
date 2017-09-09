#ifndef __TimeSignals_Inspc_h__
#define __TimeSignals_Inspc_h__
#include <applstdefJc.h>
#include <Jc/ObjectJc.h>
#include <Jc/ReflectionJc.h>
#include <Fwc/fw_String.h>





typedef struct Entry_TimeSignals_Inspc_t
{
  float time;

  int32 ixChannel;

  int32 type;

  /**Value(s) for this time, upto 6-time Vector oder 3 values as complex.*/
  float ya[6];


} Entry_TimeSignals_Inspc;



typedef struct Entries_TimeSignals_Inspc_t
{ ObjectArrayJc head;
  /**Mindestens 20 entries, Rest folgend, allociert entsprechende L�nge. */
  Entry_TimeSignals_Inspc data[20];
} Entries_TimeSignals_Inspc;





typedef struct TimeSignals_Inspc_t
{ ObjectJc base;
  
  /**Belegung von max.16 bits stimuliert. Verwendung bei [[stepBits_TimeSignals_Inspc(...)]]*/
  int16 yBits;

  /**1 if the reflections are registered on Inspector. Note: also for 4-byte-alignment.  @ refl:hide. */
  int16 bReflRegistered;
  
  #define zya_TimeSignals_Inspc 6
  //NOTE: Use value of 6 for array length for better readability + reflection generation, it cannot process symbolics.
  /**Belegung von max. 16 floats bis zu 6-er Vektor oder 3 mal complex stimuliert. Verwendung bei [[step_TimeSignals_Inspc(...)]]
   * They have to be arranged one after another, so that ya0[5][0] accesses ya5 etc.
   */
  float ya0[6], ya1[6], ya2[6], ya3[6], ya4[6], ya5[6], ya6[6], ya7[6];
  float ya8[6], ya9[6], ya10[6], ya11[6], ya12[6], ya13[6], ya14[6], ya15[6];

  //float_complex dummyFloatComplex;

  /** */
  //int32 step;

  /**Folgender Zeitpunkt in der was schalten muss. Vereinfachter Test der Zeit in jedem Schritt. */
  float stepNext;

  //float Tstep;

  /**Z�hler falls irgendwas in config-File nicht stimmt, sollte auf 0 stehen. */
  int32 errorCfg;

  /**Index des aktuell folgenden Entries bei der Abarbeitung der Stimulation. 
   * Die stepNext sollte == entries[ixEntries].time sein. 
   */
  int32 ixEntries;

  /**Instance name of this module. It is used for Reflection Node Tree too. */
  char nameModule[32];

  /**Parametrized signal names. */
  char names[16][32];

  /**Je 1 bit fuer Ausgang ist complex. */
  int32 bitsComplexY;

  int8 nrElements[16];

  /**Input file path. */
  char filepath[200];

  

  //int32 zEntries;
  /**Allocated in an extra memory range. */
  Entries_TimeSignals_Inspc* entries;

  #ifndef refl
    //don't generate reflection for this block.

    ClassJc clazz;

    FieldJc_Y fields;

    FieldJc _fields[17 - zFieldsInHead_FieldJc_Y];
  #endif//refl

} TimeSignals_Inspc;

/**Allocate and construct. */
TimeSignals_Inspc* create_TimeSignals_Inspc(int zEntries);


void XXXctor_TimeSignals_Inspc(TimeSignals_Inspc* thiz, int nrofEntries);

/**Register it in a DataNode_Inspc, invoke one time after create. */
bool registerReflection_TimeSignals_Inspc(TimeSignals_Inspc* thiz, struct DataNode_Inspc_t* reflNode);


/**The channels and filepath should be set before. 
 */
bool readConfig_TimeSignals_Inspc(TimeSignals_Inspc* thiz);

void step_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float time);

void free_TimeSignals_Inspc(TimeSignals_Inspc* thiz);

/**
 * @simulink Sfunc no-thizInit no-thizStep
 */
void ctor_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float Tstep, StringJc filepath, StringJc reflName, int nrofEntries
, StringJc name1, StringJc name2, StringJc name3, StringJc name4
, StringJc name5, StringJc name6, StringJc name7, StringJc name8
, StringJc name9, StringJc name10, StringJc name11, StringJc name12
, StringJc name13, StringJc name14, StringJc name15, StringJc name16
);

/**
 * @simulink Sfunc
 */
void dtor_TimeSignals_Inspc(TimeSignals_Inspc* thiz);


/**operation to determine type and arraysize of the output port. The parameter should be with same name as on ctor. 
 * @param dst The environment (simulink) should deliver an array of entries. Maybe as stack variable.
 * @sizeDst number of entries at maximum.
 * @param name.. The character before ':' determine type and size.
 * @simulink Sfunc
 */
int queryOutputPorts_TimeSignals_Inspc(Entry_QueryPortTypeJc* dst, int sizeDst
, StringJc name1, StringJc name2, StringJc name3, StringJc name4
, StringJc name5, StringJc name6, StringJc name7, StringJc name8
, StringJc name9, StringJc name10, StringJc name11, StringJc name12
, StringJc name13, StringJc name14, StringJc name15, StringJc name16
);


/**
 * @simulink Sfunc
 */
char const* init_TimeSignals_Inspc(TimeSignals_Inspc* thiz, struct DataNode_Inspc_t* reflNode);

/**
 * @simulink Sfunc
 */
void values_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float _simtime
, void* val1_y, void* val2_y, void* val3_y, void* val4_y
, void* val5_y, void* val6_y, void* val7_y, void* val8_y
, void* val9_y, void* val10_y, void* val11_y, void* val12_y
, void* val13_y, void* val14_y, void* val15_y, void* val16_y
, int32* error_y
);


#endif //__TimeSignals_Inspc_h__
