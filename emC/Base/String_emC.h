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
//The following include guard prevent twice include especially if appöstdefJc.h includes this file already.
#ifndef INCLUDED_emC_Base_String_emC_h
#define INCLUDED_emC_Base_String_emC_h


//NOTE: struct ObjectJc should be known for the StringBuilderJc_s, defined here.
//It is possible to include <emC_srcApplSpec/applConv/ObjectJc_simple.h> in the <applstdef_emC.h> for the simple concept.
//instead. See usage of guards there.
#include <emC/Base/Object_emC.h>

struct ObjectJc_t;
struct StringBuilderJc_t;
struct ThreadContext_emC_t;
struct MemAreaC_t;
struct Vtbl_CharSeqJc_t;


#ifndef HGUARD_emC_Base_StringBase_emC
  #include <emC/Base/StringBase_emC.h>
#endif


/**It is an extra type same as ObjectJc to mark the interface CharSeqObjJc. */
typedef struct { ObjectJc obj; } CharSeqObjJc;



/*@CLASS_C StringBuilderJc_s @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#include <emC/Base/Object_emC.h>


//#define staticSize_StringBuilderJc 80

/**A StringBuilderJc_s is a structure to manage char[]-arrays. 
 * It is derivated and adapted from the content of the java.lang.StringBuffer rsp. java.lang.StringBuilder.
 * Some Java-like methods are supplied, but not all, but some methods are additional 
 * and specifical for usages in C or C++.
 *
 * There are 2 forms of memory layout of this struct:
 * * a) The struct StringBuilderJc_s contains only the count, size and the pointer of the char[...]-buffer.
 * * b) The struct contains the char-buffer itself.
 *
 * The first variant is usefull especially if a C-like text buffer (char* with given size) is located anywhere
 * in the users data structures, and the StringBuilderJc_s-instance is only used temporary to assemble the text in the buffer.
 *
 * The last variant is possible either if a construct like
 *
 * , struct { StringBuilderJc_s b; char _b[46];} myBuilder = 
 * ,   CONST_addSizeStack_StringBuilderJc(&buffer.b, 50);
 *
 * is defined and initialized or if the [[ctorO_StringBuilderJc(...)]]-Constructor is called 
 * with an initialized ObjectJc with a size greater than sizeof(StringBuilderJc_s). It means more memory was allocated.
 * That variant needs only 1 memory block for the buffer management and the buffer itself.
 *
 * The StringBuilderJc_s-instance holds some flags such as ''located in the Thread Context'' or ''buffer is located in Stack''
 * and ''truncated'', see the appropriate methods. The internal attributes of this struct should not use immediately,
 * only the methods of this C-class should be used.
 *
 * '''Problem of reallocating a buffer''': In Java it's some more easier: Working with dynamically memory is usual, 
 * and the buffer is a private element of the StringBuilder. Therefore the buffer can be changed anytime, 
 * only a few amount of calculation time is need.
 *
 * But in C the StringBuilderJc_s is often associated with a determined buffer of the user. The user shows to its buffer,
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
  union{ ObjectJc object; CharSeqObjJc ifc_CharSeqObjJc; } base;

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
} StringBuilderJc_s;


#ifndef StringBuilderJcREFDEF
  #define StringBuilderJcREFDEF
  #ifndef TYPE_EnhancedRefJc
    #error missing definition of TYPE_EnhancedRefJc, applstdef_emC.h should define that.
  #endif
  typedef TYPE_EnhancedRefJc(StringBuilderJc);
#endif


#define sizeof_StringBuilderJc sizeof(StringBuilderJc_s)
#define sizeof_StringBufferJc sizeof_StringBuilderJc


#ifdef DEF_REFLECTION_NO
  #define ID_refl_StringBuilderJc 0x0ff6
#else
  extern_C const struct ClassJc_t refl_StringBuilderJc;
  #define refl_StringBuilderJc_s refl_StringBuilderJc
  #define refl_StringBufferJc refl_StringBuilderJc
#endif


//#define staticSize_StringBuilderJc (sizeof(((StringBuilderJc_s*)(0x1000))->value.direct))

/**This macro defines a C-constant (with {..}) for empty-initializing a StringBuffer instance with its static size.
 * @param OBJP Pointer to the instance itself. It is used to store the OWNADDRESS for the ObjectJc-part.
 */
#define CONST_StringBuilderJc(OBJP) { CONST_ObjectJc(sizeof(StringBuilderJc_s), &(OBJP)->base.object, null), 0, 0, null }


