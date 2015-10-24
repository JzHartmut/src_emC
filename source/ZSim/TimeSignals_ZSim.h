#ifndef __TimeSignals_ZSim_h__
#define __TimeSignals_ZSim_h__
#include <os_types_def.h>
#include <Jc/ObjectJc.h>
#include <Jc/ReflectionJc.h>
#include <Fwc/fw_String.h>





typedef struct Entry_TimeSignals_ZSim_t
{
  float time;

  int32 ixChannel;

  int32 type;

  float value;


} Entry_TimeSignals_ZSim;



typedef struct Entries_TimeSignals_ZSim_t
{ ObjectArrayJc head;
  /**Mindestens 20 entries, Rest folgend, allociert entsprechende Länge. */
  Entry_TimeSignals_ZSim data[20];
} Entries_TimeSignals_ZSim;





typedef struct TimeSignals_ZSim_t
{ ObjectJc base;
  
  /**Belegung von max.16 bits stimuliert. Verwendung bei [[stepBits_TimeSignals_ZSim(...)]]*/
  int16 yBits;

  /**Only for 4-byte-alignment.  @refl:hide. */
  int16 dummy1;
  
  /**Belegung von max. 16 floats stimuliert. Verwendung bei [[step_TimeSignals_ZSim(...)]]*/
  float y[16];

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

  /**Instance name in Reflection Node Tree. */
  char nameRefl[32];

  /**Parametrierte Signalbezeichnungen. */
  char names[16][32];

  /**Input file path. */
  char filepath[200];

  //int32 zEntries;
  /**Allocated in an extra memory range. */
  Entries_TimeSignals_ZSim* entries;

  #ifndef refl
    //don't generate reflection for this block.

    ClassJc clazz;

    FieldJc_Y fields;

    FieldJc _fields[17 - zFieldsInHead_FieldJc_Y];
  #endif//refl

} TimeSignals_ZSim;

/**Allocate and construct. */
TimeSignals_ZSim* create_TimeSignals_ZSim(int zEntries);


void ctor_TimeSignals_ZSim(TimeSignals_ZSim* thiz);


/**Register it in a AccessNode_Inspc, invoke one time after create. */
bool registerReflection_TimeSignals_ZSim(TimeSignals_ZSim* thiz, struct FBaccessNode_Inspc_t* reflNode);


/**The channels and filepath should be set before. 
 */
bool readConfig_TimeSignals_ZSim(TimeSignals_ZSim* thiz);

void step_TimeSignals_ZSim(TimeSignals_ZSim* thiz, float time);

void free_TimeSignals_ZSim(TimeSignals_ZSim* thiz);



#endif //__TimeSignals_ZSim_h__
