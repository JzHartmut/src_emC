#ifndef __TimeSignals_Inspc_h__
#define __TimeSignals_Inspc_h__
#include <applstdef_emC.h>
#include <emC/Inspc/FB/DataStructBase_Inspc.h>
#include <emC/Jc/ObjectJc.h>
#include <emC/Jc/ReflectionJc.h>
#include <emC/base/String_emC.h>


struct DataNode_Inspc_t;
struct DefPortTypes_emC_t;
enum EDefPortTypes_emC_t;


typedef struct float20_t{
  float d[20];
} float20;


typedef struct Entry_TimeSignals_Inspc_t
{
  /**Index back to the last entry for this channel if a ramp is required. */
  //struct Entry_TimeSignals_Inspc_t* entryTarget;

  float timeStart;

  /**Time before this target when a correction begins. timeCorr is less or equal this->timeStart. */
  float timespline;   

  /**1 then a ramp to the next point. Hint: Use int32 instead bool if this data are stored binary. bool has an unknown byte length. */
  int32 ramp;

  //int32 ixChannel;

  //int32 type;

  /**Value(s) for this time, upto 6-time Vector oder 3 values as complex.*/
  float ya[6];


} Entry_TimeSignals_Inspc;


/**The data are presented as array of 20 entries only for debugging. Really it can be more entries. */
typedef struct Array_Entry_TimeSignals_Inspc_t {
 
  /**The array contains a pointer to entries. */
  Entry_TimeSignals_Inspc* d[20];
} Array_Entry_TimeSignals_Inspc;



typedef enum ErrorCfg_t
{
  mFaultyMemoryLayout_TimeSignals_Inspc = 1
, mInternalError1_TimeSignals_Inspc = 0x01000000
, mTooMuchEntries_TimeSignals_Inspc = 0x02000000
, mNameNotFound_TimeSignals_Inspc = 0x04000000   //though the module name is correct.
, mTooManyEntriesInLine_TimeSignals_Inspc = 0x08000000
, mExceptionReadFile_TimeSignal_Inspc = 0x10000000
, mTooManyLines_TimeSignals_Inspc = 0x20000000
, mFileNotFound_TimeSignal_Inspc = 0x40000000
, mNoFileName_TimeSignal_Inspc = 0x80000000
} ErrorCfg;


typedef struct Entries_TimeSignals_Inspc_t
{ ObjectArrayJc head;
  /**Mindestens 20 entries, Rest folgend, allociert entsprechende Länge. */
  Entry_TimeSignals_Inspc data[20];
} Entries_TimeSignals_Inspc;





typedef struct TimeData_TimeSignals_Inspc_t {
  /**Pointer to Array of entries for each channel. */
  Array_Entry_TimeSignals_Inspc* entriesChn;

  /**Number of stored entries per channel. */
  int zEntryChn;

  /**The current time entry for processing. */
  int ixCurrent;
} TimeData_TimeSignals_Inspc;





