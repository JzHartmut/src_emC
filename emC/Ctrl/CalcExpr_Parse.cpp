#include "CalcExpr_Parse.h"
#include "CalcExpr.h"

#include <emC/J1c/StringPartScanJc.h>


static Operation_CalcExpr_Parse startExpr_CalcExpr = {'!', '\0', 0};


static char const* const cmpOperators[] = { ">=", ">", "<=", "<", "==", "!=", "<>", "&lt;", "&gt;", ""};
static char const* const charCmpOperators = "GgLlemmlg";
static char const* const addOperators[] = { "+", "-", ""};
static char const* const multOperators[] = { "*", "/", ""};

static StringJc openParanthesis = INIZ_StringJc("(", 1);
static StringJc closeParanthesis = INIZ_StringJc("(", 1);

static char const* const stdMathFuxxnctions[] = { "abs", "sin", "cos", "arcsin", "atan2", ""};

static FunctionList_CalcExpr stdMathFunctions[] =
{ { "abs" , "FF", null }
, { "abs" , "II", null }
, { "abs" , "SS", null }
  , { "sin" , "FF", null }
  , { "atan2" , "IFF", null }
  , { "rad2int" , "IF", null }
  , { "int2rad" , "FI", null }
  , { "sysclk", "I", sysclk_CalcExpr}
};

void parseAddExpr(StringPartScanJc_s* spExpr
                         , Operation_CalcExpr_Parse startOperation
                         , OperationList_CalcExpr* dst_listOperations
                         , ThCxt* _thCxt
                         );


/**Function pointer definition for the inner parsing. */
typedef void ParseOperand(StringPartScanJc_s* spExpr
  , Operation_CalcExpr_Parse operation
  , OperationList_CalcExpr* dst_listOperations
  , ThCxt* _thCxt
  );



static Operation_CalcExpr* ptrWriteOperand(OperationList_CalcExpr* dst_listOperations , ThCxt* _thCxt) {
  Operation_CalcExpr* dstOperation = &(dst_listOperations->operations->o[dst_listOperations->ixOperation]);
  dst_listOperations->ixOperation +=1;  //increment pointer
  if(dst_listOperations->ixOperation >dst_listOperations->zOperations){
    THROW_s0(IllegalArgumentException, "too many operations, expression is too complex.", 0, 0);
  }
  return dstOperation;
}

static void writeOperand(OperationList_CalcExpr* dst_listOperations , CalcRPN_CalcExpr* routine, void* data, ThCxt* _thCxt) {
  Operation_CalcExpr* dstOperation = ptrWriteOperand(dst_listOperations, _thCxt);
  dstOperation->oper = routine;
  dstOperation->val = data;
}


/**Parse an operand, wich can be a variable, a function call.
 * @brief parseOperand
 * @param spExpr
 * @param currOperation
 * @param dst_listOperations
 * @param _thCxt
 */
