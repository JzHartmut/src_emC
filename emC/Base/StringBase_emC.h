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
 * @content definition of A StringJc-struct, which contains the character pointer and its length,
 *   and basicly access methods.
 *   The struct defined well to return per value only in registers.
 *   Therefore an adaption to several compilers and platforms is able to done if necesarry.
 * @author Hartmut Schorrig
 * @created 2008-12-07, from other sources (Objectjc.h), the concept is from 2004
 * @version 0.83
 * @changes
 * 2010-02-01 Hartmut new: _CHARS_StringJc(REF) to access the character pointer for internal access
 *************************************************************************************************/
#ifndef HGUARD_applstdef_emC
  /**This file should be included in the applstdef_emC.h. 
   * If this file is directly included, it needs the applstdef_emC.h. But the __guard__ 
   * should not be set firstly to include the MemC.h in the given order in applstddef.h
   */
  #include <applstdef_emC.h>
#endif
//The following include guard prevent twice include especially if app?stdefJc.h includes this file already.
#ifndef HGUARD_emC_Base_StringBase_emC
#define HGUARD_emC_Base_StringBase_emC

#ifndef DEFINED_StringJc_emC
typedef struct StringJc_T {
  union { char const* str; } addr;
  int val;
} StringJc;
#endif

#ifndef mLength_StringJc
#define mLength_StringJc 0x00003fff
#endif


/**Counts the number of chars till a \0-char. 
 * In opposite to the C-standard strlen, this routine may not crash on undefined strings 
 * because the search length is limited by the application to a  convenient value.
 * The strlen-Function searches to the end of memory and crashs on that end with an memory access exception
 * if the memory is filled with non-zero bytes till the end.
 * @param text The string where the length till \0 is to detect.
 * @param maxnrofChars maximal number of chars to detect. This parameter may be set by a suitable value,
 *        for example to the maximal size of a buffer. The possibility of a memory fault access 
 *        is some more less than as in comparision with the strlen-call without any limits.
 * @return the number of chars till \0 or maxNrofChars. 
 */
extern_C int strnlen_emC ( char const* text, int maxNrofChars);



/**Copies the src to the limited dst with preventing overflow and possible guaranteed 0-termination.
 * or copy a given number of characters without 0-termination.
 * 
 * This is a alternate implementation of strncpy (it does not guaranteed a 0-termination)
 * and a alternate implementation of strlcpy from BSD (it does count the maybe unused length of src).
 *
 * It guarantees both, 0-termination if necessary and strncpy-functionality without 0-termination.
 * The routine returns the number of chars copied without the ending 0.
 * The rest of the buffer remains unchanged. (no squandering of calculation time for unsued things).
 * It means, if it contains invalid character, they remain invalid. But the C-String from dst has guaranteed its end-0.
 * If the buffer should be clean (to hide old informations), use memset(dst, 0, size).
 * ** If the length of src is >=size, then (size-1) characters are copied and a end-0 is appended.
 * The routine returns size itself. It is the number of chars copied with the end-0.
 * With comparison return value >= size the information about truncation is given (src is truncated in dst).
 *
 * 
 *
 * To concatenate Strings one can write:
 * char buffer[20] = {0};
 * char* dst = buffer;
 * int zdst = sizeof(buffer) -1;  //left place for one \0
 * int pos = 0;
 * pos += strpncpy_emC(dst, pos, zdst, src1, -1);
 * //etc.
 * dst[pos] = 0;  //a 0 termination is always possible if intended, but can be omitted if not necessary
 */
extern_C int strpncpy_emC(char* dst, int posDst, int zDst, char const* src, int zSrc);





/**strcpy
 * @param dst A buffer to hold either a 0-terminated C-string with at least sizeDst free bytes inclusive end-0
 *    or a destination for a non-0-terminated String.
 * @param src C-String maybe 0-terminiated
 * @param sizeOrNegLength if positive then number of use-able bytes from dst inclusive terminating \0.
 *        if negative, then the maximal or given number of chars to copy maybe without end-0 
 * * If sizeOrNegLength is positive, it should be the size of dst inclusively the end-0.
 * * If sizeOrNegLength is negative (-length), then the 0-termination of dst is not guaranteed:
 * ** If the length of src is >= -length then -length characters of src are copied, without ending 0.
 * This mode can be used to replace some character in a longer String in dst with given -length of src 
 * It is the same behavior like strncpy, only the number of chars should be given negative. 
 * The routine returns -length (the number of copied chars).
 * ** If the length of src till its end-0 is < -length, the end-0 is copied too, but the rest till -length is not filled with 0.
 * It is the same with remaining/hidden content. 
 * The behavior is similar but not equal strncpy, because strncpy fills the rest till length with 0.   
 * @return The number of characters copied without ending \0 .
 *   The user can check: if(returnedvalue >= sizeDst){ //set flag it is truncated ...
 *   The return value is anytime a value between 0 and <=sizeDst, never <0 and never > sizeDst.
 *   The return value is the strlen(dst) if it is < sizeDst.
 *
 */
