#ifndef __StringJc_intern_h__
#define __StringJc_intern_h__
#include <Jc/StringJc.h>


/**This method tests whether a StringJc is contained in a StringBuffer-instance already. 
 * If it is so, it will be tested whether the instance is referenced from another source. 
 * If the instance has not a reference, the instance of StringBufferJc will used.
 * If the String isn't contained in a StringBufferJc, or the instance is used from any other side,
 * a new StringBuffer is created and the content of src is filled there.
 *
 * This method is typically used for concatenations of Strings. The concatenation is done using a StringBuffer.
 * A unnecessarry copy of data should be prevent. Mostly the situation is so, that the String
 * is contained in a StringBuffer, from a concatenation statement before, and it isn't referenced from another source. 
 */
METHOD_C struct StringBufferJc_t* transsubstantiateToStringBuffer_StringJc(StringJc ythis, ThCxt* _thCxt);














/**sets the reference, java: String str = src;
*/
//METHOD_C void setRef_StringJc(StringJc* ref, StringJc src);

/**sets the reference, java: String str = src;
*/
//METHOD_C void setref_b_String(StringJc* ref, struct StringBufferJc_t* src);




/**Constructs a new String by decoding the specified subarray of bytes using the specified charset. The length of the new String is a function of the charset, and hence may not be equal to the length of the subarray. 
 * The behavior of this constructor when the given bytes are not valid in the given charset is unspecified. The CharsetDecoder class should be used when more control over the decoding process is required. 
 *
 * @param bytes - The bytes to be decoded into characters
 * @param offset - The index of the first byte to decode
 * @param length - The number of bytes to decode
 * @param charsetName - The name of a supported charset 
 * @throws UnsupportedEncodingException - If the named charset is not supported 
 * @throws IndexOutOfBoundsException - If the offset and length arguments index characters outside the bounds of the bytes array
 * @since JDK1.1 
 * @java java.lang.String(byte[] bytes, int offset, int length, String charsetName) 
 */
//xx METHOD_C StringJc new_bYiiCharset_StringJc(int8_Y* /*volatile*/ bytes, int offset, int length, StringJc charsetName, ThCxt* _thCxt);


//xx METHOD_C StringJc new_cY_StringJc(char_Y* chars, ThCxt* _thCxt);


//xx METHOD_C StringJc new_cYi_StringJc(char_Y* chars, int offset, int count, ThCxt* _thCxt);

  /** Assigns a StringBufferJc to the String, usefull to work without heap
   */

  //METHOD_C void assignBuffer_StringJc(StringJc* ythis, struct StringBufferJc_t* buffer);



//  METHOD_C int size_StringJc(StringJc const ythis, ThCxt* _thCxt);



#endif //__StringJc_intern_h__
