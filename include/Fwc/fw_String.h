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
#ifndef __fw_String_h__
#define __fw_String_h__
//#include "fw_Platform_conventions.h"
#include <os_types_def.h>


/*@DEFINE_C some_forward_types @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

struct MemAreaC_t;


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

#define ByteStringJc OS_PtrValue

#define null_ByteStringJc null_OS_PtrValue

#define length_ByteStringJc(STR) (value_OS_PtrValue(STR) & mLength__StringJc)

#define data_ByteStringJc(STR) PTR_OS_PtrValue(STR, int8)

#define byteAt_ByteStringJc(STR, pos) (PTR_OS_PtrValue(STR, int8)[pos])



/*@CLASS_C Fw_String @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**CLASS_C_Description: The ,,struct StringJc,, is the same as ,,struct OS_PtrValue,,. A StringJc consists of a reference and the number of chars.
 * But the value may contain also an index for enhanced referencing. 
 * Therefore the value is mask with some special bit definitions:
 * * mLength__StringJc: mask for bits for length. The bits are arranged in the low-bits always. 
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
 * Notation hint: The notation ,,char const*,, is the same as ,,const char*,,, but it expresses more stronly, that it is a const-pointer.
 */  
#define StringJc OS_PtrValue


typedef OS_PtrValue CharSeqJc;


extern char const sign_Mtbl_StringJc[]; 

/**Designation of the String as CharSeqJc. In this case the reference refers a CharSeqJc and the length
 * should be gotten by invocation of 
 */
#define kIsCharSequence_StringJc (mLength__StringJc -1)

/**Designation of the String as StringBuilderJc-instance. In this case the reference refers a StringBuilderJc and the length
 * should be gotten by invocation of length_StringBuilderJc(ref)
 */
#define kIsStringBuilder_StringJc (mLength__StringJc -2)

/**If this Bit is set, the StringJc referenced the whole string of a StringBufferJc to concat strings.
 * NOTE: mLength__StringJc is defined in os_types_def.h
 */
#define mNonPersists__StringJc       (mLength__StringJc +1)

/**If this Bit is set, the StringJc references a buffer in the thread context..*/
#define mThreadContext__StringJc     ((mNonPersists__StringJc)<<1)


/**Initializer-Macro for constant StringJc, initialize the StringJc-reference to a zero-terminated text.
 * The length of the text
 * is not stored inside StringJc, the length bits are setted to there maximum 
 * (value of ,,mLength__StringJc,,, see ,,fw_Platform_conventions.h,,)
 * to detect this constellation.
 * @param TEXT should be a text-literal only. If it references a char-array, 
 *             a problem with persistence may existing.
 */
#define CONST_z_StringJc(TEXT) { TEXT, mLength__StringJc}

/**Initializer-Macro for constant StringJc, initialize the StringJc-reference to a text with known length.
 * Using this macro instead ,,CONST_StringJc(...),, saves calculation time to calculate the ,,strlen(),,.
 * @param TEXT should be a text-literal only. If it references a char-array, 
 *             a problem with persistence may existing.
 * @param LEN The length as number. Do not use methods like strlen(...)
 *            to determine the length, because this is a const-initializing-macro.
 *            In C++, methods are syntaxtically able to use, but it produces more machine code
 *            and the definition cannot store in a const segment. In C it is an error.
 */
#define CONST_StringJc(TEXT, LEN) { TEXT, LEN}

#define NULL_StringJc { null, 0}





/** Initialize a StringJc instance with the reference to the given constant zeroterminated text.
  * The up till now value inside DST is not respected. This method is usefull to initialize new instances
  * espacially inside the stack.
  * @param DST The destination instance. The instance is used directly (it is a macro).
  * @param src Any char-array. The src need not be 0-terminated, a 0-char is handled like a normal char.
  * @param val Number of valid chars and persistent bit.. 
  *            The number of chars should be less than ,,mLength__StringJc,, but it is not tested here.
  *            The Bit ,,mNonPersists__StringJc,, may be set. The user is responsible to the persistence.
  * @return void, don't use inside an expression.
  */