extern_C int strcpy_emC ( char* dst, char const* src, int sizeOrNegLength);


/**Copies a defined Number of characters to a buffer. It is adequate strncpy(src, dst, length) 
 * but it fills only one \0 if src is shorter than length. 
 * It does not write a terminating \0 if src length >= the given length argument.
 *
 * @param dst A buffer to hold either a 0-terminated C-string with at least sizeDst free bytes inclusive end-0
 *    or a destination for a non-0-terminated String.
 * @param src C-String maybe 0-terminiated
 * @param length positive number of use-able bytes from dst inclusive terminating \0.
 * @return The number of characters copied without ending \0 .
 *   The user can check: if(returnedvalue >= sizeDst){ //set flag it is truncated ...
 *   The return value is anytime a value between 0 and <=sizeDst, never <0 and never > sizeDst.
 *   The return value is the strlen(dst) if it is < sizeDst.
 */
INLINE_emC int strncpy_emC ( char* dst, char const* src, int length){ return strcpy_emC(dst, src, -length); }


/**Searches a character inside a given string with terminated length.
 * NOTE: The standard-C doesn't contain such simple methods. strchr fails if the text isn't terminated with 0.
 * It is similar strnchr, but with other return value.
 * @param text do not need to be 0-terminated. A character after 0 is detect too depending on zText
 * @param zText if <0 then a 0-terminated search is done, whereby -zText is the maximal checked length.
 *     -1 checks only the first char. -0x7fff searches in 32767 chars if a '\0' was not found.
 *     Note: The length should be determined in any case to prevent memory access errors on not terminated char arrays.
 *     if zText >=0 this is the real number of chars to test independing of an 0-character.
 * @param cc char to search. 0 it possible (searches the first '\0').
 * @return position of the first occurence of cc in text, or -1 if not found. 
 */
int searchChar_emC ( char const* text, int zText, char cc);


/**Searches any character from the given any arg inside a given string with terminated length.
 * NOTE: The standard-C doesn't contain such simple methods.
 * @param text do not need to be 0-terminated. A character after 0 is detect too depending on zText
 * @param zText if <0 then a 0-terminated search is done, whereby -zText is the maximal checked length.
 *     -1 checks only the first char. -0x7fff searches in 32767 chars if a '\0' was not found.
 *     Note: The length should be determined in any case to prevent memory access errors on not terminated char arrays.
 *     if zText >=0 this is the real number of chars to test independing of an 0-character.
 * @param any a string containing chars to search.
 * @return position of the first occurence of any char from any in text, or -1 if not found. 
 */
int searchAnyChar_emC ( char const* text, int zText, char const* any);


/**Compares two strings till a given maximum of chars or till zero termination.
 * @arg maxNrofChars max length which is tested. For example size of a buffer. 
 *     If non zero terminated strings should be compare, it is the max expected length of both strings.
 *     Note: If one String is longer, till zero termination, it is not detected here.
 *     In this case an expected zero termination should be tested additonally outside of this routine.
 * @return ==0 if both strings are equal till maxNrofChars 
 *    or both have a '\0' on the same position and all characters before are equal.
 *    >0 if text2 > text1 (longer or character code higher) whereby the value is the position of the first difference.
 *    <0 if text1 > text2 (longer or character code higher) whereby the absolute value is the position of the first difference.
 */
extern_CCpp int strncmp_emC ( char const* const text1, char const* const text2, int maxNrofChars);


/**Searches a character inside a given string from end.
 * NOTE: The standard-C doesn't contain such simple methods. 
 * @param text do not need to be 0-terminated if fromIx is >=0, because it is searched from end. 
 * @param fromIx first character index in text to check.  
 *   if <0 then the 0-terminated text is searched from end + ix, it means -1: search from last char.
 * @param cc char to search.
 */
extern_CCpp int searchCharBack_emC ( char const* const text, char cc, int fromIx);


