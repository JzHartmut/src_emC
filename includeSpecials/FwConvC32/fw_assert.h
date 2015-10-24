#ifndef __fw_assert_h__
#define __fw_assert_h__


void stopAssert_Fwc();


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

#endif  // __fw_assert_h__
