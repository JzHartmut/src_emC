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
 * @version 0.92
 * @content Definition of access for network payload data.
 * list of changes:
 * 2011-11-08; Hartmut use notification int32_t instead int32 etc. It is the C99-standard. 
 * 2009-11-24: Hartmut created as new idea.
 *
 ****************************************************************************/

#ifndef HGUARD_emCBase__Endianness
#define HGUARD_emCBase__Endianness

#include <applstdef_emC.h>  //This os-specific header should contain the definition of BIGENDIAN or LITTLEENDIAN

extern_C_BLOCK_

#if defined(OSAL_BIGENDIAN)



  #define int64BigEndian int64

  #define int32BigEndian int32

  #define int16BigEndian int16

  #define floatBigEndian float

  #define doubleBigEndian double

  #define ptrBigEndian void*

  typedef union Endianess32_16_emC_T { int32 v32; struct { int16 hi, lo; } v16;} Endianess32_16_emC_s;

#elif defined(OSAL_LITTLEENDIAN)


  /**All big-endian-types are define as struct, don't access it immediately. */
  typedef struct int64BigEndian_t { int32 hiBigEndian__; int32 loBigEndian__; }GNU_PACKED int64BigEndian;

  typedef struct uint64BigEndian_t { uint32 hiBigEndian__; uint32 loBigEndian__; }GNU_PACKED uint64BigEndian;

  typedef struct int32BigEndian_t { int32 loBigEndian__; }GNU_PACKED  int32BigEndian;

  typedef struct uint32BigEndian_t { uint32 loBigEndian__; }GNU_PACKED  uint32BigEndian;

  typedef struct int16BigEndian_t { int16 loBigEndian__; }GNU_PACKED  int16BigEndian;

  typedef struct floatBigEndian_t { int32 floatBigEndian__; }GNU_PACKED  floatBigEndian;

  typedef struct doubleBigEndian_t { int32 hiBigEndian__; int32 loBigEndian__; }GNU_PACKED  doubleBigEndian;

  typedef struct ptrBigEndian_t { void* ptrBigEndian__; }GNU_PACKED  ptrBigEndian;

  typedef union Endianess32_16_emC_T { int32 v32; struct { int16 lo, hi; } v16;} Endianess32_16_emC_s;


#else
  #error either OSAL_BIGENDIAN or OSAL_LITTLEENDIAN should be defined.
#endif


#if defined(OSAL_LITTLEENDIAN) || defined(OSAL_MEMWORDBOUND)
  /**Access routines to net payload are necessary either for little endian, 
   * or if the memory organisation disallows a word boundary on non-word-addresses.
   * At example writing a int32 on a address 0x1005 is disallowed (not able to divide by sizeof(int32).
   */

  /**Use methods, because only 1 access to the memory should be done. */
  int64 getInt64BigEndian ( int64BigEndian const* addr);
  
  int32 getInt32BigEndian ( int32BigEndian const* addr);
  
  int16 getInt16BigEndian ( int16BigEndian const* addr);

  float getFloatBigEndian ( floatBigEndian const* addr);

  double getDoubleBigEndian ( doubleBigEndian const* addr);

  void* getPtrBigEndian ( ptrBigEndian const* addr);

  int64 setInt64BigEndian ( int64BigEndian* addr, int64 value);

  int32 setInt32BigEndian ( int32BigEndian* addr, int32 value);

  uint32 setUint32BigEndian ( uint32BigEndian* addr, uint32 value);

  int16 setInt16BigEndian ( int16BigEndian* addr, int16 value);

  float setFloatBigEndian ( floatBigEndian* addr, float value);

  double setDoubleBigEndian ( doubleBigEndian* addr, double value);


  /**The input is an void const*, because const pointer should be supported without any additinal effort.
   */
  void* setPtrBigEndian ( ptrBigEndian* addr, void const* value);

#else
  /**Big endian memory type with possibility to access any address with any word length: 
   * it is only a simple access.
   */
  #define getInt64BigEndian(PTR) (*((int64*)(PTR)))

  #define getInt32BigEndian(PTR) (*((int32*)(PTR)))

  #define getInt16BigEndian(PTR) (*((int16*)(PTR)))

  #define getFloatBigEndian(PTR) (*((float*)(PTR)))

  #define getDoubleBigEndian(PTR) (*((double*)(PTR)))

  #define getPtrBigEndian(PTR) (*((void**)(PTR)))

  #define setInt64BigEndian(PTR, VAL)  (*((int64*)(PTR)) = VAL)

  #define setInt32BigEndian(PTR, VAL)  (*((int32*)(PTR)) = VAL)

  #define setInt16BigEndian(PTR, VAL)  (*((int16*)(PTR)) = VAL)

  #define setFloatBigEndian(PTR, VAL)  (*((float*)(PTR)) = VAL)

  #define setDoubleBigEndian(PTR, VAL)  (*((double*)(PTR)) = VAL)

  #define setPtrBigEndian(PTR, VAL)  (*((void const**)(PTR)) = VAL)

#endif

_END_extern_C_BLOCK

#endif //HGUARD_emCBase__Endianness