/**Searches a character inside a given string with terminated length.
* NOTE: The standard-C doesn't contain such simple methods. strchr fails if the text isn't terminated with 0.
* But it is defined in divers Linux distributions. use #define strnchr strnchr_emC in the compl_adaption.h to offer it if not existent.
*/
inline char const* strnchr_emC ( char const* text, int cc, int maxNrofChars) {
  int pos = searchChar_emC(text, maxNrofChars, (char)cc);
  return pos == -1 ? null : text + pos;
}



/**Searches a String inside a given string with terminated length.
 * NOTE: The standard-C doesn't contain such simple methods. strstr fails if the text isn't terminated with 0.
 */
extern_C int searchString_emC ( char const* text, int maxNrofChars, char const* ss, int zs);

/**Returns the number of chars which are whitespaces starting from text.
 * Whitespaces are all chars with code <=0x20. It are all control chars from the ASCII and the space. 
 */
extern_C int skipWhitespaces_emC ( char const* text, int maxNrofChars);


/**Returns the number of chars which note whitespaces starting from end of text.
 * Whitespaces from begin or inside the text are not regarded.
 * Whitespaces are all chars with code <=0x20. It are all control chars from the ASCII and the space. 
 * @return length of text without right-bounded white-spaces.
 */
extern_C int trimRightWhitespaces_emC ( char const* text, int maxNrofChars);


/**Parses a given String and convert it to the integer number.
 * The String may start with a negativ sign ('-') and should contain digits after them.
 * The digits for radix > 10 where built by the numbers 'A'..'Z' respectively 'a'..'z',
 * known as hexa numbers A..F or a..f. 
 * @param src The String, non 0-terminated, see ,,size,,.
 * @param size The number of chars of the String.
 * @param radix The radix of the number, typical 2, 10 or 16, max 36.
 * @param parsedChars number of chars which is used to parse the integer. The pointer may be null if not necessary.
 * @return the Number.
 * @throws never. All possible digits where scanned, the rest of non-scanable digits are returned.
 *  At example the String contains "-123.45" it returns -123, and the retSize is 3.
 */
extern_C int parseIntRadix_emC ( const char* src, int size, int radix, int* parsedChars, char const* addChars);

extern_C float parseFloat_emC ( const char* src, int size, int* parsedChars);

extern_C double parseDouble_emC ( const char* src, int size, int* parsedChars);

extern_C int encode_StringCompactor_emC(uint8* const dst, int zdst, char const* const src, int zsrc);

extern_C int decode_StringCompactor_emC(char* bu, int zbu, uint8 const* txt, int zsrc);


/**Converts the value into a String representation.
* @param zBuffer size of the buffer. If the string representation will be longer, only the left character are written.
* @param radix of the conversion, typically 10 or 16 for hexa conversion. A value between 1..16.
* @param minNrofCharsAndNegative If this value is negativ, and the value is negativ, a ,,-,, is written first and the value is negated before conversion.
*                                The absolute value is the minimum of numbers, If the number will be less, left 0 are written.
* @return number of written chars. A 0 after the string won't be written!
If the return value is equal zBuffer, the string representation may be incomplete because clipping of following chars.
*/
extern_C int toString_int32_emC(char* buffer, int zBuffer, int32 value, int radix, int minNrofCharsAndNegative);





/*@CLASS_C ByteStringJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**CLASS_C_Description: The type ByteStringJc is the same as ,,struct OS_PtrValue,, 
 * from the OSAL level (Operation System Adaption Layer). 
 * That type is designed to represent a structure, which is returned by value in 2 registers.
 * Because it is defined in the compiler- and system-specific headerfile ,,os_types_def.h,,,
 * it can and should be adapted to the target system conditions independently of user programming.
 *
 * Because the feature of representation of a struct in registers, the usage of return per value 
 * and typically call per value for the type ByteStringJc is possible and proper.
 *
 * The ByteStringJc referes to a String which has byte-characters. The encoding is determined
 * by the using software.
 */
#define __ByteStringJc__ ByteStringJc  //define only for documentaion present, don't use this definition.

#define ByteStringJc AddrVal_emC

#define null_ByteStringJc null_AddrVal_emC

#define length_ByteStringJc(STR) (VAL_AddrVal_emC(STR) & mLength_StringJc)

#define data_ByteStringJc(STR) ADDR_AddrVal_emC(STR, int8)

#define byteAt_ByteStringJc(STR, pos) (ADDR_AddrVal_emC(STR, int8)[pos])




