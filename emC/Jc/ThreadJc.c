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
 * @content some methods to implement ThreadJc.
 *
 * @author Hartmut Schorrig
 * @version 0.91
 * list of changes:
 * 2009-10-08: Hartmut creation from older source
 *
 ****************************************************************************/

#include <emC/Jc/ThreadJc.h>
#include "emC/Jc/ObjectJc.h"      //It is a concept of CRuntimeJavalike

#ifndef __NOT_SUPPORTED_ThreadContext_emC__  //then ignore whole file

#include <emC/OSAL/os_thread.h>
#include <emC/OSAL/os_time.h>
//TODO conditional compilation or using commonly approach:
#ifndef NO_DYNAMICALLY_MEMORY
	//#include "BlockHeap/BlockHeap_emC_s.h"
#endif

//#define PRINTF2(S,V)  //empty, ready to use if debug with PRINTF is necessary.

const char sign_Vtbl_RunnableJc[] = "RunnableJc"; //to mark method tables of all implementations
const char sign_Vtbl_ThreadJc[] = "ThreadJc"; //to mark method tables of all implementations

typedef struct VtblDef_ThreadJc_t { Vtbl_ThreadJc mtbl; VtblHeadJc end; } VtblDef_ThreadJc;
extern VtblDef_ThreadJc const mtblThreadJc;






ThreadJc_s* ctorO_Runnable_s_ThreadJc(ObjectJc* othis, RunnableJc_s* pRunnable,  StringJc pName, ThCxt* _thCxt)
{ ThreadJc_s* ythis = (ThreadJc_s*)othis;  //upcasting to the real class.
  Vtbl_ThreadJc const* mtthis = &mtblThreadJc.mtbl;
  STACKTRC_TENTRY("ctorO_Runnable_s_ThreadJc");
  checkConsistence_ObjectJc(othis, sizeof(ThreadJc_s), null, _thCxt);  
  setReflection_ObjectJc(othis, &reflection_ThreadJc, sizeof(ThreadJc_s));  

  ythis->hThread = null;
  set_StringJc(&(ythis->name), pName);
  
  ythis->nPriority = NORM_PRIORITY_ThreadJc;
  ythis->stackSize = 2000;
  ythis->state = kCreatedState_ThreadJc;
  SETREFJc(ythis->target, pRunnable, RunnableJc_s);
  STACKTRC_LEAVE;
  return ythis;
}



void finalize_ThreadJc_F(ObjectJc* othis, ThCxt* _thCxt)
{ ThreadJc_s* ythis = (ThreadJc_s*)othis;  //upcasting to the real class.
  STACKTRC_TENTRY("finalize_ThreadJc_F");
  finalize_ObjectJc_F(&ythis->base.object, _thCxt);      //finalizing the superclass.
  STACKTRC_LEAVE;
}




/**This method is the start routine of all threads. Should resolve type OS_ThreadRoutine */
static int root_ThreadJc(void* data)
{

  /**Test statements, able to activate in debug mode to test faulty situations and theire execution: */
  //data = null;              //null pointer
  //data = ((int*)data) +4;   //pointer which was makes leeway. 
  ObjectJc* oRunnable = (ObjectJc*)data;
  
#ifndef NO_DYNAMICALLY_MEMORY
    //DONT USE ANY CONDITIONAL COMPILING!
		//threadContextInStack.blockHeap = first_BlockHeap_emC();
#endif  
  /**This is the first StackEntry of this thread. It allocates memory. */
  { ThCxt* _thCxt = getCurrent_ThreadContext_emC();
    STACKTRC_TENTRY("root_ThreadJc");
    /**The data is a reference to the instance, which implements the interface RunnableJc.
     * It is either the associated class target of TreadJc, or ThreadJc itself.
     * A dynamic call is executed, it checks the consistence of oRunnable.
     * If the pointer is fault, an uncatchedException is thrown here. This situation is not expect-able
     * because the data pointer is set in start_ThreadJc correct. It is only able to expect on an faulty environment.
     * Test it via activating the test statements above.
     */
    run_RunnableJc(oRunnable, _thCxt);
    STACKTRC_LEAVE;
  }
  return 0;
}



ThreadJc_s* currentThread_ThreadJc(ThCxt* _thCxt)
{ return null;  //TODO
}



