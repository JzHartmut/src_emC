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
 * @content
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 *
 * @version 0.83
 **This file is referenced to the java2c-translated MsgDispatcher_MSG.h/c */
#include "emC/VaArgBuffer_emC.h"
//
#include "emC/Formatter_emC.h"
#include <string.h>


VaArgBuffer* ctorM_VaArgBuffer(MemC mthis, int size, ThCxt* _thCxt)
{ VaArgBuffer* ythis = PTR_MemC(mthis, VaArgBuffer);
  STACKTRC_TENTRY("ctor_VaArgBuffer");
  checkSize_MemC(mthis, sizeof(VaArgBuffer), _thCxt);
  clean_VaArgBuffer(ythis, _thCxt);
  STACKTRC_LEAVE; return ythis;
}


static MemUnit* copyString_VaArgBuffer(VaArgBuffer* ythis, MemUnit* dst, char const* text, int nrofChars, char* typeArgs)
{
  if(typeArgs[1] == 0)
  { int nrofChars = ( (((MemUnit*)&ythis->data) + sizeof(ythis->data)) - dst) -1;
    strcpy_emC((char*)dst, text, nrofChars);
    ((char*)dst)[nrofChars] = 0;
    dst += nrofChars +1;
    *typeArgs = '$';  //direct 0-terminated string.
  }
  else
  { strcpy_emC((char*)dst, text, 8);
    dst += 8;
    *typeArgs = '1';  //direct string 1 unit = 8 chars.
  }
  return dst;
}








void copyFrom_VaArgBuffer(VaArgBuffer* ythis, char const* formatText, Va_listFW src, ThCxt* _thCxt)
{ va_list src_args = src.args;
  if(src.typeArgs != null)
  { strcpy_emC(ythis->sType, src.typeArgs, sizeof(ythis->sType));
  }
  else if(src.typeArgs == null && strstr(formatText, "%s")!=null)
  { /**no types are given, activity only if the argument list contains a %s,
     * because elsewhere ...
     */
    memset(ythis->sType, 0,sizeof(ythis->sType));
    detectTypeArgs_fwFormatter(ythis->sType, sizeof(ythis->sType)-1, z_StringJc(formatText));
  }
  else
  { /**No typeinfo available. */
    ythis->sType[0] = '?';
  }
  { char* typeArgs = ythis->sType;  //The description to the content of ythis->data!
    int parNrString;
    MemUnit* dst;

    if(typeArgs[ parNrString=strcspn(typeArgs, "Sz") ] !=0)
    { //NOTE: strcspn returns strlen(typeargs) if the chars aren't found.
      //any const char* inside text
      if(typeArgs[parNrString+1] == 0)
      { //a often case: the last arg is a string:
    
      }
      else
      { //the string is at any position
      }
      dst = (MemUnit*)&ythis->data;
      while(*typeArgs != 0)
      { char const* srcToCopy;
        int nrofCharsToCopy;
        switch(*typeArgs)
        { case 'C': *((char_va_list*)dst) = va_arg(src_args, char_va_list); dst += sizeof(char_va_list); break; 
          case 'Z': *((bool_va_list*)dst) = va_arg(src_args, bool_va_list); dst += sizeof(bool_va_list); break; 
          case 'B': *((int8_va_list*)dst) = va_arg(src_args, int8_va_list); dst += sizeof(int8_va_list); break;
          case 'S': *((int16_va_list*)dst) = va_arg(src_args, int16_va_list); dst += sizeof(int16_va_list); break; 
          case 'I': *((int32*)dst) = va_arg(src_args, int32); dst += sizeof(int32); break; 
          case 'J': *((int64*)dst) = va_arg(src_args, int64); dst += sizeof(int64); break; 
          case 'F': *((float_va_list*)dst) = va_arg(src_args, char_va_list); dst += sizeof(char_va_list); break; 
          case 'D': *((double*)dst) = va_arg(src_args, double); dst += sizeof(double); break; 
          case 'P': *((void**)dst) = va_arg(src_args, void*); dst += sizeof(void*); break; 
          case 's': { StringJc arg = va_arg(src_args, StringJc); 
                      srcToCopy = getCharsAndLength_StringJc(&arg, &nrofCharsToCopy);
                      dst = copyString_VaArgBuffer(ythis, dst, srcToCopy, nrofCharsToCopy, typeArgs); 
                    } break;
          case 'z': { srcToCopy = va_arg(src_args, char const*); 
                      if(srcToCopy == null)
                      { srcToCopy = "(null)";
                      }
                      nrofCharsToCopy = strlen(srcToCopy);
                      dst = copyString_VaArgBuffer(ythis, dst, srcToCopy, nrofCharsToCopy, typeArgs); 
                    } break;
          default : *((int*)dst) = va_arg(src_args, int); dst += sizeof(int); break; 
        }
        typeArgs +=1;  //next char  
      }
    }
    else
    { //No string argument in the list, it is the most standard case. 
      //Copy the stack content in the buffer.
      if(src_args != null) //if no pointer is given, no arguments are supplied.
      { ythis->data = va_arg(src_args, VaArgBuffer_Data_s);  //it is a memcpy, because struct copy from stack.
      }
      else
      { ASSERTJc_TEST(src.typeArgs == null || *src.typeArgs == 0); //typeArgs should be empty also! All others is a software error. Exception warrantable.
      }
    }
  }
}



/**Gets a variable argument list from a buffer, not from stack. */
Va_listFW get_va_list_VaArgBuffer(VaArgBuffer* ythis, ThCxt* _thCxt)
{ Va_listFW typedArgs;
  va_list args;
  //GNU-CC: error, va_start(args, ythis->sType);
  args = (va_list)(ythis->data.v);  //simple & easy, va_list is a pointer to the poor values.
  typedArgs.args = args;
  typedArgs.typeArgs = ythis->sType[0] == '?' ? null: ythis->sType;
  return typedArgs;
}


void clean_VaArgBuffer(VaArgBuffer* ythis, ThCxt* _thCxt)
{
  memset(&ythis->data, 0, sizeof(ythis->data));
}



METHOD_C void setArg_VaArgBuffer(VaArgBuffer* thiz, int32_t ix, int32_t val, ThCxt* _thCxt){
  thiz->sType[ix] = 'I';
  thiz->data.v[ix] = val;
}

#include "genRefl/emC/VaArgBuffer_emC.crefl"