/*@DEFINE_C StringJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**StringJc: The type ,,StringJc,, refers 
 * * either a ,,char const*,, with a given length. This is adequate to java.lang.String
 * * or it can refer an [[!ObjectJc.html#class_ObjectJc]] instance which implements 
 * the CharSeqJc virtual methods. Then it is adequat to java.lang.CharSequence
 * * or it referes a [[class_StringBuilderJc]] instance, which is adequate to a java.lang.StringBuilder
 * which implements a java.lang.CharSequence.
 *
 * All three forms are joined in C language with this StringJc struct 
 * to support a simple and fast access to Strings. The length element decides on Runtime
 * about the type of the reference:
 *
 * The value is (based on [[CRJS:_mLength_StringJc]] == 0x3fff for a 32-bit-system):
 * * 0x0000 ... 0x2fff: either the same how defined in [[class_StringJc]], then it contains the length of the String
 * * 0x3000 ... 0x3ffd: In this case the bits with mask 0xfff contains the index to the method table of CharSeqJc inside the whole method table of the ObjectJc
 * * 0x3ffe: or it is designated with the bits to designate the CharSeqJc as StringBuilderJc_s
 * * 0x3fff: or it is designated with the bits to designate the CharSeqJc as any instance of ObjectJc.
 * * 0x4000 mNonPersists__StringJc: Bit for non persist String
 *
 * The values are .
 *
 * 
 * The memory layout of StringJc is defined by ,,OS_PtrValue,, in the ,,compl_adaption.h,, file. 
 * That type is designed to represent a structure, which is returned by value in 2 registers.
 * Because it is defined in the compiler- and system-specific headerfile ,,os_types_def.h,,,
 * it can and should be adapted to the target system conditions independently of user programming.
 *
 * Because the feature of representation of a struct in registers, the usage of return per value 
 * and typically call per value for the type StringJc is possible and proper.
 *
 * A StringJc consists of a reference ,,char const*,, and a ,,int val,, value, which contains the number of characters.
 * The value can contain some mask bits, and also an index for enhanced referencing. 
 * Therefore the value is mask with some special bit definitions:
 * * mLength_StringJc: mask for bits for length. The bits are arranged in the low-bits always. 
 * * mNonPersists__StringJc: 
 * This bit definitions are contained  in the include-file ,,fw_Platform_conventions,,, which is included here. 
 * The user can fine-adjust the maximum of length for Strings there.
 *
 * Some methods are ''basicly''. This methods and ,,define,, are defined in a ''framework''-context and not in the ''CRuntimeJavallike''-Library.
 * This elements are defined in this headerfile and they are named as ,,Fw-String,,-class for UML-representation of C-Code.
 * The basicly elements are able to use independend of all other features of the CRuntimeJavalike, they are independend simple C constructs 
 * with no other dependencies. Therefore there are able to use in a operation system adaption layer or in a operation system implementation too.
 *
 * A character string itself, representated in a char-array is named as ''text'' in the description parts of this headerfile. 
 * A ''text-literal'' is a construct written in C like ,,"textliteral",,. 
 * It is stored in machine code commonly in a const memory area and can be referenced by a ,,char const*,,. 
 * Where a instance of ,,StringJc,, references such an text. The type ,,StringJc,, consists of the pointer to the text, its length
 * and some other bits, especially the ''persistent''-bit.
 *
 * The headerfile ,,emC/Base/String_emC.h,, defines the type and some basicly functionalities
 * to use a StringJc-instance in a low independent level to refer a text..
 * This headerfile against that defines the typically String functionality,
 * which followes the [[sunJavadoc/java/lang/String]] class-functinality. 
 * But some enhancements are given, because the string processing in fast real time embedded systems
 * may work without dynamically memory too.
 *
 * Notation hint: The notation ,,char const*,, is the same as ,,const char*,,, but it expresses more stronly, that it is a const-pointer.
 * 
 */ 

/**The memory layout of CharSeqJc is the same like StringJc. 
 * A StringJc is a CharSeqJc (is-a, inheritance).
 * But a CharSeqJc can be a reference to any instance which implements the methods of CharSeqJc.
 * In this header only the formalism of CharSeqJc are defined. To work with CharSeqJc in full capability,
 * include <Jc/StringJc.h> and compile Jc/StringJc.c.
 */
#define CharSeqJc StringJc




/**Definition of masks and const for val element in StringJc and CharSeqJc: */
#ifndef DEF_CharSeqJcCapabilities
  #define mVtbl_CharSeqJc 0
  #define kIsCharSeqJc_CharSeqJc 0
  #define kMaxNrofChars_StringJc (mLength_StringJc -2)
  #define mIsCharSeqJcVtbl_CharSeqJc 0