/**This macro defines a C-constant (with {..}) for initializing a StringBuffer instance with an additional size.
 * This macro is usefull if a StringBuffer with a following char array is defined 
 * to increase the size of the immediate text in buffer.
 * The definition of such an construct is possible inside a struct definition with followed sample:
 *
 * ,,struct { ... ; StringBuilderJc_s buffer; char bufferIncreasingCharArray[120]; ... } myData =
 *
 * The ,,bufferIncreasingCharArray,, have to be assembled immediately after the ,,buffer,,. 
 * The initializer of this part may be written in form of:
 *
 * ,,{ ... , CONST_addSize_StringBuilderJc(&myData.buffer, 120), { 0 }, ... },,
 *
 * The using of a following char array to increase the buffer is opportune to get a larger StringBuffer, 
 * because the compiler will always assigns the memory of the followed char array 
 * immediately after the previous element, the StringBuilderJc_s, and the own char array of the StringBuilderJc_s 
 * is assigned as the last element there. The problem of additional bytes because 4-Byte-allignment or such 
 * is not present, because a StringBuilderJc_s have a size of multiple 4 bytes.
 * But the user should define the size of the char array as multiple of 4 to prevent alignment problems also.
 *
 * Note: Outside a struct, the definition of elements one after another doesn't may assigned one after another in memory.
 * It differents from compiler versions or other conditions such as segmentation sizes of physical memory!
 *
 * @param OBJP Pointer to the instance itself. It is used to store the OWNADDRESS for the ObjectJc-part.
 * @param ADDSIZE The additional size of the StringBuffer, defined by sizeof the followed char array.
 */
#define INIZ_addSize_StringBuilderJc(OBJ, ADDSIZE) { { INIZ_ObjectJc(OBJ, refl_StringBuilderJc, 0)}, 0, sizeof((OBJ).value) + (ADDSIZE) -1, 0 }
#define CONST_addSize_StringBuilderJc(OBJP, ADDSIZE) { CONST_ObjectJc(sizeof(StringBuilderJc_s) + (ADDSIZE), &(OBJP)->base.object, null), 0, sizeof((OBJP)->value) + (ADDSIZE) -1, 0 }
//#define CONST_addSize_StringBuilderJc INIZ_addSize_StringBuilderJc

/**This macro defines a C-constant (with {..}) for initializing a StringBuffer instance with an additional size.
 * which is located in the Stack. See ,,CONST_addSize_StringBuilderJc(...),, 
 * It have to be used if the StringBuilderJc_s-instance is located in Stack. 
 * The mode bits ,,_mStack_StringBuilderJc,, is set. 
 * The definition of such an construct is recommended as astruct definition like following:
 *
 * struct { StringBuilderJc_s u; char _[120]; } uBuffer = { CONST_addSize_StringBuilderJc(&uBuffer.buffer, 120), { 0 }};
 *
 * The a StringBuilder with immediately buffer for 123 characters and a 0 on end is placed in the stack.
 * See macro INSTACK_StringBuilderJc(...).
 * @param OBJP The reference to the StringBuilder-instance itself
 * @param ADDSIZE size of the char[] after the StringBuilderJc_s-instance.
 */
#define CONST_addSizeStack_StringBuilderJc(OBJP, ADDSIZE) { { CONST_ObjectJc(sizeof(StringBuilderJc_s) + (ADDSIZE), &(OBJP)->base.object, null) }, 0, sizeof((OBJP)->value) + (ADDSIZE) -1, _mStack_StringBuilderJc}



/**This macro defines a StringBuffer instance with an additional size to locate in the stack.
 * which is located in the Stack. See ,,CONST_addSize_StringBuilderJc(...),, 
 * It have to be used if the StringBuilderJc_s-instance is located in Stack. 
 * The mode bits ,,_mStack_StringBuilderJc,, is set. 
 * The definition of such an construct is recommended as astruct definition like following:
 *
 * struct { StringBuilderJc_s b; char _[120]; } uBuffer = { CONST_addSize_StringBuilderJc(&uBuffer.buffer, 120), { 0 }};
 *
 * The a StringBuilder with immediately buffer for 123 characters and a 0 on end is placed in the stack.
 * See macro INSTACK_StringBuilderJc(...).
 * @param name The name of the StringBuilder-instance
 * @param chars number of chars inclusive the ending 0-char.
 */
#define INSTACK_StringBuilderJc(name, chars) struct { StringBuilderJc_s u; char _[chars-4]; } buffer = { CONST_addSizeStack_StringBuilderJc(&buffer.u, chars-4), {0}}



/**Constructs a StringBuilderJc_s with a given buffer.
 * The buffer will be cleared.
 * @param buffer any buffer
 * @param size characters in the buffer, sizeof(*buffer).
 */
