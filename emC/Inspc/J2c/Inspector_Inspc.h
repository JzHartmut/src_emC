/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#ifndef __InspcJ2c_Inspector_Inspc_h__
#define __InspcJ2c_Inspector_Inspc_h__

#include "emC/Base/MemC_emC.h"        //basic concept

#include "emC/Jc/ObjectJc.h"        //basic concept

#include "emC/Jc/StringJc.h"        //used often

   //basic concept


/* J2C: Forward declaration of struct ***********************************************/
struct Inspector_Inspc_t;
struct ObjectJc_t;


/* J2C: Enhanced references *********************************************************
 * In this part all here used enhanced references are defined conditionally.
 * The inclusion of all that header files isn't necessary, to prevent circular inclusion.
 * It is adequate a struct pointer forward declaration.
 */
#ifndef Inspector_InspcREFDEF
  //J2C: definition of enhanced reference where it was need firstly: 
  #define Inspector_InspcREFDEF
  struct Inspector_Inspc_t;
  typedef TYPE_EnhancedRefJc(Inspector_Inspc);
#endif


/* J2C: includes *********************************************************/
#include "emC/Inspc/J2c/ClassContent_Inspc.h"  //embedded type in class data
#include "emC/Inspc/J2c/CmdExecuter_Inspc.h"  //embedded type in class data
#include "emC/Inspc/J2c/Comm_Inspc.h"  //embedded type in class data


/*@CLASS_C Inspector_Inspc @@@@@@@@@@@@@@@@@@@@@@@@*/

//tag::Inspector_Inspc_s[]
typedef struct Inspector_Inspc_t
{ 
  union { ObjectJc object; } base; 
  ClassContent_Inspc_s classContent;   /*The sub module ClassContent should be accessible from outside to offer methods of it in the application itself.*/
  CmdExecuter_Inspc_s cmdExecuter;   /*The main cmd executer. There may be more as one {@link CmdConsumer_ifc} */
  Comm_Inspc_s comm;   /*The communication class. */
} Inspector_Inspc_s;
//end::Inspector_Inspc_s[]  

#define sizeof_Inspector_Inspc_s sizeof(Inspector_Inspc_s)


/**J2c: Definitions of the enhanced reference. It's conditinally because it may be defined in a included header before. */
#ifndef Inspector_InspcREFDEF
  //J2C: definition of enhanced reference where it was need firstly: 
  #define Inspector_InspcREFDEF
  struct Inspector_Inspc_t;
  typedef TYPE_EnhancedRefJc(Inspector_Inspc);
#endif

/**J2c: Definitions of the array forms. NOTE: The number of elements are a helper for debug, the really used number depends on the memory size! */
typedef struct Inspector_Inspc_X_t { ObjectArrayJc head; Inspector_InspcREF data[50]; } Inspector_Inspc_X;
typedef struct Inspector_Inspc_Y_t { ObjectArrayJc head; Inspector_Inspc_s data[50]; } Inspector_Inspc_Y;

 extern_C struct ClassJc_t const refl_Inspector_Inspc;
  


/**CONST_Type useable as initializer for embedded/stack-instances*/
#define CONST_Inspector_Inspc(OBJP) { CONST_ObjectJc(sizeof(Inspector_Inspc_s), OBJP, &refl_Inspector_Inspc), 0 }

/**J2C: finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_Inspector_Inspc_F(ObjectJc* othis, ThCxt* _thCxt);


 extern StringJc version_Inspector_Inspc;   /*Version and history*/
 extern Inspector_InspcREF singleton_Inspector_Inspc; 

//!!usage: static init code, invoke that one time in start of main.
void initStatic_Inspector_Inspc();




/*** */
METHOD_C struct Inspector_Inspc_t* ctorO_Inspector_Inspc(ObjectJc* othis, StringJc commOwnAddr, ThCxt* _thCxt);


void dtor_Inspector_Inspc(Inspector_Inspc_s* thiz);

/**Returns the first instance of the Inspector in this application. Usual only one instance is used,
* then it is a singleton. More as one instance is possible, then the first instance is the singleton returned here.
* If the Inspector is not created yet, this method returns null. 
* 
* */
METHOD_C struct Inspector_Inspc_t* get_Inspector_Inspc(/*J2C:static method*/ ThCxt* _thCxt);

/**Start the execution. */
typedef void MT_start_Inspector_Inspc(Inspector_Inspc_s* thiz, struct ClassJc_t const* rootClass, MemSegmJc rootAddr, ThCxt* _thCxt);
/* J2C:Implementation of the method, used for an immediate non-dynamic call: */
METHOD_C void start_Inspector_Inspc_F(Inspector_Inspc_s* thiz, struct ClassJc_t const* rootClazz, MemSegmJc rootAddr, ThCxt* _thCxt);

/* J2C:Call of the method at this class level, executes a dynamic call of the override-able method: */
METHOD_C void start_ClassAddr_Inspector_Inspc(Inspector_Inspc_s* thiz, struct ClassJc_t const* rootClazz, MemSegmJc rootAddr, ThCxt* _thCxt);

/**Shutdown the communication, close the thread. This routine should be called 
* either on shutdown of the whole system or on closing the inspector functionality.
* The inspector functionality can be restarted calling {@link #start(Object)}.
* 
*/
typedef void MT_shutdown_Inspector_Inspc(Inspector_Inspc_s* thiz, ThCxt* _thCxt);
/* J2C:Implementation of the method, used for an immediate non-dynamic call: */
METHOD_C void shutdown_Inspector_Inspc_F(Inspector_Inspc_s* thiz, ThCxt* _thCxt);
/* J2C:Call of the method at this class level, executes a dynamic call of the override-able method: */
METHOD_C void shutdown_Inspector_Inspc(Inspector_Inspc_s* thiz, ThCxt* _thCxt);


/* J2C: Method table contains all dynamic linked (virtual) methods
 * of the class and all super classes and interfaces. */
 extern const char sign_Vtbl_Inspector_Inspc[]; //marker for methodTable check
#ifdef DEF_ClassJc_Vtbl
typedef struct Vtbl_Inspector_Inspc_t
{ VtblHeadJc head;
  MT_start_Inspector_Inspc* start;
  MT_shutdown_Inspector_Inspc* shutdown;
  Vtbl_ObjectJc ObjectJc;
} Vtbl_Inspector_Inspc;
#endif //def DEF_ClassJc_Vtbl



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
/* J2C: The C++-class-definition. */
class Inspector_Inspc : private Inspector_Inspc_s
{ public:

  Inspector_Inspc(StringJcpp commOwnAddr){ init_ObjectJc(&this->base.object, sizeof(Inspector_Inspc_s), 0); setReflection_ObjectJc(&this->base.object, &refl_Inspector_Inspc, 0); ctorO_Inspector_Inspc(&this->base.object, commOwnAddr,  null/*_thCxt*/); }

  struct Inspector_Inspc_t* get(){  return get_Inspector_Inspc( null/*_thCxt*/); }

  virtual void shutdown(){ shutdown_Inspector_Inspc_F(this,  null/*_thCxt*/); }

  virtual void start(struct ObjectJc_t* rootObj){ start_Inspector_Inspc_F(this, rootObj,  null/*_thCxt*/); }
};

#endif /*__CPLUSPLUSJcpp*/

#endif //__InspcJ2c_Inspector_Inspc_h__