#define INIT_StringJc(DST, src, val) set_OS_PtrValue(DST, src, val)


/** Initialize a StringJc instance with an other given StringJc.
  * The up till now value inside DST is not respected. This method is usefull to initialize new instances
  * espacially inside the stack. It is a simple copy.
  * @param YTHIS The destination instance. The instance is used directly (it is a macro).
  * @param src Any source StringJc
  * @return void, don't use inside an expression.
  */
#define INIT_s_StringJc(YTHIS, src) copy_OS_PtrValue(YTHIS, src)



/**A pointer to StringJc structure containing null-values.
 * NOTE: a pointer is necessary because a const problem occurs otherwise.
 */
extern StringJc const null_StringJc;

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
METHOD_C StringJc z_StringJc(char const* src);
#define s0_StringJc z_StringJc

/**Creates a StringJc reference to the given char array with given length.
 * This is a common way to get a StringJc-Instance if a char-buffer is given.
 * It is a fast C-routine, because the StringJc is stored in CPU-registers, no memory is need.
 * The StringJc is designated as persistent, mostly the persistence is not need. See ,,z_StringJc(...),,. 
 * See [[StringJc.toStringFromPersist_zI_StringJc(...)]] to build a persistent StringJc from a persistent buffer. 
 * @param any 0-terminated ,,char const*,, text, typically to a text-literal, possible to a buffer. 
 *        The user is responsible to its persistence respectively the need of persistence of the result.
 * @param len the number of chars valid from text
 * @return StringJc-instance per value, it is hold in 2 register by most of C-compilers and therefore effective.
 */
METHOD_C StringJc zI_StringJc(char const* src, int len);
#define s0i_StringJc zI_StringJc



/**Returns true if the StringJc contains null. The user should use this macro instead straigtly using of the basicly definitions,
 * because the definition of OS_PtrValue and therefore the definition of StringJc is os-specific. 
 * @param STR StringJc-instance to test. The macro uses the instance directly.
 * @return true only if the text-reference is ,,null,,. false if it is an empty or non-empty text.
 */
#define isNull_StringJc(STR) (PTR_OS_PtrValue(STR, void*)==null)


#define isEmpty_s0_Fwc(TEXT) ((TEXT)==null || *(TEXT)==0)


/**Returns the length. If the source stores the value mLength__StringJc in its value-element,
 * the length is got calling ,,strlen(ptr),,. Otherwise the length is the value-element,
 * mask with mLength__StringJc, independent of the text. The text may contain 0-chars
 * inside the given length.
 * @return The length of the text.
 */
METHOD_C int length_StringJc(StringJc const ythis);


/**Copy the content to a buffer of the user.
 * The text will be terminated with 0 always. If the src text is to long. it will be truncated.
 * If the returned length == maxSizeBuffer-1, it is not determined whether the text is truncated or not.
 * Note: if the src-text (ythis) contains 0-characters in its active area, they will be copied too as normal chars.
 * 
 * @param buffer The destination buffer as char[]
 * @param maxSizeBuffer The number of bytes in Buffer.The max number of chars copied is maxSizeBuffer -1
 * @return number of chars copied. It is the number of valid chars in buffer always.
*/
METHOD_C int copyToBuffer_StringJc(const StringJc ythis, char* buffer, int maxSizeBuffer);



/**Gets a zero-terminated String from a given String. 
 * This routine uses a buffer to copy the string. This buffer is used only if the given String is not zero-terminated already.
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
METHOD_C char const* getCharConst_StringJc(StringJc const thiz, char* const buffer, int const zBuffer);




/** Set this as reference to a text as a light copy. It means, no back reference is stored
  * if a garbage collector is used. This method should be only used, if the dst is temporary.
  * The text src may be a constant text, a substring or a StringBuffer.
  * @param src The source StringJc. Note: It is given per value, not per reference,
           so direct output from StringJc-returning methods are useable as argument.
           The value consist of 2 processor registers.
  * @deprecated use direct assignment instead. 
  */
