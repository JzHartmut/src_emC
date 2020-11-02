#ifndef __CalcExpr_h__
#define __CalcExpr_h__

#include <applstdef_emC.h>

/**The data for calculation of any expression. */
typedef struct CalcExpr_T {
  union {float accuF;  int32 accuI; int16 accuS;} accu;

  /**Type in accu, uses 'F' I' 'S' for float, int32, int16*/
  int cType;    //Note: uses processor specific register width, it is a char

  int ixStack;  //use processor specific int, 16 bit for 16-bit-CPU

  int ixStackMax;

  union {float F;  int32 I; int16 S;} stack[61];

} CalcExpr;






/**The inner execution operation. A function type. */
typedef void CalcRPN_CalcExpr(CalcExpr* thiz, void* arg);




typedef struct FunctionList_CalcExpr_T {
  /**Name in the input source*/
  char const* name;
  /**Any char is one argument. Use F I S z for float, int32, int16 char const* */
  char const* typeArguments;

  /**The function pointer*/
  CalcRPN_CalcExpr* oper;

} FunctionList_CalcExpr;



/**Defines the entry for one operation with operation and value. */
typedef struct Operation_CalcExpr_T {
  CalcRPN_CalcExpr* oper;
  void* val;
} Operation_CalcExpr;

/**Only used as pointer type for debug instead simple Operation_CalcExpr* */
typedef struct Operation_CalcExpr_ARRAY20_T {
  Operation_CalcExpr o[20];
} *PTR_Operation_CalcExpr_ARRAY20;


typedef struct OperationList_CalcExpr_T {
  PTR_Operation_CalcExpr_ARRAY20 operations;
  //Operation_CalcExpr* operations;
  int zOperations;
  int ixOperation;
} OperationList_CalcExpr;


/**Initializes.
 * @arg stacksizeAdditional. It is possible to define:
 *   CalcExpr expression; int32 moreStack[12];
 *   in one structure. Then the expression has more stack. The given 12 is the stacksizeAdditional
 */
void ctor_CalcExpr(CalcExpr* thiz, int stacksizeAdditional);



/**This is the core routine for calculation.
 * @arg operations: should be filled with valid operation functions!!! elsewhere memory crash
 * @arg zOperations: Number of valid operations.
 * @return the result is contained in the accu in the given format.
 */
void calc_CalcExpr(CalcExpr* thiz, Operation_CalcExpr* operations, int zOperations);


inline float getFloat_CalcExpr(CalcExpr const* thiz){ return thiz->accu.accuF; }


/*==== Prototypes for Operations ==========================================================
 */

/**Sets the accu with the given value. input should be a float*. */
void setF_CalcExpr(CalcExpr* thiz, void* input);

/**Sets the accu with the given value. input should be a int32*. */
void setI_CalcExpr(CalcExpr* thiz, void* input);

/**Sets the accu with the given value. input should be a int16*. */
void setS_CalcExpr(CalcExpr* thiz, void* input);

/**Adds the accu with the given value. input should be a float*. */
void addF_CalcExpr(CalcExpr* thiz, void* input);

/**Sub the accu with the given value. input should be a float*. */
void subF_CalcExpr(CalcExpr* thiz, void* input);

/**Multiplicate the accu with the given value. input should be a float*. */
void mulF_CalcExpr(CalcExpr* thiz, void* input);

/**Divide the accu with the given value. input should be a float*. */
void divF_CalcExpr(CalcExpr* thiz, void* input);

/**Push the accu to the stack to free the accu for a inner operation. */
void push_CalcExpr(CalcExpr* thiz, void* unused);

/**Adds the accu with the pop value from stack content. */
void addFs_CalcExpr(CalcExpr* thiz, void* unused);

/**Divide pop-stack - accu */
void subFs_CalcExpr(CalcExpr* thiz, void* unused);

void mulFs_CalcExpr(CalcExpr* thiz, void* unused);

/**Divide pop-stack / accu */
void divFs_CalcExpr(CalcExpr* thiz, void* unused);

/**A filter for the accu value.
 * @arg vfilter: pointer to the T1_DF_FB structure. */
void T1filterF_CalcExpr(CalcExpr* thiz, void* vfilter);

/**Systems fast clock for time measurement */
void sysclk_CalcExpr(CalcExpr* thiz, void* unused);



#endif //__CalcExpr_h__
