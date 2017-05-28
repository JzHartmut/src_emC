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
#ifndef __applstdefJc_h__
  /**This file MemC should be included in the applstdefJc.h. 
   * If this file is directly included, it needs the applstdefJc.h. But the __MemC_h__ guard should not be set firstly
   * to include the MemC.h in the given order in applstddef.h
   */
  #include <applstdefJc.h>
#endif
//The following include guard prevent twice include especially if appöstdefJc.h includes this file already.
#ifndef __fw_String_h__
#define __fw_String_h__


struct ObjectJc_t;
struct StringBuilderJc_t;

struct MemAreaC_t;




/**Counts the number of chars till a \0-char. 
 * In opposite to the C-standard strlen, this routine may not crash on undefined strings. 
 * @param text The string where the length till \0 is to detect.
 * @param maxnrofChars maximal number of chars to detect. This parameter may be set by a suitable value,
 *        at example the maximal size of a buffer. The possibility of a memory fault access 
 *        is some more less than as in comparision with the strlen-call without any limits.
 * @return the number of chars till \0 or maxNrofChars. 
 */
extern_C int strlen_Fwc(char const* text, int maxNrofChars);

/**Searches a character inside a given string with terminated length.
 * NOTE: The standard-C doesn't contain such simple methods. strchr fails if the text isn't terminated with 0.
 */
extern_C int searchChar_Fwc(char const* text, int maxNrofChars, char cc);

/**Searches a String inside a given string with terminated length.
 * NOTE: The standard-C doesn't contain such simple methods. strstr fails if the text isn't terminated with 0.
 */
extern_C int searchString_Fwc(char const* text, int maxNrofChars, char const* ss, int zs);

/**Returns the number of chars which are whitespaces starting from text.
 * Whitespaces are all chars with code <=0x20. It are all control chars from the ASCII and the space. 
 */
extern_C int skipWhitespaces_Fwc(char const* text, int maxNrofChars);


/**Returns the number of chars which note whitespaces starting from end of text.
 * Whitespaces from begin or inside the text are not regarded.
 * Whitespaces are all chars with code <=0x20. It are all control chars from the ASCII and the space. 
 * @return length of text without right-bounded white-spaces.
 */
extern_C int trimRightWhitespaces_Fwc(char const* text, int maxNrofChars);





/**Mask bits for position of method table of CharSequJc.
 * If mLength__StringJc == 0x3fff (default for 32 bit system), the mask is 0x0fff.
 * See [[kMaxLength_StringJc]], it will be therewith 0x3000 -1 = 0x2fff.
 */
#define mMtbl_CharSeqJc (mLength__StringJc >>2)


/**The limit for the length of a StringJc. It is derived from the platform-specific definition of ,,mLength__StringJc,, 
 * contained in the platform-specific ,,compl_adaption.h,,. 
 * If the ,,mLength_StringJc,, is defined with ,,0x3fff,, then this value is ,,0x2fff,,.
 * 
 * If a ,,StringJc,, is designated with this value for the ,,mLength__StringJc,, bits, then the length should be gotten 
 * on demand. The [[length_StringJc(...)]] regards that.  
 */
#define kMaxLength_StringJc ((mLength__StringJc & ~mMtbl_CharSeqJc)-1)

/**If this Bit is set, the StringJc referenced the whole string of a StringBufferJc to concat strings.
 * If mLength is defined with 0x3fff the value is 0x04000. mLength is defined os- and platform-depended in os_types_def.h
 */
#define mNonPersists__StringJc       (mLength__StringJc +1)

/**If this Bit is set, the StringJc references a buffer in the thread context..
 * If mLength is defined with 0x3fff the value is 0x08000. mLength is defined os- and platform-depended in os_types_def.h
 */
#define mThreadContext__StringJc     ((mNonPersists__StringJc)<<1)



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
 * The value is (based on [[CRJS:_mLength__StringJc]] == 0x3fff for a 32-bit-system):
 * * 0x0000 ... 0x2fff: either the same how defined in [[class_StringJc]], then it contains the length of the String
 * * 0x3000 ... 0x3ffd: In this case the bits with mask 0xfff contains the index to the method table of CharSeqJc inside the whole method table of the ObjectJc
 * * 0x3ffe: or it is designated with the bits to designate the CharSeqJc as StringBuilderJc
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
 * The headerfile ,,Fwc/fw_String.h,, defines the type and some basicly functionalities
 * to use a StringJc-instance in a low independent level to refer a text..
 * This headerfile against that defines the typically String functionality,
 * which followes the [[sunJavadoc/java/lang/String]] class-functinality. 
 * But some enhancements are given, because the string processing in fast real time embedded systems
 * may work without dynamically memory too.
 *
 * Notation hint: The notation ,,char const*,, is the same as ,,const char*,,, but it expresses more stronly, that it is a const-pointer.
 * 
 */ 