#else   

  /**Mask bits for position of method table of CharSequJc.
  * If mLength_StringJc == 0x3fff (default for 32 bit system), the mask is 0x0fff
  * The val info in a CharSeqJc will be 0x3000..0x3fff..
  * See [[kMaxLength_StringJc]], .
  */
  #define mVtbl_CharSeqJc (mLength_StringJc >>2)

  /**Designation of the String as CharSeqJc without a method table offset. In this case the reference refers a CharSeqJc and the length
  * should be gotten by invocation of [[length_CharSeqJc(...)]].
  * If mLength is defined with 0x3fff the value is 0x03ffe. mLength is defined os- and platform-depended in os_types_def.h
  */
  #define kIsCharSeqJc_CharSeqJc (mLength_StringJc -2)

  /**The limit for the length of a StringJc. It is derived from the platform-specific definition of ,,mLength_StringJc,,
  * contained in the platform-specific ,,compl_adaption.h,,.
  * If the ,,mLength_StringJc,, is defined with ,,0x3fff,, then this value is ,,0x2fff,,.
  *
  * If a ,,StringJc,, is designated with this value for the ,,mLength_StringJc,, bits, then the length should be gotten
  * on demand. The [[length_StringJc(...)]] regards that.
  */
  #define kMaxNrofChars_StringJc ((mLength_StringJc & ~mVtbl_CharSeqJc)-1)

  /**Designation of the String as CharSeqJc maybe with a method table offset. In this case the reference refers a CharSeqJc and the length
  * should be gotten by invocation of [[length_CharSeqJc(...)]].
  * If mLength is defined with 0x3fff the value is 0x3000. mLength is defined os- and platform-depended in os_types_def.h
  */
  #define mIsCharSeqJcVtbl_CharSeqJc (mLength_StringJc & ~mVtbl_CharSeqJc)
#endif



/**Returns true if the StringJc contains null. The user should use this macro instead straigtly using of the basicly definitions,
 * because the definition of OS_PtrValue and therefore the definition of StringJc is os-specific. 
 * @param STR StringJc-instance to test. The macro uses the instance directly.
 * @return true only if the text-reference is ,,null,,. false if it is an empty or non-empty text.
 */
#define isNull_StringJc(STR) ((STR).addr.str ==null)



/**Designation of the String as 0-terminated. In this case the length is calculated
 * using [[strnlen_emC(...)]] before usage.
 * If mLength is defined with 0x3fff the value is 0x03fff. 
 * mLength can be special defined in applstdef_emC.h
 */
#define kIs_0_terminated_StringJc (mLength_StringJc)

/**Designation of the String as StringBuilderJc_s-instance. 
 * In this case the reference refers a StringBuilderJc_s and the length
 * should be gotten by invocation of length_StringBuilderJc(ref)
 * If mLength is defined with 0x3fff the value is 0x03ffe. 
 * mLength can be special defined in applstdef_emC.h
 */
#define kIsStringBuilder_CharSeqJc (mLength_StringJc -1)

/**If this Bit is set, the StringJc referenced the whole string of a StringBufferJc to concat strings.
 * If mLength is defined with 0x3fff the value is 0x04000. mLength is defined os- and platform-depended in os_types_def.h
 */
#define mNonPersists__StringJc       (mLength_StringJc +1)

/**If this Bit is set, the StringJc references a buffer in the thread context..
 * If mLength is defined with 0x3fff the value is 0x08000. mLength is defined os- and platform-depended in os_types_def.h
 */
#define mThreadContext__StringJc     ((mNonPersists__StringJc)<<1)



//Note: INIZ_StringJc are now part of emC/Base/types_def_common.h because simple non 0-terminated Strings may be used overall.

//tag::z_StringJc[]
/**Set a StringJc instance with the reference to the given constant text.
  * This method is usefull to initialize new instances espacially inside the stack.
  * @param src Any char-array. The src need not be 0-terminated, a 0-char is handled like a normal char.
  * @param LEN Number of valid chars and persistent bit.. 
  *            The number of chars should be less than ,,mLength_StringJc,, but it is not tested here.
  *            The Bit ,,mNonPersists__StringJc,, may be set. The user is responsible to the persistence.
  * @return void, don't use inside an expression.
  */
INLINE_emC void set_s0len_StringJc (StringJc* thiz, char const* src, int len) {
  thiz->addr.str = src; thiz->val = len;
}


