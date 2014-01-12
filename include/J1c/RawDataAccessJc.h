/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#ifndef __J1c_RawDataAccessJc_h__
#define __J1c_RawDataAccessJc_h__

#include "Jc/ObjectJc.h"        //basic concept

#include "Jc/StringJc.h"        //used often

#include "Fwc/fw_Exception.h"   //basic concept


/* J2C: Forward declaration of struct ***********************************************/
struct RawDataAccessJc_t;


/* J2C: includes *********************************************************/
#include "J1c/ByteDataAccessJc.h"  //superclass


/*@CLASS_C RawDataAccessJc @@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct RawDataAccessJc_t
{ 
  union { ObjectJc object; ByteDataAccessJc_s super;} base; 
} RawDataAccessJc_s;
  

#define sizeof_RawDataAccessJc_s sizeof(RawDataAccessJc_s)


/**J2c: Definitions of the enhanced reference. It's conditinally because it may be defined in a included header before. */
#ifndef RawDataAccessJcREFDEF
  //J2C: definition of enhanced reference where it was need firstly: 
  #define RawDataAccessJcREFDEF
  struct RawDataAccessJc_t;
  DEFINE_EnhancedRefJc(RawDataAccessJc);
#endif

/**J2c: Definitions of the array forms. NOTE: The number of elements are a helper for debug, the really used number depends on the memory size! */
typedef struct RawDataAccessJc_X_t { ObjectArrayJc head; RawDataAccessJcREF data[50]; } RawDataAccessJc_X;
typedef struct RawDataAccessJc_Y_t { ObjectArrayJc head; RawDataAccessJc_s data[50]; } RawDataAccessJc_Y;

 extern_C struct ClassJc_t const reflection_RawDataAccessJc_s;
  


/**CONST_Type useable as initializer for embedded/stack-instances*/
#define CONST_RawDataAccessJc(OBJP) { CONST_ObjectJc(sizeof(RawDataAccessJc_s), OBJP, &reflection_RawDataAccessJc_s), 0 }

/**J2C: finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_RawDataAccessJc_F(ObjectJc* othis, ThCxt* _thCxt);




METHOD_C struct RawDataAccessJc_t* ctorO_RawDataAccessJc(ObjectJc* othis, ThCxt* _thCxt);

/* J2C:Implementation of the method, used for an immediate non-dynamic call: */
METHOD_C void specifyEmptyDefaultData_RawDataAccessJc_F(ByteDataAccessJc_s* ithis, ThCxt* _thCxt);
/* J2C:Call of the method at this class level, executes a dynamic call of the override-able method: */
METHOD_C void specifyEmptyDefaultData_RawDataAccessJc(ByteDataAccessJc_s* ithis, ThCxt* _thCxt);

/* J2C:Implementation of the method, used for an immediate non-dynamic call: */
METHOD_C int32 specifyLengthElement_RawDataAccessJc_F(ByteDataAccessJc_s* ithis, ThCxt* _thCxt);
/* J2C:Call of the method at this class level, executes a dynamic call of the override-able method: */
METHOD_C int32 specifyLengthElement_RawDataAccessJc(ByteDataAccessJc_s* ithis, ThCxt* _thCxt);

/* J2C:Implementation of the method, used for an immediate non-dynamic call: */
METHOD_C int32 specifyLengthElementHead_RawDataAccessJc_F(ByteDataAccessJc_s* ithis, ThCxt* _thCxt);
/* J2C:Call of the method at this class level, executes a dynamic call of the override-able method: */
METHOD_C int32 specifyLengthElementHead_RawDataAccessJc(ByteDataAccessJc_s* ithis, ThCxt* _thCxt);

/* J2C:Implementation of the method, used for an immediate non-dynamic call: */
METHOD_C void setBigEndian_b_RawDataAccessJc_F(ByteDataAccessJc_s* ithis, bool value, ThCxt* _thCxt);
/* J2C:Call of the method at this class level, executes a dynamic call of the override-able method: */
METHOD_C void setBigEndian_b_RawDataAccessJc(ByteDataAccessJc_s* ithis, bool value, ThCxt* _thCxt);

/**Gets a integer value from any offset started from Object_Jc*/
METHOD_C int32 getIntVal_RawDataAccessJc(RawDataAccessJc_s* thiz, int32 idx, int32 nrofBytes, ThCxt* _thCxt);

/**Gets a float value from any offset started from Object_Jc*/
METHOD_C float getFloatVal_RawDataAccessJc(RawDataAccessJc_s* thiz, int32 idx, ThCxt* _thCxt);

