/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#ifndef __InspcJ2c_Inspector_Inspc_h__
#define __InspcJ2c_Inspector_Inspc_h__

#include "Fwc/fw_MemC.h"        //basic concept

#include "Jc/ObjectJc.h"        //basic concept

#include "Jc/StringJc.h"        //used often

#include "Fwc/fw_Exception.h"   //basic concept


/* J2C: Forward declaration of struct ***********************************************/
struct Inspector_Inspc_t;
struct ObjectJc_t;


/* J2C: includes *********************************************************/
#include "InspcJ2c/ClassContent_Inspc.h"  //embedded type in class data
#include "InspcJ2c/CmdExecuter_Inspc.h"  //embedded type in class data
#include "InspcJ2c/Comm_Inspc.h"  //embedded type in class data


/*@CLASS_C Inspector_Inspc @@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct Inspector_Inspc_t
{ 
  union { ObjectJc object; } base; 
  ClassContent_Inspc_s classContent; 
  CmdExecuter_Inspc_s cmdExecuter;   /*The main cmd executer. There may be more as one {@link CmdConsumer_ifc} */
  Comm_Inspc_s comm;   /*The communication class. */
} Inspector_Inspc_s;
  

#define sizeof_Inspector_Inspc_s sizeof(Inspector_Inspc_s)


/**J2c: Definitions of the enhanced reference. It's conditinally because it may be defined in a included header before. */
#ifndef Inspector_InspcREFDEF
  //J2C: definition of enhanced reference where it was need firstly: 
  #define Inspector_InspcREFDEF
  struct Inspector_Inspc_t;
  DEFINE_EnhancedRefJc(Inspector_Inspc);
#endif

/**J2c: Definitions of the array forms. NOTE: The number of elements are a helper for debug, the really used number depends on the memory size! */
typedef struct Inspector_Inspc_X_t { ObjectArrayJc head; Inspector_InspcREF data[50]; } Inspector_Inspc_X;
typedef struct Inspector_Inspc_Y_t { ObjectArrayJc head; Inspector_Inspc_s data[50]; } Inspector_Inspc_Y;

 extern_C struct ClassJc_t const reflection_Inspector_Inspc_s;
  


/**CONST_Type useable as initializer for embedded/stack-instances*/
#define CONST_Inspector_Inspc(OBJP) { CONST_ObjectJc(sizeof(Inspector_Inspc_s), OBJP, &reflection_Inspector_Inspc_s), 0 }

/**J2C: finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_Inspector_Inspc_F(ObjectJc* othis, ThCxt* _thCxt);


#define version_Inspector_Inspc 0x20111118  /*Version and history*/


/*** */
METHOD_C struct Inspector_Inspc_t* ctorO_Inspector_Inspc(ObjectJc* othis, StringJc commOwnAddr, ThCxt* _thCxt);

/**Start the execution. */
typedef void MT_start_Inspector_Inspc(Inspector_Inspc_s* thiz, struct ObjectJc_t* rootObj, ThCxt* _thCxt);
/* J2C:Implementation of the method, used for an immediate non-dynamic call: */
METHOD_C void start_Inspector_Inspc_F(Inspector_Inspc_s* thiz, struct ObjectJc_t* rootObj, ThCxt* _thCxt);
/* J2C:Call of the method at this class level, executes a dynamic call of the override-able method: */
METHOD_C void start_Inspector_Inspc(Inspector_Inspc_s* thiz, struct ObjectJc_t* rootObj, ThCxt* _thCxt);

/**Shutdown the communication, close the thread*/
typedef void MT_shutdown_Inspector_Inspc(Inspector_Inspc_s* thiz, ThCxt* _thCxt);
/* J2C:Implementation of the method, used for an immediate non-dynamic call: */
METHOD_C void shutdown_Inspector_Inspc_F(Inspector_Inspc_s* thiz, ThCxt* _thCxt);
/* J2C:Call of the method at this class level, executes a dynamic call of the override-able method: */
METHOD_C void shutdown_Inspector_Inspc(Inspector_Inspc_s* thiz, ThCxt* _thCxt);


/* J2C: Method table contains all dynamic linked (virtual) methods
 * of the class and all super classes and interfaces. */
 extern const char sign_Mtbl_Inspector_Inspc[]; //marker for methodTable check
typedef struct Mtbl_Inspector_Inspc_t
{ MtblHeadJc head;
  MT_start_Inspector_Inspc* start;
  MT_shutdown_Inspector_Inspc* shutdown;
  Mtbl_ObjectJc ObjectJc;
} Mtbl_Inspector_Inspc;



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
/* J2C: The C++-class-definition. */
class Inspector_Inspc : private Inspector_Inspc_s
{ public:

  Inspector_Inspc(StringJcpp commOwnAddr){ init_ObjectJc(&this->base.object, sizeof(Inspector_Inspc_s), 0); setReflection_ObjectJc(&this->base.object, &reflection_Inspector_Inspc_s, 0); ctorO_Inspector_Inspc(&this->base.object, commOwnAddr,  null/*_thCxt*/); }

  virtual void shutdown(){ shutdown_Inspector_Inspc_F(this,  null/*_thCxt*/); }

  virtual void start(struct ObjectJc_t* rootObj){ start_Inspector_Inspc_F(this, rootObj,  null/*_thCxt*/); }
};

#endif /*__CPLUSPLUSJcpp*/

#endif //__InspcJ2c_Inspector_Inspc_h__
