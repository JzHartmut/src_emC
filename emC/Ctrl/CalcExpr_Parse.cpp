
#include <emC/Base/Object_emC.h>
#ifdef DEF_ObjectJcpp_REFLECTION  //only possible with reflection because Vtable is need

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

void parseAddExpr(StringPartScanJc& spExpr
                         , Operation_CalcExpr_Parse startOperation
                         , OperationList_CalcExpr* dst_listOperations
                         , ThCxt* _thCxt
                         );


/**Function pointer definition for the inner parsing. */
typedef void ParseOperand(StringPartScanJc& spExpr
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
static void parseOperand ( StringPartScanJc& spExpr
  , Operation_CalcExpr_Parse currOperation
  , OperationList_CalcExpr* dst_listOperations
  , ThCxt* _thCxt
  ) {
  STACKTRC_TENTRY("parseArgument_CalcExpr");
  OS_PtrValue currOperand = {0};
  if(spExpr.scanIdentifier().scanOk()) {
    Part_StringPartJc_s* csvar = spExpr.getLastScannedString();
    char cvar[32] = {0};
    copyToBuffer_Part_StringPartJc(csvar, cvar, 0, sizeof(cvar), _thCxt);
    if(spExpr.scan(openParanthesis).scanOk()) {
      //function call, firstly write arguments to the stack.
      spExpr.skipWhitespaceAndComment();
      char cc = spExpr.getCurrentChar();
      //check std function
      uint nrArgs = 0;
      while(cc != ')'){
        if(cc == ',') { spExpr.seekPos(1); }
        writeOperand(dst_listOperations, push_CalcExpr, null, _thCxt); //save accu as following operand
        parseAddExpr(spExpr, startExpr_CalcExpr, dst_listOperations, _thCxt); //any argument string
        nrArgs +=1;
      }
      spExpr.seekPos( 1); //over ')' Note: all other character are denied by parseAddExpr
      spExpr.scan();  //next scan from current position!
      bool foundFunction = false;
      uint ixOper = 0;
      while(!foundFunction && ixOper < ARRAYLEN_emC(stdMathFunctions)){ ////
        FunctionList_CalcExpr* stdOper = &stdMathFunctions[ixOper++];
        if(strcmp(stdOper->name, cvar)==0 && nrArgs == (strlen(stdOper->typeArguments)-1)){
          for(uint ixArg = 0; ixArg < nrArgs; ++ixArg){
             //TODO check args to distinguish between same operation name
          }
          void* dataForOperation = null;  //TODO how to assiciate instance data?
          writeOperand(dst_listOperations, stdOper->oper, dataForOperation, _thCxt); //save accu as following operand
          foundFunction = true;
        }
      }
      if(!foundFunction) {
        THROW_s0(IllegalArgumentException, "function not found", (int)spExpr.getCurrentPosition(), 0);
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
    THROW_s0(IllegalArgumentException, "expected variable or math operation", (int)spExpr.getCurrentPosition(), 0);
  }
  STACKTRC_LEAVE;

}

/**
 * @param checkOperators array of 0-term. Strings with possible operators
 * @param operandFunction The routine to parse an operand, 
 *        for example parseMultiplication inside parseAddition-Expression.
 */
static void parseOperatorExpr(StringPartScanJc& spExpr
  , Operation_CalcExpr_Parse startOperation
  , char const* const checkOperators[]
  , char const* charOperators
  , ParseOperand* operandFunction
  , OperationList_CalcExpr* dst_listOperations
  , ThCxt* _thCxt
  ) {
  STACKTRC_TENTRY("parseArgument_CalcExpr");
  Operation_CalcExpr_Parse operation = startOperation;  //it is set, or ENTER in ReversPolishNotation
  //a mult expression should start with an operand.
  bool contOperatorExpr = true;
  do {
    (*operandFunction)(spExpr, operation, dst_listOperations, _thCxt); //parse left operand
    contOperatorExpr = false; //default if not found
    char const* const* checkOperators1 = checkOperators;
    int ixOperator = 0;
    spExpr.scan();  //next scan from current position!
    while(!contOperatorExpr && **checkOperators1 !=0) {
      StringJc sCheck = z_StringJc(*checkOperators1);
      spExpr.scan(sCheck);
      if(spExpr.scanOk()){
        //possible operator found
        contOperatorExpr = true;
        if(charOperators == null){                  //set the next operation due to scanned operator.
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



static void parseMultExpr(StringPartScanJc& spExpr
  , Operation_CalcExpr_Parse startOperation
  , OperationList_CalcExpr* dst_listOperations
  , ThCxt* _thCxt
  ) {
  parseOperatorExpr(spExpr, startOperation, multOperators, null, parseOperand, dst_listOperations, _thCxt);
}



void parseAddExpr(StringPartScanJc& spExpr
  , Operation_CalcExpr_Parse startOperation
  , OperationList_CalcExpr* dst_listOperations
  , ThCxt* _thCxt
  ) {
  parseOperatorExpr(spExpr, startOperation, addOperators, null, parseMultExpr, dst_listOperations, _thCxt);
}


//Parse a string given common Expression
void parse_CalcExpr(StringJc expr
  , OperationList_CalcExpr* dst_listOperations
  , ThCxt* _thCxt
  ) {
  STACKTRC_TENTRY("parse_CalcExpr");
  StringPartScanJc spExpr(expr);  //organization instance for parsind, sufficient as Stack instance.
  spExpr.setIgnoreWhitespaces(true);
//  ctorO_Cs_StringPartScanJc(&spExpr.base.object, expr, _thCxt);
  //yet the highest level is add
  parseAddExpr(*&spExpr, startExpr_CalcExpr, dst_listOperations, _thCxt);
  STACKTRC_LEAVE;
}


#endif //DEF_ObjectJcpp_REFLECTION
