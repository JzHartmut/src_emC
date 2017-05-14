#ifndef __applstdefJc_h__
  #include <applstdefJc.h>
#endif
#ifndef __fw_assert_h__
#define __fw_assert_h__

//TODO: Simulink abort and error message!
//void stopAssert_Fwc();
#define stopAssert_Fwc()

/**Asserts that the value containing in VAR is in range MIN to MAX. 
 * This macro doesn't throws any exception but limits the value.
 * Another implementation of this macro may throw an exception. The user should accept generally that its algorithm throws here.
 *
 * @param VAR any variable (left value)
 * @param MIN the admissible minimum value in VAR. It should be a immediate const in the same numerical format as VAR. 
 * @param MAX the admissible maximum value in VAR. It should be a immediate const in the same numerical format as VAR.
 * @retunr void
 */
#define ASSERT_Range(VAR, MIN, MAX) { if(VAR < (MIN)) { VAR = (MIN); } else if(VAR > (MAX)){ VAR = (MAX); } }

#define ASSERT_Fwc(cond) { if((cond)==0) stopAssert_Fwc(); }

#define ASSERT(cond) ASSERT_Fwc(cond)


/**Checks whether the cond is true, elsewhere sets an error status for simulink. 
 * This macro should be contained in a define-macro which is used for a user method's wrapper.
 * Only if the called method it is a macro the identifier SimStruct* S is known.
 */ 
#define ASSERT_Simulink(cond, text) { if(!(cond)) { ssSetErrorStatus(S, text); } }

#define SIMULINK_Error(text) ssSetErrorStatus(S, text)
#define ASSERT_s0_Fwc(cond, TEXT, VALUE) { if((cond)==0) { stopAssert_Fwc(); } }

#endif  // __fw_assert_h__