typedef OS_PtrVal_DEF(StringJc, char const);

/**Designation of the String as CharSeqJc without a method table offset. In this case the reference refers a CharSeqJc and the length
 * should be gotten by invocation of [[length_CharSeqJc(...)]].
 * If mLength is defined with 0x3fff the value is 0x03ffe. mLength is defined os- and platform-depended in os_types_def.h
 */
#define kIsCharSeqJc_CharSeqJc (mLength__StringJc -1)


/**Designation of the String as CharSeqJc maybe with a method table offset. In this case the reference refers a CharSeqJc and the length
 * should be gotten by invocation of [[length_CharSeqJc(...)]].
 * If mLength is defined with 0x3fff the value is 0x3000. mLength is defined os- and platform-depended in os_types_def.h
 */
#define mIsCharSeqJcMtbl_CharSeqJc (mLength__StringJc & ~(mLength__StringJc >>2))

/**Designation of the String as StringBuilderJc-instance. In this case the reference refers a StringBuilderJc and the length
 * should be gotten by invocation of length_StringBuilderJc(ref)
 * If mLength is defined with 0x3fff the value is 0x03ffd. mLength is defined os- and platform-depended in os_types_def.h
 */
#define kIsStringBuilder_CharSeqJc (mLength__StringJc -2)




/**Initializer-Macro for constant StringJc, initialize the StringJc-reference to a zero-terminated text.
 * The length of the text
 * is not stored inside StringJc, the length bits are setted to there maximum 
 * (value of ,,mLength__StringJc,,, see ,,fw_Platform_conventions.h,,)
 * to detect this constellation.
 * @param TEXT should be a text-literal only. If it references a char-array, 
 *             a problem with persistence may existing.
 */
#define CONST_z_StringJc(TEXT) { TEXT, kMaxLength_StringJc}

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
#define INIT_StringJc(DST, src, val) set_OS_PtrValue((DST), src, val)


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
INLINE_Fwc StringJc z_StringJc(char const* src)
{ StringJc ret;
  int size = strlen_Fwc(src, kMaxLength_StringJc);
  set_OS_PtrValue(ret, src, size); 
  return ret;
}

#define s0_StringJc z_StringJc



/**Creates a StringJc reference to the given character string with given length.
 * This is a common way to get a StringJc-Instance if a char-buffer with a known length is given.
 * It is a fast C-routine, because the StringJc is stored in CPU-registers, no memory is need.
 * The StringJc is designated as persistent, though mostly the persistence is not need. See ,,z_StringJc(...),,. 
 * See [[StringJc.toStringFromPersist_zI_StringJc(...)]] to build a persistent StringJc from a persistent buffer. 
 * @param any ,,char const*,, text, possible to a text-literal or to a buffer. 
 *        The user is responsible to its persistence respectively the need of persistence of the result.
 * @param len the number of chars valid from text.
 * * If it is 0, the string has a pointer but the length is 0. 
 * * If it is >= mLength__StringJc then it is truncated without any warning. 
 * * If it is -1. then the length of src is count using [[[strlen_Fwc(...)]].
 * * If it is <= -2, the length of src is count and the length is shortenend by (-length+1). -2: The last char is truncated etc.  
 * @return StringJc-instance per value, it is hold in 2 register by most of C-compilers and therefore effective.
 */
INLINE_Fwc StringJc zI_StringJc(char const* src, int len)
{ StringJc ret;
  if(len < 0){ len = strlen_Fwc(src, kMaxLength_StringJc) - (-len) +1; } //nr of chars from end, -1 is till end. -2: without last char.
  else if(len >= mLength__StringJc) { len = mLength__StringJc -1; }  //limit it to max. 
  set_OS_PtrValue(ret, src, (len & mLength__StringJc)); 
  return ret;
}

