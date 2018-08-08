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
 * 4) But the LPGL is not appropriate for a whole software product,
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
 * Description:
 * This file contains simple C routines which stores exception information in a data struct 
 * without an extra mechanism to store in a file, communicate etc.
 * It is intended to read out the exceptin data with a low level debugging tool (memory access)
 * or especially with the inspector communication if it is integrated in the target anyway.
 * To read out another special mechanism can be used too.
 * This source can be copied and adapted in the application. 
 * Copy it before change. Do not change the sources inside the CRuntimeJavalike source area.
  
 * @author Hartmut Schorrig www.vishia.org
 * creation: 2017-04-07
 * changes:
 *
 ****************************************************************************/

#include <applstdef_emC.h>  //should contain all definition for exception handling.


ExceptionJc exceptionArray_ExceptionJc[20];


void throw_sJc_(char const* exceptionNr, StringJc msg, int value, int line)
{
}



void throw_s0Jc_(char const* exceptionNr, const char* msg, int value, int line)
{
}


char const* errorFile;

int errorFileline = -1;

char const* errorText;


void assertJc(bool condition)
{
  if(!condition) {
    errorText = "assertJc-fails";
    

  }

}






