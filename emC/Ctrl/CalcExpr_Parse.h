#ifndef __CalcExpr_Parse_h__
#define __CalcExpr_Parse_h__
#include <applstdef_emC.h>
#include <emC/base/String_emC.h>

#include "CalcExpr.h"

typedef struct Operation_CalcExpr_Parse_T {
  char operation;
  char type;
  int16 dummyalign;
} Operation_CalcExpr_Parse;



/**This routine should be resolved by the user.
 * @arg name of variable, non persistent reference (maybe in stack), do not store.
 * @return the address of the variable and its type in the value (char 'F', 'S' etc.)
 */
AddrVal_emC getVarAddrType_CalcExpr(char const* name);

void parse_CalcExpr(StringJc expr
  , OperationList_CalcExpr* dst_listOperations
  , ThCxt* _thCxt);





#endif //__CalcExpr_Parse_h__