static void parseOperand(StringPartScanJc_s* spExpr
  , Operation_CalcExpr_Parse currOperation
  , OperationList_CalcExpr* dst_listOperations
  , ThCxt* _thCxt
  ) {
  STACKTRC_TENTRY("parseArgument_CalcExpr");
  AddrVal_emC currOperand = {0};
  if(scanOk_StringPartScanJc(scanIdentifier_StringPartScanJc(spExpr,_thCxt), _thCxt)) {
    Part_StringPartJc_s* csvar = getLastScannedString_StringPartScanJc(spExpr, _thCxt);
    char cvar[32] = {0};
    copyToBuffer_Part_StringPartJc(csvar, cvar, 0, sizeof(cvar), _thCxt);
    if(scanOk_StringPartScanJc(scan_Cs_StringPartScanJc(spExpr, openParanthesis, _thCxt), _thCxt)) {
      //function call, firstly write arguments to the stack.
      skipWhitespaceAndComment_StringPartJc(&spExpr->base.super, _thCxt);
      char cc = getCurrentChar_StringPartJc(&spExpr->base.super, _thCxt);
      //check std function
      unsigned int nrArgs = 0;
      while(cc != ')'){
        if(cc == ',') { seekPos_StringPartJc(&spExpr->base.super, 1, _thCxt); }
        writeOperand(dst_listOperations, push_CalcExpr, null, _thCxt); //save accu as following operand
        parseAddExpr(spExpr, startExpr_CalcExpr, dst_listOperations, _thCxt); //any argument string
        nrArgs +=1;
      }
      seekPos_StringPartJc(&spExpr->base.super, 1, _thCxt); //over ')' Note: all other character are denied by parseAddExpr
      scan_StringPartScanJc(spExpr, _thCxt);  //next scan from current position!
      bool foundFunction = false;
      unsigned int ixOper = 0;
      while(!foundFunction && ixOper < ARRAYLEN_emC(stdMathFunctions)){ ////
        FunctionList_CalcExpr* stdOper = &stdMathFunctions[ixOper++];
        if(strcmp(stdOper->name, cvar)==0 && nrArgs == (strlen(stdOper->typeArguments)-1)){
          for(unsigned int ixArg = 0; ixArg < nrArgs; ++ixArg){
             //TODO check args to distinguish between same operation name
          }
          //first push the accu to stack, the accu will be set by result of function call.
          writeOperand(dst_listOperations, push_CalcExpr, null, _thCxt);
          //Then write arguments to the stack.
          void* dataForOperation = null;  //TODO how to associate instance data?
          writeOperand(dst_listOperations, stdOper->oper, dataForOperation, _thCxt); //save accu as following operand
          foundFunction = true;
        }
      }
      if(!foundFunction) {
        THROW_s0(IllegalArgumentException, "function not found", (int)getCurrentPosition_StringPartJc(&spExpr->base.super, _thCxt), 0);
      }
      if(currOperation.operation != '!'){
        Operation_CalcExpr* dstOperation = ptrWriteOperand(dst_listOperations, _thCxt);
        switch((char)currOperand.val){
        case 'F': break; //TODO    check type, create conversion operations.
        }
        //after a function-operation or with variable: store the operation.
        switch(currOperation.operation){
        case '+': dstOperation->oper = addFs_CalcExpr; break;
        case '-': dstOperation->oper = subFs_CalcExpr; break;
        case '*': dstOperation->oper = mulFs_CalcExpr; break;
        case '/': dstOperation->oper = divFs_CalcExpr; break;
        default: THROW_s0(IllegalArgumentException, "faulty operator", currOperation.operation, 0);
        }
      }
    } else {
      currOperand = getVarAddrType_CalcExpr(cvar);
      Operation_CalcExpr* dstOperation = ptrWriteOperand(dst_listOperations, _thCxt);
      switch((char)currOperand.val){
        case 'F': break; //TODO    check type, create conversion operations.
      }
      //after a function-operation or with variable: store the operation.
      switch(currOperation.operation){
      case '!': dstOperation->oper = setF_CalcExpr; dstOperation->val = currOperand.addr; break;
      case '+': dstOperation->oper = addF_CalcExpr; dstOperation->val = currOperand.addr; break;
      case '-': dstOperation->oper = subF_CalcExpr; dstOperation->val = currOperand.addr; break;
      case '*': dstOperation->oper = mulF_CalcExpr; dstOperation->val = currOperand.addr; break;
      case '/': dstOperation->oper = divF_CalcExpr; dstOperation->val = currOperand.addr; break;
      default: THROW_s0(IllegalArgumentException, "faulty operator", currOperation.operation, 0);
      }
    }
  } else {
    THROW_s0(IllegalArgumentException, "expected variable or math operation", (int)getCurrentPosition_StringPartJc(&spExpr->base.super, _thCxt), 0);
  }
  STACKTRC_LEAVE;

}



static void parseOperatorExpr(StringPartScanJc_s* spExpr
  , Operation_CalcExpr_Parse startOperation
  , char const* const checkOperators[]
  , char const* charOperators
  , ParseOperand* operandFunction
  , OperationList_CalcExpr* dst_listOperations
  , ThCxt* _thCxt
  ) {
  STACKTRC_TENTRY("parseArgument_CalcExpr");
  Operation_CalcExpr_Parse operation = startOperation;
  //a mult expression should start with an operand.
  bool contOperatorExpr = true;
  do {
    (*operandFunction)(spExpr, operation, dst_listOperations, _thCxt);
    contOperatorExpr = false; //default if not found
    char const* const* checkOperators1 = checkOperators;
    int ixOperator = 0;
    scan_StringPartScanJc(spExpr, _thCxt);  //next scan from current position!
    while(!contOperatorExpr && **checkOperators1 !=0) {
      StringJc sCheck = z_StringJc(*checkOperators1);
      scan_Cs_StringPartScanJc(spExpr, sCheck, _thCxt);
      if(scanOk_StringPartScanJc(spExpr, _thCxt)){
        //possible operator found
        contOperatorExpr = true;
        if(charOperators == null){
          operation.operation = **checkOperators1;  //first or only one char of operators
        } else {
          operation.operation = charOperators[ixOperator];
        }

      } else {
        checkOperators1 +=1;  //next string
        ixOperator +=1;
      }
    }
  } while(contOperatorExpr);
  STACKTRC_LEAVE;
}



static void parseMultExpr(StringPartScanJc_s* spExpr
  , Operation_CalcExpr_Parse startOperation
  , OperationList_CalcExpr* dst_listOperations
  , ThCxt* _thCxt
  ) {
  parseOperatorExpr(spExpr, startOperation, multOperators, null, parseOperand, dst_listOperations, _thCxt);
}



void parseAddExpr(StringPartScanJc_s* spExpr
  , Operation_CalcExpr_Parse startOperation
  , OperationList_CalcExpr* dst_listOperations
  , ThCxt* _thCxt
  ) {
  parseOperatorExpr(spExpr, startOperation, addOperators, null, parseMultExpr, dst_listOperations, _thCxt);
}



void parse_CalcExpr(StringJc expr
  , OperationList_CalcExpr* dst_listOperations
  , ThCxt* _thCxt
  ) {
  STACKTRC_TENTRY("parse_CalcExpr");
  StringPartScanJc_s spExpr = {0};
  ctorO_Cs_StringPartScanJc(&spExpr.base.object, expr, _thCxt);
  parseAddExpr(&spExpr, startExpr_CalcExpr, dst_listOperations, _thCxt);
  STACKTRC_LEAVE;
}

