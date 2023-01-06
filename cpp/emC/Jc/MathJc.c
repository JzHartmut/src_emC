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
 *
 * @content Implementation of java.lang.Math
 *
 * @author Jchartmut www.vishia.org
 * @version 0.82
 * list of changes:
 * 2008-04-22: JcHartmut adap:The elements idSemaphore and idWaitingThread are combined to idSyncHandles.
 * 2006-05-00: www.vishia.de creation
 *
 ****************************************************************************/
#include "emC/Jc/ObjectJc.h"  


#include <emC/Jc/MathJc.h>
#include "math.h"
#include "stdlib.h"
double pow_MathJc(double a, double b) //, ThCxt* _thCxt)
{ return pow(a,b);
}


double random_MathJc() //ThCxt* _thCxt)
{
  double x = (double)rand() / (double)(RAND_MAX);
  return x;
}