typedef struct CurrValues_TimeSignals_Inspc_t {

  float ystart[6];

  /**The current output base values. */
  float yb[6];

  /**The current output step values. */
  float yd[6];

  /**The current output values.  */
  float ya[6];

  /**Grow dy/dx for calculation points in ramp. */
  float dyx[6];

  /**Growth per step. Velocity for position output. */
  float dya[6];

  /**The new value for the growth per step. Velocity for position output in a correction phase. 
   * Only for view in debug to check correctness..
   */
  float dyaNew[6];

  /**Change of Growth per step. Acceleration for position output. */
  float ddya[6];

  /**Change of change of Growth per step. Jerk for position output. */
  float dddya[6];

  /**The next target point. */
  float yt[6];

  /**The next growth after target point. Target for growth on spline. */
  float dyt[6];

  int32 stepsToTarget;

  int32 stepsCalcdynew;

  int32 stepsSplineStart;
  
  /**Number of steps for the half spline time. 
   * If this value is ==0 then the direction of dddya is reversed.
   */
  int32 stepsSpline;

  /**Negative value for end of splining. 
   * If stepsSpline <= stepsSplineEnd then splining should be ended.
   * dddya should be about 0, or near 0. ddya is stable.
   * Both are set to 0, so that dya is contant now, the new value of growth or velocity.
   */
  int32 stepsSplineEnd;

  float time_Start;

  /**Time to target used for ramp. */
  float time_Target;

  /**Is shows which branch was used in [[checkNextEntryChn_TimeSignals_Inspc(...)]]. See source. */
  int32 dbgSel;
  #define ct_DbgSel_TimeSignals_Inspc 0xf

  #define noSplineEntry_DbgSel_TimeSignals_Inspc 0x10
  #define noSplineEntryVal_DbgSel_TimeSignals_Inspc 0x20
  #define splineEntry_DbgSel_TimeSignals_Inspc 0x40
  #define jmpEntryVal_DbgSel_TimeSignals_Inspc 0x80

  #define noRampNextEntry_DbgSel_TimeSignals_Inspc 0x100
  #define noRampNextEntryVal_DbgSel_TimeSignals_Inspc 0x200
  #define rampNextEntryVal_DbgSel_TimeSignals_Inspc 0x400
  #define noNextEntry_DbgSel_TimeSignals_Inspc 0x800

  #define noSplineNextEntry_DbgSel_TimeSignals_Inspc 0x1000
  #define splineNextEntry_DbgSel_TimeSignals_Inspc 0x2000

  #define checksplineLengthNextEntry_DbgSel_TimeSignals_Inspc 0x4000
  #define reduceSplineLengthNextNextEntry_DbgSel_TimeSignals_Inspc 0x10000
  #define reduceSplineLengthNextEntry_DbgSel_TimeSignals_Inspc 0x20000

  int32 dbg_zValues; 

} CurrValues_TimeSignals_Inspc;




/**The instance data of the TimeSignals Function Block. 
 */
typedef struct TimeSignals_Inspc_t
{ 

  union { DataStructBase_Inspc_s super; ObjectJc object; } base;
  

  struct Param_t {
    
    int32 stepsDynew;

    int32 testAddStepSpline;
    int32 testNoJergLim : 1;
  } par;

  /**Belegung von max.16 bits stimuliert. Verwendung bei [[stepBits_TimeSignals_Inspc(...)]]*/
  int16 yBits;

  /**1 if the reflections are registered on Inspector. Note: also for 4-byte-alignment.  @ refl:hide. */
  int32 bReflRegistered;
  

  #define zya_TimeSignals_Inspc 6

  /**Current values for 16 channels. */
  CurrValues_TimeSignals_Inspc curr[16];



  /**Folgender Zeitpunkt in der was schalten muss. Vereinfachter Test der Zeit in jedem Schritt. */
  float stepNext;

  float Tstep;

  /**Zähler falls irgendwas in config-File nicht stimmt, sollte auf 0 stehen. */
  int32 errorCfg;

  /**Index des aktuell folgenden Entries bei der Abarbeitung der Stimulation. 
   * Die stepNext sollte == entries[ixEntries].time sein. 
   */
  int32 ixEntries;

  /**Instance name of this module. It is used for Reflection Node Tree too. */
  char nameModule[32];

  /**Parametrized signal names. */
  //char names[16][32];

  /**Je 1 bit fuer Ausgang ist complex. */
  int32 bitsComplexY;

  int8 nrElements[16];

  /**Input file path. */
  //char filepath[200];

  
    //int32 zEntries;
    /**Allocated in an extra memory range. */
    //Entries_TimeSignals_Inspc* entries;

  TimeData_TimeSignals_Inspc timeData [16];

  #ifndef NO_PARSE_ZbnfCheader
    //don't generate reflection for this block.

    ClassOffset_idxVtblJc1 superThiz;

    /**The Reflection info will be assembled with the input parameter. */
    ClassJc clazz;

    /**Fields for type and reflection. Note: FieldJc_Y contains about 10 FieldJc for debugging. Define the rest to 17 after them. 
     * Note: 16 Fields are necessary for upto 16 outputs. The field after the last used is for the own data struct for debugging. 17 fields are used as maximum.
     */
    FieldJc_Y fields; FieldJc _fields_Rest_[17 - zFieldsInHead_FieldJc_Y];
  #endif//NO_PARSE_ZbnfCheader

    struct {
      int32 ixChnCheckEntry;
    }debug;


} TimeSignals_Inspc;