/**Macro form. THIZ is the instance, not the reference. 
  * The up till now value inside THIZ is not respected. This method is usefull to initialize new instances
  * espacially inside the stack.
  * @param THIZ The destination instance. The instance is used directly (it is a macro).
  * @param SRC Any char-array. The src need not be 0-terminated, a 0-char is handled like a normal char.
  * @param LEN Number of valid chars and persistent bit.. 
  *            The number of chars should be less than ,,mLength_StringJc,, but it is not tested here.
  *            The Bit ,,mNonPersists__StringJc,, may be set. The user is responsible to the persistence.
  * @return void, don't use inside an expression.
  */
#define SET_StringJc(THIZ, SRC, LEN) { (THIZ).addr.str = SRC; (THIZ).val = LEN; }


/**Creates a StringJc-reference to the given zero terminated text (char array).
 * This is a simple way if a method requires a StringJc object as value argument 
 * but the user want to write only a constant char literal.
 * It is a fast C-routine, because the StringJc is stored in CPU-registers, no memory is need.
 * The StringJc is designated as persistent, in most of cases a text-literal would be given.
 * The user should not use this method with an argument of a non-persistent buffer,
 * and than use the StringJc as persistent. To build a non-persistent String, use [[Fw_String.INIT_StringJc(...)]].
 * In typically cases the persistence is not need, because this method is used only to build a temporary StringJc
 * as parameter of a routine, which use the String non-persistent. Than a non-persistent buffer can be used as argument.
 * @param any 0-terminated ,,char const*,, text, typically to a text-literal, possible to a buffer. 
 *        The user is responsible to its persistence respectively the need of persistence of the result.
 * @return StringJc-instance per value, it is hold in 2 register by most of C-compilers and therefore effective.
 * @javalike Java builds a String instance automatically, if "text-literal" is given. 
 *           In Java it is able to write at example ,,"checkChars".indexOf(ch),, to convert a char into a index-number.
 *           The same it is able to write using ,,indexOf_C_StringJc(z_StringJc("checkChars"), ch),, in C javalike.
 */
INLINE_emC StringJc z_StringJc ( char const* src)
{ StringJc ret;
  int size = strnlen_emC(src, kMaxNrofChars_StringJc);
  SET_StringJc(ret, src, size); 
  return ret;
}
#define s0_StringJc z_StringJc


/**Creates a StringJc-reference. The given src is either 0-terminated or has a length of at least max.
 * The String is dedicated as non-persistent, because this routine refers a buffer typically, which does not guarantees persistence.
 * This operation is proper if a char[] is hold in an array, and the string content should not be 0-terminated
 * if the buffer is used till max.
 */
extern_C StringJc zMax_StringJc ( char const* src, int max);


/**Creates a StringJc reference to the given character string with given length.
 * This is a common way to get a StringJc-Instance if a char-buffer with a known length is given.
 * It is a fast C-routine, because the StringJc is stored in CPU-registers, no memory is need.
 * The StringJc is designated as persistent, though mostly the persistence is not need. See ,,z_StringJc(...),,. 
 * See [[StringJc.toStringFromPersist_zI_StringJc(...)]] to build a persistent StringJc from a persistent buffer. 
 * @param any ,,char const*,, text, possible to a text-literal or to a buffer. 
 *        The user is responsible to its persistence respectively the need of persistence of the result.
 * @param len the number of chars valid from text.
 * * If it is 0, the string has a pointer but the length is 0. 
 * * If it is >= mLength_StringJc then it is truncated without any warning. 
 * * If it is -1. then the length of src is count using [[[strnlen_emC(...)]].
 * * If it is <= -2, the length of src is count and the length is shortenend by (-length+1). -2: The last char is truncated etc.  
 * @return StringJc-instance per value, it is hold in 2 register by most of C-compilers and therefore effective.
 */
extern_C StringJc zI_StringJc ( char const* src, int len);
#define s0i_StringJc zI_StringJc
//end::z_StringJc[]




#define isEmpty_s0_emC(TEXT) ((TEXT)==null || *(TEXT)==0)



/**Returns the length of the given String. It regards a 0-terminated String, then [[strlen_emC(...)] is invoked.
 * If the value-element designates that it is a CharSeqJc, than 0 is returned (more correct: THROw error). 
 * Use [[length_CharSeqJc(...)]]  if this refers a StringBuilderJc_s or any other implementation of CharSeqJc.
 * The difference to CharSeqJc(...) is: the last one needs to compile StringCharSeq_emc.c
 * @return The length of the string.
*/
INLINE_emC int length_StringJc(StringJc thiz)  //INLINE
{
  int val = thiz.val & mLength_StringJc;
  if (val < kMaxNrofChars_StringJc) {
    //simple form, inline, fast:
    return val;
  }
  else if (val == kIs_0_terminated_StringJc) {
    //assume it is 0-terminated.:
    return strnlen_emC(thiz.addr.str, mLength_StringJc - 3);
  }
  else {
    return 0; //not expected.
  }
}