#define s0i_StringJc zI_StringJc



/**Returns true if the StringJc contains null. The user should use this macro instead straigtly using of the basicly definitions,
 * because the definition of OS_PtrValue and therefore the definition of StringJc is os-specific. 
 * @param STR StringJc-instance to test. The macro uses the instance directly.
 * @return true only if the text-reference is ,,null,,. false if it is an empty or non-empty text.
 */
#define isNull_StringJc(STR) (PTR_OS_PtrValue((STR), void*)==null)


#define isEmpty_s0_Fwc(TEXT) ((TEXT)==null || *(TEXT)==0)


/**Returns the length. If the source stores the value kMaxLength__StringJc in its value-element,
 * the length is got calling ,,strlen(ptr),,. Otherwise the length is the value-element,
 * mask with mLength__StringJc, independent of the string itself. Note that the string may contain 0-chars
 * inside the given length.
 * @return The length of the string.
 */
METHOD_C int length_StringJc(StringJc const ythis);




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
#define lightCopy_StringJc(ythis, src) { *ythis = src; } //{(ythis)->s.refbase = (src).refbase; (ythis)->s.ref = (src).ref; }


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
#define PTR_StringJc(THIZ) PTR_OS_PtrValue((THIZ), char const)


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
#define VAL_StringJc(THIZ) value_OS_PtrValue((THIZ))



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



/**Copy the content to a buffer of the user.
 * The text will be terminated with 0 always. If the src text is to long. it will be truncated.
 * If the returned length == maxSizeBuffer-1, it is not determined whether the text is truncated or not.
 * Note: if the src-text (ythis) contains 0-characters in its active area, they will be copied too as normal chars.
 * 
 * Note: thiz should a really StringJc or a reference to a StringBuilderJc on runtime.
 * If it may be a CharSeqJc , use [[copyToBuffer_CharSeqJc]].
 * That method regards simple Strings too.
 *
 * @param buffer The destination buffer as char[]
 * @param start start character in the StringJc.
 * @param end exclusive end position in StringJc. If -1 then the whole StringJc till end should be copied.
 * @param maxSizeBuffer The number of bytes in Buffer.The max number of chars copied is maxSizeBuffer -1
 * @return number of chars copied. It is the number of valid chars in buffer always.
*/
METHOD_C int copyToBuffer_StringJc(const StringJc thiz, int start, int end, char* buffer, int maxSizeBuffer);


#include <Fwc/objectBaseC.h>



/*@CLASS_C StringBuilderJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


//#define staticSize_StringBuilderJc 80

/**A StringBuilderJc is a structure to manage char[]-arrays. 
 * It is derivated and adapted from the content of the java.lang.StringBuffer rsp. java.lang.StringBuilder.
 * Some Java-like methods are supplied, but not all, but some methods are additional 
 * and specifical for usages in C or C++.
 *
 * There are 2 forms of memory layout of this struct:
 * * a) The struct StringBuilderJc contains only the count, size and the pointer of the char[...]-buffer.
 * * b) The struct contains the char-buffer itself.
 *
 * The first variant is usefull especially if a C-like text buffer (char* with given size) is located anywhere
 * in the users data structures, and the StringBuilderJc-instance is only used temporary to assemble the text in the buffer.
 *
 * The last variant is possible either if a construct like
 *
 * , struct { StringBuilderJc b; char _b[46];} myBuilder = 
 * ,   CONST_addSizeStack_StringBuilderJc(&buffer.b, 50);
 *
 * is defined and initialized or if the [[ctorO_StringBuilderJc(...)]]-Constructor is called 
 * with an initialized ObjectJc with a size greater than sizeof(StringBuilderJc). It means more memory was allocated.
 * That variant needs only 1 memory block for the buffer management and the buffer itself.
 *
 * The StringBuilderJc-instance holds some flags such as ''located in the Thread Context'' or ''buffer is located in Stack''
 * and ''truncated'', see the appropriate methods. The internal attributes of this struct should not use immediately,
 * only the methods of this C-class should be used.
 *
 * '''Problem of reallocating a buffer''': In Java it's some more easier: Working with dynamically memory is usual, 
 * and the buffer is a private element of the StringBuilder. Therefore the buffer can be changed anytime, 
 * only a few amount of calculation time is need.
 *
 * But in C the StringBuilderJc is often associated with a determined buffer of the user. The user shows to its buffer,
 * The StringBuilder-instance is only a helper to deal with the content. A situation, that an unexpected overflow of the buffer size
 * occurs during an append operation, than the StringBuilder swaps the content in a new allocated buffer, will be a confusion.
 * The user looks to its buffer, no content is changed, why? He doesn't look to the StringBuilder-Instance.
 *
 * Because on other side the handling with dynamically memory is restricted often in C-applications, the reallocation of buffer
 * is only suitable by calling the method ,,ensureCapacity,,. This method is not supported in this version, but it may be supported.
 * Than the user is responsible to the correctness of handling with its old buffer. If the user ensures actively, it should look what it means.
 * If the [[BlockHeap]] or an adequate mechanism with equal-size-blocks are used for dynamically memory-management, 
 * a new allocated buffer has the highest size of block which are possible in the system. So an enhancement of capacity is not possible.
 * The system limit of equal size blocks are decisive anyway. An increasing is not possible, because the highest size is given anyway.
 *
 * The allocation is not limited in startup-phase using [[BlockHeap]], but in a startup phase the allocated memory is used
 * as fix memory on runtime. An accidental buffer for a String-building is not desired mostly.  
 *
 * Therefore the concept is: An enhancement of content never changes the buffer. 
 * Either an exception is thrown (to detect maybe an error of given conditions) or an truncation is done.
 */
