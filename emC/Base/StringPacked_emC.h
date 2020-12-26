#ifndef HGUARD_emC_Base_StringPacked_emC
#define HGUARD_emC_Base_StringPacked_emC
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
 * @content Packed strings are only a topic of interest for CPUs which have not a byte addressing in memory.
 * For example some TI processors have a 16-bit-word adressing, and some ADSP processors have a 32-bit-widht adressing.
 * This is sufficient and efficient for numerical operations which are typical for that processors.
 * It reduces costs of hardware on the chip.
 * Strings are stored as string literals with one character per memory location. It means that a string is not packed to bytes.
 * This is not a problem, and it is compliant to C standards, if the strings are only used locally on the processors space.
 *
 * But if the strings are communicated with other processors, and the communication is based on a memory image,
 * the other processor receives the non-packed strings in its memory (from telegram payload or immediately access).
 * If the other processor has a different memory access approach, usual bytewise (for PC) the interpretation of the strings is disturbed.
 *
 * Hence, for this strings, used in communication, a packed format is necessary.
 * It means, if the address width is 32 bit, one address position on memory contains 4 characters.
 * It supposed, that 8 bit characters are used in the communication, which is true for standard-ASCII, UTF8, some more encodings,
 * but not for UTF16. UTF16 can be handled simple, but should not be confused with standard string literals which are usual US-ASCII or UTF8.
 *
 * This source contains conversion and compare routines for packed Strings. It runs on any memory access approach in a compatible kind.
 * It uses the MemUnit as type of the string which addresses always one memory location, independent of its length.
 * on a memory location 1, 2 or 4 characters are stored for 8, 16 and 32 bit memory addressing.
 *
 * @author Hartmut Schorrig
 * @created 2020-12-18,
 * @changes
 *************************************************************************************************/
#ifndef HGUARD_compl_adaption
  #include <compl_adaption.h>
#endif


/** get a character instead the simple access to text[ix] for non packed strings.
 */
static inline char getCharPacked ( MemUnit const* text, int ix) {
  MemUnit val = text[ ix / BYTE_IN_MemUnit];
  int byte = ix % BYTE_IN_MemUnit;     //always 0 in byte adressing, optimized for byte processors.
  return (char)( val >> (8*byte));  //do not shift in byte addressing, optimized for byte processors.

}


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
extern_C int strnlenPacked_emC ( MemUnit const* text, int maxNrofChars);

/**Compares two strings with a given maximum of chars.
 * @arg maxNrofChars If no zero terminated strings should be compare, it is the length of both strings.
 *     In this case a different length of Strings should be checked before, and the length difference
 *     can be used as result already.
 * @return ==0 if both strings are equal till maxNrofChars or both have a '\0'.
 *    >0 if text2 > text1 (longer or character code higher) whereby the value is the position of the first difference in text2.
 *    <0 if text1 > text2 (longer or character code higher) whereby the absolute value is the position of the first difference in text2.
 */
extern_C int strncmpPacked_emC ( MemUnit const* const text1, char const* const text2, int const maxNrofChars);





#endif //HGUARD_emC_Base_StringPacked_emC