#define charAt_StringJc(THIZ, POS) charAt_CharSeqJc(THIZ, POS, null)



/**Gets a zero-terminated String from a given String. 
 * This routine may use the given buffer to copy the string. 
 * This buffer is used only if the given String is not zero-terminated already.
 * If the String is zero-terminated in its original StringJc-reference, it is used without copying. 
 * In that case some calculation time will be saved.
 * Only if the given String is not zero-termintated, the given part of string will be copied 
 * and terminated with a 0-character. 
 *
 * If the length of the given String is greater then zBuffer-1, it is truncated.
 * In this case the last character in the buffer is replaced with a '?'.
 * Usual the length of the string may be limitated, the application may provide a buffer with enough size. 
 * The application can check whether ,,strlen(buffer) == sizeof(buffer)-1 && buffer[strlen(buffer)] =='?',,. 
 * In that case the String may be truncated. Otherwise an outputted String may be recognized as truncated.
 *
 * See also [[gets0_StringJc(...)]]
 *  
 * @param buffer any buffer, where the content of thiz may be copied to.
 * @param zBuffer size of the buffer. The size should be the really size. A \\0 is guaranted at end of buffer.
 * @return The pointer to the zero terminated String. Either it is the String referenced in thiz, or it is buffer. 
 */
extern_C char const* getCharConst_StringJc ( StringJc const thiz, char* const buffer, int const zBuffer);




/** Set this as reference to a text as a light copy. It means, no back reference is stored
  * if a garbage collector is used. This method should be only used, if the dst is temporary.
  * The text src may be a constant text, a substring or a StringBuffer.
  * @param src The source StringJc. Note: It is given per value, not per reference,
           so direct output from StringJc-returning methods are useable as argument.
           The value consist of 2 processor registers.
  * @deprecated use direct assignment instead. 
  */
#define lightCopy_StringJc(thiz, src) { *thiz = src; } //{(thiz)->s.refbase = (src).refbase; (thiz)->s.ref = (src).ref; }

//tag::getCharsAndLength_StringJc[]
/* Gets the char-pointer and the number of chars stored in a StringJc.
 * This is a common way to get a the content of a StringJc-Instance if a char-pointer is necessary.
 * The char-pointer is either the immediately reference as stored in the StringJc,
 * or it is a pointer to the content of a referenced StringBuilderJc.  
 * The referenced character array may be persistent or not.
 * In generally, the user should not store and use the return value persistently outside of the StringJc-concept.
 * The routine is given to support evaluating the chars immediately in a C-like-way.
 * @param length destination variable (reference) to store the realy length. 
 *   The destination variable will be set anytime.
 *   If it is -1 then the StringJc is a CharSequence interface. 
 * @return the pointer to the chars. It may be null if the StringJc contains a null-reference.
 *   Or it is a CharSequence interface
 */
extern_C char const* getCharsAndLength_StringJc ( StringJc const* thiz, int* length);
//end::getCharsAndLength_StringJc[]



/**Returns the pointer to the character text itself. Note: It is not a 0-terminated text. 
 * The pointer should used only for memory management tests.
 * see ,,getCharsAndCount_StringJc(...),,. 
 * @return memory address of the text itself. The type is ,,char const*,,.
 */
#define PTR_StringJc(THIZ) ((THIZ).addr.str)


/**Returns the value which is stored in the SRC.
 * This macro should be used inside only. 
 * The value contains the length mask with mLength_StringJc, the bit mNonPersists__StringJc
 * and some additonal bits for enhanced-reference management 
 * (used for [[BlockHeap]] or another memory management).
 * @return value which is stored in the StringJc instance.
 *         The length of the text is mask with ,,mLength_StringJc,, defined in the headerfile ,,fw_Platform_conventions.h,,.
 *         If the bit ,,mNonPersists__StringJc,, is set (see ,,fw_Platform_conventions.h,,),
 *         than the referenced text may be not persistent. It may be located especially in the stack or in the thread context.
 *         If this bit is not set, than the StringJc should dedicated as persistent.
 */ 
#define VAL_StringJc(THIZ) ((THIZ).val)



/**Returns whether the StringJc should dedicated as persistent.
 * @return true if it should be persistent. The text is persistent really, if the user has kept in mind all building rules.
 *         The contract is: The user has to do so, and the StringJc referes a persistent text, if this routine returns true.
 */ 
