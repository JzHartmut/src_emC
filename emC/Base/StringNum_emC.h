#ifndef HGUARD_emC_Base__StringNum_emC
#define HGUARD_emC_Base__StringNum_emC
#include <applstdef_emC.h>

#ifndef DEF_NO_StringUSAGE  //Note: this capabilities should not be used on DEF_NO_StringUSAGE



/**Bit in last argument of toString_int32_emC: Show space instead leading 0. */
#define m_leadingSpace_toString_int32_emC 0x0800

/**Bits in last argument of toString_int32_emC: Check value, if negative, negate and show leading "-". */
#define m_showNegative_toString_int32_emC 0x3000

/**Bits in last argument of toString_int32_emC: Check value, if negative, negate and show leading "-". */
#define k_showPositiveSpace_toString_int32_emC 0x2000

/**Bits in last argument of toString_int32_emC: Check value, if negative, negate and show leading "-". */
#define k_showPositivePlus_toString_int32_emC 0x1000


/**Converts the value into a String representation.
* @param zBuffer size of the buffer. If the string representation will be longer, only the left character are written.
* @param radix of the conversion, typically 10 or 16 for hexa conversion. A value between 1..16.
* @param minNrofCharsAndFlags If this value is negativ, and the value is negativ, a ,,-,, is written first and the value is negated before conversion.
*  The absolute value is the minimum of numbers, If the number will be less, left 0 are written.
*  Additional the both flag bits leadingSpace_toString_int32_emC and showNegative_toString_int32_emC are accepted.
* @return number of written chars. A terminating '\0' after the string won't be written! Should be done outside.
* If the return value is equal zBuffer, the string representation may be incomplete because clipping of following chars.
*/
extern_C int toString_int32_emC(char* buffer, int zBuffer, int32 value, int radix, int minNrofCharsAndFlags);

int toString_float_emC(char* buffer, int zBuffer, float value, char const* format);


/**Parses a given String and convert it to the integer number.
 * The String may start with a negativ sign ('-') and should contain digits after them.
 * The digits for radix > 10 where built by the numbers 'A'..'Z' respectively 'a'..'z',
 * known as hexa numbers A..F or a..f. 
 * @param src The String, non 0-terminated, see ,,size,,.
 * @param size The number of chars of the String.
 * @param radix The radix of the number, typical 2, 10 or 16, max 36.
 * @param parsedChars number of chars which is used to parse the integer. The pointer may be null if not necessary.
 * @param ctrlChars Some control chars: ' ' skip over space first, '\n' skip over whitespace first.
 *   '-' check and process negative sign, '+' check also positive sign, ' ' after '+' or '-': check space after sign.
 *   'x' check x or 0x designation to parse hex also if radix = 10 is given.
 *   For example: "\n+ x": skip over whitespace, check '+' or '-' as sign, skip over space after sign,
 *   accept "0x" of "x" for hexa value, return the negative hexa value if - is detected.
 * @return the Number.
 * @throws never. All possible digits where scanned, the rest of non-scanable digits are returned.
 *  For example the String contains "-123.45" it returns -123, and the retSize is 3.
 */
extern_C int parseIntRadix_emC ( const char* src, int size, int radix, int* parsedChars, char const* ctrlChars);

extern_C float parseFloat_emC ( const char* src, int size, int* parsedChars);

extern_C double parseDouble_emC ( const char* src, int size, int* parsedChars);


#endif //ndef DEF_NO_StringUSAGE  //Note: this capabilities should not be used on DEF_NO_StringUSAGE

#endif //ndef HGUARD_emC_Base__StringNum_emC
