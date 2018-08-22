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
#ifndef __applstdef_emC_h__
  /**This file should be included in the applstdef_emC.h. 
   * If this file is directly included, it needs the applstdef_emC.h. But the __guard__ 
   * should not be set firstly to include the MemC.h in the given order in applstddef.h
   */
  #include <applstdef_emC.h>
#endif
//The following include guard prevent twice include especially if appöstdefJc.h includes this file already.
#ifndef __fw_String_h__
#define __fw_String_h__


//NOTE: struct ObjectJc should be known for the StringBuilderJc, defined here.
//It is possible to include <incApplSpecific/applConv/ObjectJc_simple.h> in the <applstdef_emC.h> for the simple concept.
//instead. See usage of guards there.
#include <emC/Object_emC.h>

struct ObjectJc_t;
struct StringBuilderJc_t;
struct ThreadContext_emC_t;
struct MemAreaC_t;
struct Mtbl_CharSeqJc_t;



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
extern_C int strlen_emC(char const* text, int maxNrofChars);



/**Copies the src to the limited dst with preventing overflow and guaranteed 0-termination.
 * This is a alternate implementation of strncpy (it does not guaranteed a 0-termination)
 * and a alternate implementation of strlcpy from BSD (it does not count the maybe unused length of src).
 *
 * Copies maximal sizeDst-1 characters from src to dst but ends on a \0 chararcter in src. 
 * Ends the dst with a \0 in any case. Do nothing for the rest of bytes in dst till dst + sizeDst 
 * (no squandering of calculation time for unsued things).
 *
 * To concatenate Strings one can write:
 * char buffer[20];
 * char* dst = buffer;
 * int zdst = sizeof(buffer);
 * int zcpy = 0;
 * zdst -= zcpy = strlcpy_emC(dst, src1, zdst);
 * zdst -= zcpy = strlcpy_emC(dst += zcpy, src2, zdst);
 * zdst -= zcpy = strlcpy_emC(dst += zcpy, src3, zdst);
 * //etc.
 * If zdst is 0, nothing is done furthermore.
 *
 * @param dst A buffer to hold a 0-terminated C-string with at least sizeDst free bytes.
 * @param src C-String
 * @param size either number of use-able bytes from dst inclusive terminating \0. 
 *     Usual sizeof(dst) if dst is a char buffer[...]
 *     or the (desired number of character from src +1) if src is not 0-terminated. 
 *     In the last one case the application should consider that size <= sizeof(dst). 
 *     if sizeDst <=0, do nothing and returns 0.
 * @return The number of characters copied without ending \0 if the \0 in src was found 
       or == sizeDst if the \0 in src was not found (not copied till 0-end).
 *   The user can check: if(returnedvalue >= sizeDst){ //set flag it is truncated ...
 *   The return value is anytime a value between 0 and <=sizeDst, never <0 and never > sizeDst.
 *   The return value is the strlen(dst) if it is < sizeDst.
 */
extern_C int strcpy_emC(char* dst, char const* src, int sizeDst);


/**Searches a character inside a given string with terminated length.
 * NOTE: The standard-C doesn't contain such simple methods. strchr fails if the text isn't terminated with 0.
 */
extern_C int searchChar_emC(char const* text, int maxNrofChars, char cc);

/**Searches a String inside a given string with terminated length.
 * NOTE: The standard-C doesn't contain such simple methods. strstr fails if the text isn't terminated with 0.
 */
extern_C int searchString_emC(char const* text, int maxNrofChars, char const* ss, int zs);

/**Returns the number of chars which are whitespaces starting from text.
 * Whitespaces are all chars with code <=0x20. It are all control chars from the ASCII and the space. 
 */
extern_C int skipWhitespaces_emC(char const* text, int maxNrofChars);


/**Returns the number of chars which note whitespaces starting from end of text.
 * Whitespaces from begin or inside the text are not regarded.
 * Whitespaces are all chars with code <=0x20. It are all control chars from the ASCII and the space. 
 * @return length of text without right-bounded white-spaces.
 */
