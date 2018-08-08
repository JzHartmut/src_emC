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
**end copyright***************************************************************************************
*
* This file contains only operations without dependencies to other CRJ files. 
*/
#include <applstdefJc.h>
#include <Fwc/objectBaseC.h>
#include <Fwc/fw_String.h>
#include <string.h>  //C-standard

//Note: Implementation to search \0 in an limited range. 
int strlen_Fwc(char const* text, int maxNrofChars)
{ register char const* text1 = text;
  register char const* text9 = text + maxNrofChars;
  //optimization: test only one pointer register, which is incremented too
  while(text1 < text9 && *text1 != 0){ text1+=1;}
  return (text1 - text);
}




bool equals_zI_StringJc(const StringJc ythis, const char* strCmp, int valueCmp  )
{ int countThis = VAL_StringJc(ythis) & mLength__StringJc; 
  int countCmp = valueCmp & mLength__StringJc;
  const char* strThis = PTR_StringJc(ythis);
  if(countThis == mLength__StringJc){
    countThis = strlen_Fwc(strThis, mLength__StringJc);
  }
  if(countCmp == mLength__StringJc){
    countCmp = strlen_Fwc(strCmp, countThis+1);
  }
  if(countCmp != countThis)
  { return(false);
  }
  else if(strThis == strCmp){
    return true;  //same length and same addresses of text.
  }
  else
  { bool bRet = memcmp(strThis, strCmp, countCmp) == 0;
    return(bRet);
  }
}


