/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this source the LGPL Lesser General Public License,
 * published by the Free Software Foundation is valid.
 * It means:
 * 1) You can use this source without any restriction for any desired purpose.
 * 2) You can redistribute copies of this source to everybody.
 * 3) Every user of this source, also the user of redistribute copies
 *    with or without payment, must accept this license for further using.
 * 4) But the LPGL ist not appropriate for a whole software product,
 *    if this source is only a part of them. It means, the user
 *    must publish this part of source,
 *    but don't need to publish the whole source of the own product.
 * 5) You can study and modify (improve) this source
 *    for own using or for redistribution, but you have to license the
 *    modified sources likewise under this LGPL Lesser General Public License.
 *    You mustn't delete this Copyright/Copyleft inscription in this source file.
 *
 * This source may be used also with another licence, if the author 
 * and all other here named co-authors have agreed to this contract.
 * Especially a company can use a copy of this sources in its products without publishing.
 * The user should have a underwritten contract therefore.
 *
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @author Hartmut Schorrig, 
 *
 * @version 0.96
 * @content Definition of String processing Java-like
 *   Note: The included file Fwc/fw_String.h contains the definition of the type StringJc
 *   and basicly access macros. If any routines from the Fwc-Level (Framework C)
 *   uses this type to reference a character field with given length, it need not include 
 *   the full definitions given here, but only the basicly things.
 *
 *   This file contains the definitions for enhanced methods of StringJc 
 *   and the CLASS_C StringBuilderJc.
 *
 * list of changes:
 * 2012-04-10 Hartmut new: gets0_StringJc(...) copies in a buffer only if necessary, returns a 0-terminated const char*
 *   new: substring_StringBuilderJc() returns a reference to the internal String in its source,
 *  TODO create class StringBuilderJc in Java if an adequate behavior, TODO flag in StringBuilder for persistence or more global Flag in ThreadContext.
 *   new: indexOf_z_StringBuilderJc()
 * 2010-04-04 Hartmut: Fully revised. A description of working with Strings in german language were written
 *        see www.vishia.org/Jc/String_Jc.html         
 *   chg: The class StringBufferJc is now named 'StringBuilderJc', it is adequate java.lang.StringBuilder.
 *        To support downward compatibility, a #define StringBuffer... is added.
 *   new: setTruncateMode..() and wasTruncated..(..). The concept of truncated versus exception
 *   chg: Some obsolte and old methods are removed:
 *        
 * 2009-10-30 Hartmut:
 *   new: transsubstantiateToStringBuffer_StringJc(...) now extern defined,
 *   chg: struct StringBufferJc contains element 'mode' for designation _mTemporary_StringBufferJc.
 *   new: ctorM_i_StringBufferJc(...)
 *   new: setTemporary_StringBufferJc(YTHIS)
 *   corr: All accesses to element count in defines regard mLength__StringJc
 *   chg: Renaming of methods, the Java-typical type-chars and their enhancements for reflection-fields are used:
 *     insert_sII_StringBufferJc instead insert_sii_StringBufferJc
 *     insert_C_StringBufferJc instead insert_c_StringBufferJc
 *     replace_zI_StringBufferJc instead replace_z_StringBufferJc
 *     replace_zI_StringBufferJc instead replace_z_StringBufferJc
 *     etc, some insert--methods are defined with its replace counterpart.
 * 2009-02-05: Hartmut new: capacity_StringBufferJc
 * 2008-12-00: Hartmut a lot of changes, not documented yet.
 * 2004-05-00: Hartmut creation
 *
 ****************************************************************************/
#include <applstdefJc.h>
#ifndef __StringJc_h__
#define __StringJc_h__
#include "Fwc/fw_String.h"    //based on the there defined type StringJc and the access macros.
#include "Fwc/fw_Va_list.h" 
#include "Jc/ObjectJc.h"      //Hint: Simple StringJc: use Fwc/fw_String.h
//#include "Jc/ReflectionJc.h"
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>  //abs
//compatibility
#define StringBufferJc StringBuilderJc
#define StringBufferJc_t StringBuilderJc_t
#define StringBufferJcpp StringBuilderJcpp

struct ThreadContextFW_t;

struct StringBuilderJc_t;
struct CharsetJc_t;

/*@CLASS_C StringJc_ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**CLASS_C_Description StringJc_: This division in the headerfile <Jc/StringJc.h> contains the definitions 
 * of [[class_StringJc]] which depends on [[CRJO:_class_ObjectJc]]. The header file <Jc/ObjectJc.h> is included in this file.
 */

/**Definition of an array of String, able to use as pointer type. 
 * Note: If a fix string array of a given number of Strings is necessary, it should be defined
 * as untyped struct in the equivalent form with the necessary number of Strings.
 * Example: StringJc_Y* sArray; //array of any number of Strings.
 *          struct myStringArray_t{ ObjectArrayJc head; StringJc data[17]; } myStringArray; 
 */
typedef struct StringJc_Y_t{ ObjectArrayJc head; StringJc data[50]; } StringJc_Y;

/**Reference type definition for enhanced references. */
/*Note: The define is necessary, because a reference type definition may be defined in any using header.*/
#ifndef StringJc_YREFDEF
  #define StringJc_YREFDEF
  typedef TYPE_EnhancedRefJc(StringJc_Y);
#endif

/** Clears the content of the String. If the string references any buffer in the [[BlockHeap]],
  * the back references to this enhanced reference will be release. A StringJc is an enhanced reference too.
  * The buffer may be inside the block of BlockHeap as part of a StringBuilderJc, or a substring,
  * it is detected correctly.
  */
METHOD_C void clear_StringJc(StringJc* ythis);


/** Set this as reference to a text.
  * The src-text may be a reference to a constant text, or any other text.
  *
  * If the src-text in not persistent, a new buffer will be created calling [[new_StringBuilderJc(...)]].
  * Note, that that operation causes an exception if no dynamically memory for the new_StringBuilderJc(...) operation
  * is available. Because the routine tests whether the text is persistent, it sh�uld be used
  * in a system without dynamically memory always, to increase the software-safety by runtime-test.
  *
  * If the string references any buffer in the block heap,
  * the back references to this enhanced reference will be set. A StringJc is an enhanced reference too.
  * The buffer may be inside the block as part of a StringBuilderJc, or a substring,
  * it is detected correctly.
  * @param src The source StringJc. It is given per value, not per reference,
           so direct output from StringJc-returning methods are useable as argument.
           The value consist of 2 processor registers.
  */
METHOD_C void set_StringJc(StringJc* ythis, StringJc src);







/* *****************************************************************************************
 * create instances of StringJc
 */



/**Constructs a new String by decoding the specified subarray of bytes using the specified charset. 
 * The length of the new String is a function of the charset, and hence may not be equal to the length of the subarray. 
 *
 * The behavior of this constructor when the given bytes are not valid in the given charset is unspecified. 
 * The CharsetDecoder class should be used when more control over the decoding process is required. 
 *
 * @param bytes - The bytes to be decoded into characters
 * @param offset - The index of the first byte to decode
 * @param length - The number of bytes to decode
 * @param charsetName - The name of a supported charset 
 * @throws UnsupportedEncodingException - If the named charset is not supported 
 * @throws IndexOutOfBoundsException - If the offset and length arguments index characters outside the bounds of the bytes array
 * @since JDK1.1 
 * @javalike [[sunJavadoc/java/lang/String#String(byte[], int, int, java.lang.String)|String(byte[] bytes, int offset, int length, String charsetName)]]
 *           Note: The actual implementation doesn't support encoding. The method may be improved to convert from any charset
 *           to the internal used 8-byte non-UTF8 charset. Internally anytime a char has 8 bit.
 *
 */
METHOD_C StringJc new_BYIICharset_StringJc(int8_Y* bytes, int offset, int length, StringJc charsetName, struct ThreadContextFW_t* _thCxt);


/**Constructs a new String by decoding the specified subarray of bytes using the specified charset. 
 * The length of the new String is a function of the charset, and hence may not be equal to the length of the subarray. 
 *
 * The behavior of this constructor when the given bytes are not valid in the given charset is unspecified. 
 * The CharsetDecoder class should be used when more control over the decoding process is required. 
 *
 * @param bytes - The bytes to be decoded into characters
 * @param offset - The index of the first byte to decode
 * @param length - The number of bytes to decode
 * @param charsetName - The name of a supported charset 
 * @throws UnsupportedEncodingException - If the named charset is not supported 
 * @throws IndexOutOfBoundsException - If the offset and length arguments index characters outside the bounds of the bytes array
 * @since JDK1.1 
 * @javalike [[sunJavadoc/java/lang/String#String(byte[], int, int, java.lang.String)|String(byte[] bytes, int offset, int length, String charsetName)]]
 *           Note: The actual implementation doesn't support encoding. The method may be improved to convert from any charset
 *           to the internal used 8-byte non-UTF8 charset. Internally anytime a char has 8 bit.
 *
 */
METHOD_C StringJc new_vIICharset_StringJc(ByteStringJc bytes, int offset, int length, StringJc charsetName, struct ThreadContextFW_t* _thCxt);


/**Constructs a new String by decoding the specified subarray of bytes using the specified charset. 
 * The length of the new String is a function of the charset, and hence may not be equal to the length of the subarray. 
 *
 * The behavior of this constructor when the given bytes are not valid in the given charset is unspecified. 
 * The CharsetDecoder class should be used when more control over the decoding process is required. 
 *
 * @param bytes - The bytes to be decoded into characters
 * @param offset - The index of the first byte to decode
 * @param length - The number of bytes to decode
 * @param charsetName - The name of a supported charset 
 * @throws UnsupportedEncodingException - If the named charset is not supported 
 * @throws IndexOutOfBoundsException - If the offset and length arguments index characters outside the bounds of the bytes array
 * @since JDK1.1 
 * @javalike [[sunJavadoc/java/lang/String#String(byte[], int, int, java.lang.String)|String(byte[] bytes, int offset, int length, String charsetName)]]
 *           Note: The actual implementation doesn't support encoding. The method may be improved to convert from any charset
 *           to the internal used 8-byte non-UTF8 charset. Internally anytime a char has 8 bit.
 *
 */
METHOD_C StringJc new_mBYIIEncoding_StringJc(PtrVal_int8 bytes, int offset, int length, struct CharsetJc_t* charset, struct ThreadContextFW_t* _thCxt);


/**Returns the StringJc to the text which is stored in the given char-array.
 * This method is able to use without dynamically memory.
 * @param chars Char-array.
 * @return non-peristent String zo the char array.
 * @javalike The method is defined in Java, but in opposite to Java no new string data were created. The returned String is a non-persistent String. 
 *           The persistence will be produced while storing the String or calling ,,persist_StringJc(...),,
 */
METHOD_C StringJc new_CY_StringJc(char_Y* chars, struct ThreadContextFW_t* _thCxt);


/**Returns the StringJc to the text which is stored in the given char-array.
 * This method is able to use without dynamically memory.
 * @param chars Char-array.
 * @param offset start of text inside the Char-array
 * @param count  number of chars.
 * @return non-peristent String zo the char array.
 * @javalike The method is defined in Java, but in opposite to Java no new string data were created. The returned String is a non-persistent String. 
 *           The persistence will be produced while storing the String or calling [[persist_StringJc(...)]]
 */
METHOD_C StringJc new_CYI_StringJc(char_Y* chars, int offset, int count, struct ThreadContextFW_t* _thCxt);





/** Set this as reference to a Stringbuffer.
  * If block-heap with garbage collection is used, the back referenced to ythis will be
  * registered in buffer. If ythis was a reference before, the reference will be
  * released. If the reference is already a reference to the same buffer,
  * nothing will be done.
  * @param ythis the String to be set.
  * @param buffer the buffer to be referenced.
  * @deprecated. Use set_StringJc(ythis, toString_StringBuilderJc(buffer)); It is more uniform, not an 'little extra'.
  */
METHOD_C void xxxsetFromBuffer_StringJc(StringJc* ythis, struct StringBuilderJc_t* buffer);