#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_TimeSignals_Inspc;
#endif




/**Allocate and construct. */
//TimeSignals_Inspc* create_TimeSignals_Inspc(int zEntries);


/**Register it in a DataNode_Inspc, invoke one time after create. */
bool registerReflection_TimeSignals_Inspc(TimeSignals_Inspc* thiz, struct DataNode_Inspc_t* reflNode);


/**The channels and filepath should be set before. 
 */
bool readConfig_TimeSignals_Inspc(TimeSignals_Inspc* thiz, char const* filepath);

//void step_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float time);

//void free_TimeSignals_Inspc(TimeSignals_Inspc* thiz);

/**Constructor for TimeSignals.
 * @param Tstep used for Simulink S-Function-Genertion: The associated step time.
 * @param filepath the absolute or relative file path to the stimuli file.
 *        Note: It is a pointer with the definition name[size]. 
 *        The size of the vector has no meaning, it is a feature of C and C++.
 *        But for simulink S-function generation the size is used 
 *        as internal buffer size for the argument string. It should be enough for a longer path.
 * @param reflName The name of this S-Function-data for reflection view.
 * @paran nrofEntries size of the buffer which holds the timesignal entries read from the timesignals file.
 *
 * @simulink ctor 
 */
void ctor_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float Tstep, struct DefPortTypes_emC_t* fbInfo, char const filepath[500], StringJc reflName, int nrofEntries
  , char const outputDefinition[500]

//, StringJc name1, StringJc name2, StringJc name3, StringJc name4
//, StringJc name5, StringJc name6, StringJc name7, StringJc name8
//, StringJc name9, StringJc name10, StringJc name11, StringJc name12
//, StringJc name13, StringJc name14, StringJc name15, StringJc name16
);

/**
 * @simulink dtor
 */
void dtor_TimeSignals_Inspc(TimeSignals_Inspc* thiz);


/**operation to determine type and arraysize of the output port. The parameter should be with same name as on ctor. 
 * @param outputDefinition The environment (simulink) should deliver an array of entries. Maybe as stack variable.
 * @simulink defPortTypes
 */
char const* definePortTypes_TimeSignals_Inspc(struct DefPortTypes_emC_t* fbInfo, enum EDefPortTypes_emC_t cause
  , char const outputDefinition[500]
);



char const* XXXdefOutputPorts_TimeSignals_Inspc(struct DefPortTypes_emC_t* dst, enum EDefPortTypes_emC_t cause
, StringJc name1, StringJc name2, StringJc name3, StringJc name4
, StringJc name5, StringJc name6, StringJc name7, StringJc name8
, StringJc name9, StringJc name10, StringJc name11, StringJc name12
, StringJc name13, StringJc name14, StringJc name15, StringJc name16
);


/**Initialization of time signals with aggregations.
 * @param reflNode maybe null, then reflection access is not possible. It is not necessary.
 * @simulink init
 */
bool init_TimeSignals_Inspc(TimeSignals_Inspc* thiz); //, struct DataNode_Inspc_t* reflNode);

/**
 * @simulink Object-FB, no-thizStep.
 */
void values_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float _simtime
//, void* val1_y, void* val2_y, void* val3_y, void* val4_y
//, void* val5_y, void* val6_y, void* val7_y, void* val8_y
//, void* val9_y, void* val10_y, void* val11_y, void* val12_y
//, void* val13_y, void* val14_y, void* val15_y, void* val16_y
, int32* error_y, int _zVaargs_, ...
);


/**
 * @ simulink Object-FB, no-thizInit, no-thizStep
 */
void bits_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float _simtime
, uint16* bits_y
, int32* error_y
);


#endif //__TimeSignals_Inspc_h__
