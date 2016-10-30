#ifndef __InspcTargetTelg_h__
#define __InspcTargetTelg_h__
#include <os_types_def.h>
#include <os_endian.h>  //supports both big endian conversion and access to even address on memory.

#include "InspcTargetProxyTelg.h"


/**This struct describes the common head of any telegram for inspector communication. 16 Byte. */
typedef struct InspcTelgHead_Inspc_t
{
  /**Nr of bytes of this telegram. */
  int16BigEndian nrofBytes;

  /**The command is a version identificator too. A new version uses new command constants. 
   * That is used as BOM (Byte Order Mark) too: 
   * * A big endian command sets its bit15 to 0 anyway. It means the bit 7 in the first byte is 0.
   * * A little endian command sets its bit 7 to 1. It means the bit 7 in the first byte is 1. 
   */
  int16BigEndian cmdTelg;

  #define mLittleEndianCmdTelg_Inspc 0x0080;

  /**A number to support an encryption. For future extensions. */
  int32BigEndian encryption;

  /**The sequence number of this telegram. The request and the answer have the same sequence number. */
  int32BigEndian seqnr;

  /**A answer number if the answer uses more as one telegram. */
  int16BigEndian answernr;

  /**Distinction if more as one service is used with the same port of communication. */ 
  int16BigEndian entrant;


} InspcTelgHead_Inspc_s;






#endif //__InspcTargetTelg_h__