/**Builds a persistent String, if the given String is non-persistent.
 * This routine calls [[new_StringBuilderJc(...)]] if the String is non-persistent. 
 * The routine may not able to use in a system without any management of dynamically memory for text buffers.
 * If a new text buffer is not able to allocate, an Exception is thrown. See Implementation of ,,new_StringBuilderJc(...),,.
 * @param src any String, may be persistent or not
 * @return a persistent String. If src is persistent, src will be returned.
 */
METHOD_C StringJc persist_StringJc(StringJc src);



/**Declares this string as persistent. The routine should be applied only to a String, 
 * which references a staticly buffer, which is persistent really. 
 * Attention: Do not apply to Strings in stack or thread-context.
 */
StringJc declarePersist_StringJc(StringJc ythis);
//#define declarePersist_StringJc(YTHIS) setValue_OsValuePtr(YTHIS, value_OsValuePtr(YTHIS) & ~mNonPersists__StringJc)


/**Copies the referenced text in the Thread-Context-Buffer and returns the reference to it.
 * This method should be used especially if a routine should return a String, 
 * which is buffered in the stack up to now.
 * @param src The source-String, may be result of [[toString_StringBuilderJc(...)]].
 * @return StringJc-reference per value, it references the text in the thread context buffer.
 */
METHOD_C StringJc copyToThreadCxt_StringJc(StringJc src, struct ThreadContextFW_t* _thCxt);



/**Gets a zero-terminated String from a given String. 
 * This routine needs a buffer to copy the string. But if the given String is zero-terminated already,
 * It is used without copying. In this case some calculation time will be saved.
 * Only if the given String is not zero-termintated, the given part of string will be copied 
 * and terminated with a 0-character. 
 * If the length of the given String is greater then zBuffer-1, either an exception will be thrown 
 * or the String will be truncated.
 *  
 * @param buffer any buffer, where the content of thiz may be copied to.
 * @param zBuffer size of the buffer. The size should be the really size. A \\0 is guaranted at end of buffer.
 * @param exceptionOnLessBuffer true then an exception is thrown if (zBuffer -1) is less then the length of thiz and thiz is not zero-terminated.
 *   If the string refered with thiz is zero terminated, an exception is never thrown.
 *   If false, then the string will be truncated. The parameter _thCtx may be null then.
 * @return The pointer to the zero terminated String. Either it is the String referenced in thiz, or it is buffer. 
 */
METHOD_C char const* gets0_StringJc(StringJc const thiz, char* const buffer, int const zBuffer, bool exceptionOnLessBuffer, struct ThreadContextFW_t* _thCxt);





/* *****************************************************************************************
 * compare methods
 */





/** Compares this string to the specified String. 
  * @param cmp the String to compare
  * @return The result is true if
  *         and only if the argument is not null and is a String object that represents
  *         the same sequence of characters as this object.
  * @javalike But the cmp-Parameter is of type StringJc always. [[sunJavadoc/java/lang/String#equals(java.lang.Object)]]  
  *
  * NOTE compatibility with java: In Java this routine is defined as overrideable method of Object, the cmp-Parameter is of type Object.
  * Java tests whether the parameter is of instance type String (String is derived from Object). 
  * Only if the parameter is of type ,,java.lang.String,, this method compares the text. 
  * Otherwise it returns true if the instances ,,this,, and ,,cmp,, are the same instance, elsewhere returns false. 
  * There is not a call of ,,Object.toString(),,.
  * The Java2C-Translator tests, whether the parameter is of type String 
  * and generates the call of this method with the given String directly. 
  * If the parameter is of type Object or ,,void*,,, a simple comparision of the addresses of the instances will be generated.
  * That is the same behaviour as in Java. The comparision of Objects, which are the same String-instances,
  * may be necessary if the reference to the String is stored in a List<Object>. 
  * This behaviour ist tested by me with Java Version 6, and it is documented in Sun-Javadoc. 
  */
bool equals_StringJc(const StringJc ythis, const StringJc cmp);


/**Compares this string to the specified character text.
 * @param strCmp Any character text
 * @param valueCmp Number of chars to compare, but mask with ,,mLength__StringJc,,.
 *        If -1 or all bits of ,,mLength__StringJc,, are set, 
 *        than the length is got from ,,strlen_Fwc(sCmp, mLength__StringJc),,,
 *        The other bits were not used.
 * @return The result is true if
 *         and only if the argument is not null and the text of this represents
 *         the same sequence of characters as strCmp.
 */
bool equals_zI_StringJc(const StringJc ythis, const char* strCmp, int valueCmp );

/** Compares this string to the specified text. The result is true if
  * and only if the argument is not null and the StringJc referes
  * the same sequence of characters as this object.
  * @param CMP 0-terminated String to compare with this.
  * @return The result is true if
  *         and only if the argument is not null and is a text that represents
  *         the same sequence of characters as this object.
  */
#define equals_z_StringJc(YTHIS, CMP) equals_zI_StringJc(YTHIS, CMP, mLength__StringJc)
/** @deprecated*/
#define equals_s0_StringJc(YTHIS, CMP) equals_z_StringJc(YTHIS, CMP)



/**Tests if this string starts with the specified prefix.
 * javalike, see String.startsWith(String)
 * @param cmp String to compare.
 * @return true if the given String starts with the same character sequence as cmp.
 */
METHOD_C bool startsWith_StringJc(const StringJc ythis, const StringJc cmp);

/**Tests if this string starts with the specified prefix.
 * @param strCmp pointer to a text (,,char const*,,).
 * @param valueCmp number of chars to cmp. If it is -1, the strCmp is accepted as 0-terminated String.
 * @return true if the given String starts with the same character sequence as cmp.
 */
bool startsWith_zI_StringJc(const StringJc ythis, const char* strCmp, int valueCmp );

/**Tests if this string starts with the specified prefix.
 * @param CMP pointer to a text (,,char const*,,) as 0-terminated text.
 * @return true if the given String starts with the same character sequence as cmp.
 */
#define startsWith_z_StringJc(YTHIS, CMP) startsWith_zI_StringJc(YTHIS, CMP, mLength__StringJc)
/**@deprecated*/
#define startsWith_s0_StringJc(YTHIS, CMP) startsWith_z_StringJc(YTHIS, CMP);

/**@deprecated*/
#define startsWith_s0i_StringJc(YTHIS, sCMP, zCMP) startsWith_zI_StringJc(YTHIS, zI_StringJc(sCMP, zCMP));




/**Tests if this string ends with the specified prefix.
 * javalike, see String.endsWith(String)
 * @param cmp String to compare.
 * @return true if the given String ends with the same character sequence as cmp.
 */
METHOD_C bool endsWith_StringJc(const StringJc ythis, const StringJc cmp);

/**Tests if this string ends with the specified suffix.
 * This is the base variant of the method.
 * @param strCmp The suffix
 * @param valueCmp The value from a StringJc, or the number of chars.
 *        Only bits mask with mLength__StringJc (defined in fw_Platform_Conventions.h)
 *        are considered. 
 *        If this parameter is equal mLength__StringJc, 
 *        than the param strCmp is recognized as 0-terminated text.
 * @return true if the given String ends with the same character sequence as cmp.
 */
bool endsWith_zI_StringJc(const StringJc ythis, const char* strCmp, int valueCmp );

/**Tests if this string ends with the specified suffix.
 * @param CMP The suffix as 0-terminated text.
 * @return true if the given String ends with the same character sequence as cmp.
 */
#define endsWith_z_StringJc(YTHIS, CMP) endsWith_zI_StringJc(YTHIS, CMP, mLength__StringJc)





/**Returns a new string that is a substring of this string. 
 * The substring begins at the specified beginIndex and extends to the character at index endIndex - 1.
 * Thus the length of the substring is endIndex-beginIndex.
 * @param startIndex the beginning index, inclusive.
 * @param endIndex the ending index, exclusive. If -1, than the endIndex is the length of string, 
 *        This is used to support the Java-form without parameter endIndex. Java causes an excpetion in this case.
 * @throws IndexOutOfBoundsException - if the beginIndex is negative,
 * or endIndex is larger than the length of this String object, or beginIndex is larger than endIndex.
 * @javalike Lightly modified from Java, see [[sunJavadoc/java/lang/String#substring(int, int)]]
 */
METHOD_C StringJc substring_StringJc(StringJc ythis, int beginIndex, int endIndex, struct ThreadContextFW_t* _thCxt);

/**Returns a new string that is a substring of this string. 
 * The substring begins at the specified beginIndex and extends to the length of the given String..
 * @param BEGIN the beginning index, inclusive.
 * @throws IndexOutOfBoundsException - if the beginIndex is negative,
 * @javalike see [[sunJavadoc/java/lang/String#substring(int)]]
 */
#define substring_I_StringJc(STR, BEGIN, _THC) substring_StringJc(STR, BEGIN, -1, _THC)


/**Returns a new string that is a substring of this string. 
 * The substring begins at the specified beginIndex and extends to the character at index endIndex - 1.
 * Thus the length of the substring is endIndex-beginIndex.
 * @param startIndex the beginning index, inclusive.
 * @param endIndex the ending index, exclusive. If -1, than the endIndex is the length of string, 
 *        This is used to support the Java-form without parameter endIndex. Java causes an excpetion in this case.
 * @throws IndexOutOfBoundsException - if the beginIndex is negative,
 * or endIndex is larger than the length of this String object, or beginIndex is larger than endIndex.
 * @javalike Lightly modified from Java, see [[sunJavadoc/java/lang/String#substring(int, int)]]
 */
#define subSequence_StringJc(STR, BEGIN, END, _THC) substring_StringJc(STR, BEGIN, END, _THC)






/** Returns the index within this string of the first occurrence
    of the specified character. If a character with value ch occurs in
    the character sequence represented by this String object,
    then the index of the first such occurrence is returned --
    that is, the smallest value k such that:

    , this.charAt(k) == ch

    is true. If no such character occurs in this string, then -1 is returned.

 * @param CH a character.
 * @return The index of the first occurrence of the character in the character sequence represented by this object, 
 *         or -1 if the character does not occur.
 * @javalike [[sunJavadoc/java/lang/String#indexOf(int)]], but the codepoint-coding weren't supported,
 *           see [[sunJavadoc/java/lang/String/codePointAt(int)]].
 */
#define indexOf_C_StringJc(YTHIS, CH)  indexOf_CI_StringJc(YTHIS, CH, 0)


/** Returns the index within this text of the first occurrence
    of the specified character, starting the search at the specified index.

    If a character with value ch occurs in the character sequence
    represented by this text object at an index no smaller than fromIndex,
    then the index of the first such occurrence is returned
    --that is, the smallest value k such that:

    , (this.charAt(k) == ch) && (k >= fromIndex)

    is true. If no such character occurs in this text at or after position fromIndex, then -1 is returned.

    There is no restriction on the value of fromIndex.
    If it is negative, it has the same effect as if it were zero:
    this entire text may be searched. If it is greater than the length of this text,
    it has the same effect as if it were equal to the length of this text: -1 is returned.
    Same as in Java.

    @param ch - a character.
    @param fromIndex the index to start the search from.
    @return the index of the first occurrence of the character in the character sequence represented by this object, or -1 if the character does not occur.
 * @javalike [[sunJavadoc/java/lang/String#indexOf(int, int)]] without CodePoint-support.
 */
METHOD_C int indexOf_CI_StringJc(StringJc ythis, int ch, int fromIndex);
/**@deprecated*/
#define indexOf_i_StringJc indexOf_CI_StringJc

/**Searches the text within the given String.
 * @param str text to search referenced with a StringJc
 * @param fromIndex start position to search.
 * @return position of the first occurence counted from start of this String (first position is 0). 
 *         The return value is alway ,,>= fromIndex,,, if the ,,str,, is contained in this.
 *         Return -1 if the ,,str,, is not contain in this.
 * @javalike [[sunJavadoc/java/lang/String#indexOf(java.lang.String, int)]].
 */
METHOD_C int indexOf_sI_StringJc(StringJc ythis, StringJc str, int fromIndex);
/**@deprecated*/
#define indexOf_si_StringJc indexOf_sI_StringJc