typedef struct  StringBuilderJc_t
{
  /** It based on ,,ObjectJc,,. @sizeof=20*/
  union{ ObjectJc object;} base;

  /**Actual nr of characters. 0 or positive. All attributes are privave. 
   * The struct should use only via its methods. */
  int16 _count;

  /**The size of the Buffer and marker to use value. 
   * If this number is negative, a buffer is referenced, use value.buffer. 
   * If this number is positive, the buffer follows immediately, use value.direct. 
   */
  int16 size;

  /**Some mode-bits,see defines ,,_m...,,. */
  int32 _mode;
  /**If this bit is set in _mode, no exception will be thrown on buffer overflow, instead truncate. */
  #define _mNoException_StringBuilderJc 0x0001
  /**If this bit is set in _mode, the buffer content was truncated in an append or insert operation. */
  #define _mTruncated_StringBuilderJc 0x0002
  /**The mode is designated with this bits, if the instance is only created temporary while concatenating Strings. */
  #define _mStringConcatBuffer_StringBuilderJc 0x0010
  /**The mode is designated with this bits, if the instance is located in the Stack range. */
  #define _mStack_StringBuilderJc 0x0020
  /**The mode is designated with this bits, if the instance is located in the Thread context. */
  #define _mThread_StringBuilderJc 0x0040

  #define _mStringBuilt_StringBuilderJc 0x80 
  
  /**The buffer itself is either referenced or it is embedded here. 
   * @sizeof=4.
   */
  union value_t
  {
    /** The buffer may be disposed directly in this structure. 
    */
    char direct[4];
    //#define offsetChars_StringBuilderJc (sizeof(ObjectJc) + 2* sizeof(int16)) + sizeof(int32)  //sizeof(count) + sizeof(maxNumberOfChars)

    /**Pointer to the referenced buffer.
     * If this is choosen, the size is negative.
    */
    char* buffer;
  }value;
}StringBuilderJc;


#define sizeof_StringBuilderJc sizeof(StringBuilderJc)
#define sizeof_StringBufferJc sizeof_StringBuilderJc

extern_C const struct ClassJc_t reflection_StringBuilderJc;
#define reflection_StringBuilderJc_s reflection_StringBuilderJc
#define reflection_StringBufferJc reflection_StringBuilderJc


//#define staticSize_StringBuilderJc (sizeof(((StringBuilderJc*)(0x1000))->value.direct))

/**This macro defines a C-constant (with {..}) for empty-initializing a StringBuffer instance with its static size.
 * @param OBJP Pointer to the instance itself. It is used to store the OWNADDRESS for the ObjectJc-part.
 */
#define CONST_StringBuilderJc(OBJP) { CONST_ObjectJc(sizeof(StringBuilderJc), &(OBJP)->base.object, null), 0, 0, null }


