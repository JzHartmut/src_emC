#ifndef __ParseArgs_emC_h__
#define __ParseArgs_emC_h__
/**This file supports parsing especially command line arguments or all other string-array given arguments or parameter.
 */



/**This struct is helpfull as pointer to see characters for debugging.
 * Using pattern see emC/ParseArgs_emC.c:
 * ,,int main(int nArgs, char** cArgs){
 * ,,CharArray20 const* args = cArgs;  //view args in debugger! You see up to 20 strings.
 * ,,printf(args.arg[2]);  //access
 */
typedef struct {char const* args[20]; } CharArray20;  //With this type debugging in the IDE for array element is better


typedef int ArgEvalOper(int nArg, CharArray20 const* args);

/**Describes one element as evaluation control for an argument. 
 */
typedef struct Ctrl_ParseArgs_t {
  /**First character of argument, usual "-opt:" */
  char const* option;

  /**Any text to show help, not used for evaluation. */
  char const* help;

  /**If not null, the address for a argument immediately after "-opt:" */
  char const** dst;

  /**If not null, any routine to evaluate the argument and following arguments. See example. */
  ArgEvalOper* argEvalOp;

} Ctrl_ParseArgs;




/**Evaluates the given command line args or any other parameter text in argsCmd with ctrl
 * 
 * Using pattern: See example TODO
 */
void eval_ParseArgs ( Ctrl_ParseArgs const ctrl[], int zCtrl, char const* const* argsCmd, int nArgs);




#endif //__ParseArgs_emC_h__