/**Searches the text within the given String.
 * @param str text to search referenced with a StringJc
 * @return position of the first occurence from start of this String. The first position is 0. 
 *         Return -1 if the ,,str,, is not contain in this.
 * @javalike [[sunJavadoc/java/lang/String#indexOf(java.lang.String, int)]].
 */
#define indexOf_s_StringJc(YTHIS, str)  indexOf_sI_StringJc(YTHIS, str, 0)
/**@deprecated*/
#define indexOf_S_StringJc(YTHIS, STR)  indexOf_sI_StringJc(YTHIS, STR, 0)


/**Searches the text within the given String.
 * @param str text to search referenced with a StringJc. It is a 0-termninated simple ,,char const*,, 
 *            (recommending only string-literals)
 * @param FROMINDEX start position to search.
 * @return position of the first occurence from start of this String. The first position is 0. 
 *         Return -1 if the ,,str,, is not contain in this.
 */
#define indexOf_zI_StringJc(YTHIS, str, FROMINDEX) indexOf_sI_StringJc(YTHIS, z_StringJc(str), FROMINDEX)
/**@deprecated*/
#define indexOf_s0i_StringJc indexOf_zI_StringJc


/**Searches the text within the given String.
 * @param str text to search referenced with a StringJc. It is a 0-termninated simple ,,char const*,, 
 *            (recommending only string-literals)
 * @param FROMINDEX start position to search.
 * @return position of the first occurence from start of this String. The first position is 0. 
 *         Return -1 if the ,,str,, is not contain in this.
 */
#define indexOf_z_StringJc(YTHIS, str)  indexOf_zI_StringJc(YTHIS, str, 0)
/**@deprecated*/
#define indexOf_s0_StringJc(YTHIS, str)  indexOf_zI_StringJc(YTHIS, str, 0)


/**Searches the character within the given String backward started from fromIndex.
 * @param ch Char to search
 * @param fromIndex start position to search backward. There is no restriction on the value of fromIndex. 
 *        If it is greater than or equal to the length of this string, it has the same effect 
 *        as if it were equal to one less than the length of this string: this entire string may be searched. 
 *        If it is negative, it has the same effect as if it were -1: -1 is returned. 
 * @return position of the last occurence of the char in this String, which is less or equal fromIndex. 
 *         Return -1 if the ,,str,, is not contain in this range.
 * @javalike [[sunJavadoc/java/lang/String#lastIndexOf(int, int)]].
 */
METHOD_C int lastIndexOf_CI_StringJc(StringJc ythis, int ch, int fromIndex );
/**@deprecated*/
#define lastIndexOf_i_StringJc lastIndexOf_CI_StringJc

/**Searches the character within the given String backward started from end.
 * @param ch Char to search
 * @return position of the last occurence of the char in this String. 
 *         Return -1 if the ,,str,, is not contain in this range.
 * @javalike [[sunJavadoc/java/lang/String#lastIndexOf(int)]].
 */
#define lastIndexOf_C_StringJc(YTHIS, ch)  lastIndexOf_CI_StringJc(YTHIS, ch, mLength__StringJc)



/**Searches the text within the given String backward started from fromIndex.
 * @param str text to search referenced with a StringJc
 * @param fromIndex start position to search backward. 
 *        If the text starts at this position with its first char, it is found. 
 *        There is no restriction on the value of fromIndex. 
 *        If it is greater than or equal to the length of this string, it has the same effect 
 *        as if it were equal to one less than the length of this string: this entire string may be searched. 
 *        If it is negative, it has the same effect as if it were -1: -1 is returned. 
 * @return position of the last occurence of the text in this String, which is less or equal fromIndex. 
 *         Return -1 if the ,,str,, is not contain in this range.
 * @javalike [[sunJavadoc/java/lang/String#lastIndexOf(java.lang.String, int)]].
 */
METHOD_C int lastIndexOf_sI_StringJc(StringJc ythis, StringJc str, int fromIndex);

/**Searches the text within the given String backward started from end.
 * @param str text to search referenced with a StringJc
 * @return position of the last occurence of the text in this String. 
 *         Return -1 if the ,,str,, is not contain in this range.
 * @javalike [[sunJavadoc/java/lang/String#lastIndexOf(java.lang.String)]].
 */
#define lastIndexOf_s_StringJc(YTHIS, str)  lastIndexOf_sI_StringJc(YTHIS, str, mLength__StringJc)

/**Searches the text within the given String backward started from fromIndex.
 * @param str text to search referenced with a StringJc. It is given as 0-termninated simple ,,char const*,, 
 *            (recommending only string-literals)
 * @param fromIndex start position to search backward. 
 *        If the text starts at this position with its first char, it is found. 
 *        There is no restriction on the value of fromIndex. 
 *        If it is greater than or equal to the length of this string, it has the same effect 
 *        as if it were equal to one less than the length of this string: this entire string may be searched. 
 *        If it is negative, it has the same effect as if it were -1: -1 is returned. 
 * @return position of the last occurence of the text in this String, which is less or equal fromIndex. 
 *         Return -1 if the ,,str,, is not contain in this range.
 */
#define lastIndexOf_zI_StringJc(YTHIS, str, fromIndex) lastIndexOf_sI_StringJc(YTHIS, z_StringJc(str), fromIndex)

/**Searches the text within the given String backward started from fromIndex.
 * @param str text to search referenced with a StringJc. It is given as 0-termninated simple ,,char const*,, 
 *            (recommending only string-literals)
 * @return position of the last occurence of the text in this String. 
 *         Return -1 if the ,,str,, is not contain in this range.
 */
#define lastIndexOf_z_StringJc(YTHIS, str) lastIndexOf_sI_StringJc(YTHIS, z_StringJc(str), mLength__StringJc)



/**Returns a formatted string using the specified format string and arguments.
 * @param format A format string
 * @param typeArgs 0-terminated text with the type chars for the following arguments. 
 *        The arguments should be matching to the format String generally.
 *        But some modifications are allowed, see behaviour in Java.
 *        The type of the following arguments need 1 char per argument.
 *        * The char is ,,BSIJFDZ,, for the basicly types int8, int16, int32, int64, float, double and boolean.
 *        The int-types are adequate the Java-types byte, short, int, long.
 *        * The char is ,,szP,, for argument Types ,,StringJc,,, ,,char const*,, and ,,void*,,.
 *        A void* will be shown with its pointer value, like used on sprintf.
 *        * An ObjectJc as argument is not supported yet. It should have the ,,o,, as character,
 *        and the toString-Method should be invoked (TODO).
 * @param vargList Arguments referenced by the format specifiers in the format string. 
 *        If there are more arguments than format specifiers, the extra arguments are ignored. 
 *        The number of arguments is variable and may be zero.  
 * @return The formatted string, buffer in Thread-Context 
 * @javalike [[sunJavadoc/java/lang/String#format(java.lang.String, java.lang.Object...)]]. 
 *           But the kind of handling with the variable argument list is modified. 
 *           In Java the arguments are all of type Object, derived from it, and its type is able to test.
 *           In the C-Implementation the argument list is handled like described in ,,<stdarg.h>,,.
 *           The types of the arguments should be given extra. The [[Java2C]]-Translator translates it correctly.
 */
METHOD_C StringJc format_a_StringJc(StringJc format, char const* typeArgs, ...); 

/**Returns a formatted string using the specified format string and arguments.
 * @param format A format string as 0-terminated text, recommended a text-literal.
 * @param typeArgs Type of the Arguments referenced by the format specifiers in the format string. If there are more arguments than format specifiers, the extra arguments are ignored. The number of arguments is variable and may be zero. The maximum number of arguments is limited by the maximum dimension of a Java array as defined by the Java Virtual Machine Specification. The behaviour on a null argument depends on the conversion. 
 * @return The formatted string, buffer in Thread-Context 
 */
METHOD_C StringJc format_za_StringJc(char const* format, char const* typeArgs, ...); 



/**Returns a formatted string using the specified format string and arguments.
 * @param format A format string
 * @param vargList Arguments referenced by the format specifiers in the format string. 
 *        If there are more arguments than format specifiers, the extra arguments are ignored. 
 *        The number of arguments is variable and may be zero.  
 * @return The formatted string, buffer in Thread-Context 
 * @javalike [[sunJavadoc/java/lang/String#format(java.lang.String, java.lang.Object...)]]. 
 *           But the kind of handling with the variable argument list is modified. 
 *           In Java the arguments are all of type Object, derived from it, and its type is able to test.
 *           This C-Implementation gets the argument list in form of a special structure.
 */
METHOD_C StringJc format_A_StringJc(StringJc format, Va_listFW vargList, struct ThreadContextFW_t* _thCxt);


/**Returns a string representation of the double argument. All characters mentioned below are ASCII characters.
 * The representation is following the output of sprintf.
 * @return String buffer in Thread-context.
 * @javalike It is like [[sunJavadoc/java/lang/Double#toString()]].
 */
METHOD_C StringJc toString_DoubleJc(double value, struct ThreadContextFW_t* _thCxt);

/**Returns the string representation of the int argument. 
 * The representation is exactly the one returned by the Int.toString method of one argument
 * @return String buffer in Thread-context.
 * @javalike It is like [[sunJavadoc/java/lang/String#valueOf(int)]].
 */
#define valueOf_I_StringJc(VAL) toString_IntegerJc(VAL, _thCxt) 


/**Returns the string representation of the double argument. 
 * The representation is exactly the one returned by the Double.toString method of one argument
 * @return String buffer in Thread-context.
 * @javalike It is like [[sunJavadoc/java/lang/String#valueOf(double)]].
 */
#define valueOf_D_StringJc(VAL) toString_DoubleJc(VAL, _thCxt) 



/**Returns a new string resulting from replacing all occurrences of oldChar in this string with newChar.
 * If the character oldChar does not occur in the character sequence represented by this String object, 
 * then a reference to this String object is returned. 
 * Otherwise, a new String object is created that represents a character sequence identical 
 * to the character sequence represented by this String object, except that every occurrence of oldChar 
 * is replaced by an occurrence of newChar. 
 * @param oldChar The char which was to replace at any occurence.
 * @param newChar Char to set.
 * @return String with buffer in Thread-context.
 * @javalike It is like [[sunJavadoc/java/lang/String#replace(char, char)]].
 */
METHOD_C StringJc replace_StringJc(StringJc ythis, char oldChar, char newChar, struct ThreadContextFW_t* _thCxt);


/**Replaces the chars using a StringBuilder-buffer to store the result.
 * @param oldChar The char which was to replace at any occurence.
 * @param newChar Char to set.
 * @param buffer A StringBuilder-Instance to use as buffer for the result String. 
 *        The buffer of the StringBuilder is intitialized with the content of the given text. 
 *        It is typically, that the text of this is stored already in the buffer,
 *        because the same buffer in used to build the string.
 *        That situation is detected by compare the reference to the text in this and the buffer-address.
 * @return the given StringBuilder-Instance.
 * @javalike: Java doesn't know a simple method to replace chars in a StringBuilder. This method is created
 *            firstly to support ,,String.replace(...),,, if the buffer is known and the String should not persistent.
 *            This conditions can be given by [[Java2C]]-Translation as annotations in the Java-source.
 *            Than the replacement works time-optimal.
 */
METHOD_C struct StringBuilderJc_t* replace_u_StringJc(StringJc ythis, char oldChar, char newChar
           , struct StringBuilderJc_t* buffer, struct ThreadContextFW_t* _thCxt);





/**copies the content of the src into a char*-buffer.
 * Copies characters from this string into the destination character array. 
 * The first character to be copied is at index srcBegin; 
 * the last character to be copied is at index srcEnd-1 
 * (thus the total number of characters to be copied is srcEnd-srcBegin). 
 * The characters are copied into the subarray of dst starting at index dstBegin and ending at index:
 * ,  dstbegin + (srcEnd-srcBegin) - 1
 *
 * @param srcBegin index of the first character in the string to copy.
 * @param srcEnd index after the last character in the string to copy.
 * @param dst the destination array.
 * @param dstBegin the start offset in the destination array. 
 * @throws IndexOutOfBoundsException - If any of the following is true: 
 * * srcBegin is negative. 
 * * srcBegin is greater than srcEnd 
 * * srcEnd is greater than the length of this string 
 * * dstBegin is negative 
 * * dstBegin+(srcEnd-srcBegin) is larger than dst.length.
 * @javalike [[sunJavadoc/java/lang/String#getChars(int, int, char[], int)]]
 */