extern_C void ctor_Buffer_StringBuilderJc ( StringBuilderJc_s* thiz, char* buffer, int size);


/**Constructs a StringBuilderJc_s with a immediately following buffer.
 * The StringBuilderJc_s have to be organized in a struct definition with following pattern:
 * ,,StringBuilderJc_s mySb; char __addBuffer__[124]:
 * The data element ,,__addBuffer__,, should not used anywhere else.
 * 
 * The buffer will be cleared.
 * @param addSize the sizeof() of the immediately following buffer..
 */
extern_C void ctor_addSize_StringBuilderJc (StringBuilderJc_s* thiz, int addSize);

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
extern_C StringBuilderJc_s* ctorO_StringBuilderJc(ObjectJc* othis, struct ThreadContext_emC_t* _thCxt);
#define ctorO_StringBufferJc ctorO_StringBuilderJc


/**Gets the buffer as char* to use in C-Standard-Routines. 
 * The buffer content is zero-terminated always. 
 * @return 0-terminated content of buffer.
 */
#define chars_StringBuilderJc(THIZ) ((THIZ)->size < 0 ? (THIZ)->value.buffer : (THIZ)->value.direct)


/**Gets the buffer and the size of the buffer. 
 * @param size a ,,int*,, reference to a variable, into which the value of buffer-size is stored.
 * @return ,,char*,,-pointer to the buffer.
 */
extern_C char* getCharsAndSize_StringBuilderJc (StringBuilderJc_s* thiz, int* size);


/**Gets the buffer and the actual nr of chars in the buffer. 
 * @param count a ,,int*,, reference to a variable, into which the value of number of chars is stored.
 * @return ,,char*,,-pointer to the buffer.
 */
extern_C char const* getCharsAndCount_StringBuilderJc (StringBuilderJc_s const* thiz, int* count);

/**Gets the buffer, the size and the actual nr of chars in the buffer.
 * @param size a ,,int*,, reference to a variable, into which the value of buffer-size is stored.
 * @param count a ,,int*,, reference to a variable, into which the value of number of chars is stored.
 * @return ,,char*,,-pointer to the buffer. It can be used to change for special cases.
 */
extern_C char* getCharsSizeCount_StringBuilderJc (StringBuilderJc_s* thiz, int* size, int* count);

/**Sets the nr of chars immediately. Only internal use. 
 * @param count actual number of chars.
 */
extern_C void _setCount_StringBuilderJc (StringBuilderJc_s* thiz, int count);


/**Returns the char at position idx.
 * @param index The index. It should be a positiv number and less than the length of the text.
 *        Because this is a fast access using a macro, the index in not tested. If the index is fault,
 *        an undefined value is returned. If the built position with this index is outside the memory area,
 *        an memory exception can be thrown. Therefore: Only use correct indices.
 * @return character at the position of text + idx.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#charAt(int)]] but a test of idx is not done.
 */
extern_C char charAt_StringBuilderJc (StringBuilderJc_s const* ythis, int index, struct ThreadContext_emC_t* _thCxt);

/**Sets the char at position.
 * @param index The index. It should be a positiv number and less than the length of the text.
 * @param ch char to set.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#setCharAt(int, char)]].
 */
extern_C void setCharAt_StringBuilderJc (StringBuilderJc_s* ythis, int index, char ch, struct ThreadContext_emC_t* _thCxt);



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
extern_C void setLength_StringBuilderJc (StringBuilderJc_s* thiz, int newLength, struct ThreadContext_emC_t* _thCxt);
#define setLength_StringBufferJc setLength_StringBuilderJc

/**Clears the content. It is the same like setLength(0).
 * @see [[setLength_StringBuilderJc()]]
 * @javalike [[sunJavadoc/java/lang/StringBuilder#setLength(int)]] with 0 as parameter.
 */
extern_C void clear_StringBuilderJc (StringBuilderJc_s* thiz);
#define clear_StringBufferJc clear_StringBuilderJc






/**Gets the number of chars in buffer.
 * @return the number of chars without the terminating 0-char.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#length()]].
 */
#define length_StringBuilderJc(YTHIS) ((YTHIS)->_count)
//extern_C int length_StringBuilderJc(const StringBuilderJc_s* thiz, struct ThreadContext_emC_t* _thCxt);

/**Gets the size of buffer.
 * @return the maximal number of chars able to store in buffer. It is count without a 0-char at end. 
 *         It means, it is the physical size of buffer -1.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#capacity()]].
 */
extern_C int capacity_StringBuilderJc (StringBuilderJc_s* thiz);