#define lightCopy_StringJc(ythis, src) { *ythis = src; } //{(ythis)->s.refbase = (src).s.refbase; (ythis)->s.ref = (src).s.ref; }


/**Returns the char at position idx.
 * @param idx The index. It should be a positiv number and less than the length of the text.
 *        Because this is a fast access using a macro, the index in not tested. If the index is fault,
 *        an undefined value is returned. If the built position with this index is outside the memory area,
 *        an memory exception can be thrown. Therefore: Only use correct indices.
 * @return character at the position of text + idx.
 * @javalike [[sunJavadoc/java/lang/String#charAt(int)]] but a test of idx is not done.
 */
#define charAt_StringJc(YTHIS, idx)  PTR_StringJc(YTHIS)[idx] //( ((StringJcx*)&(YTHIS))->s.ref[idx])

/* Gets the char-pointer and the number of chars stored in a StringJc.
 * This is a common way to get a the content of a StringJc-Instance if a char-pointer is used.
 * It is a fast C-routine, because the StringJc is stored in CPU-registers, no memory is need.
 * The char-pointer is the same reference as in the StringJc. It may be persistent or not.
 * In generally, the user shouldn't store the reference persistently outside of the StringJc-concept.
 * The routine is given to support evaluating the chars in a C-like-way.
 * @param length destination variable (reference) to store the realy length. The destination variable will be set anytime.
 * @return the pointer to the chars. It may be null if the StringJc contains a null-reference.
 */
METHOD_C char const* getCharsAndLength_StringJc(StringJc const* ythis, int* length);



/**Returns the pointer to the character text itself. Note: It is not a 0-terminated text. 
 * The pointer should used only for memory management tests.
 * see ,,getCharsAndCount_StringJc(...),,. 
 * @return memory address of the text itself. The type is ,,char const*,,.
 */
#define PTR_StringJc(YTHIS) PTR_OS_PtrValue(YTHIS, char const)


/**Returns the value which is stored in the SRC.
 * This macro should be used inside only. 
 * The value contains the length mask with mLength__StringJc, the bit mNonPersists__StringJc
 * and some additonal bits for enhanced-reference management 
 * (used for [[BlockHeap]] or another memory management).
 * @return value which is stored in the StringJc instance.
 *         The length of the text is mask with ,,mLength__StringJc,, defined in the headerfile ,,fw_Platform_conventions.h,,.
 *         If the bit ,,mNonPersists__StringJc,, is set (see ,,fw_Platform_conventions.h,,),
 *         than the referenced text may be not persistent. It may be located especially in the stack or in the thread context.
 *         If this bit is not set, than the StringJc should dedicated as persistent.
 */ 
#define VAL_StringJc(YTHIS) value_OS_PtrValue(YTHIS)



/**Returns whether the StringJc should dedicated as persistent.
 * @return true if it should be persistent. The text is persistent really, if the user has kept in mind all building rules.
 *         The contract is: The user has to do so, and the StringJc referes a persistent text, if this routine returns true.
 */ 
#define isPersistent_StringJc(YTHIS) (value_OS_PtrValue(YTHIS) & mNonPersists__StringJc) == 0)

/**Checks whether the text refered from this instance is zero-terminated.
 * Note: The zero-termination is not a necessary property of any String
 * and it cannot assumed. But in some cases, dependently from the source of the String,
 * the zero-termination is given. It is a unexpensive machine code, if the pointer 
 * to the referenced text [[PTR_StringJc()]] is able to use immediately as a ,,char const*,, 
 * to a zero-terminated text. But the user should test this situation with this method.
 * If the text is not zero-terminated, it have to be copy to a buffer
 * using [[copyToBuffer_StringJc(...)]] to get a zero-terminated pointer to the text.
 */
METHOD_C bool isZeroTerminated_StringJc(StringJc const ythis);

#endif //__fw_String_h__
