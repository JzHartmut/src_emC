#ifndef __fw_String_h__  //should also prevent include of fw_String.h
#define __fw_String_h__

typedef OS_PtrVal_DEF(CharSeqJc, void );

/**minimalistic definition of StringJc to work with. instead including Fwc/fw_StringJc
 * It is only for platforms which does not use StringJc, especially for only numeric caculations.
 * For all other include <Fwc/fw_String.h> before including this file, especially include it in the <applstdefJc.h>. 
 */
typedef OS_PtrVal_DEF(StringJc, char const);



/**Returns true if the StringJc contains null. The user should use this macro instead straigtly using of the basicly definitions,
 * because the definition of OS_PtrValue and therefore the definition of StringJc is os-specific. 
 * @param STR StringJc-instance to test. The macro uses the instance directly.
 * @return true only if the text-reference is ,,null,,. false if it is an empty or non-empty text.
 */
#define isNull_StringJc(STR) (PTR_OS_PtrValue((STR), void*)==null)




#endif //__fw_String_h__
