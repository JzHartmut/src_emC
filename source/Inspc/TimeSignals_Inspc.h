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
  /**Mindestens 20 entries, Rest folgend, allociert entsprechende Länge. */
  Entry_TimeSignals_Inspc data[20];
} Entries_TimeSignals_Inspc;





typedef struct TimeSignals_Inspc_t
{ ObjectJc base;
  
  /**Belegung von max.16 bits stimuliert. Verwendung bei [[stepBits_TimeSignals_Inspc(...)]]*/
  int16 yBits;

  /**Only for 4-byte-alignment.  @refl:hide. */
  int16 dummy1;
  
  #define zya_TimeSignals_Inspc 6
  //NOTE: Use value of 6 for array length for better readability + reflection generation, it cannot process symbolics.
  /**Belegung von max. 16 floats bis zu 6-er Vektor oder 3 mal complex stimuliert. Verwendung bei [[step_TimeSignals_Inspc(...)]]*/
  float ya0[6], ya1[6], ya2[6], ya3[6], ya4[6], ya5[6], ya6[6], ya7[6];
  float ya8[6], ya9[6], ya10[6], ya11[6], ya12[6], ya13[6], ya14[6], ya15[6];

  //float_complex dummyFloatComplex;

  /** */
  //int32 step;

  /**Folgender Zeitpunkt in der was schalten muss. Vereinfachter Test der Zeit in jedem Schritt. */
  float stepNext;

  //float Tstep;

  /**Zähler falls irgendwas in config-File nicht stimmt, sollte auf 0 stehen. */
  int errorCfg;

  /**Index des aktuell folgenden Entries bei der Abarbeitung der Stimulation. 
   * Die stepNext sollte == entries[ixEntries].time sein. 
   */
  int ixEntries;

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


void ctor_TimeSignals_Inspc(TimeSignals_Inspc* thiz, int nrofEntries);


/**Register it in a FBaccessNode_Inspc, invoke one time after create. */
bool registerReflection_TimeSignals_Inspc(TimeSignals_Inspc* thiz, struct FBaccessNode_Inspc_t* reflNode);


/**The channels and filepath should be set before. 
 */
bool readConfig_TimeSignals_Inspc(TimeSignals_Inspc* thiz);

void step_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float time);

void free_TimeSignals_Inspc(TimeSignals_Inspc* thiz);



#endif //__TimeSignals_Inspc_h__