METHOD_C void getChars_StringJc(StringJc ythis, int srcBegin, int srcEnd, char_Y* dst, int dstBegin, struct ThreadContextFW_t* _thCxt);


/**Returns the String as byte stream. */
//METHOD_C int8_Y* getBytes_StringJc(StringJc ythis, struct ThreadContextFW_t* _txCtx);

#define getBytes_StringJc(STR, THCXT) getBytesEncoding_StringJc(STR, null_StringJc, THCXT)

/**Returns the String as byte stream. */
METHOD_C ByteStringJc getBytesEncoding_StringJc(StringJc ythis, StringJc encoding, struct ThreadContextFW_t* _txCtx);



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)

/**The C++-Variante. It is comfortable to use C++ because some methods and operators are argument-sensitive (overloaded),
 * and the code is better readable.
 * This class defines only methods, and the methods are not virutal. It followes the java convention: The class java.lang.String is final.
 * Thats why a applicable side action exists: The memory layout of StringJcpp is identical with the memory layout of StringJc.
 * So conversions may be able without any problems. Using static_cast<StringJc*>
 */
class  StringJcpp: public StringJc
{ public:

  StringJcpp(){ set_OS_PtrValue(*(static_cast<StringJc*>(this)), null,0); }

  StringJcpp(const char* src)
  { INIT_StringJc(*this, src, strlen(src));
  }

   StringJcpp(const char* src, int size)
  { INIT_StringJc(*this, src, size);
  }

  StringJcpp(const StringJc src)
  { StringJc* super = this;
    INIT_s_StringJc(*super, src);
  }

   StringJcpp&  operator=(class StringBufferJcpp& src);

   StringJcpp(class StringBufferJcpp& src);

  ~StringJcpp(){ } //  CLEARREFJc(*static_cast<StringJc*>(this)); }

   operator StringJc(){ return *static_cast<StringJc*>(this); }

   char charAt(int idx)const{ return charAt_StringJc(*static_cast<StringJc const*>(this), idx); }


   StringJcpp& operator=(StringJcpp src)
  {
    set_StringJc(this, src); return *this;
  }

   StringJcpp& operator=(StringJc src)
  {
    set_StringJc(this, src); return *this;
  }

   StringJcpp& operator=(const char* src)
  {
    clear_StringJc(this); set_StringJc(this, z_StringJc(src)); return *this;
  }

   StringJcpp& operator=(int src)  //src may be only 0
  {
    clear_StringJc(this); return *this;
  }


   bool equals(const char* sCmp) const
  { return equals_s0_StringJc(*static_cast<StringJc const*>(this), sCmp);
  }

   bool equals(const StringJc sCmp) const
  { return equals_StringJc(*static_cast<StringJc const*>(this), sCmp);
  }

   int length() const
  { return length_StringJc(*static_cast<StringJc const*>(this));
  }

   bool startsWith(const char* sCmp) const
  { return startsWith_z_StringJc(*static_cast<StringJc const*>(this), sCmp);
  }

   bool startsWith(const StringJc sCmp) const
  { return startsWith_StringJc(*static_cast<StringJc const*>(this), sCmp);
  }

   bool endsWith(const char* sCmp) const
  { return endsWith_z_StringJc(*static_cast<StringJc const*>(this), sCmp);
  }

   bool endsWith(const StringJc sCmp) const
  { return endsWith_StringJc(*static_cast<StringJc const*>(this), sCmp);
  }

   int indexOf(char cc) const
  { return indexOf_C_StringJc(*static_cast<StringJc const*>(this), cc);
  }

   int indexOf(char cc, int fromIndex) const
  { return indexOf_CI_StringJc(*static_cast<StringJc const*>(this), cc, fromIndex);
  }

   int indexOf(const char* str) const
  { return indexOf_z_StringJc(*static_cast<StringJc const*>(this), str);
  }

   int indexOf(const char* str, int pos) const
  { return indexOf_zI_StringJc(*static_cast<StringJc const*>(this), str, pos);
  }

   int indexOf(StringJc str) const
  { return indexOf_s_StringJc(*static_cast<StringJc const*>(this), str);
  }

   int indexOf(StringJc str, int pos) const
  { return indexOf_sI_StringJc(*static_cast<StringJc const*>(this), str, pos);
  }

   int lastIndexOf(char cc) const
  { return lastIndexOf_C_StringJc(*static_cast<StringJc const*>(this), cc);
  }

   int lastIndexOf(char cc, int fromIndex) const
  { return lastIndexOf_CI_StringJc(*static_cast<StringJc const*>(this), cc, fromIndex);
  }

   int lastIndexOf(const char* str) const
  { return lastIndexOf_z_StringJc(*static_cast<StringJc const*>(this), str);
  }

   int lastIndexOf(const char* str, int pos) const
  { return lastIndexOf_zI_StringJc(*static_cast<StringJc const*>(this), str, pos);
  }

   int lastIndexOf(StringJc str) const
  { return lastIndexOf_s_StringJc(*static_cast<StringJc const*>(this), str);
  }

   int lastIndexOf(StringJc str, int pos) const
  { return lastIndexOf_sI_StringJc(*static_cast<StringJc const*>(this), str, pos);
  }


   StringJc substring(int beginIndex, int endIndex) const
  { StringJc ret = substring_StringJc(*static_cast<StringJc const*>(this), beginIndex, endIndex, null);
    return ret;
  }

   StringJc substring(int beginIndex) const
  { StringJc ret = substring_StringJc(*static_cast<StringJc const*>(this), beginIndex, -1, null);
    return ret;
  }
};

//StringJc operator char const*(char const* src){ return zI_StringJc(src, strlen_Fwc(src, mLength__StringJc); }


#endif //__CPLUSPLUSJcpp


/*@CLASS_C StringJc_CharSeqJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**This struct is only used for invocation of methods of [[class_CharSeqJc]] via method table 
 * if a [[class_StringJc]] is given as argument. This struct is necessary because the method table routines
 * need a [[CRJO:_class_ObjectJc]] reference to work. An instance of this struct may only necessary as argument
 * for [[getMtblRef_CharSeqJc(...)]] placed in the stack local data for immediately usage.
 */
typedef struct StringJc_CharSeqJc_t
{
  ObjectJc base;
  char const* s;
  int32 length;
} StringJc_CharSeqJc;




/*@CLASS_C CharSeqJc_ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**A CharSeqJc is the same as StringJc. The difference is: The reference type can be also an ObjectJc*, 
 * whereby the ObjectJc-instance should implement the CharSeqJc interface. 
 * ,,#define CharSeqJc StringJc is contained in <Fwc/fw_String.h>
 */


typedef int32 MT_length_CharSeqJc(struct ObjectJc_t* ithiz, ThCxt* _thCxt);
typedef char MT_charAt_CharSeqJc(struct ObjectJc_t* ithiz, int32 ix, ThCxt* _thCxt);
typedef CharSeqJc MT_subSequence_CharSeqJc(struct ObjectJc_t* ithiz, int32 from, int32 to, ThCxt* _thCxt);

/**To organize dynamic link method call the jump table of virtual methods is neccessary. */
typedef struct Mtbl_CharSeqJc_t
{ MtblHeadJc head;
  MT_length_CharSeqJc* length;
  MT_charAt_CharSeqJc* charAt;
  MT_subSequence_CharSeqJc* subSequence;
  Mtbl_ObjectJc mtblObjectJc;  //same method types as ObjectJc
} Mtbl_CharSeqJc;

extern char const sign_Mtbl_CharSeqJc[];



/**A pointer to StringJc structure containing null-values.
 * NOTE: a pointer is necessary because a const problem occurs otherwise.
 */
#define null_CharSeqJc null_StringJc

#define NULL_CharSeqJc NULL_StringJc

extern char const sign_Mtbl_CharSeqJc[];


#define PTR_CharSeqJc(THIZ) PTR_OS_PtrValue(THIZ, ObjectJc const)

#define VAL_CharSeqJc(THIZ) value_OS_PtrValue(THIZ)

#define isStringJc_CharSeqJc(THIZ) ((value_OS_PtrValue(THIZ) & mLength__StringJc) <= kMaxLength_StringJc)

#define z_CharSeqJc z_StringJc

/*
INLINE_Fwc CharSeqJc z_CharSeqJc(char const* src)
{ CharSeqJc ret;
  int size = strlen_Fwc(src, kMaxLength_StringJc);
  set_OS_PtrValue(ret, src, size); 
  return ret;
}
*/

/**Builds a CharSeqJc from a given C-string with given length. 
 * @param length The length. It should be match to src. If length is negative, the length is counted from end
     of the 0-terminated length of src, -1 is the end.
 * @return a CharSeqJc which is a StringJc with known length.
 */
#define zI_CharSeqJc zI_StringJc
/*
INLINE_Fwc CharSeqJc zI_CharSeqJc(char const* src, int length)
{ CharSeqJc ret;
  if(length < 0) {
    int lengthSrc = strlen_Fwc(src, kMaxLength_StringJc);
    length = lengthSrc - (-length) +1;
  }
  set_OS_PtrValue(ret, src, length); 
  return ret;
}
*/



//see fromObjectJc_CharSeqJc(...) for further methods.




#ifndef CharSeqJcMTBDEF
  #define CharSeqJcMTBDEF
  typedef struct CharSeqJcMTB_t { struct Mtbl_CharSeqJc_t const* mtbl; struct ObjectJc_t* ref; } CharSeqJcMTB;
#endif


/**Builds a struct ,,CharSeqJcMTB,, which contains the reference to the method table of dynamic methods of a CharSeqJc
 * for any given ,,CharSeqJc,,. 
 *
 * If the given ,,CharSeqJc,,-instance may be a simple ,,StringJc,, an instance ,,dst,, should be given.
 * Then the following form should be used:
 * ,StringJc_CharSeqJc cstr;
 * ,CharSeqJcMTB csm = getMtblRef_CharSeqJc(mycs, &cstr, _thCxt);
 * The ,,cstr,, is referenced in ,,csm,,. Both should be used in the local stack context in the current thread only.
 *
 * With that method it is possible to access any ,,CharSeqJc,, with fast dynamic method invocation, for example:
 * ,for (i=0; i<length; ++i){
 * ,  char cc = csm->charAt(i, _thCxt);
 * ,  buffer[i] = cc;
 * ,}
 * Elsewhere [[charAt_CharSeqJc(...)]] should be used which needs a longer time for any character because the content
 * of the given CharSeqJc should be tested firstly whether it is a ,,StringJc,,, ,,StringBuilderJc,, etc. 
 * or whether a given index to the method table is correct.
 *
 * @param dst_StringJc can be null if thiz is never a simple [[class_StringJc]]. Elsewhere this instance should be given.
 * @return the method table and the ObjectJc*-reference by value. 
 * @throws IllegalArgumentException if thiz is a StringJc and ,,dst_StringJc,, is not given.
 * If exception handling is not present then the return values are null instead the exception.
 */
METHOD_C CharSeqJcMTB getMtblRef_CharSeqJc(CharSeqJc thiz, StringJc_CharSeqJc* dst_StringJc, ThCxt* _thCxt);



/**Builds a CharSeqJc {ref, val} tupel from an instance of ObjectJc which implements the CharSeqJc-interface. 
 * The CharSeqJc {ref, val} tupel contains the reference to the ObjectJc-instance (ref)
 * and the index in the method table of the instance-type to the CharSeqJc-part. That method table is searched
 * using [[CRJO:_getMtbl_ObjectJc(...)]]. ,,val,, contains the index and the designation with [[mIsCharSeqJcMtbl_CharSeqJc]].
 * The methods [[length_CharSeqJc(...)]] etc. detect this designation, use the index to the method table
 * and don't need to invoke [[CRJO:_getMtbl_ObjectJc(...)]] again. That methods test the consistence of the instance, 
 * reflection and method table with [[CRJO:_checkMtbl_ObjectJc(...)]] which gives safety but need lesser calculation time.
 */