/**This macro defines a C-constant (with {..}) for initializing a StringBuffer instance with an additional size.
 * This macro is usefull if a StringBuffer with a following char array is defined 
 * to increase the size of the immediate text in buffer.
 * The definition of such an construct is possible inside a struct definition with followed sample:
 *
 * ,,struct { ... ; StringBuilderJc buffer; char bufferIncreasingCharArray[120]; ... } myData =
 *
 * The ,,bufferIncreasingCharArray,, have to be assembled immediately after the ,,buffer,,. 
 * The initializer of this part may be written in form of:
 *
 * ,,{ ... , CONST_addSize_StringBuilderJc(&myData.buffer, 120), { 0 }, ... },,
 *
 * The using of a following char array to increase the buffer is opportune to get a larger StringBuffer, 
 * because the compiler will always assigns the memory of the followed char array 
 * immediately after the previous element, the StringBuilderJc, and the own char array of the StringBuilderJc 
 * is assigned as the last element there. The problem of additional bytes because 4-Byte-allignment or such 
 * is not present, because a StringBuilderJc have a size of multiple 4 bytes.
 * But the user should define the size of the char array as multiple of 4 to prevent alignment problems also.
 *
 * Note: Outside a struct, the definition of elements one after another doesn't may assigned one after another in memory.
 * It differents from compiler versions or other conditions such as segmentation sizes of physical memory!
 *
 * @param OBJP Pointer to the instance itself. It is used to store the OWNADDRESS for the ObjectJc-part.
 * @param ADDSIZE The additional size of the StringBuffer, defined by sizeof the followed char array.
 */
#define CONST_addSize_StringBuilderJc(OBJP, ADDSIZE) { CONST_ObjectJc(sizeof(StringBuilderJc) + (ADDSIZE), &(OBJP)->base.object, null), 0, sizeof((OBJP)->value) + (ADDSIZE) -1, 0 }


/**This macro defines a C-constant (with {..}) for initializing a StringBuffer instance with an additional size.
 * which is located in the Stack. See ,,CONST_addSize_StringBuilderJc(...),, 
 * It have to be used if the StringBuilderJc-instance is located in Stack. 
 * The mode bits ,,_mStack_StringBuilderJc,, is set. 
 * The definition of such an construct is recommended as astruct definition like following:
 *
 * struct { StringBuilderJc u; char _[120]; } uBuffer = { CONST_addSize_StringBuilderJc(&uBuffer.buffer, 120), { 0 }};
 *
 * The a StringBuilder with immediately buffer for 123 characters and a 0 on end is placed in the stack.
 * See macro INSTACK_StringBuilderJc(...).
 * @param OBJP The reference to the StringBuilder-instance itself
 * @param ADDSIZE size of the char[] after the StringBuilderJc-instance.
 */
#define CONST_addSizeStack_StringBuilderJc(OBJP, ADDSIZE) { { CONST_ObjectJc(sizeof(StringBuilderJc) + (ADDSIZE), &(OBJP)->base.object, null) }, 0, sizeof((OBJP)->value) + (ADDSIZE) -1, _mStack_StringBuilderJc}



/**This macro defines a StringBuffer instance with an additional size to locate in the stack.
 * which is located in the Stack. See ,,CONST_addSize_StringBuilderJc(...),, 
 * It have to be used if the StringBuilderJc-instance is located in Stack. 
 * The mode bits ,,_mStack_StringBuilderJc,, is set. 
 * The definition of such an construct is recommended as astruct definition like following:
 *
 * struct { StringBuilderJc b; char _[120]; } uBuffer = { CONST_addSize_StringBuilderJc(&uBuffer.buffer, 120), { 0 }};
 *
 * The a StringBuilder with immediately buffer for 123 characters and a 0 on end is placed in the stack.
 * See macro INSTACK_StringBuilderJc(...).
 * @param name The name of the StringBuilder-instance
 * @param chars number of chars inclusive the ending 0-char.
 */
#define INSTACK_StringBuilderJc(name, chars) struct { StringBuilderJc u; char _[chars-4]; } buffer = { CONST_addSizeStack_StringBuilderJc(&buffer.u, chars-4), {0}}

/**Gets the buffer as char* to use in C-Standard-Routines. 
 * The buffer content is zero-terminated always. 
 * @return 0-terminated content of buffer.
 */
METHOD_C char* chars_StringBuilderJc(StringBuilderJc* ythis);


