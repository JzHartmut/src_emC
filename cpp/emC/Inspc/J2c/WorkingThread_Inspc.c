/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#include <applstdef_emC.h>
#ifdef DEF_ClassJc_Vtbl
//NOTE: This file can only be used with full capability of emC, not for simple applications.
//      It is only necessary to full including the Inspc symbolic access on target

#include "emC/Inspc/J2c/WorkingThread_Inspc.h"
#include <string.h>  //because using memset()
#include <emC/Jc/ReflectionJc.h>   //Reflection concept 
  //basic stacktrace concept
#include "emC/Jc/MathJc.h"  //reference-association: MathJc_s


/* J2C: Forward declaration of struct ***********************************************/

/**This is a class which does anything to display it with the reflectPro-target. 
It creates an own thread and calculates some sine-curve-values.
@author Hartmut Schorrig.

*/


const char sign_Vtbl_WorkingThread_Inspc[] = "WorkingThread_Inspc"; //to mark method tables of all implementations

typedef struct VtblDef_WorkingThread_Inspc_t { Vtbl_WorkingThread_Inspc mtbl; VtblHeadJc end; } VtblDef_WorkingThread_Inspc;
 extern VtblDef_WorkingThread_Inspc const mtblWorkingThread_Inspc;

/*Constructor */
struct WorkingThread_Inspc_t* ctorO_WorkingThread_Inspc(ObjectJc* othis, ThCxt* _thCxt)
{ WorkingThread_Inspc_s* thiz = (WorkingThread_Inspc_s*)othis;  //upcasting to the real class.
  STACKTRC_TENTRY("ctorO_WorkingThread_Inspc");
  checkConsistence_ObjectJc(othis, sizeof(WorkingThread_Inspc_s), null, _thCxt);  
  setReflection_ObjectJc(othis, &refl_WorkingThread_Inspc_s, sizeof(WorkingThread_Inspc_s));  
  //j2c: Initialize all class variables:
  {ObjectJc *newObj1_1=null; /*J2C: temporary Objects for new operations
      */
    //J2C: constructor for embedded element-ObjectJc
      init_ObjectJc(&(thiz->data.base.object), sizeof(thiz->data), 0); 
      ctorO_Data_WorkingThread_Inspc(/*J2C:static method call*/&(thiz->data.base.object), _thCxt);
    //J2C: constructor for embedded element-ObjectJc
      init_ObjectJc(&(thiz->theThreadRun.base.object), sizeof(thiz->theThreadRun), 0); 
      ctorO_C_theThreadRun_WorkingThread_Inspc(thiz, &(thiz->theThreadRun.base.object), _thCxt);
    SETREFJc(thiz->theThreadMng, ctorO_ThreadMng_WorkingThread_Inspc(thiz, (newObj1_1 = alloc_ObjectJc(sizeof_ThreadMng_WorkingThread_Inspc_s, 0, _thCxt)), _thCxt), ThreadMng_WorkingThread_Inspc_s);
    activateGC_ObjectJc(newObj1_1, null, _thCxt);
  }
  { 
    
    
  }
  STACKTRC_LEAVE;
  return thiz;
}



/**Start of the thread, should be called initially if the application is built completely. */
void start_WorkingThread_Inspc_F(WorkingThread_Inspc_s* thiz, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("start_WorkingThread_Inspc_F");
  
  { 
    
    start_ThreadJc(& (REFJc    (thiz->theThreadMng)->thread), -1, _thCxt);
  }
  STACKTRC_LEAVE;
}

/*J2C: dynamic call variant of the override-able method: */
void start_WorkingThread_Inspc(WorkingThread_Inspc_s* thiz, ThCxt* _thCxt)
{ Vtbl_WorkingThread_Inspc const* mtbl = (Vtbl_WorkingThread_Inspc const*)getVtbl_ObjectJc(&thiz->base.object, sign_Vtbl_WorkingThread_Inspc);
  mtbl->start(thiz, _thCxt);
}


/**Terminate the thread for ever, should be called on termination of the application.*/
void terminate_WorkingThread_Inspc_F(WorkingThread_Inspc_s* thiz, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("terminate_WorkingThread_Inspc_F");
  
  { 
    
    REFJc    (thiz->theThreadMng)->bRun = false;
  }
  STACKTRC_LEAVE;
}