CharSeqJc fromObjectJc_CharSeqJc(struct ObjectJc_t* thiz);


/**Definition of an array of String, able to use as pointer type. 
 * Note: If a fix string array of a given number of Strings is necessary, it should be defined
 * as untyped struct in the equivalent form with the necessary number of Strings.
 * Example: StringJc_Y* sArray; //array of any number of Strings.
 *          struct myStringArray_t{ ObjectArrayJc head; StringJc data[17]; } myStringArray; 
 */
//typedef struct CharSeqJc_Y_t{ ObjectArrayJc head; CharSeqJc data[50]; } CharSeqJc_Y;
//#define CharSeqJc_Y StringJc_Y

typedef struct CharSeqJc_Y_t{ ObjectArrayJc head; CharSeqJc data[50]; } CharSeqJc_Y;



/**Reference type definition for enhanced references. */
/*Note: The define is necessary, because a reference type definition may be defined in any using header.*/
#ifndef CharSeqJc_YREFDEF
//  #define CharSeqJc_YREFDEF
//  DEFINE_EnhancedRefJc(CharSeqJc);
#endif


extern_C struct ClassJc_t const reflection_CharSeqJc;






#define subSequence_CharSeqJc(THIZ, from, to, THC) (\
  isValid_ObjectJc((THIZ).ref) \
  ? ((Mtbl_CharSeqJc*)getMtbl_ObjectJc((ObjectJc*)(THIZ).ref, sign_Mtbl_CharSeqJc))->subSequence((ObjectJc*)(THIZ).ref, from, to, THC) \
  : substring_StringJc(*(StringJc*)&(THIZ), from, to, THC ) )

/**Converts a given CharSeqJc to a String. Reads all Chars and stores it in a buffer in ThreadContext. 
 * * If thiz is a really StringJc, it returns thiz.
 * * If thiz contains a StringBuilderJc-Reference (marked with [[StringJc#kIsStringBuilder_StringJc]]) 
 * then the pointer to the content of the StringBuilder is returned. It means the String may not persistent. 
 * Use [[toStringPersist_StringBuilderJc(...)]] to build a persistent String.
 * * If thiz contains a reference to any Object which implements CharSequence then a new buffer is build in the thread context. 
 * The characters are read with invocation of [[charAt_CharSeqJc(...)]] and written in the buffer. Therewith the string is prepared already.
 * The returned string is persistent, but not permanent.
 */
METHOD_C StringJc toString_CharSeqJc(CharSeqJc thiz);

#define SET_CharSeqJc(DST, SRC) { if(isValid_ObjectJc((SRC).ref)) { SETREFJc((DST), (SRC).ref, CharSeqJc); } else {  (DST) = (SRC); } }

//#define from_StringBuilder_CharSeqJc from_StringBuilder_CharSeqJc

/*@CLASS_C StringBuilderJc_ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct Mtbl_StringBufferJc_t 
{ MtblHeadJc head;
  Mtbl_ObjectJc ObjectJc; 
  //Method table of interfaces:
  Mtbl_CharSeqJc CharSeqJc;
} Mtbl_StringBufferJc;


typedef struct MtblDef_StringBufferJc_t { Mtbl_StringBufferJc mtbl; MtblHeadJc end; } MtblDef_StringBufferJc;

extern MtblDef_StringBufferJc const mtblStringBufferJc;



/**Finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_StringBuilderJc_F(ObjectJc* othis, struct ThreadContextFW_t* _thCxt);




/**Initializes the Stringbuffer with an immediate buffer after the StringBuffer management values.
 * The size stored inside ObjectJc determines the size of the buffer. 
 * @param othis The ObjectJc-head data, initialized. The size inside the othis-Instance 
 *              determines the length for the buffer.
 * @return the initialized instance at that memory placement.
 * @throws RuntimeException if the memory is to less.
 * @javalike In Java the [[sunJavadoc/java/lang/StringBuilder#StringBuilder()]] constructs an empty (small) buffer.
 *           The behaviour is similar, but the buffer has its fix size 
 *           given by memory amount of the instance referes with othis.
 *           The difference is, that a realloc of buffer isn't supported.
 */
METHOD_C StringBuilderJc* ctorO_StringBuilderJc(ObjectJc* othis, struct ThreadContextFW_t* _thCxt);
#define ctorO_StringBufferJc ctorO_StringBuilderJc

/**Initializes the Stringbuffer to reference the given buffer with content with the given size.
 * This method should be used if an external char[] is to be used.
 * The nrof chars in the StringBuffer is determined by the content of the buffer
 * with the 0-terminated C-like method.
 * The char[] can also be a part of a char[].
 * @param othis Intance for the StringBuilderJc. The ObjectJc-part have to be initialized. 
 *              The size of the instance, given in the ObjectJc-data, should be equal or maybe greater
 *              as sizeof(StringBuilder). 
 * @param buffer A char[...]-buffer with content. write 0 at start if it should be empty.
 * @param size the nrof bytes for buffer. The size inside the StringBuilderJc is set to this value -1,
 *        It is because a last zero-Byte should be able to place any time.
 * @javalike In Java the [[sunJavadoc/java/lang/StringBuilder(int)]] constructs an empty buffer
 *           with the given size. Here it is similar respectively size, but the location of the buffer
 *           is given too. The difference is, that Java uses always the dynamical memory to allocate.
 *           where in C more possibilites of determine the locations of memory are need.
 *           The possibility of provide an initialized buffer is a combination with the 
 *           [[sunJavadoc/java/lang/StringBuilder#StringBuilder(java.lang.string)]]-constructor.
 */
METHOD_C StringBuilderJc* ctorO_zI_StringBuilderJc(ObjectJc* othis, char* buffer, int size, struct ThreadContextFW_t* _thCxt);
#define ctorO_zI_StringBufferJc ctorO_zI_StringBuilderJc


/**Initializes a StringBuffer with no characters in it and an initial capacity specified by the capacity argument.
 * @param othis The initialized ObjectJc of the instance. 
 *              If the Object conaints enaugh space for size (field ,,ObjectJc.objectIdentSize,,),
 *              than the buffer will be assigned immediately after the StringBuilderJc-instance.
 * @param size the nrof bytes for buffer. A buffer will be allocated, if the size of the othis 
 *              is less than ,,size - (sizeof(StringBuilderJc) -4),,. 
 *              Otherwise the space after the StringBuilderJc-instance started with the _buffer-Element (last 4 Bytes)
 *              is used as buffer.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#StringBuilder(int)]] with the difference, that the immediate buffer is supported here.
 *           Java allocates the buffer in heap anytime.  
 */
METHOD_C StringBuilderJc* ctorO_I_StringBuilderJc(ObjectJc* othis, int size, struct ThreadContextFW_t* _thCxt);
#define ctorO_I_StringBufferJc ctorO_I_StringBuilderJc

/**Initalizes the given Instance with the content of src.
 * @param othis The initialized ObjectJc of the instance. 
 *              If the Object conaints enaugh space for str (field ,,ObjectJc.objectIdentSize,,),
 *              than the buffer will be assigned immediately after the StringBuilderJc-instance.
 * @param src the initializing content. If the length of src is less or equal the space of the othis for buffer, that buffer will be used.
 *            Elsewhere a buffer will be allocated in the heap.  
 * @javalike [[sunJavadoc/java/lang/StringBuilder#StringBuilder(java.lang.String)]] with the difference, that the immediate buffer is supported here.
 *           Java allocates the buffer in heap anytime. The other difference is: A reallocation of buffer is not supported. It means, 
 *           if str is only the start content and an append will be called, it does fail here if the ctor allocates the space for buffer itself.
 *           It does not fail, if the space is allocated in the [[BlockHeap]] and the block-size is enaugh (the block size is constant),
 *           or if the allocation is done with enaugh space for the instance itself (than the text is stored immediately)
 *           or if the instance is embedded and has immediate space for the text after it, like described in [[CONST_addSize_StringBuilderJc(...)]].
 */
#define ctorO_s_StringBuilderJc(THIZ, SRC, THCXT) ctorO_cs_StringBuilderJc(THIZ, (SRC), THCXT)
//METHOD_C StringBuilderJc* ctorO_s_StringBuilderJc(ObjectJc* othis, StringJc src, struct ThreadContextFW_t* _thCxt);
#define ctorO_s_StringBufferJc ctorO_s_StringBuilderJc



/**Initalizes the given Instance with the content of src.
 * @param othis The initialized ObjectJc of the instance. 
 *              If the Object conaints enaugh space for str (field ,,ObjectJc.objectIdentSize,,),
 *              than the buffer will be assigned immediately after the StringBuilderJc-instance.
 * @param src the initializing content. If the length of src is less or equal the space of the othis for buffer, that buffer will be used.
 *            Elsewhere a buffer will be allocated in the heap.  
 * @javalike [[sunJavadoc/java/lang/StringBuilder#StringBuilder(java.lang.String)]] with the difference, that the immediate buffer is supported here.
 *           Java allocates the buffer in heap anytime. The other difference is: A reallocation of buffer is not supported. It means, 
 *           if str is only the start content and an append will be called, it does fail here if the ctor allocates the space for buffer itself.
 *           It does not fail, if the space is allocated in the [[BlockHeap]] and the block-size is enaugh (the block size is constant),
 *           or if the allocation is done with enaugh space for the instance itself (than the text is stored immediately)
 *           or if the instance is embedded and has immediate space for the text after it, like described in [[CONST_addSize_StringBuilderJc(...)]].
 */
METHOD_C StringBuilderJc* ctorO_cs_StringBuilderJc(ObjectJc* othis, CharSeqJc src, struct ThreadContextFW_t* _thCxt);
#define ctorO_cs_StringBufferJc ctorO_cs_StringBuilderJc



/**Creates a new StringBuilder-instance if possible. 
 * This routine assumes, that dynamically memory is present. 
 * In long-running-realtime-applications a dynamic-memory-management may be spurious.
 * But it may be possible to allocate some memory in startupt time.
 * The implementation of this routine uses the routine ,,alloc_ObjectJc(...),,.
 * This routine may be implemented in a special way adequate to the system definitions.
 * @param SIZE The size for buffer. -1, than the standard size will be used (block size of [[BlockHeap]] or other concept).
 * @return the instance.
 * @throws Exception if no dynamically memory is available.
 * @javalike call of ,,new StringBuilder(size),,
 */
#define new_StringBuilderJc(SIZE, _thCxt) ctorO_StringBuilderJc(alloc_ObjectJc(-1, 0, _thCxt), _thCxt)
#define new_StringBufferJc new_StringBuilderJc



/**Returns the StringBuilderJc-instance in the Thread Context. 
 * This instance should used if a StringJc is to return. 
 * The contract for such returned StringJc is: It should be used immediately, 
 * it shouldn't be referenced for further using. 
 * The reason therefore is: There is only one instance per Thread.
 * The storing a text in the Thread Context prevent the needness of an extra Buffer.
 * @param sign a number to support debugging which part of code has allocated, use a unified number if possible.
 * @return the empty instance in thread-context-buffer. 
 *          This instance is designated ''locate in threadBuffer'' using the mode-bit ,,_mThread_StringBuilderJc,,.
 */
METHOD_C StringBuilderJc* threadBuffer_StringBuilderJc(char const* sign, struct ThreadContextFW_t* _thCxt);
#define threadBuffer_StringBufferJc threadBuffer_StringBuilderJc

/**Initializes the StringBuilderJc-instance in the Thread Context with the given String
 * and returns it.
 * This variant is proper to use for example if the src is stored in the Stack and should be returned now.
 * If a StringJc should be returned, use this method and call than [[toString_StringBuilderJc()]]
 * or call [[toStringInThreadCxt_StringBuilderJc(...)]] with the given StringBuilderJc-instance, it does the same.
 * @param src The initialized content.
 * @return the initialized instance in thread-context-buffer. 
 *          This instance is designated as ''locate in threadBuffer'' using the mode-bit ,,_mThread_StringBuilderJc,,.
 */
METHOD_C StringBuilderJc* threadBuffer_s_StringBuilderJc(CharSeqJc src, char const* sign, struct ThreadContextFW_t* _thCxt);
#define threadBuffer_s_StringBufferJc threadBuffer_s_StringBuilderJc