extern_C int trimRightWhitespaces_emC(char const* text, int maxNrofChars);


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
extern_C int parseIntRadix_emC(const char* src, int size, int radix, int* parsedChars);

extern_C float parseFloat_emC(const char* src, int size, int* parsedChars);

extern_C double parseDouble_emC(const char* src, int size, int* parsedChars);






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
 * The headerfile ,,emC/String_emC.h,, defines the type and some basicly functionalities
 * to use a StringJc-instance in a low independent level to refer a text..
 * This headerfile against that defines the typically String functionality,
 * which followes the [[sunJavadoc/java/lang/String]] class-functinality. 
 * But some enhancements are given, because the string processing in fast real time embedded systems
 * may work without dynamically memory too.
 *
 * Notation hint: The notation ,,char const*,, is the same as ,,const char*,,, but it expresses more stronly, that it is a const-pointer.
 * 
 */ 
#ifndef __StringJc_defined__  //NOTE: may be defined in ObjectJc.h too.
  typedef OS_PtrVal_DEF(StringJc, char const);

  #define __StringJc_defined__
#endif //ifdef isNull_StringJc

/**The memory layout of CharSeqJc is the same like StringJc. 
 * A StringJc is a CharSeqJc (is-a, inheritance).
 * But a CharSeqJc can be a reference to any instance which implements the methods of CharSeqJc.
 * In this header only the formalism of CharSeqJc are defined. To work with CharSeqJc in full capability,
 * include <Jc/StringJc.h> and compile Jc/StringJc.c.
 */
#define CharSeqJc StringJc

/**Returns true if the StringJc contains null. The user should use this macro instead straigtly using of the basicly definitions,
 * because the definition of OS_PtrValue and therefore the definition of StringJc is os-specific. 
 * @param STR StringJc-instance to test. The macro uses the instance directly.
 * @return true only if the text-reference is ,,null,,. false if it is an empty or non-empty text.
 */
#define isNull_StringJc(STR) (PTR_OS_PtrValue((STR), void*)==null)


#ifdef __NoCharSeqJcCapabilities__
  #define mMtbl_CharSeqJc 0
  #define kIsCharSeqJc_CharSeqJc 0
  #define kMaxNrofChars_StringJc (mLength__StringJc -2)
  #define mIsCharSeqJcMtbl_CharSeqJc 0
#else   

  /**Mask bits for position of method table of CharSequJc.
   * If mLength__StringJc == 0x3fff (default for 32 bit system), the mask is 0x0fff
   * The val info in a CharSeqJc will be 0x3000..0x3fff..
   * See [[kMaxLength_StringJc]], .
   */
  #define mMtbl_CharSeqJc (mLength__StringJc >>2)

  /**Designation of the String as CharSeqJc without a method table offset. In this case the reference refers a CharSeqJc and the length
   * should be gotten by invocation of [[length_CharSeqJc(...)]].
   * If mLength is defined with 0x3fff the value is 0x03ffe. mLength is defined os- and platform-depended in os_types_def.h
   */
  #define kIsCharSeqJc_CharSeqJc (mLength__StringJc -2)

  /**The limit for the length of a StringJc. It is derived from the platform-specific definition of ,,mLength__StringJc,, 
   * contained in the platform-specific ,,compl_adaption.h,,. 
   * If the ,,mLength_StringJc,, is defined with ,,0x3fff,, then this value is ,,0x2fff,,.
   * 
   * If a ,,StringJc,, is designated with this value for the ,,mLength__StringJc,, bits, then the length should be gotten 
   * on demand. The [[length_StringJc(...)]] regards that.  
   */
  #define kMaxNrofChars_StringJc ((mLength__StringJc & ~mMtbl_CharSeqJc)-1)

  /**Designation of the String as CharSeqJc maybe with a method table offset. In this case the reference refers a CharSeqJc and the length
   * should be gotten by invocation of [[length_CharSeqJc(...)]].
   * If mLength is defined with 0x3fff the value is 0x3000. mLength is defined os- and platform-depended in os_types_def.h
   */
  #define mIsCharSeqJcMtbl_CharSeqJc (mLength__StringJc & ~mMtbl_CharSeqJc)