void start_ThreadJc(ThreadJc_s* ythis, int stackSize, ThCxt* _thCxt)
{
  int ok;
  RunnableJc_s* target = REFJc(ythis->target);  //pointer as part of the enhanced reference.
  void* data;
  char nameBuffer[16];
  STACKTRC_TENTRY("start_ThreadJc");
  /**either given target or the Thread class itself. It is the instance which contains the appopriate run method.*/
  data = target == null ? (void*)ythis : (void*)target;  
  /**The name is given as StringJc, it doesn't may be zero-terminated, therefore use a copy-buffer in Stack. */
  copyToBuffer_StringJc(ythis->name, 0, -1, nameBuffer, sizeof(nameBuffer));
  /**Create and start: */
  ythis->stackSize = stackSize;
  //PRINTX2(0, "start_ThreadJc:\n",0); 
  ok = os_createThread(&ythis->hThread, root_ThreadJc, data, nameBuffer, ythis->nPriority, ythis->stackSize);
  if(ok < 0){

    THROW1_s0(RuntimeException, "Error creating thread", -ok);
  }
  STACKTRC_LEAVE;
}




void run_RunnableJc(ObjectJc* ithis, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("run_RunnableJc");
  { Vtbl_RunnableJc const* mtbl = (Vtbl_RunnableJc const*)getVtbl_ObjectJc(ithis, sign_Vtbl_RunnableJc);
    mtbl->run(ithis, _thCxt);
  }
  STACKTRC_LEAVE;
}


void run_ThreadJc_F(ObjectJc* ithis, ThCxt* _thCxt)
{ ThreadJc_s* ythis = (ThreadJc_s*)ithis;       //upcasting to the real class.
  RunnableJc_s* target = REFJc(ythis->target);  //pointer as part of the enhanced reference.
  STACKTRC_TENTRY("run_Thread_F");
  if(target != null)
  { Vtbl_RunnableJc const* mtbl = (Vtbl_RunnableJc const*)getVtbl_ObjectJc(&target->base.object, sign_Vtbl_RunnableJc);
    mtbl->run(&((REFJc(ythis->target))->base.object), _thCxt);
  }
  STACKTRC_LEAVE;
}



bool isAlive_Thread_Jc(ThreadJc_s* ythis)
{
  return(ythis->state > kCreatedState_ThreadJc && ythis->state < kFinishedState_ThreadJc);
}



void sleep_ThreadJc(int32 milliseconds, ThCxt* _thCxt)
{
  STACKTRC_TENTRY("sleep_ThreadJc");
  os_delayThread(milliseconds);     //now the cpu is switched to another thread.
  STACKTRC_LEAVE;
}




/**J2C: Reflections and Method-table *************************************************/
const VtblDef_ThreadJc mtblThreadJc = {
{ { sign_Vtbl_ThreadJc//J2C: Head of methodtable.
  , (struct Size_Vtbl_t*)((0 +2) * sizeof(void*)) //size. NOTE: all elements are standard-pointer-types.
  }
, { { sign_Vtbl_ObjectJc//J2C: Head of methodtable.
    , (struct Size_Vtbl_t*)((5 +2) * sizeof(void*)) //size. NOTE: all elements are standard-pointer-types.
    }
  , clone_ObjectJc_F //clone
  , equals_ObjectJc_F //equals
  , finalize_ObjectJc_F //finalize
  , hashCode_ObjectJc_F //hashCode
  , toString_ObjectJc_F //toString
  }
  /**J2C: Vtbl-interfaces of ThreadJc: */
, { { sign_Vtbl_RunnableJc
    , (struct Size_Vtbl_t*)((1 +2) * sizeof(void*)) //size. NOTE: all elements are standard-pointer-types.
    }
  , run_ThreadJc_F //processIfcMethod
  , { { sign_Vtbl_ObjectJc//J2C: Head of methodtable.
      , (struct Size_Vtbl_t*)((5 +2) * sizeof(void*)) //size. NOTE: all elements are standard-pointer-types.
      }
    , clone_ObjectJc_F //clone
    , equals_ObjectJc_F //equals
    , finalize_ObjectJc_F //finalize
    , hashCode_ObjectJc_F //hashCode
    , toString_ObjectJc_F //toString
    }
  }
}, { signEnd_Vtbl_ObjectJc, null } 
}; //Vtbl


#include <emC/Jc/genRefl/ThreadJc.crefl>

#endif //not __NOT_SUPPORTED_ThreadContext_emC__