/**Copies the text in the given buffer. Use the set mode of ,,setTruncateMode_StringBuilderJc(..),, 
 * to desire, whether an exception is thrown or the text will be truncated if the zBuffer is less.
 * @param buffer any buffer, where the content of thiz is copied to.
 * @param start start character in the string in the StringBuilderJc_s.
 * @param end exclusive end position in string in the StringBuilderJc_s. If -1 then the whole string till end should be copied.
 * @param zBuffer size of the buffer. The size should be the really size. A \\0 is guaranted at end of buffer.
 *                It means, the ,,length_StringBuilderJc(thiz),, should less as zBuffer, not equal.
 * @return number of chars without the terminating 0-char. The max value is ,,zBuffer -1,,.
 */
extern_C int copyToBuffer_StringBuilderJc (StringBuilderJc_s const* thiz, int start, int end, char* buffer, int zBuffer);


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
extern_C StringBuilderJc_s* replace_cII_StringBuilderJc (StringBuilderJc_s* ythis, int pos, int end, CharSeqJc value, int from, int to, struct ThreadContext_emC_t* _thCxt);




/**Inserts the text CharSeqJc into this sequence.
 *
 * @param pos - the offset.
 * @param value - an CharSeqJc. It is a CharSeqJc, a StringBuilderJc_s or any other class accessed via method table.
 * @param start index of the first char in value
 * @param end index after the last char in value
 * @return a reference to this object.
 * @throws StringIndexOutOfBoundsException - if the offset is invalid.
 * @see [[valueOf_I_StringJc(...)]]
 * @javalike [[sunJavadoc/java/lang/StringBuilder#insert(int, double)]].
 */
#define insert_cYii_StringBuilderJc(THIS, POS, ADD, FROM, TO, _THCXT) replace_cII_StringBuilderJc(THIS, POS, POS, ADD, FROM, TO, _THCXT) 
//extern_C StringBuilderJc_s* insert_cYii_StringBuilderJc(StringBuilderJc_s* ythis, int offset, CharSeqJc value, int start, int end, struct ThreadContext_emC_t* _thCxt);


/**Handle append(CharSequence) in the same way like append(String). distinghuish on runtime. */
#define append_c_StringBuilderJc(THIZ, VAL, THCXT) replace_cII_StringBuilderJc(THIZ, -1, -1, VAL, 0, -1, THCXT)  //insert_cYii_StringBuilderJc(THIZ, -1, VAL, 0, -1, THCXT) 


/**Appends a text at the end.
 * @param src ,,char const*,, text. The maximal detected length of the text is mLength_StringJc. Use it only for "literal".
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
//extern_C StringBuilderJc_s* append_s_StringBuilderJc(StringBuilderJc_s* ythis, CharSeqJc src, struct ThreadContext_emC_t* _thCxt);
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
//extern_C StringBuilderJc_s* append_sII_StringBuilderJc(StringBuilderJc_s* ythis, CharSeqJc src, int start, int end, struct ThreadContext_emC_t* _thCxt);
#define append_sII_StringBufferJc append_sII_StringBuilderJc


/**Appends the text of the given StringBuilder at the end.
 * @param src StringBuilder containing the text.
 * @return this.
 * @javalike [[sunJavadoc/java/lang/StringBuilder#append(java.lang.StringBuffer)]]
 */ 
extern_C StringBuilderJc_s* append_u_StringBuilderJc (StringBuilderJc_s* ythis, StringBuilderJc_s const* src, struct ThreadContext_emC_t* _thCxt);
#define append_u_StringBufferJc append_u_StringBuilderJc



/**Builds a CharSeqJc {ref, val} tupel from an instance of StringBuilderJc_s. 
 * The CharSeqJc {ref, val} tupel contains the reference to the StringBuilderJc_s-instance (ref)
 * and the designation with [[kIsStringBuilderJc_CharSeqJc]] in val.
 * The methods [[length_CharSeqJc(...)]] etc. detect this designation and invoke the proper methods of StringBuilderJc_s immediately
 * which runs fast.
 */
INLINE_emC CharSeqJc toCharSeqJc_StringBuilderJc (struct StringBuilderJc_t const* thiz)
{ CharSeqJc ret;
  SET_StringJc(ret, (char const*)thiz, kIsStringBuilder_CharSeqJc); 
  //ret.addr.bu = thiz;
  //ret.val = kIsStringBuilder_CharSeqJc; 
  return ret;
}


#define fromStringBuilderJc_CharSeqJc(THIZ) toCharSeqJc_StringBuilderJc(THIZ)




