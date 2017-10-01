#ifndef __fw_assert_h__
#define __fw_assert_h__


void message_zI_Fwc(char const* file, int line, char const* text, int value);

/**Macro uses __FILE__ and __LINE__ from the invocation line. 
 */
#define STOP_zI_Fwc(TEXT, VAL) message_zI_Fwc(__FILE__, __LINE__, TEXT, VAL)


void assertJc(bool condition);


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


/**Macro uses __FILE__ and __LINE__ from the invocation line. 
 */
#define ASSERT_Fwc(cond) { if((cond)==0) message_zI_Fwc(__FILE__, __LINE__, null, cond); }
#define ASSERT(cond) ASSERT_Fwc(cond) 


/**Writes a log text or THROW_s0 */
#define ASSERT_zI_Fwc(cond, TEXT, VALUE) { if((cond)==0) { message_zI_Fwc(__FILE__, __LINE__, TEXT, VALUE); } }

#endif  // __fw_assert_h__