/**Set the stringConcatBuffer flag. A StringBuilderJc-Instance should be dedicated in that way, 
 * if the instance is created only to concatenate a text, and there is no other reference to it.
 * If hava to be a persistent location (not in Stack, not in Thread-Context, but allocated dynamically),
 * its buffer is used as the persistent buffer for a CharSeqJc immediately. The allocation of an extra buffer isn't need.
 * @return value of _mode, but do not use it. The macro is able to use in a ( expr, expr, ...) form.
 */
#define setStringConcatBuffer_StringBuilderJc(YTHIS) ((YTHIS)->_mode |= _mStringConcatBuffer_StringBuilderJc)



/**Set the truncate mode. In this mode on buffer overflow the text will be truncated, 
 * instead calling an exception. Use [[wasTruncated_StringBuilderJc()]] to check whether a truncate was occured.
 * @param bTruncate true than truncate without exception, false than cause an exception on buffer overflow.
 * @return the current mode before.
 */
bool setTruncateMode_StringBuilderJc(StringBuilderJc* ythis, bool bTruncate);

/**Checks whether the buffer content was truncated any time before. 
 * The truncate bit is reseted thereby, so a next call returns false if a new truncation event doesn't occur. 
 * @return true if the buffer content was truncated during an insert-, replace- or append-operation. 
 */
bool wasTruncated_StringBuilderJc(StringBuilderJc* ythis);

/**Releases the buffer from the designation of a built StringJc-reference. The StringBuilder can used now
 * for new changing operations. But see and use also [[toStringNonPersist_StringBuilderJc(...)]].
 * If the user calls this method, it should be assured, that no reference is used furthermore, 
 * which assumes the previous content. It is a method to optimize buffer usage in C.
 * @return value of _mode, but do not use it. The macro is able to use in a ( expr, expr, ...) form.
 */
#define releaseStringBuilt_StringBuilderJc(YTHIS) ((YTHIS)->_mode &= ~_mStringBuilt_StringBuilderJc)


/**
 * return the size of the StringBuilder with its immediate following text
 * or -1 if the text is referenced.
 */
INLINE_Fwc int _reduceCapacity_StringBuilderJc(StringBuilderJc* thiz, int16 size){
  ASSERTJc_EXCLMAX(size, abs(thiz->size));
  if(thiz->size > 0) {
    thiz->size = size;
    return sizeof(StringBuilderJc)  - sizeof(thiz->value) + size;
  } else {
    //buffer referenced. 
    thiz->size = (int16)(-size);
    return -1;
  }
}



/**Returns a new string that is a substring from the content in the StringBuilder.
 * The substring begins at the specified beginIndex and extends to the character at index endIndex - 1.
 * Thus the length of the substring is endIndex-beginIndex.
 *
 * This method is a macro which calls [[substring_StringJc(...)]] from [[toString_StringBuilderJc(...)]].
 * No additional data are created in stack or heap (proper for C usage).
 * The StringBuilder (this) is designated as persistent after this call. It means that
 *
 * @param startIndex the beginning index, inclusive.
 * @param endIndex the ending index, exclusive. If -1, than the endIndex is the length of string, 
 *        This is used to support the Java-form without parameter endIndex. Java causes an excpetion in this case.
 * @throws IndexOutOfBoundsException - if the beginIndex is negative,
 * or endIndex is larger than the length of this String object, or beginIndex is larger than endIndex.
 * @javalike Lightly modified from Java, see [[sunJavadoc/java/lang/StringBuilder#substring(int, int)]]
 */
#define substring_StringBuilderJc(THIZ, BEGIN, END, _THC) substring_StringJc(toString_StringBuilderJc(&(THIZ)->base.object, _THC), BEGIN, END, _THC)


/**Returns a new string that is a substring of this string. 
 * The substring begins at the specified beginIndex and extends to the length of the given String..
 * @param BEGIN the beginning index, inclusive.
 * @throws IndexOutOfBoundsException - if the beginIndex is negative,
 * @javalike see [[sunJavadoc/java/lang/String#substring(int)]]
 */
#define substring_I_StringBuilderJc(THIZ, STR, BEGIN, _THC) substring_StringBuilderJc(THIZ, STR, BEGIN, -1, _THC)




/**Searches the text within the buffer of the StringBuilder.
 * @param str text to search referenced with a CharSeqJc
 * @param fromIndex start position to search.
 * @return position of the first occurence counted from start of this String (first position is 0). 
 *         The return value is alway ,,>= fromIndex,,, if the ,,str,, is contained in this.
 *         Return -1 if the ,,str,, is not contain in this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#indexOf(java.lang.String, int)]].
 */
//METHOD_C int indexOf_I_StringBuilderJc(const StringBuilderJc* ythis, const StringJc str, int fromIndex, struct ThreadContextFW_t* _thCxt);
#define indexOf_I_StringBuilderJc(THIZ, STR, POS, _THC) indexOf_sI_StringJc(toStringNonPersist_StringBuilderJc(&(THIZ)->base.object, _THC), STR, POS)


/**Searches the text within the buffer of the StringBuilder.
 * @param str text to search referenced with a CharSeqJc
 * @return position of the first occurence counted from start of this String (first position is 0). 
 *         The return value is alway ,,>= fromIndex,,, if the ,,str,, is contained in this.
 *         Return -1 if the ,,str,, is not contain in this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#indexOf(java.lang.String)]].
 */
#define indexOf_StringBuilderJc(YTHIS, str, _THC) indexOf_I_StringBuilderJc(YTHIS, str, 0, _THC)

/**Searches the text within the buffer of the StringBuilder.
 * @param STR text to search
 * @return position of the first occurence counted from start of this String (first position is 0). 
 *         The return value is alway ,,>= fromIndex,,, if the ,,str,, is contained in this.
 *         Return -1 if the ,,str,, is not contain in this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#indexOf(java.lang.String, int)]].
 */
//#define indexOf_s_StringBuilderJc(YTHIS, STR, POS, _THC) indexOf_I_StringBuilderJc(YTHIS, STR, 0, _THC)
#define indexOf_s_StringBuilderJc(THIZ, STR, _THC) indexOf_sI_StringJc(toStringNonPersist_StringBuilderJc(&(THIZ)->base.object, _THC), STR, 0)

/**Searches the text within the buffer of the StringBuilder.
 * @param STR text to search referenced with a 0-terminated C-string
 * @return position of the first occurence counted from start of this String (first position is 0). 
 *         The return value is alway ,,>= fromIndex,,, if the ,,str,, is contained in this.
 *         Return -1 if the ,,str,, is not contain in this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#indexOf(java.lang.String, int)]].
 */
//#define indexOf_z_StringBuilderJc(YTHIS, STR, POS, _THC) indexOf_I_StringBuilderJc(YTHIS, s0_StringJc(STR), 0, _THC)
#define indexOf_z_StringBuilderJc(THIZ, STR, _THC) indexOf_sI_StringJc(toStringNonPersist_StringBuilderJc(&(THIZ)->base.object, _THC), s0_StringJc(STR), 0)


/**Searches the text within the buffer of the StringBuilder.
 * @param STR text to search
 * @param POS start search from this position.
 * @return position of the first occurence counted from start of this String (first position is 0). 
 *         The return value is alway ,,>= fromIndex,,, if the ,,str,, is contained in this.
 *         Return -1 if the ,,str,, is not contain in this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#indexOf(java.lang.String, int)]].
 */
//#define indexOf_sI_StringBuilderJc(YTHIS, STR, POS, _THC) indexOf_I_StringBuilderJc(YTHIS, STR, POS, _THC)
#define indexOf_sI_StringBuilderJc(THIZ, STR, POS, _THC) indexOf_sI_StringJc(toStringNonPersist_StringBuilderJc(&(THIZ)->base.object, _THC), STR, POS)

/**Searches the text within the buffer of the StringBuilder.
 * @param STR text to search referenced with a 0-terminated C-string
 * @param POS start search from this position.
 * @return position of the first occurence counted from start of this String (first position is 0). 
 *         The return value is alway ,,>= fromIndex,,, if the ,,str,, is contained in this.
 *         Return -1 if the ,,str,, is not contain in this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#indexOf(java.lang.String, int)]].
 */
#define indexOf_zI_StringBuilderJc(THIZ, STR, POS, _THC) indexOf_sI_StringJc(toStringNonPersist_StringBuilderJc(&(THIZ)->base.object, _THC), s0_StringJc(STR), POS)

/**Insert a text at the given position.
 * @param pos position of char at which the text will be inserted
 * @param str Reference to the text which will be insert. It may be non-persistent.
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#insert(int, java.lang.String)]]
 *        or [[sunJavadoc/java/lang/StringBuilder#insert(int, java.lang.CharSequence)]]
 *        The Relation to CharSequence is explained in the method [[insert_sII_StringBuilderJc(...)]].
 * @macro It calls [[replace_zI_StringBuilderJc(...)]].
 */ 
#define insert_s_StringBuilderJc(YTHIS, pos, str, _THC) replace_StringBuilderJc(YTHIS,pos, 0, str, _THC)
//METHOD_C StringBuilderJc* insert_s_StringBuilderJc(StringBuilderJc* ythis, int offset, StringJc add, struct ThreadContextFW_t* _thCxt);



/**Insert a part of a text at the given position.
 * @param pos position of char at which the text will be inserted
 * @param src Reference to the text which will be insert. It may be non-persistent.
 * @param start The starting index of the subsequence to be inserted.
 * @param end The end index of the subsequence to be inserted.
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#insert(int, java.lang.CharSequence, int, int)]].
 *        A CharSequence in Java is an interface to a String or a StringBuilder. 
 *        In the CRuntimeJavalike this interface is not present. The Java2C-Translator will be generate a call
 *        to a conversion routine to StringJc, if the used instance in Java is not a String itself.
 *        A CharSequence-interface to a StringBuilder is the same as the non-persistent String
 *        returned by [[toStringNonPersist_StringBuilderJc(...)]] in the CRuntimeJavalike.
 *        It means, the buffer content is used as is.
 */ 
#define insert_sII_StringBuilderJc(thiz, pos, add, start, end, _thCxt) replace_cII_StringBuilderJc(thiz, pos, pos, add, start, end, _thCxt)



/**Inserts the content of the character array at the given position. 
 * @param pos position of char at which the text will be inserted
 * @param src Character Array which contains the text. It may be non-persistent. 
 * @param offset position within the character array from where the text are copied.
 * @param len Number of chars to copy from the array.
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#insert(int, char[], int, int)]].
 */ 
METHOD_C StringBuilderJc* insert_CYII_StringBuilderJc(StringBuilderJc* ythis, int pos, char_Y* src, int offset, int len, struct ThreadContextFW_t* _thCxt);
//#define insert_IcYII_StringBuilderJc(YTHIS, pos, charY, offset, len, _THC) replace_zI_StringBuilderJc(YTHIS,pos, 0, & (charY)->data[offset],len, _THC)

/**Inserts the content of the character array at the given position. 
 * @param pos position of char at which the text will be inserted
 * @param src Character Array which contains the text. It may be non-persistent. 
 *        In C a character array is built with a [[Jc/ObjectArrayJc]] as head and with a following ,,char[size],,-array.
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#insert(int, char[], int, int)]].
 * @macro It calls [[insert_CYII_StringBuilderJc(...)]].
 */ 
#define insert_CY_StringBuilderJc(YTHIS, pos, src, _THC) insert_CYII_StringBuilderJc(YTHIS,pos, src,0, -1, _THC)

/**Inserts the character at the given position. 
 * @param pos position of char at which the text will be inserted
 * @param src Character 
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#insert(int, char)]].
 */ 
METHOD_C StringBuilderJc* insert_C_StringBuilderJc(StringBuilderJc* ythis, int pos, char src, struct ThreadContextFW_t* _thCxt);


/**Inserts a referenced ,,char const*,, text with given number of chars at the given position. 
 * @param pos position of char at which the text will be inserted
 * @param src ,,char const*,, text
 * @param len Number of chars to insert.
 * @return this.
 * @macro It calls [[replace_zI_StringBuilderJc(...)]].
 */ 