/*@CLASS_C CharSeqJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

//This routines are the basic for StringJc too, do not exclude with __NoCharSeqJcCapabilities__.
//The implementing routines _...PRIV... are empty for __NoCharSeqJcCapabilities__ because there are never called.

int _length_PRIV_CharSeqJc(CharSeqJc thiz, struct ThreadContext_emC_t* _thCxt);

/**Returns the length. If the source stores the value kMaxLength__StringJc in its value-element,
* the length is got calling ,,strlen(ptr),,. Otherwise the length is the value-element,
* mask with mLength_StringJc, independent of the string itself. Note that the string may contain 0-chars
* inside the given length.
* @return The length of the string.
*/
INLINE_emC int length_CharSeqJc(CharSeqJc thiz, struct ThreadContext_emC_t* _thCxt)  //INLINE
{
#ifndef __ignoreInCheader_zbnf__  //ignore following block while parsing, dont't ignore for C-Compilation!
  int val = thiz.val & mLength_StringJc;
  if (val < kMaxNrofChars_StringJc) {
    //simple form, inline, fast:
    return val;
  }
  else if (val == kIs_0_terminated_StringJc) {
    //assume it is 0-terminated.:
    return strnlen_emC(thiz.addr.str, mLength_StringJc - 3);
  }
#ifndef DEF_ONLY_CHAR_StringJc
  else if (val == kIsStringBuilder_CharSeqJc) {
    return length_StringBuilderJc(thiz.addr.bu);
  }
  else {
    //all other is too much for inline:
    return _length_PRIV_CharSeqJc(thiz, _thCxt);
  }
#endif//DEF_ONLY_CHAR_StringJc
#endif//__ignoreInCheader_zbnf__
}






char _charAt_PRIV_CharSeqJc(CharSeqJc thiz, int pos, struct ThreadContext_emC_t* _thCxt);

/**Returns the character which is addressed with the position.
* This method is inlined for checking whether thiz is a StringJc or a StringBuilderJc_s. Then it is a fast operation.
* In the other cases the inner method ,,_charAt_PRIV_CharSeqJc(...),, will be invoked.
* That checks whether a index of the method table is given or the method table of any ObjectJc which implements the
*/
INLINE_emC char charAt_CharSeqJc(CharSeqJc thiz, int pos, struct ThreadContext_emC_t* _thCxt)
{
#ifndef __ignoreInCheader_zbnf__  //ignore following block while parsing, dont't ignore for C-Compilation!
  int val = thiz.val & mLength_StringJc;
  if (val < kMaxNrofChars_StringJc && pos < val) {
    //simple form, inline, fast:
    return thiz.addr.str[pos];
  }
  else {
    //all other is too much for inline:
    return _charAt_PRIV_CharSeqJc(thiz, pos, _thCxt);
  }
#endif//__ignoreInCheader_zbnf__
}




/**Copy the content to a given buffer.
 * 
 * If the returned length == maxSizeBuffer-1, it is not determined whether the text is truncated or not.
 * Note: if the src-text (thiz) contains 0-characters in its active area, they will be copied too as normal chars.
 * The text is not 0-terminated here. If neccesary you can get a 0-termination with the following statements:
 * ,,char buffer[100];
 * ,,int nchars = copyToBuffer_StringJc(myString, 0, -1, buffer, sizeof(buffer) -1);
 * ,,buffer[nchars] = 0; //because max 99 characters are copied, there is at least on space for the 0. 
 *
 * Note: thiz should a really StringJc or a reference to a StringBuilderJc_s on runtime.
 * If it is any reference to a CharSeqJc, use [[copyToBuffer_CharSeqJc]. That method regards simple Strings too.
 *
 * @param start start character in the StringJc.
 * @param end exclusive end position in StringJc. 
 *   If -1 then the whole StringJc till end should be copied. If <=-2 then (-end)-1 characters from end won't be copied. 
 * @param buffer The destination buffer as char[]
 * @param maxSizeBuffer The max number of chars copied. If the src text is longer, it will be truncated.
 * @return number of chars copied. It is the number of valid chars in buffer always.
*/
extern_C int copyToBuffer_CharSeqJc ( const CharSeqJc thiz, int start, int end, char* buffer, int maxSizeBuffer, struct ThreadContext_emC_t* _thCxt);





extern_C struct Vtbl_CharSeqJc_t const* getVtbl_CharSeqJc(CharSeqJc thiz, struct ThreadContext_emC_t* _thCxt);






/*@inline @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**StringJc : Additional to StringJc after definiton of [[length_StringBuilderJc(...)]]. */





/*@END*/





#endif //INCLUDED_emC_Base_String_emC_h