#endif




/**Designation of the String as 0-terminated. In this case the length is calculated
 * using [[strlen_emC(...)]] before usage.
 * If mLength is defined with 0x3fff the value is 0x03fff. mLength is defined os- and platform-depended in os_types_def.h
 */
#define kIs_0_terminated_StringJc (mLength__StringJc)

/**Designation of the String as StringBuilderJc-instance. In this case the reference refers a StringBuilderJc and the length
 * should be gotten by invocation of length_StringBuilderJc(ref)
 * If mLength is defined with 0x3fff the value is 0x03ffd. mLength is defined os- and platform-depended in os_types_def.h
 */
#define kIsStringBuilder_CharSeqJc (mLength__StringJc -1)

/**If this Bit is set, the StringJc referenced the whole string of a StringBufferJc to concat strings.
 * If mLength is defined with 0x3fff the value is 0x04000. mLength is defined os- and platform-depended in os_types_def.h
 */
#define mNonPersists__StringJc       (mLength__StringJc +1)

/**If this Bit is set, the StringJc references a buffer in the thread context..
 * If mLength is defined with 0x3fff the value is 0x08000. mLength is defined os- and platform-depended in os_types_def.h
 */
#define mThreadContext__StringJc     ((mNonPersists__StringJc)<<1)




/**Initializer-Macro for constant StringJc, initialize the StringJc-reference to a zero-terminated text.
 * The length of the text
 * is not stored inside StringJc, the length bits are setted to there maximum 
 * (value of ,,mLength__StringJc,,, see ,,fw_Platform_conventions.h,,)
 * to detect this constellation.
 * @param TEXT should be a text-literal only. If it references a char-array, 
 *             a problem with persistence may existing.
 */
#define CONST_z_StringJc(TEXT) { TEXT, kIs_0_terminated_StringJc}

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
inline StringJc z_StringJc(char const* src)
{ StringJc ret;
  int size = strlen_emC(src, kMaxNrofChars_StringJc);
  set_OS_PtrValue(ret, src, size); 
  return ret;
}

#define s0_StringJc z_StringJc


/**Creates a StringJc-reference. The given src is either 0-terminated or has a length of at least max.
 * The String is dedicated as non-persistent, because this routine refers a buffer typically, which does not guarantees persistence.
 * This operation is proper if a char[] is hold in an array, and the string content should not be 0-terminated
 * if the buffer is used till max.
 */