/*J2C: dynamic call variant of the override-able method: */
void terminate_WorkingThread_Inspc(WorkingThread_Inspc_s* thiz, ThCxt* _thCxt)
{ Vtbl_WorkingThread_Inspc const* mtbl = (Vtbl_WorkingThread_Inspc const*)getVtbl_ObjectJc(&thiz->base.object, sign_Vtbl_WorkingThread_Inspc);
  mtbl->terminate(thiz, _thCxt);
}

void step_WorkingThread_Inspc(WorkingThread_Inspc_s* thiz, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("step_WorkingThread_Inspc");
  
  { 
    
    thiz->data.ww += thiz->data.dw;/*increasing of angle. Runs wrapping over PI*/
    
    
    float  ww = (float /*J2C_cast*/)(thiz->data.ww * PI_MathJc / 0x80000000);
    if(thiz->data.ww >= PI_MathJc) 
    { 
      
      thiz->data.ww -= ((/*J2C:cast% from double*/int32)(2 * PI_MathJc));/*runs in range -Pi .. +PI */
      
    }
    thiz->data.wFloat = ww;/*Note: Java knows only the double versions of trigonometric functions.*/
    
    thiz->data.ySin = (float /*J2C_cast*/)sin(/*J2C:static method call*/ww);
    thiz->data.ySin2 = (float /*J2C_cast*/)sin(/*J2C:static method call*/(float /*J2C_cast*/)(2 * ww + PI_MathJc / 2));
    thiz->data.ySin3 = (float /*J2C_cast*/)sin(/*J2C:static method call*/(float /*J2C_cast*/)(3 * ww));
    thiz->data.yCos = (float /*J2C_cast*/)cos(/*J2C:static method call*/ww);
    thiz->data.yOut1 = thiz->data.ySin + thiz->data.ySin2;/* + data.ySin3;*/
    
  }
  STACKTRC_LEAVE;
}


void finalize_WorkingThread_Inspc_F(ObjectJc const* othis, ThCxt* _thCxt)
{ WorkingThread_Inspc_s* thiz = (WorkingThread_Inspc_s*)othis;  //upcasting to the real class.
 STACKTRC_TENTRY("finalize_WorkingThread_Inspc_F");
  finalize_ObjectJc_F(&thiz->data.base.object, _thCxt); //J2C: finalizing the embedded instance.
  finalize_ObjectJc_F(&thiz->theThreadRun.base.object, _thCxt); //J2C: finalizing the embedded instance.
  CLEAR_REFJc(thiz->theThreadMng);
  finalize_ObjectJc_F(&thiz->base.object, _thCxt); //J2C: finalizing the superclass.
  STACKTRC_LEAVE;
}