/**Gets a double value from any offset started from Object_Jc*/
#define getDoubleVal_RawDataAccessJc(THIZ, idx) \
(longBitsToDouble_DoubleJc(/*static*/_getLong_ByteDataAccessJc(& ((* ((THIZ))).base.super), idx, 8, _thCxt)))

/*** */
#define setIntVal_RawDataAccessJc(THIZ, idx, nrofBytes, value) \
\
{ \
  \
  TRY\
  { \
    \
    _setLong_ByteDataAccessJc(& ((* ((THIZ))).base.super), idx, nrofBytes, value, _thCxt);/*test2*/\
    \
  }_TRY\
  CATCH(ExceptionJc, exc)\
  \
    { \
      \
      { throw_EJc(ident_RuntimeExceptionJc, exc, 0, &_thCxt->stacktraceThreadContext, __LINE__); };/*only test*/\
      \
    }\
  END_TRY\
}

METHOD_C void setFloatVal_RawDataAccessJc(RawDataAccessJc_s* thiz, int32 idx, float value, ThCxt* _thCxt);

#define setDoubleVal_RawDataAccessJc(THIZ, idx, value) \
\
{ /*:call of the protected super method.*/\
  \
  \
  /** */\
  if(idx < 0) /** */\
  \
  { \
    StringJc msg = CONST_z_StringJc("setDoubleVal:"); \
    \
    StringBuilderJc* _stringBuilderThCxt = threadBuffer_StringBuilderJc(_thCxt);\
    \
    msg = \
      ( setLength_StringBuilderJc(_stringBuilderThCxt, 0, _thCxt)\
      , append_z_StringBuilderJc(_stringBuilderThCxt, "setDoubleVal:", _thCxt)\
      , append_I_StringBuilderJc(_stringBuilderThCxt, idx, _thCxt)\
      , toString_StringBuilderJc(&(_stringBuilderThCxt)->base.object, _thCxt)\
      )/*J2C:non-persistent*/;\
    /** */\
    { throw_sJc(ident_IndexOutOfBoundsExceptionJc, msg, 0, &_thCxt->stacktraceThreadContext, __LINE__); };\
  }\
  setDouble_ByteDataAccessJc((&(THIZ)->base.super), idx, value);\
}


/* J2C: Method table contains all dynamic linked (virtual) methods
 * of the class and all super classes and interfaces. */
 extern const char sign_Mtbl_RawDataAccessJc[]; //marker for methodTable check
typedef struct Mtbl_RawDataAccessJc_t
{ MtblHeadJc head;
  Mtbl_ByteDataAccessJc ByteDataAccessJc;
} Mtbl_RawDataAccessJc;



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
/* J2C: The C++-class-definition. */
class RawDataAccessJc : private RawDataAccessJc_s
{ public:

  RawDataAccessJc(){ init_ObjectJc(&this->base.object, sizeof(RawDataAccessJc_s), 0); setReflection_ObjectJc(&this->base.object, &reflection_RawDataAccessJc_s, 0); ctorO_RawDataAccessJc(&this->base.object,  null/*_thCxt*/); }

  double getDoubleVal(int32 idx){  return getDoubleVal_RawDataAccessJc(this, idx); }

  float getFloatVal(int32 idx){  return getFloatVal_RawDataAccessJc(this, idx,  null/*_thCxt*/); }

  int32 getIntVal(int32 idx, int32 nrofBytes){  return getIntVal_RawDataAccessJc(this, idx, nrofBytes,  null/*_thCxt*/); }

  virtual void setBigEndian(bool value){ setBigEndian_b_RawDataAccessJc_F(&this->base.super, value,  null/*_thCxt*/); }

  void setDoubleVal(int32 idx, double value){ setDoubleVal_RawDataAccessJc(this, idx, value); }

  void setFloatVal(int32 idx, float value){ setFloatVal_RawDataAccessJc(this, idx, value,  null/*_thCxt*/); }

  void setIntVal(int32 idx, int32 nrofBytes, int64 value){ setIntVal_RawDataAccessJc(this, idx, nrofBytes, value); }

  virtual void specifyEmptyDefaultData(){ specifyEmptyDefaultData_RawDataAccessJc_F(&this->base.super,  null/*_thCxt*/); }

  virtual int32 specifyLengthElementHead(){  return specifyLengthElementHead_RawDataAccessJc_F(&this->base.super,  null/*_thCxt*/); }

  virtual int32 specifyLengthElement(){  return specifyLengthElement_RawDataAccessJc_F(&this->base.super,  null/*_thCxt*/); }
};

#endif /*__CPLUSPLUSJcpp*/

#endif //__J1c_RawDataAccessJc_h__