inline StringJc zMax_StringJc(char const* src, int max)
{
  StringJc ret;
  if(max > kMaxNrofChars_StringJc){ 
    max = kMaxNrofChars_StringJc;   //limit it, only for abstruse situation.  
  }
  int size = strlen_emC(src, max);
  size |= mNonPersists__StringJc;
  set_OS_PtrValue(ret, src, size);
  return ret;
}






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
 * * If it is -1. then the length of src is count using [[[strlen_emC(...)]].
 * * If it is <= -2, the length of src is count and the length is shortenend by (-length+1). -2: The last char is truncated etc.  
 * @return StringJc-instance per value, it is hold in 2 register by most of C-compilers and therefore effective.
 */
inline StringJc zI_StringJc(char const* src, int len)
{ StringJc ret;
  if(len < 0){ len = strlen_emC(src, kMaxNrofChars_StringJc) - (-len) +1; } //nr of chars from end, -1 is till end. -2: without last char.
  else if(len >= mLength__StringJc) { len = mLength__StringJc -1; }  //limit it to max. 
  set_OS_PtrValue(ret, src, (len & mLength__StringJc)); 
  return ret;
}

#define s0i_StringJc zI_StringJc




#define isEmpty_s0_emC(TEXT) ((TEXT)==null || *(TEXT)==0)

int _length_PRIV_CharSeqJc(CharSeqJc thiz, struct ThreadContext_emC_t* _thCxt);


/**Returns the length. If the source stores the value kMaxLength__StringJc in its value-element,
 * the length is got calling ,,strlen(ptr),,. Otherwise the length is the value-element,
 * mask with mLength__StringJc, independent of the string itself. Note that the string may contain 0-chars
 * inside the given length.
 * @return The length of the string.
 */
inline int length_CharSeqJc(CharSeqJc thiz, struct ThreadContext_emC_t* _thCxt)  //INLINE
{
  int val = value_OS_PtrValue(thiz) & mLength__StringJc;
  if(val < kMaxNrofChars_StringJc) { 
    //simple form, inline, fast:
    return val;
  } else {
    //all other is too much for inline:
    return _length_PRIV_CharSeqJc(thiz, _thCxt);
  }
}






char _charAt_PRIV_CharSeqJc(CharSeqJc thiz, int pos, struct ThreadContext_emC_t* _thCxt);

/**Returns the character which is addressed with the position.
 * This method is inlined for checking whether thiz is a StringJc or a StringBuilderJc. Then it is a fast operation.
 * In the other cases the inner method ,,_charAt_PRIV_CharSeqJc(...),, will be invoked. 
 * That checks whether a index of the method table is given or the method table of any ObjectJc which implements the 
 */
inline char charAt_CharSeqJc(CharSeqJc thiz, int pos, struct ThreadContext_emC_t* _thCxt)
{
#ifndef __ignoreInCheader_zbnf__  //ignore following block while parsing, dont't ignore for C-Compilation!
  int val = value_OS_PtrValue(thiz) & mLength__StringJc;
  if(val < kMaxNrofChars_StringJc && pos < val) { 
    //simple form, inline, fast:
    return PTR_OS_PtrValue(thiz, char const)[pos];
  } else {
    //all other is too much for inline:
    return _charAt_PRIV_CharSeqJc(thiz, pos, _thCxt);
  }
#endif//__ignoreInCheader_zbnf__
}

#define charAt_StringJc(THIZ, POS) charAt_CharSeqJc(THIZ, POS, null)



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
#define lightCopy_StringJc(thiz, src) { *thiz = src; } //{(thiz)->s.refbase = (src).refbase; (thiz)->s.ref = (src).ref; }


/* Gets the char-pointer and the number of chars stored in a StringJc.
 * This is a common way to get a the content of a StringJc-Instance if a char-pointer is used.
 * It is a fast C-routine, because the StringJc is stored in CPU-registers, no memory is need.
 * The char-pointer is the same reference as in the StringJc. It may be persistent or not.
 * In generally, the user shouldn't store the reference persistently outside of the StringJc-concept.
 * The routine is given to support evaluating the chars in a C-like-way.
 * @param length destination variable (reference) to store the realy length. The destination variable will be set anytime.
 * @return the pointer to the chars. It may be null if the StringJc contains a null-reference.
 */
METHOD_C char const* getCharsAndLength_StringJc(StringJc const* thiz, int* length);



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
METHOD_C bool isZeroTerminated_StringJc(StringJc const thiz);



/**Copy the content to a given buffer.
 * 
 * If the returned length == maxSizeBuffer-1, it is not determined whether the text is truncated or not.
 * Note: if the src-text (thiz) contains 0-characters in its active area, they will be copied too as normal chars.
 * The text is not 0-terminated here. If neccesary you can get a 0-termination with the following statements:
 * ,,char buffer[100];
 * ,,int nchars = copyToBuffer_StringJc(myString, 0, -1, buffer, sizeof(buffer) -1);
 * ,,buffer[nchars] = 0; //because max 99 characters are copied, there is at least on space for the 0. 
 *
 * Note: thiz should a really StringJc or a reference to a StringBuilderJc on runtime.
 * If it is any reference to a CharSeqJc, use [[copyToBuffer_CharSeqJc]. That method regards simple Strings too.
 *
 * @param start start character in the StringJc.
 * @param end exclusive end position in StringJc. 
 *   If -1 then the whole StringJc till end should be copied. If <=-2 then (-end)-1 characters from end won't be copied. 
 * @param buffer The destination buffer as char[]
 * @param maxSizeBuffer The max number of chars copied. If the src text is longer, it will be truncated.
 * @return number of chars copied. It is the number of valid chars in buffer always.
*/
METHOD_C int copyToBuffer_CharSeqJc(const CharSeqJc thiz, int start, int end, char* buffer, int maxSizeBuffer, struct ThreadContext_emC_t* _thCxt);



/**Copy the content to a given buffer.
 * it should be guaranteed that thiz is a StringJc instance. If it is not so, an exception is thrown on runtime.
 * A StringJc does refer only to a immediate char const*. 
*
* @param start start character in the StringJc.
* @param end exclusive end position in StringJc.
*   If -1 then the whole StringJc till end should be copied. If <=-2 then (-end)-1 characters from end won't be copied.
* @param buffer The destination buffer as char[]
* @param maxSizeBuffer The max number of chars copied. If the src text is longer, it will be truncated.
* @return number of chars copied. It is the number of valid chars in buffer always.
*/
METHOD_C int copyToBuffer_StringJc(const CharSeqJc thiz, int start, int end, char* buffer, int maxSizeBuffer);

//old: #define copyToBuffer_StringJc(THIZ, START, END, BUFFER, SIZE) copyToBuffer_CharSeqJc(THIZ, START, END, BUFFER, SIZE, null)


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
 *        than the length is got from ,,strlen_emC(sCmp, mLength__StringJc),,,
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



/*@CLASS_C CharSeqJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


#ifndef __ObjectJc_simple__



extern_C struct Mtbl_CharSeqJc_t const* getMtbl_CharSeqJc(CharSeqJc thiz, struct ThreadContext_emC_t* _thCxt);


#endif

/*@CLASS_C StringBuilderJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#include <emC/Object_emC.h>


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


#ifndef StringBuilderJcREFDEF
  #define StringBuilderJcREFDEF
  #ifndef TYPE_EnhancedRefJc
    #error missing definition of TYPE_EnhancedRefJc, applstdef_emC.h should define that.
  #endif
  typedef TYPE_EnhancedRefJc(StringBuilderJc);
#endif


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



/**Constructs a StringBuilderJc with a given buffer.
 * The buffer will be cleared.
 * @param buffer any buffer
 * @param size characters in the buffer, sizeof(*buffer).
 */
METHOD_C void ctor_Buffer_StringBuilderJc(StringBuilderJc* thiz, char* buffer, int size);


/**Constructs a StringBuilderJc with a immediately following buffer.
 * The StringBuilderJc have to be organized in a struct definition with following pattern:
 * ,,StringBuilderJc mySb; char __addBuffer__[124]:
 * The data element ,,__addBuffer__,, should not used anywhere else.
 * 
 * The buffer will be cleared.
 * @param addSize the sizeof() of the immediately following buffer..
 */
METHOD_C void ctor_addSize_StringBuilderJc(StringBuilderJc* thiz, int addSize);


/**Gets the buffer as char* to use in C-Standard-Routines. 
 * The buffer content is zero-terminated always. 
 * @return 0-terminated content of buffer.
 */
METHOD_C char* chars_StringBuilderJc(StringBuilderJc* thiz);


/**Gets the buffer and the size of the buffer. 
 * @param size a ,,int*,, reference to a variable, into which the value of buffer-size is stored.
 * @return ,,char*,,-pointer to the buffer.
 */
METHOD_C char* getCharsAndSize_StringBuilderJc(StringBuilderJc* thiz, int* size);


/**Gets the buffer and the actual nr of chars in the buffer. 
 * @param count a ,,int*,, reference to a variable, into which the value of number of chars is stored.
 * @return ,,char*,,-pointer to the buffer.
 */
METHOD_C char* getCharsAndCount_StringBuilderJc(StringBuilderJc* thiz, int* count);

/**Gets the buffer, the size and the actual nr of chars in the buffer.
 * @param size a ,,int*,, reference to a variable, into which the value of buffer-size is stored.
 * @param count a ,,int*,, reference to a variable, into which the value of number of chars is stored.
 * @return ,,char*,,-pointer to the buffer.
 */
METHOD_C char* getCharsSizeCount_StringBuilderJc(StringBuilderJc* thiz, int* size, int* count);

/**Sets the nr of chars immediately. Only internal use. 
 * @param count actual number of chars.
 */
METHOD_C void _setCount_StringBuilderJc(StringBuilderJc* thiz, int count);


/**Returns the char at position idx.
 * @param index The index. It should be a positiv number and less than the length of the text.
 *        Because this is a fast access using a macro, the index in not tested. If the index is fault,
 *        an undefined value is returned. If the built position with this index is outside the memory area,
 *        an memory exception can be thrown. Therefore: Only use correct indices.
 * @return character at the position of text + idx.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#charAt(int)]] but a test of idx is not done.
 */
METHOD_C char charAt_StringBuilderJc(StringBuilderJc* ythis, int index, struct ThreadContext_emC_t* _thCxt);

/**Sets the char at position.
 * @param index The index. It should be a positiv number and less than the length of the text.
 * @param ch char to set.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#setCharAt(int, char)]].
 */
METHOD_C void setCharAt_StringBuilderJc(StringBuilderJc* ythis, int index, char ch, struct ThreadContext_emC_t* _thCxt);



/**Deletes the char at the given position. The text-length will be reduced by 1 char.
 * @param IDX position of char to delete.
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#deleteCharAt(int)]].
 * @macro It calls [[replace_zI_StringBuilderJc(...)]].
 */ 
#define deleteCharAt_StringBuilderJc(YTHIS, IDX, _THC) replace_zI_StringBuilderJc(YTHIS,IDX, IDX+1, null, 0, _THC)

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
METHOD_C void setLength_StringBuilderJc(StringBuilderJc* thiz, int newLength, struct ThreadContext_emC_t* _thCxt);
#define setLength_StringBufferJc setLength_StringBuilderJc

/**Clears the content. It is the same like setLength(0).
 * @see [[setLength_StringBuilderJc()]]
 * @javalike [[sunJavadoc/java/lang/StringBuilder#setLength(int)]] with 0 as parameter.
 */
METHOD_C void clear_StringBuilderJc(StringBuilderJc* thiz);
#define clear_StringBufferJc clear_StringBuilderJc






/**Gets the number of chars in buffer.
 * @return the number of chars without the terminating 0-char.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#length()]].
 */
#define length_StringBuilderJc(YTHIS) ((YTHIS)->_count)
//METHOD_C int length_StringBuilderJc(const StringBuilderJc* thiz, struct ThreadContext_emC_t* _thCxt);

/**Gets the size of buffer.
 * @return the maximal number of chars able to store in buffer. It is count without a 0-char at end. 
 *         It means, it is the physical size of buffer -1.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#capacity()]].
 */
METHOD_C int capacity_StringBuilderJc(StringBuilderJc* thiz);


/**Copies the text in the given buffer. Use the set mode of ,,setTruncateMode_StringBuilderJc(..),, 
 * to desire, whether an exception is thrown or the text will be truncated if the zBuffer is less.
 * @param buffer any buffer, where the content of thiz is copied to.
 * @param start start character in the string in the StringBuilderJc.
 * @param end exclusive end position in string in the StringBuilderJc. If -1 then the whole string till end should be copied.
 * @param zBuffer size of the buffer. The size should be the really size. A \\0 is guaranted at end of buffer.
 *                It means, the ,,length_StringBuilderJc(thiz),, should less as zBuffer, not equal.
 * @return number of chars without the terminating 0-char. The max value is ,,zBuffer -1,,.
 */
METHOD_C int copyToBuffer_StringBuilderJc(StringBuilderJc* thiz, int start, int end, char* buffer, int zBuffer);


/**Replaces the characters in a part of this sequence with characters in the specified String. 
 *
 * It is the core method to insert, append, replace, delete with a given ,,CharSeqJc,,. All those methods are implemented with this method.
 * @param pos The position where characters will will be deleted and inserted. Use -1 for append on end. Negative numbers counts the position from end.
 * @param end The position till characters will be removed. Use same value as pos or 0 if no characters should be deleted.
 *    Negative numbers counts the end position from the end of the buffer content.
 * @param add reference to the insertion text given in a CharSeqJc. 
 *    If a simple char* should be inserted, use [[z_CharSeqJc(...)]] or [[zI_CharSeqJc(...)]] to built the add
 * @param from start position inside the CharSeqJc for the insertion text. If negative then it counts from end. -2 is one char to end.
 * @param to end position inside the CharSeqJc. If equal from, especially both are null, then nothing will be inserted. 
 *    If negative then it is the neg. number of characters.
 * @throws StringIndexOutOfBoundsException if the pos, end, from, to are faulty or there is not enough capacity to insert.
 *    See [[_mNoException_StringBuilderJc]].
 * @javalike [[sunJavadoc/java/lang/StringBuilder#replace(int, int, java.lang.String)]].
 */
METHOD_C StringBuilderJc* replace_cII_StringBuilderJc(StringBuilderJc* ythis, int pos, int end, CharSeqJc value, int from, int to, struct ThreadContext_emC_t* _thCxt);




/**Inserts the text CharSeqJc into this sequence.
 *
 * @param pos - the offset.
 * @param value - an CharSeqJc. It is a CharSeqJc, a StringBuilderJc or any other class accessed via method table.
 * @param start index of the first char in value
 * @param end index after the last char in value
 * @return a reference to this object.
 * @throws StringIndexOutOfBoundsException - if the offset is invalid.
 * @see [[valueOf_I_StringJc(...)]]
 * @javalike [[sunJavadoc/java/lang/StringBuilder#insert(int, double)]].
 */
#define insert_cYii_StringBuilderJc(THIS, POS, ADD, FROM, TO, _THCXT) replace_cII_StringBuilderJc(THIS, POS, POS, ADD, FROM, TO, _THCXT) 
//METHOD_C StringBuilderJc* insert_cYii_StringBuilderJc(StringBuilderJc* ythis, int offset, CharSeqJc value, int start, int end, struct ThreadContext_emC_t* _thCxt);


/**Handle append(CharSequence) in the same way like append(String). distinghuish on runtime. */
#define append_c_StringBuilderJc(THIZ, VAL, THCXT) replace_cII_StringBuilderJc(THIZ, -1, -1, VAL, 0, -1, THCXT)  //insert_cYii_StringBuilderJc(THIZ, -1, VAL, 0, -1, THCXT) 


/**Appends a text at the end.
 * @param src ,,char const*,, text. The maximal detected length of the text is mLength__StringJc. Use it only for "literal".
 * @return this
 */
#define append_z_StringBuilderJc(YTHIS, src, _THC) replace_zI_StringBuilderJc(YTHIS, -1, -1, src, -1, _THC)
#define append_z_StringBufferJc append_z_StringBuilderJc
/** C-like: appends a character text with given length. */

/**Appends a text at the end.
 * @param src reference of type ,,char const*,, to the text to insert, may be null, than nothing is inserted idenendent of ,,len,,. 
 *            The text is not 0-terminated. ,,\0,,-chars are copied into the buffer without extra handling. 
 * @param lenSrc Number of chars to insert. It may be 0, than nothing is inserted independent of ,,add,,.
 * @return this
 */
#define append_zI_StringBuilderJc(YTHIS, src, lenSrc, _THC) replace_zI_StringBuilderJc(YTHIS, -1, -1, src, lenSrc, _THC)
#define append_zI_StringBufferJc append_zI_StringBuilderJc


/**Appends a text at the end.
 * @param src Reference to the text which will be append. It may be non-persistent.
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#append(java.lang.String)]]
 *        or [[sunJavadoc/java/lang/StringBuilder#insert(int, java.lang.CharSequence)]]
 *        The Relation to CharSequence is explained in the method [[insert_sII_StringBuilderJc(...)]].
 */ 
//METHOD_C StringBuilderJc* append_s_StringBuilderJc(StringBuilderJc* ythis, CharSeqJc src, struct ThreadContext_emC_t* _thCxt);
#define append_s_StringBuilderJc(thiz, src, _thCxt) replace_cII_StringBuilderJc(thiz, -1, -1, src, 0, -1, _thCxt)
#define append_s_StringBufferJc append_s_StringBuilderJc

#define append_c_StringBufferJc append_c_StringBuilderJc

/**Appends a text at the end.
 * @param src Reference to the text which will be append. It may be non-persistent.
 * @param start The starting index of the subsequence to be inserted.
 * @param end The end index of the subsequence to be inserted.
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#append(java.lang.String)]]
 *        or [[sunJavadoc/java/lang/StringBuilder#insert(int, java.lang.CharSequence)]]
 *        The Relation to CharSequence is explained in the method [[insert_sII_StringBuilderJc(...)]].
 */ 
#define append_sII_StringBuilderJc(thiz, add, start, end, _thCxt) replace_cII_StringBuilderJc(thiz, -1, -1, add, start, end, _thCxt)
//METHOD_C StringBuilderJc* append_sII_StringBuilderJc(StringBuilderJc* ythis, CharSeqJc src, int start, int end, struct ThreadContext_emC_t* _thCxt);
#define append_sII_StringBufferJc append_sII_StringBuilderJc


/**Appends the text of the given StringBuilder at the end.
 * @param src StringBuilder containing the text.
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#append(java.lang.StringBuffer)]]
 */ 
METHOD_C StringBuilderJc* append_u_StringBuilderJc(StringBuilderJc* ythis, StringBuilderJc* src, struct ThreadContext_emC_t* _thCxt);
#define append_u_StringBufferJc append_u_StringBuilderJc



/**Builds a CharSeqJc {ref, val} tupel from an instance of StringBuilderJc. 
 * The CharSeqJc {ref, val} tupel contains the reference to the StringBuilderJc-instance (ref)
 * and the designation with [[kIsStringBuilderJc_CharSeqJc]] in val.
 * The methods [[length_CharSeqJc(...)]] etc. detect this designation and invoke the proper methods of StringBuilderJc immediately
 * which runs fast.
 */
inline CharSeqJc toCharSeqJc_StringBuilderJc(struct StringBuilderJc_t const* thiz)
{ CharSeqJc ret;
  set_OS_PtrValue(ret, thiz, kIsStringBuilder_CharSeqJc); 
  return ret;
}


#define fromStringBuilderJc_CharSeqJc(THIZ) toCharSeqJc_StringBuilderJc(THIZ)


/*@inline @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**StringJc : Additional to StringJc after definiton of [[length_StringBuilderJc(...)]]. */

inline int length_StringJc(StringJc thiz)  //INLINE
{
  int val = value_OS_PtrValue(thiz) & mLength__StringJc;
  if (val < kMaxNrofChars_StringJc) {
    //simple form, inline, fast:
    return val;
  }
  else if (val == kIs_0_terminated_StringJc) {
    //assume it is 0-terminated.:
    return strlen_emC(thiz.ref, mLength__StringJc - 3);
  }
  else if (val == kIsStringBuilder_CharSeqJc) {
    return length_StringBuilderJc(PTR_OS_PtrValue(thiz, struct StringBuilderJc_t));
  }
  else {
    return 0; //not expected.
  }
}


/*@END*/





#endif //__fw_String_h__