#define insert_zI_StringBuilderJc(YTHIS, pos, src, len, _THC) replace_zI_StringBuilderJc(YTHIS, pos, pos, src, len, _THC)

/**Inserts a referenced ,,char const*,, 0-terminated text at the given position. 
 * @param pos position of char at which the text will be inserted
 * @param src ,,char const*,, text. The maximal detected length of the text is mLength__StringJc. Use it only for "literal".
 * @return this.
 * @macro It calls [[replace_zI_StringBuilderJc(...)]].
 */ 
#define insert_z_StringBuilderJc(YTHIS, pos, src, _THC) replace_zI_StringBuilderJc(YTHIS, pos, pos, src, -1, _THC)


/**Replaces the characters in a substring of this sequence with characters in the specified String. 
 * The substring begins at the specified start and extends to the character at index end - 1 
 * or to the end of the sequence if no such character exists. 
 * First the characters in the substring are removed and then the specified String is inserted 
 * at start. (This sequence will be lengthened to accommodate the specified String if necessary.) 
 *
 * It is the core method to insert, append, replace, delete with a given char* and a given lenght. All those methods are implemented with this method.
 * @param start position of the first char which will be deleted. The parameter isn't use if start == end or end == 0.
 * @param end position after the last char which will be deleted. If this parameter is 0, no characters were deleted. 
 *            If this Parameter is negative, its absolute value is the number of chars to delete. This definition is in opposite to Java 
 *            and supports the usage of macros for the other insert, append and replace-operations, if the number of chars are 0 or 1.
 *            NOTE: A twice usage of given value in macro may force twice call of the supplying method, and that may be false.
 *            See implementation of the macros using this method.
 * @param src reference of type ,,char const*,, to the text to insert, may be null, than nothing is inserted idenendent of ,,len,,. 
 *            The text is not 0-terminated. ,,\0,,-chars are copied into the buffer without extra handling. 
 * @param lenSrc Number of chars to insert. It may be 0, than nothing is inserted independent of ,,add,,.
 * @throws StringIndexOutOfBoundsException if the range doesn't match.
 * @javalike It is the ,,char const*,,-form of [[sunJavadoc/java/lang/StringBuilder#replace(int, int, java.lang.String)]].
 */
//METHOD_C StringBuilderJc* replace_zI_StringBuilderJc(StringBuilderJc* ythis, int start, int end, char const* src, int lenSrc, struct ThreadContextFW_t* _thCxt);
#define replace_zI_StringBuilderJc(thiz, start, end, src, lenSrc, _thCxt) replace_cII_StringBuilderJc(thiz, start, end, zI_CharSeqJc(src, lenSrc), 0, lenSrc, _thCxt)

/**Replaces the characters in a substring of this sequence with characters in the specified String. 
 * The substring begins at the specified start and extends to the character at index end - 1 
 * or to the end of the sequence if no such character exists. 
 * First the characters in the substring are removed and then the specified String is inserted 
 * at start. (This sequence will be lengthened to accommodate the specified String if necessary.) 
 *
 * It is the core method to insert, append, replace, delete with a given ,,CharSeqJc,,. All those methods are implemented with this method.
 * @param start position of the first char which will be deleted. The parameter isn't use if start == end or end == 0.
 * @param end position after the last char which will be deleted. If this parameter is 0, no characters were deleted. 
 *            If this Parameter is negative, its absolute value is the number of chars to delete. This definition is in opposite to Java 
 *            and supports the usage of macros for the other insert, append and replace-operations.
 *            
 * @param add reference to the text given in a CharSeqJc.
 * @throws StringIndexOutOfBoundsException if the range doesn't match.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#replace(int, int, java.lang.String)]].
 */
#define replace_StringBuilderJc(thiz, start, end, add, _thCxt) replace_cII_StringBuilderJc(thiz, start, end, add, 0, -1, _thCxt)


/**Inserts the text representation of the second int argument into this sequence.
 * The second argument is converted to a text as if by the method String.valueOf,
 * and the characters of that text are then inserted into this sequence at the indicated position.
 *
 * @param pos - the offset.
 * @param value - an int.
 * @return a reference to this object.
 * @throws StringIndexOutOfBoundsException - if the offset is invalid.
 * @see [[valueOf_I_StringJc(...)]]
 * @javalike [[sunJavadoc/java/lang/StringBuilder#insert(int, int)]].
 */
#define insert_I_StringBuilderJc(YTHIS, pos, value, _THC) insert_Ir_StringBuilderJc(YTHIS, pos, value, 10, _THC)


/**Inserts the text representation with given radix of the second int argument into this sequence.
 * The second argument is converted to a text as if by the method String.valueOf,
 * and the characters of that text are then inserted into this sequence at the indicated position.
 *
 * @param pos - the offset.
 * @param value - an int.
 * @return a reference to this object.
 * @throws StringIndexOutOfBoundsException - if the offset is invalid.
 * @see [[valueOf_I_StringJc(...)]]
 * @javalike This method is not present in Java, but see [[sunJavadoc/java/lang/Integer#toString(int, int)]].
 *           This method is used as core-method of [[insert_I_StringBuilderJc(...)]].
 */
METHOD_C StringBuilderJc* insert_Ir_StringBuilderJc(StringBuilderJc* ythis, int pos, int32 value, int radix, struct ThreadContextFW_t* _thCxt);

/**Inserts the text representation of the second int argument into this sequence.
 * The second argument is converted to a text as if by the method String.valueOf,
 * and the characters of that text are then inserted into this sequence at the indicated position.
 *
 * @param pos - the offset.
 * @param value - an int.
 * @return a reference to this object.
 * @throws StringIndexOutOfBoundsException - if the offset is invalid.
 * @see [[valueOf_I_StringJc(...)]]
 * @javalike [[sunJavadoc/java/lang/StringBuilder#insert(int, long)]].
 */
#define insert_J_StringBuilderJc(YTHIS, pos, value, _THC) insert_Jr_StringBuilderJc(YTHIS, pos, value, 10, _THC)

/**Inserts the text representation with given radix of the second int argument into this sequence.
 * The second argument is converted to a text as if by the method String.valueOf,
 * and the characters of that text are then inserted into this sequence at the indicated position.
 *
 * @param pos - the offset.
 * @param value - an int64
 * @return a reference to this object.
 * @throws StringIndexOutOfBoundsException - if the offset is invalid.
 * @see [[valueOf_I_StringJc(...)]]
 * @javalike This method is not present in Java, but see [[sunJavadoc/java/lang/Integer#toString(int, int)]].
 *           This method is used as core-method of [[insert_I_StringBuilderJc(...)]].
 */
METHOD_C StringBuilderJc* insert_Jr_StringBuilderJc(StringBuilderJc* ythis, int pos, int64 value, int radix, struct ThreadContextFW_t* _thCxt);

/**Inserts the text representation of the second int argument into this sequence.
 * The second argument is converted to a text as if by the method String.valueOf,
 * and the characters of that text are then inserted into this sequence at the indicated position.
 *
 * @param pos - the offset.
 * @param value - an int.
 * @return a reference to this object.
 * @throws StringIndexOutOfBoundsException - if the offset is invalid.
 * @see [[valueOf_I_StringJc(...)]]
 * @javalike [[sunJavadoc/java/lang/StringBuilder#insert(int, float)]].
 */
METHOD_C StringBuilderJc* insert_F_StringBuilderJc(StringBuilderJc* ythis, int offset, float value, struct ThreadContextFW_t* _thCxt);

/**Inserts the text representation of the second int argument into this sequence.
 * The second argument is converted to a text as if by the method String.valueOf,
 * and the characters of that text are then inserted into this sequence at the indicated position.
 *
 * @param pos - the offset.
 * @param value - an int.
 * @return a reference to this object.
 * @throws StringIndexOutOfBoundsException - if the offset is invalid.
 * @see [[valueOf_I_StringJc(...)]]
 * @javalike [[sunJavadoc/java/lang/StringBuilder#insert(int, double)]].
 */
METHOD_C StringBuilderJc* insert_D_StringBuilderJc(StringBuilderJc* ythis, int offset, double value, struct ThreadContextFW_t* _thCxt);

/** java:StringBuffer.append(String) */
//METHOD_C StringBuilderJc* append_z_StringBuilderJc(StringBuilderJc* ythis, const char* add, struct ThreadContextFW_t* _thCxt);
//#define append_z_StringBuilderJc(YTHIS, ADD, THREADC) append_s_StringBuilderJc((YTHIS), s0_StringJc(ADD), THREADC);

/** java:StringBuffer.append(char) */
//METHOD_C StringBuilderJc* append_C_StringBuilderJc(StringBuilderJc* ythis, char add, struct ThreadContextFW_t* _thCxt);

/**Appends the given char at the end.
 * @param char The char to append.
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#append(char)]], but the char is represented in 1 byte, like usual in C.
 */ 
#define append_C_StringBuilderJc(YTHIS, char, _THC) insert_C_StringBuilderJc(YTHIS, (YTHIS)->_count & mLength__StringJc, char, _THC)
#define append_C_StringBufferJc append_C_StringBuilderJc


/**Appends the text reprentation of the given integer value at the end.
 * @param value to append in its text format.
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#append(int)]].
 * @macro using [[insert_Ir_StringBuilderJc(...)]]
 */ 
#define append_I_StringBuilderJc(YTHIS, value, _THC) insert_Ir_StringBuilderJc(YTHIS, (YTHIS)->_count & mLength__StringJc, value, 10, _THC)
#define append_I_StringBufferJc append_I_StringBuilderJc

/**Appends the text reprentation of the given float value at the end.
 * @param value to append in its text format.
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#append(float)]].
 * @macro using [[insert_F_StringBuilderJc(...)]]
 */ 
#define append_F_StringBuilderJc(YTHIS, value, _THC) insert_F_StringBuilderJc(YTHIS,(YTHIS)->_count & mLength__StringJc, value, _THC)
#define append_F_StringBufferJc append_F_StringBuilderJc

/**Appends the text reprentation of the given double value at the end.
 * @param value to append in its text format.
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#append(float)]].
 * @macro using [[insert_D_StringBuilderJc(...)]]
 */ 
#define append_D_StringBuilderJc(YTHIS, value, _THC) insert_D_StringBuilderJc(YTHIS,(YTHIS)->_count & mLength__StringJc, value, _THC)
#define append_D_StringBufferJc append_D_StringBuilderJc


/**Appends the text reprentation of the given long value at the end.
 * @param value to append in its text format.
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#append(float)]].
 * @macro using [[insert_Jr_StringBuilderJc(...)]]
 */ 
#define append_J_StringBuilderJc(YTHIS, VALUE, _THC) insert_Jr_StringBuilderJc(YTHIS, (YTHIS)->_count & mLength__StringJc, VALUE, 10, _THC)
#define append_J_StringBufferJc append_J_StringBuilderJc

/**Removes the characters in a substring of this sequence.
 * The substring begins at the specified start and extends to the character
 * at index end - 1 or to the end of the sequence if no such character exists.
 * If start is equal to end, no changes are made.
 *
 * @params start The beginning index, inclusive.
 * @params end The ending index, exclusive.
 * @return this.
 * @throws StringIndexOutOfBoundsException if start is negative, greater than length(),
 *           or greater than end.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#delete(int, int)]].
 *
 */
METHOD_C StringBuilderJc* delete_StringBuilderJc(StringBuilderJc* ythis, int start, int end, struct ThreadContextFW_t* _thCxt);


/**Replaces single chars in the buffer.
 * @param oldChar The char which was to replace at any occurence.
 * @param newChar Char to set.
 * @return this.
 * @javalike: Java doesn't know a simple method to replace chars in a StringBuilder. 
 *            But it may necessary.
 *
 */
METHOD_C StringBuilderJc* replace_CC_StringBuilderJc(StringBuilderJc* ythis, char oldChar, char newChar);