/**Gets the buffer and the size of the buffer. 
 * @param size a ,,int*,, reference to a variable, into which the value of buffer-size is stored.
 * @return ,,char*,,-pointer to the buffer.
 */
METHOD_C char* getCharsAndSize_StringBuilderJc(StringBuilderJc* ythis, int* size);


/**Gets the buffer and the actual nr of chars in the buffer. 
 * @param count a ,,int*,, reference to a variable, into which the value of number of chars is stored.
 * @return ,,char*,,-pointer to the buffer.
 */
METHOD_C char* getCharsAndCount_StringBuilderJc(StringBuilderJc* ythis, int* count);

/**Gets the buffer, the size and the actual nr of chars in the buffer.
 * @param size a ,,int*,, reference to a variable, into which the value of buffer-size is stored.
 * @param count a ,,int*,, reference to a variable, into which the value of number of chars is stored.
 * @return ,,char*,,-pointer to the buffer.
 */
METHOD_C char* getCharsSizeCount_StringBuilderJc(StringBuilderJc* ythis, int* size, int* count);

/**Sets the nr of chars immediately. Only internal use. 
 * @param count actual number of chars.
 */
METHOD_C void _setCount_StringBuilderJc(StringBuilderJc* ythis, int count);


/**Sets the length of the character sequence. It's like java.lang.StringBuffer.setLength().
 * The sequence is changed to a new character sequence whose length is specified by the argument.
 * For every nonnegative index k less than newLength, the character at index k in the new character sequence
 * is the same as the character at index k in the old sequence if k is less than the length of the old character sequence;
 * otherwise, it is the null character '\u0000'.
 * In other words, if the newLength argument is less than the current length, the length is changed to the specified length.
 *
 * If the newLength argument is greater than or equal to the current length, sufficient null characters ('\u0000')
 * are appended so that length becomes the newLength argument.
 *
 * The newLength argument must be greater than or equal to 0.
 *
 * @param newLength The new length
 * @throws IndexOutOfBoundsException if the newLength argument is negative or greater than the maximal possible buffer size.
 * @see [[length_StringBuilderJc()]]
 * @javalike [[sunJavadoc/java/lang/StringBuilder#setLength(int)]].
 */
METHOD_C void setLength_StringBuilderJc(StringBuilderJc* ythis, int newLength, struct ThreadContextFW_t* _thCxt);
#define setLength_StringBufferJc setLength_StringBuilderJc

/**Clears the content. It is the same like setLength(0).
 * @see [[setLength_StringBuilderJc()]]
 * @javalike [[sunJavadoc/java/lang/StringBuilder#setLength(int)]] with 0 as parameter.
 */
METHOD_C void clear_StringBuilderJc(StringBuilderJc* ythis);
#define clear_StringBufferJc clear_StringBuilderJc






/**Gets the number of chars in buffer.
 * @return the number of chars without the terminating 0-char.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#length()]].
 */
#define length_StringBuilderJc(YTHIS) ((YTHIS)->_count)
//METHOD_C int length_StringBuilderJc(const StringBuilderJc* ythis, struct ThreadContextFW_t* _thCxt);

/**Gets the size of buffer.
 * @return the maximal number of chars able to store in buffer. It is count without a 0-char at end. 
 *         It means, it is the physical size of buffer -1.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#capacity()]].
 */
METHOD_C int capacity_StringBuilderJc(StringBuilderJc* ythis);


/**Copies the text in the given buffer. Use the set mode of ,,setTruncateMode_StringBuilderJc(..),, 
 * to desire, whether an exception is thrown or the text will be truncated if the zBuffer is less.
 * @param buffer any buffer, where the content of ythis is copied to.
 * @param start start character in the string in the StringBuilderJc.
 * @param end exclusive end position in string in the StringBuilderJc. If -1 then the whole string till end should be copied.
 * @param zBuffer size of the buffer. The size should be the really size. A \\0 is guaranted at end of buffer.
 *                It means, the ,,length_StringBuilderJc(ythis),, should less as zBuffer, not equal.
 * @return number of chars without the terminating 0-char. The max value is ,,zBuffer -1,,.
 */
METHOD_C int copyToBuffer_StringBuilderJc(StringBuilderJc* ythis, int start, int end, char* buffer, int zBuffer);


#endif //__fw_String_h__