/**J2C: Reflections and Method-table *************************************************/
const VtblDef_WorkingThread_Inspc mtblWorkingThread_Inspc = {
{ { sign_Vtbl_WorkingThread_Inspc //J2C: Head of methodtable of WorkingThread_Inspc
  , (struct Size_Vtbl_t*)((2 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
  }
  //J2C: Dynamic methods of the class :WorkingThread_Inspc:
, start_WorkingThread_Inspc_F //start
, terminate_WorkingThread_Inspc_F //terminate
  //J2C: The superclass's methodtable: 
, { { sign_Vtbl_ObjectJc //J2C: Head of methodtable of ObjectJc
    , (struct Size_Vtbl_t*)((5 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
    }
    //J2C: Dynamic methods of the class :ObjectJc:
  , clone_ObjectJc_F //clone
  , equals_ObjectJc_F //equals
  , finalize_WorkingThread_Inspc_F //finalize
  , hashCode_ObjectJc_F //hashCode
  , toString_ObjectJc_F //toString
  }
}, { signEnd_Vtbl_ObjectJc, null } }; //Vtbl


 extern_C struct ClassJc_t const refl_ObjectJc;
 static struct superClasses_WorkingThread_Inspc_s_t
 { ObjectArrayJc head;
   ClassOffset_idxVtblJc data[1];
 }superclasses_WorkingThread_Inspc_s =
 { CONST_ObjectArrayJc(ClassOffset_idxVtblJc, 1, OBJTYPE_ClassOffset_idxVtblJc, null, null)
 , { {&refl_ObjectJc, OFFSET_Vtbl(Vtbl_WorkingThread_Inspc, ObjectJc) }
   }
 };

extern_C struct ClassJc_t const refl_WorkingThread_Inspc_s;
extern_C struct ClassJc_t const refl_C_theThreadRun_WorkingThread_Inspc_s;
extern_C struct ClassJc_t const refl_Data_WorkingThread_Inspc_s;
extern_C struct ClassJc_t const refl_ThreadMng_WorkingThread_Inspc_s;
const struct Reflection_Fields_WorkingThread_Inspc_s_t
{ ObjectArrayJc head; FieldJc data[3];
} refl_Fields_WorkingThread_Inspc_s =
{ CONST_ObjectArrayJc(FieldJc, 3, OBJTYPE_FieldJc, null, &refl_Fields_WorkingThread_Inspc_s)
, {
     { "data"
    , 0 //nrofArrayElements
    , &refl_Data_WorkingThread_Inspc_s
    , kEmbedded_Modifier_reflectJc |mObjectJc_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((WorkingThread_Inspc_s*)(0x1000))->data) - (intptr_t)(WorkingThread_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_WorkingThread_Inspc_s
    }
   , { "theThreadRun"
    , 0 //nrofArrayElements
    , &refl_C_theThreadRun_WorkingThread_Inspc_s
    , kEmbedded_Modifier_reflectJc |mObjectJc_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((WorkingThread_Inspc_s*)(0x1000))->theThreadRun) - (intptr_t)(WorkingThread_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_WorkingThread_Inspc_s
    }
   , { "theThreadMng"
    , 0 //nrofArrayElements
    , &refl_ThreadMng_WorkingThread_Inspc_s
    , kEnhancedReference_Modifier_reflectJc /*@*/ |mObjectJc_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((WorkingThread_Inspc_s*)(0x1000))->theThreadMng) - (intptr_t)(WorkingThread_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_WorkingThread_Inspc_s
    }
} };
const ClassJc refl_WorkingThread_Inspc_s = 
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ObjectJc, &refl_ClassJc) 
, "WorkingThread_Inspc_s"
,  0 //position of ObjectJc
, sizeof(WorkingThread_Inspc_s)
, (FieldJc_Y const*)&refl_Fields_WorkingThread_Inspc_s
, null //method
, &superclasses_WorkingThread_Inspc_s.head.object //superclass
, null //interfaces
, 0    //modifiers
, &mtblWorkingThread_Inspc.mtbl.head
};


const char sign_Vtbl_Data_WorkingThread_Inspc[] = "Data_WorkingThread_Inspc"; //to mark method tables of all implementations

typedef struct VtblDef_Data_WorkingThread_Inspc_t { Vtbl_Data_WorkingThread_Inspc mtbl; VtblHeadJc end; } VtblDef_Data_WorkingThread_Inspc;
 extern VtblDef_Data_WorkingThread_Inspc const mtblData_WorkingThread_Inspc;

/*Constructor *//**J2C: autogenerated as default constructor. */
struct Data_WorkingThread_Inspc_t* ctorO_Data_WorkingThread_Inspc(ObjectJc* othis, ThCxt* _thCxt)
{ Data_WorkingThread_Inspc_s* thiz = (Data_WorkingThread_Inspc_s*)othis;  //upcasting to the real class.
  STACKTRC_TENTRY("ctorO_Data_WorkingThread_Inspc");
  checkConsistence_ObjectJc(othis, sizeof(Data_WorkingThread_Inspc_s), null, _thCxt);  
  setReflection_ObjectJc(othis, &refl_Data_WorkingThread_Inspc_s, sizeof(Data_WorkingThread_Inspc_s));  
  //j2c: Initialize all class variables:
  {
    thiz->dw = 20000;
  }/*J2C:No body for constructor*/

  STACKTRC_LEAVE;
  return thiz;
}




/**J2C: Reflections and Method-table *************************************************/
const VtblDef_Data_WorkingThread_Inspc mtblData_WorkingThread_Inspc = {
{ { sign_Vtbl_Data_WorkingThread_Inspc //J2C: Head of methodtable of Data_WorkingThread_Inspc
  , (struct Size_Vtbl_t*)((0 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
  }
  //J2C: The superclass's methodtable: 
, { { sign_Vtbl_ObjectJc //J2C: Head of methodtable of ObjectJc
    , (struct Size_Vtbl_t*)((5 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
    }
    //J2C: Dynamic methods of the class :ObjectJc:
  , clone_ObjectJc_F //clone
  , equals_ObjectJc_F //equals
  , finalize_ObjectJc_F //finalize
  , hashCode_ObjectJc_F //hashCode
  , toString_ObjectJc_F //toString
  }
}, { signEnd_Vtbl_ObjectJc, null } }; //Vtbl


 extern_C struct ClassJc_t const refl_ObjectJc;
 static struct superClasses_Data_WorkingThread_Inspc_s_t
 { ObjectArrayJc head;
   ClassOffset_idxVtblJc data[1];
 }superclasses_Data_WorkingThread_Inspc_s =
 { CONST_ObjectArrayJc(ClassOffset_idxVtblJc, 1, OBJTYPE_ClassOffset_idxVtblJc, null, null)
 , { {&refl_ObjectJc, OFFSET_Vtbl(Vtbl_Data_WorkingThread_Inspc, ObjectJc) }
   }
 };

extern_C struct ClassJc_t const refl_Data_WorkingThread_Inspc_s;
const struct Reflection_Fields_Data_WorkingThread_Inspc_s_t
{ ObjectArrayJc head; FieldJc data[8];
} refl_Fields_Data_WorkingThread_Inspc_s =
{ CONST_ObjectArrayJc(FieldJc, 8, OBJTYPE_FieldJc, null, &refl_Fields_Data_WorkingThread_Inspc_s)
, {
     { "dw"
    , 0 //nrofArrayElements
    , REFLECTION_int32
    , 4 << kBitPrimitiv_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((Data_WorkingThread_Inspc_s*)(0x1000))->dw) - (intptr_t)(Data_WorkingThread_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_Data_WorkingThread_Inspc_s
    }
   , { "ww"
    , 0 //nrofArrayElements
    , REFLECTION_int32
    , 4 << kBitPrimitiv_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((Data_WorkingThread_Inspc_s*)(0x1000))->ww) - (intptr_t)(Data_WorkingThread_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_Data_WorkingThread_Inspc_s
    }
   , { "wFloat"
    , 0 //nrofArrayElements
    , REFLECTION_float
    , 4 << kBitPrimitiv_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((Data_WorkingThread_Inspc_s*)(0x1000))->wFloat) - (intptr_t)(Data_WorkingThread_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_Data_WorkingThread_Inspc_s
    }
   , { "ySin"
    , 0 //nrofArrayElements
    , REFLECTION_float
    , 4 << kBitPrimitiv_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((Data_WorkingThread_Inspc_s*)(0x1000))->ySin) - (intptr_t)(Data_WorkingThread_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_Data_WorkingThread_Inspc_s
    }
   , { "ySin2"
    , 0 //nrofArrayElements
    , REFLECTION_float
    , 4 << kBitPrimitiv_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((Data_WorkingThread_Inspc_s*)(0x1000))->ySin2) - (intptr_t)(Data_WorkingThread_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_Data_WorkingThread_Inspc_s
    }
   , { "ySin3"
    , 0 //nrofArrayElements
    , REFLECTION_float
    , 4 << kBitPrimitiv_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((Data_WorkingThread_Inspc_s*)(0x1000))->ySin3) - (intptr_t)(Data_WorkingThread_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_Data_WorkingThread_Inspc_s
    }
   , { "yCos"
    , 0 //nrofArrayElements
    , REFLECTION_float
    , 4 << kBitPrimitiv_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((Data_WorkingThread_Inspc_s*)(0x1000))->yCos) - (intptr_t)(Data_WorkingThread_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_Data_WorkingThread_Inspc_s
    }
   , { "yOut1"
    , 0 //nrofArrayElements
    , REFLECTION_float
    , 4 << kBitPrimitiv_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((Data_WorkingThread_Inspc_s*)(0x1000))->yOut1) - (intptr_t)(Data_WorkingThread_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_Data_WorkingThread_Inspc_s
    }
} };
const ClassJc refl_Data_WorkingThread_Inspc_s = 
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ObjectJc, &refl_ClassJc) 
, "Data_WorkingThread_Inspc_s"
,  0 //position of ObjectJc
, sizeof(Data_WorkingThread_Inspc_s)
, (FieldJc_Y const*)&refl_Fields_Data_WorkingThread_Inspc_s
, null //method
, &superclasses_Data_WorkingThread_Inspc_s.head.object //superclass
, null //interfaces
, 0    //modifiers
, &mtblData_WorkingThread_Inspc.mtbl.head
};


const char sign_Vtbl_ThreadMng_WorkingThread_Inspc[] = "ThreadMng_WorkingThread_Inspc"; //to mark method tables of all implementations

typedef struct VtblDef_ThreadMng_WorkingThread_Inspc_t { Vtbl_ThreadMng_WorkingThread_Inspc mtbl; VtblHeadJc end; } VtblDef_ThreadMng_WorkingThread_Inspc;
 extern VtblDef_ThreadMng_WorkingThread_Inspc const mtblThreadMng_WorkingThread_Inspc;

/*Constructor *//**J2C: autogenerated as default constructor. */
struct ThreadMng_WorkingThread_Inspc_t* ctorO_ThreadMng_WorkingThread_Inspc(struct WorkingThread_Inspc_t* outer, ObjectJc* othis, ThCxt* _thCxt)
{ ThreadMng_WorkingThread_Inspc_s* thiz = (ThreadMng_WorkingThread_Inspc_s*)othis;  //upcasting to the real class.
  STACKTRC_TENTRY("ctorO_ThreadMng_WorkingThread_Inspc");
  checkConsistence_ObjectJc(othis, sizeof(ThreadMng_WorkingThread_Inspc_s), null, _thCxt);  
  setReflection_ObjectJc(othis, &refl_ThreadMng_WorkingThread_Inspc_s, sizeof(ThreadMng_WorkingThread_Inspc_s));  
  thiz->outer = outer;
  //j2c: Initialize all class variables:
  {
    //J2C: constructor for embedded element-ObjectJc
      init_ObjectJc(&(thiz->thread.base.object), sizeof(thiz->thread), 0); 
      ctorO_Runnable_s_ThreadJc(/*J2C:static method call*/&(thiz->thread.base.object), & ((thiz->outer->theThreadRun).base.RunnableJc), s0_StringJc("WorkingThread"), _thCxt);
  }/*J2C:No body for constructor*/

  STACKTRC_LEAVE;
  return thiz;
}




/**J2C: Reflections and Method-table *************************************************/
const VtblDef_ThreadMng_WorkingThread_Inspc mtblThreadMng_WorkingThread_Inspc = {
{ { sign_Vtbl_ThreadMng_WorkingThread_Inspc //J2C: Head of methodtable of ThreadMng_WorkingThread_Inspc
  , (struct Size_Vtbl_t*)((0 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
  }
  //J2C: The superclass's methodtable: 
, { { sign_Vtbl_ObjectJc //J2C: Head of methodtable of ObjectJc
    , (struct Size_Vtbl_t*)((5 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
    }
    //J2C: Dynamic methods of the class :ObjectJc:
  , clone_ObjectJc_F //clone
  , equals_ObjectJc_F //equals
  , finalize_ObjectJc_F //finalize
  , hashCode_ObjectJc_F //hashCode
  , toString_ObjectJc_F //toString
  }
}, { signEnd_Vtbl_ObjectJc, null } }; //Vtbl


 extern_C struct ClassJc_t const refl_ObjectJc;
 static struct superClasses_ThreadMng_WorkingThread_Inspc_s_t
 { ObjectArrayJc head;
   ClassOffset_idxVtblJc data[1];
 }superclasses_ThreadMng_WorkingThread_Inspc_s =
 { CONST_ObjectArrayJc(ClassOffset_idxVtblJc, 1, OBJTYPE_ClassOffset_idxVtblJc, null, null)
 , { {&refl_ObjectJc, OFFSET_Vtbl(Vtbl_ThreadMng_WorkingThread_Inspc, ObjectJc) }
   }
 };

extern_C struct ClassJc_t const refl_ThreadMng_WorkingThread_Inspc_s;
extern_C struct ClassJc_t const refl_C_theThreadRun_WorkingThread_Inspc_s;
extern_C struct ClassJc_t const refl_Data_WorkingThread_Inspc_s;
extern_C struct ClassJc_t const refl_ThreadJc;
extern_C struct ClassJc_t const refl_ThreadMng_WorkingThread_Inspc_s;
const struct Reflection_Fields_ThreadMng_WorkingThread_Inspc_s_t
{ ObjectArrayJc head; FieldJc data[2];
} refl_Fields_ThreadMng_WorkingThread_Inspc_s =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &refl_Fields_ThreadMng_WorkingThread_Inspc_s)
, {
     { "bRun"
    , 0 //nrofArrayElements
    , REFLECTION_bool
    , 4 << kBitPrimitiv_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((ThreadMng_WorkingThread_Inspc_s*)(0x1000))->bRun) - (intptr_t)(ThreadMng_WorkingThread_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ThreadMng_WorkingThread_Inspc_s
    }
   , { "thread"
    , 0 //nrofArrayElements
    , &refl_ThreadJc
    , kEmbedded_Modifier_reflectJc |mObjectJc_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((ThreadMng_WorkingThread_Inspc_s*)(0x1000))->thread) - (intptr_t)(ThreadMng_WorkingThread_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ThreadMng_WorkingThread_Inspc_s
    }
} };
const ClassJc refl_ThreadMng_WorkingThread_Inspc_s = 
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ObjectJc, &refl_ClassJc) 
, "ThreadMng_WorkingT_d_Inspc_s"
,  0 //position of ObjectJc
, sizeof(ThreadMng_WorkingThread_Inspc_s)
, (FieldJc_Y const*)&refl_Fields_ThreadMng_WorkingThread_Inspc_s
, null //method
, &superclasses_ThreadMng_WorkingThread_Inspc_s.head.object //superclass
, null //interfaces
, 0    //modifiers
, &mtblThreadMng_WorkingThread_Inspc.mtbl.head
};


const char sign_Vtbl_C_theThreadRun_WorkingThread_Inspc[] = "C_theThreadRun_WorkingThread_Inspc"; //to mark method tables of all implementations

typedef struct VtblDef_C_theThreadRun_WorkingThread_Inspc_t { Vtbl_C_theThreadRun_WorkingThread_Inspc mtbl; VtblHeadJc end; } VtblDef_C_theThreadRun_WorkingThread_Inspc;
 extern VtblDef_C_theThreadRun_WorkingThread_Inspc const mtblC_theThreadRun_WorkingThread_Inspc;
void run_C_theThreadRun_WorkingThread_Inspc_F(ObjectJc* ithis, ThCxt* _thCxt)
{ C_theThreadRun_WorkingThread_Inspc_s* thiz = (C_theThreadRun_WorkingThread_Inspc_s*)ithis;
  
  STACKTRC_TENTRY("run_C_theThreadRun_WorkingThread_Inspc_F");
  
  { 
    
    REFJc    (thiz->outer->theThreadMng)->bRun = true;
    
    while(REFJc    (thiz->outer->theThreadMng)->bRun)
      { 
        
        TRY
        { 
          
          sleep_ThreadJc(/*J2C:static method call*/10, _thCxt);
        }_TRY
        CATCH(InterruptedException, exc)
        
          { 
            
            
          }
        END_TRY
        { int32 ii; 
          for(ii = 0; ii < 100; ++ii)
            { /*:runs 100 times the step routine, it is adequate a step-time of 100 us*/
              
              
              step_WorkingThread_Inspc((struct WorkingThread_Inspc_t * /*J2C chg access*/)(thiz)->outer, _thCxt);
            }
        }
      }
  }
  STACKTRC_LEAVE;
}

/*J2C: dynamic call variant of the override-able method: */
void run_C_theThreadRun_WorkingThread_Inspc(ObjectJc* ithis, ThCxt* _thCxt)
{ Vtbl_RunnableJc const* mtbl = (Vtbl_RunnableJc const*)getVtbl_ObjectJc(ithis, sign_Vtbl_RunnableJc);
  mtbl->run(ithis, _thCxt);
}


/*Constructor *//**J2C: autogenerated as default constructor. */
struct C_theThreadRun_WorkingThread_Inspc_t* ctorO_C_theThreadRun_WorkingThread_Inspc(struct WorkingThread_Inspc_t* outer, ObjectJc* othis, ThCxt* _thCxt)
{ C_theThreadRun_WorkingThread_Inspc_s* thiz = (C_theThreadRun_WorkingThread_Inspc_s*)othis;  //upcasting to the real class.
  STACKTRC_TENTRY("ctorO_C_theThreadRun_WorkingThread_Inspc");
  checkConsistence_ObjectJc(othis, sizeof(C_theThreadRun_WorkingThread_Inspc_s), null, _thCxt);  
  setReflection_ObjectJc(othis, &refl_C_theThreadRun_WorkingThread_Inspc_s, sizeof(C_theThreadRun_WorkingThread_Inspc_s));  
  thiz->outer = outer;
  //j2c: Initialize all class variables:
  {
  }/*J2C:No body for constructor*/

  STACKTRC_LEAVE;
  return thiz;
}




/**J2C: Reflections and Method-table *************************************************/
const VtblDef_C_theThreadRun_WorkingThread_Inspc mtblC_theThreadRun_WorkingThread_Inspc = {
{ { sign_Vtbl_C_theThreadRun_WorkingThread_Inspc //J2C: Head of methodtable of C_theThreadRun_WorkingThread_Inspc
  , (struct Size_Vtbl_t*)((0 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
  }
  //J2C: The superclass's methodtable: 
, { { sign_Vtbl_ObjectJc //J2C: Head of methodtable of ObjectJc
    , (struct Size_Vtbl_t*)((5 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
    }
    //J2C: Dynamic methods of the class :ObjectJc:
  , clone_ObjectJc_F //clone
  , equals_ObjectJc_F //equals
  , finalize_ObjectJc_F //finalize
  , hashCode_ObjectJc_F //hashCode
  , toString_ObjectJc_F //toString
  }
  //J2C: The interface's methodtable: 
  //J2C: Vtbl-interfaces of :C_theThreadRun_WorkingThread_Inspc: */
, { { sign_Vtbl_RunnableJc //J2C: Head of methodtable of RunnableJc
    , (struct Size_Vtbl_t*)((1 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
    }
    //J2C: Dynamic methods of the class :RunnableJc:
  , run_C_theThreadRun_WorkingThread_Inspc_F //run
    //J2C: The superclass's methodtable: 
  , { { sign_Vtbl_ObjectJc //J2C: Head of methodtable of ObjectJc
      , (struct Size_Vtbl_t*)((5 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
      }
      //J2C: Dynamic methods of the class :ObjectJc:
    , clone_ObjectJc_F //clone
    , equals_ObjectJc_F //equals
    , finalize_ObjectJc_F //finalize
    , hashCode_ObjectJc_F //hashCode
    , toString_ObjectJc_F //toString
    }
  }
}, { signEnd_Vtbl_ObjectJc, null } }; //Vtbl


 extern_C struct ClassJc_t const refl_ObjectJc;
 static struct superClasses_C_theThreadRun_WorkingThread_Inspc_s_t
 { ObjectArrayJc head;
   ClassOffset_idxVtblJc data[1];
 }superclasses_C_theThreadRun_WorkingThread_Inspc_s =
 { CONST_ObjectArrayJc(ClassOffset_idxVtblJc, 1, OBJTYPE_ClassOffset_idxVtblJc, null, null)
 , { {&refl_ObjectJc, OFFSET_Vtbl(Vtbl_C_theThreadRun_WorkingThread_Inspc, ObjectJc) }
   }
 };

 extern_C struct ClassJc_t const refl_RunnableJc;
 static struct ifcClasses_C_theThreadRun_WorkingThread_Inspc_s_t
 { ObjectArrayJc head;
   ClassOffset_idxVtblJc data[1];
 }interfaces_C_theThreadRun_WorkingThread_Inspc_s =
 { CONST_ObjectArrayJc(ClassOffset_idxVtblJc, 1, OBJTYPE_ClassOffset_idxVtblJc, null, null)
, { {&refl_RunnableJc, OFFSET_Vtbl(Vtbl_C_theThreadRun_WorkingThread_Inspc, RunnableJc) }
  }
};

const ClassJc refl_C_theThreadRun_WorkingThread_Inspc_s = 
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ObjectJc, &refl_ClassJc) 
, "C_theThreadRun_Wor_d_Inspc_s"
, (int16)((intptr_t)(&((C_theThreadRun_WorkingThread_Inspc_s*)(0x1000))->base.object) - (intptr_t)(C_theThreadRun_WorkingThread_Inspc_s*)0x1000)
, sizeof(C_theThreadRun_WorkingThread_Inspc_s)
, null //attributes and associations
, null //method
, &superclasses_C_theThreadRun_WorkingThread_Inspc_s.head.object //superclass
, (ClassOffset_idxVtblJcARRAY*)&interfaces_C_theThreadRun_WorkingThread_Inspc_s //interfaces
, mObjectJc_Modifier_reflectJc
, &mtblC_theThreadRun_WorkingThread_Inspc.mtbl.head
};


#endif //def DEF_ClassJc_Vtbl