/**Returns the String which represents the content of the StringBuffer.
 * If a dynamic memory is not present, this method freezes the StringBuilder by invoking [[toStringMarkPersist_StringBuilderJc(...)]].
 * That is because no other memory is given.
 * 
 * If a dynamic memory management is available, this method copies the String in an extra buffer (like in Java)
 * if the StringBuilder is not marked with TODO
 *
 * Note: The calling instance (this) should be given as ObjectJc-pointer. 
 * That is because this method is defined for Object and it is overwritten only.
 * But the instance has to be a StringBuilderJc.
 *
 * @return a StringJc which is persistent.
 * @javalike [[javadoc/java/lang/StringBuilder#toString()]], but Java returns 
 *           an persistent String in a new allocated buffer anytime.
 * @see [[toStringPersist_StringBuilderJc()]] and [[toStringNonPersist_StringBuilderJc()]].
 */ ///
#define toString_StringBuilderJc(YTHIS, _THC) toStringMarkPersist_StringBuilderJc(YTHIS, _THC)
#define toString_StringBufferJc toString_StringBuilderJc



/**Marks the StringBuilder as persistent (freezed) and returns the referenced String in this builder.
 * It sets the [[mode_StringBuilderJc]] with the bit [[_mStringBuilt_StringBuilderJc]].
 * A changing of content after call of toString will be caused an IllegalStateException: "Buffer was used in StringJc".
 * The StringBuilderJc-instance can be released with [[releaseStringBuilt_StringBuilderJc(...)]]. 
 * Then all referenced Strings should not be used no more.
 * This method should used especially if a String is assembled in a StringBuilder, this String is referenced, 
 * and the StringBuilder itself is not referenced. Then nobody can change the content.
 *
 * @return A StringJc instance which refers the buffer of the StringBuilder. 
 *         It is designated as persistent only if the StringBuilderJc-instance is designated
 *         as an instance only for concatenating a String, 
 *         see [[StringBuilder.setStringConcatBuffer_StringBuilderJc(...)]].
 *         Otherwise it is dedignated as non-persistent.
 * @javalike [[javadoc/java/lang/StringBuilder#toString()]], but Java returns 
 *           an persistent String in a new allocated buffer anytime.
 * @see [[toStringPersist_StringBuilderJc()]] and [[toStringNonPersist_StringBuilderJc()]].
 */
#define toStringMarkPersist_StringBuilderJc(YTHIS, _THC) ( ((StringBuilderJc*)(YTHIS))->_mode |= _mStringBuilt_StringBuilderJc, toStringNonPersist_StringBuilderJc(YTHIS, _THC))
//#define toStringMarkPersist_StringBuilderJc(YTHIS, _THC) ( ((StringBuilderJc*)(YTHIS))->_mode |= _mStringBuilt_StringBuilderJc, toStringNonPersist_StringBuilderJc(YTHIS, _THC))

#define toString_StringJc(STRING) (STRING)

/**Returns the String which represents the content of the StringBuffer.
 *
 * The StringBuffer will not be designated as freezed. 
 *
 * @return A StringJc instance which refers the buffer of the StringBuilder. 
 *         It is designated as non-persistent. 
 *         If the text in this is changed, the String will be changed also.
 * @javalike: It is non java-like, but a special form of [[sunJavadoc/java/lang/StringBuilder#toString()]],
 *            which is effective in C. It have the same behaviour like Java
 *            if the String is used only immediately without storing its reference.
 */ 
METHOD_C StringJc toStringNonPersist_StringBuilderJc(ObjectJc* othis, struct ThreadContextFW_t* _thCxt);


/**Returns the String which represents the content of the StringBuffer.
 * If the StringBuilder is designated only to use for concatenation of a String,
 * it is persistent itself. Than the returned String referes the StringBuffer.
 * Otherwise a new Instance for the text is created dynamically and its refference is returned.
 *
 * The StringBuilder is designated only to use for concatenation if the method 
 * [[setStringConcatBuffer_StringBuilderJc()]] was called. 
 * Than the String must not located in Stack or ThreadContext, 
 * but it should be allocated dynamically too.
 * 
 * 
 * @return A StringJc instance which refers the buffer of the StringBuilder. 
 *         It is designated as non-persistent. 
 *         If the text in this is changed, the String will be changed also.
 * @javalike: It is the java-adequate behaviour of [[sunJavadoc/java/lang/StringBuilder#toString()]],
 */ 
METHOD_C StringJc toStringPersist_StringBuilderJc(ObjectJc* othis, struct ThreadContextFW_t* _thCxt);


/**Copies the content of buffer in the Thread-Context-Buffer and refers it with the returned instance.
 *
 * @return A StringJc instance which referes a text in the Thread Context. It is designated as non-persistent
 *         and with the ''threadContext''-designation (bits ,,mThreadContext__StringJc,,).
 */ 
METHOD_C StringJc toStringInThreadCxt_StringBuilderJc(StringBuilderJc* othis, struct ThreadContextFW_t* _thCxt);






/**cleans the Rest of content in the buffer after the valid chars.
 * This method is enhanced in comparision to Java. It consideres a usage of StringBuilderJc for text fields in structures.
 * The content in the structur's fields should be cleanly. The naming of the method is contrastable 
 * to the Java method [[sunJavadoc/java/lang/StringBuilder#trimToSize()]].
 */
METHOD_C void cleanToSize_StringBuilderJc(StringBuilderJc* ythis);



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)

/**The C++-Variante. It is comfortable to use C++ because some methods and operators are argument-sensitive (overloaded),
 * and the code is better readable.
 * This class defines only methods, and the methods are not virutal. It followes the java convention: The class java.lang.String is final.
 * Thats why a applicable side action exists: The memory layout of StringJcpp is identical with the memory layout of StringJc.
 * So conversions may be able without any problems. Using static_cast<StringJc*>
 *
 */
class  StringBuilderJcpp: public ObjectifcBaseJcpp, public StringBuilderJc
{ public:

  static StringBuilderJcpp* threadBuffer(struct ThreadContextFW_t* _thCxt);
  
  StringBuilderJcpp(){ STACKTRC_ENTRY("StringBuilderJcpp::StringBuilderJcpp()"); init_ObjectJc(&base.object, sizeof(StringBuilderJc), 0); ctorO_StringBuilderJc(&this->base.object, _thCxt); }

  StringBuilderJcpp(char* buffer, int len){ STACKTRC_ENTRY("StringBuilderJcpp::StringBuilderJcpp(char*, len)"); init_ObjectJc(&base.object, sizeof(StringBuilderJc), 0); ctorO_zI_StringBuilderJc(&this->base.object, buffer, len, _thCxt); }

  StringBuilderJcpp(bool immediately, int addSize){ STACKTRC_ENTRY("StringBuilderJcpp::StringBuilderJcpp(addSize)"); init_ObjectJc(&base.object, sizeof(StringBuilderJc) + addSize, 0); ctorO_StringBuilderJc(&this->base.object, _thCxt); }

  StringBuilderJcpp(ObjectJc* othis){ init_ObjectJc(&base.object, sizeof(StringBuilderJc), 0); ctorO_StringBuilderJc(othis, null); }
  
  StringBuilderJcpp& operator()(CharSeqJc src)
  { STACKTRC_ENTRY("StringBuilderJcpp(StringJc)");
    setLength_StringBuilderJc(this, 0, _thCxt);
    append_s_StringBuilderJc(this, src, _thCxt);
    return *this;
  }
  
   char charAt(int index){ return charAt_StringBuilderJc(this, index, null); }

   void setCharAt(int index, char ch){ setCharAt_StringBuilderJc(this, index, ch, null); }

   StringBuilderJcpp* append(CharSeqJc str){ append_s_StringBuilderJc(this, str, null); return this; }

   StringBuilderJcpp& operator=(StringJc str){ setLength_StringBuilderJc(this, 0, null); append_s_StringBuilderJc(this, str, null); return *this; }

  /*volatile*/ StringBuilderJcpp& operator+(CharSeqJc str) /*volatile*/{ append_s_StringBuilderJc((StringBuilderJc*)(static_cast<StringBuilderJc /*volatile*/*>(this)), str, null); return *this; }
  /*volatile*/ StringBuilderJcpp& operator+=(CharSeqJc str) /*volatile*/{ append_s_StringBuilderJc((StringBuilderJc*)(static_cast<StringBuilderJc /*volatile*/*>(this)), str, null); return *this; }
  
   StringBuilderJcpp* append(const char* str){append_z_StringBuilderJc(this, str, null); return this; }

   StringBuilderJcpp& operator=(const char* str){ setLength_StringBuilderJc(this, 0, null); append_z_StringBuilderJc(this, str, null); return *this; }

  /*volatile*/ StringBuilderJcpp& operator+(const char* str) /*volatile*/{append_z_StringBuilderJc((StringBuilderJc*)(static_cast<StringBuilderJc /*volatile*/*>(this)), str, null); return *this; }
  
   StringBuilderJcpp& operator<<(const char* str){append_z_StringBuilderJc(this, str, null); return *this; }

   StringBuilderJcpp* append(int val){ append_I_StringBuilderJc(this, val, null); return this; }

  /*volatile*/ StringBuilderJcpp& operator+(int val) /*volatile*/{append_I_StringBuilderJc((StringBuilderJc*)(static_cast<StringBuilderJc /*volatile*/*>(this)), val, null); return *this; }
  
  StringBuilderJcpp& insert(int pos, char cc){ insert_C_StringBuilderJc(this, pos, cc, null); return *this; }
  
  void setLength(int newLength){ setLength_StringBuilderJc(this, newLength, null); }
  
  /**sets the length, used especially to clear. */
  StringBuilderJcpp& operator()(int newLength){ setLength_StringBuilderJc(this, newLength, null); return *this;}

  StringBuilderJcpp& clear(){ clear_StringBuilderJc(this); return *this; }
  

  StringBuilderJcpp* delete_(int start, int end){ delete_StringBuilderJc(this, start, end, null); return this; }

  void cleanToSize(){ cleanToSize_StringBuilderJc(this); }

  StringJc toString(){ return toString_StringBuilderJc(&this->base.object, null); }  

  StringJc toStringInThreadCxt(){ return toStringInThreadCxt_StringBuilderJc(this, null); }  

  StringJc toStringNonPersist(){ return toStringNonPersist_StringBuilderJc(&this->base.object, null); }  

  StringJc toStringPersist(){ return toStringPersist_StringBuilderJc(&this->base.object, null); }  

  operator StringJc() /*volatile*/{ return toString_StringBuilderJc(&this->base.object, null); }

  StringBuilderJcpp& replace(char oldChar, char newChar)
  { STACKTRC_ENTRY("StringBuilderJcpp::replace(char, char)"); 
    replace_u_StringJc(toStringNonPersist_StringBuilderJc(&this->base.object, _thCxt)
                      , oldChar, newChar, this, _thCxt); 
    return *this;
  }

  ObjectJc* toObjectJc(){ return &this->base.object; }
};


class StringBuilder240Jcpp: public StringBuilderJcpp
{
  char _buffer[236];
  public: StringBuilder240Jcpp(bool stack): StringBuilderJcpp(true, 236)
  { //STACKTRC_ENTRY("StringBuilder240Jcpp::StringBuilder240Jcpp"); init_ObjectJc(&base.object, sizeof(StringBuilderJc) + 236, 0); ctorO_StringBuilderJc(&this->base.object, _thCxt); 
    if(stack){ _mode |= _mStack_StringBuilderJc; }
  }
};

#define INSTACK_StringBuilderJcpp 

//error compiler 'operator +' must have at least one formal parameter of class type:
//  StringBuilderJcpp& operator+(char const*, int);


/**Do not use, because it isn't settled, how to allocate without responsibility of the user
 * but also without garbage collection.
 * Therefore this solution isn't able to use.
 */
//cc1 StringBuilderJcpp& operator+(StringJc src, StringJc src2);


/**Do not use, because it isn't settled, how to allocate without responsibility of the user
 * but also without garbage collection.
 * Therefore this solution isn't able to use.
 */
StringBuilderJcpp* new_StringBuilderJcpp(int size);



StringBuilderJcpp* threadBuffer_StringBuilderJcpp(struct ThreadContextFW_t* _thCxt);

StringBuilderJcpp* threadBuffer_s_StringBuilderJcpp(CharSeqJc src, struct ThreadContextFW_t* _thCxt);


#endif //__CPLUSPLUSJcpp


#endif //__StringJc_h__