#define isPersistent_StringJc(YTHIS) (VAL_AddrVal_emC(YTHIS) & mNonPersists__StringJc) == 0)

/**Checks whether the text refered from this instance is zero-terminated.
 * Note: The zero-termination is not a necessary property of any String
 * and it cannot assumed. But in some cases, dependently from the source of the String,
 * the zero-termination is given. It is a unexpensive machine code, if the pointer 
 * to the referenced text [[PTR_StringJc()]] is able to use immediately as a ,,char const*,, 
 * to a zero-terminated text. But the user should test this situation with this method.
 * If the text is not zero-terminated, it have to be copy to a buffer
 * using [[copyToBuffer_StringJc(...)]] to get a zero-terminated pointer to the text.
 */
extern_C bool isZeroTerminated_StringJc ( StringJc const thiz);



/**Copy the content to a given buffer.
 * It should be guaranteed that thiz is a StringJc instance and not any CharSeqJc-interface. If it is not so, an exception is thrown on runtime.
 * A StringJc does refer only to a immediate char const*. 
 * It copies without 0-terminating. If you want to have a null-termination, use the following template:
 *
 *   char myBuffer[100];
 *   int zChars = copyToBuffer_StringJc(string, start, end, myBuffer, sizeof(myBuffer)-1);
 *   myBuffer[zChars] = 0;
 * 
 * @param start start character in the StringJc.
 * @param end exclusive end position in StringJc.
 *   If -1 then the whole StringJc till end should be copied. If <=-2 then (-end)-1 characters from end won't be copied.
 *   If end > length of String, it is limit to the length and the whole string till end is copied. Note: Use kMaxNrofChars_StringJc as Arg value.
 * @param buffer The destination buffer as char[]
 * @param maxSizeBuffer The max number of chars copied. If the src text is longer, it will be truncated.
 *   Note: It does not produce a 0-terminated String. If you want to have a 0-terminated string, use sizeof(buffer)-1 for this argument.
 * @return number of chars copied. It is the number of valid chars in buffer always.
 */
extern_C int copyToBuffer_StringJc ( const StringJc thiz, int start, int end, char* buffer, int maxSizeBuffer);

//old: #define copyToBuffer_StringJc(THIZ, START, END, BUFFER, SIZE) copyToBuffer_CharSeqJc(THIZ, START, END, BUFFER, SIZE, null)



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
extern_C char const* gets0_StringJc(StringJc const thiz, char* const buffer, int const zBuffer, bool exceptionOnLessBuffer, struct ThreadContext_emC_t* _thCxt);






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
extern_C bool equals_StringJc ( const StringJc ythis, const StringJc cmp);


/**Compares this string to the specified character text.
 * @param strCmp Any character text
 * @param valueCmp Number of chars to compare, but mask with ,,mLength_StringJc,,.
 *        If -1 or all bits of ,,mLength_StringJc,, are set, 
 *        than the length is got from ,,strnlen_emC(sCmp, mLength_StringJc),,,
 *        The other bits were not used.
 * @return The result is true if
 *         and only if the argument is not null and the text of this represents
 *         the same sequence of characters as strCmp.
 */
bool equals_zI_StringJc ( const StringJc ythis, const char* strCmp, int valueCmp );

/** Compares this string to the specified text. The result is true if
  * and only if the argument is not null and the StringJc referes
  * the same sequence of characters as this object.
  * @param CMP 0-terminated String to compare with this.
  * @return The result is true if
  *         and only if the argument is not null and is a text that represents
  *         the same sequence of characters as this object.
  */
#define equals_z_StringJc(YTHIS, CMP) equals_zI_StringJc(YTHIS, CMP, mLength_StringJc)
/** @deprecated*/
#define equals_s0_StringJc(YTHIS, CMP) equals_z_StringJc(YTHIS, CMP)





/*@CLASS_C CharacterJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

INLINE_emC bool isIdentifierStart_CharacterJc(char cc) { return (cc >= 'a' && cc <= 'z') || (cc >= 'A' && cc <= 'Z') || cc == '_'; }

INLINE_emC bool isIdentifierPart_CharacterJc(char cc) { return isIdentifierStart_CharacterJc(cc) || (cc >= '0' && cc <= '9'); }



/*@inline @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**StringJc : Additional to StringJc after definiton of [[length_StringBuilderJc(...)]]. */





/*@END*/





#endif //HGUARD_emC_Base_StringBase_emC
