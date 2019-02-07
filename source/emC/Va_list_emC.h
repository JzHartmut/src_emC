#ifndef __fw_Va_list_h__
#define __fw_Va_list_h__

//#include <stdarg.h>


/* @ CLASS_C Va_listFW @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This struct fuses a variable argument list defined in standard-C with a string,
 * which contains one char per type in variable argument list.
 * The following chars should be used to sign the types:
 * * Z boolean
 * * C a char
 * * F float, 32 bit
 * * D double, 64 bit
 * * B a byte
 * * S int16
 * * I int32 
 * * J int64
 * * L ObjectJc*
 * * K, M, N int32, an special index
 * * P void* pointer of 32 bit
 * * Q void* large pointer (32 bit + segment)  //TODO
 * * R void* near pointer //TODO
 * * ? unknown
 * * z char* zero-terminated String
 * * s instance of StringJc
 * * 1 char[8]: direct up to 8 chars.
 * * 2 ..8 char[16] .. char[64]
 * * $ char[..] direct chars zero terminated. It is the last member anytime.
 * * t instance of OS_TimeStamp 
 */ 
typedef struct Va_listFW_t
{ 
/**Zero terminated string of type chars. */
  char const* typeArgs;

  /**Variable arguments. The type va_list is defined in Standard-c-,,stdarg.h,,.
   * This type is platform/compiler dependend, mostly a char*.
   * The image of types in the variable argument list is platform/comiler dependend,
   * to get the values use va_arg(args, TYPE) defined in ,,stdarg.h,,,
   * where type is one of the types defined in ,,os_types_def.h,,
   * * int8_va_list instead int8
   * * int16_va_list instead int16
   * * float_va_list instead float
   * * bool_va_list instead bool
   * * char_va_list instead char
   * The reason to use the special types: In a variable argument list 
   * the compiler casts types with less bytes in wide types to prevent a mix up of types
   * because automatically type conversions are possible.
   * But for an evaluation of content the types e.g. float and double may be differented well.
   */
  va_list args;
} Va_listFW;

#define CONST_Va_listFW(args) {args, null}

#define size_Va_listFW(args) (strlen(args.typeArgs)) 

//Va_listFW* ctorM_Va_listFW(MemC mthis, 


/**This identifier can be used instead a name in Rhapsody's method parameter definition. 
 * It is empty for compilation. The type in Rhapsody is ,,...,, like in C
 */
#define VA_LIST_PARAM 
#endif //__fw_Va_list_h__

