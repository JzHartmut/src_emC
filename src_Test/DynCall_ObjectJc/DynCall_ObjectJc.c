#include <applstdefJc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DynCall_ObjectJc.h"
#include "Ifc_ExampleJc.h"

typedef struct MainData {

  DynCall_ExampleJc_s data;

  ImplIfc_ExampleJc_s implIfc;  

  int step;

} MainData;


static MainData mainData = {
  { INITIALIZER_ObjectJc( mainData.data, &reflection_DynCall_ExampleJc_s, 0), 0}   
, { INITIALIZER_ObjectJc( mainData.implIfc, &reflection_ImplIfc_ExampleJc_s, 0), 0} 
, 0 //int step
};


void execute_DynCall_ExampleJc(DynCall_ExampleJc_s* thiz, int arg)
{
  thiz->val = arg;
}


static char charAt_DynCall_ExampleJc(struct ObjectJc_t* ithiz, int32 ix, ThCxt* _thCxt)
{
  return 0;
}

static int length_DynCall_ExampleJc(struct ObjectJc_t* ithiz, ThCxt* _thCxt)
{
  return 0;
}

CharSeqJc subSequence_DynCall_ExampleJc(struct ObjectJc_t* ithiz, int32 from, int32 to, ThCxt* _thCxt)
{
  CharSeqJc ret = {0};
  return ret;
}


char const* sign_Vtbl_DynCall_ExampleJc = "Vtbl_DynCall_ExampleJc";



const struct VtblDef_DynCall_ExampleJc_t
{
  Vtbl_DynCall_ExampleJc tbl;
  MtblHeadJc end;
} vtbl_DynCall_ExampleJc =
{
  { { sign_Vtbl_DynCall_ExampleJc
    , (struct Size_Mtbl_t*)((2 +1) * sizeof(void*))
    }
  , execute_DynCall_ExampleJc
  , { { sign_Mtbl_ObjectJc
      , (struct Size_Mtbl_t*)((2 +5) * sizeof(void*))
      }
      , clone_ObjectJc_F    
      , equals_ObjectJc_F   
      , finalize_ObjectJc_F 
      , hashCode_ObjectJc_F 
      , toString_ObjectJc_F 
    }
  , { { sign_Mtbl_CharSeqJc
      , (struct Size_Mtbl_t*)((3 +1) * sizeof(void*))
      }
      , length_DynCall_ExampleJc
      , charAt_DynCall_ExampleJc
      , subSequence_DynCall_ExampleJc
      , { { sign_Mtbl_ObjectJc
          , (struct Size_Mtbl_t*)((2 +5) * sizeof(void*))
          }
          , clone_ObjectJc_F    
          , equals_ObjectJc_F   
          , finalize_ObjectJc_F 
          , hashCode_ObjectJc_F 
          , toString_ObjectJc_F 
        }
    }
  }     
, { signEnd_Mtbl_ObjectJc
  , null
  }
};





void execute_ImplIfc_ExampleJc(ObjectJc* othiz, int arg)
{
  ImplIfc_ExampleJc_s* thiz = (ImplIfc_ExampleJc_s*)othiz;
  thiz->val = arg;
}



char const* sign_Vtbl_Ifc_ExampleJc = "sign_Vtbl_Ifc_ExampleJc"; 


/**The implementor of the interface should only contain this one interface in its vtbl.
 * Especially it does not need an own struct definition for Vtbl inthe header.
 */
const struct //No named unit is ok. //VtblDef_ImplIfc_ExampleJc_t
{
  Vtbl_Ifc_ExampleJc tbl;
  MtblHeadJc end;           //The end tag is necessary in any kind. For search-end.
} vtbl_ImplIfc_ExampleJc =
{
  { { sign_Vtbl_Ifc_ExampleJc
    , NrofMethodsForSize_VTBL_Jc(1)
    }
  , execute_ImplIfc_ExampleJc          //the implementing routine
  , { { sign_Mtbl_ObjectJc             //The routines of ObjectJc are also accessable in interfaces
      , NrofMethodsForSize_VTBL_Jc(5)  
      }
      , clone_ObjectJc_F               //The implenting routines, if not overridden, use from ObjectJc.
      , equals_ObjectJc_F   
      , finalize_ObjectJc_F 
      , hashCode_ObjectJc_F 
      , toString_ObjectJc_F 
    } //Vtbl_ObjectJc
  } //Vtbl_Ifc_ExampleJc
, { signEnd_Mtbl_ObjectJc
  , null
  }
};



void main(const char** args)
{
  Vtbl_DynCall_ExampleJc* vtbl = (Vtbl_DynCall_ExampleJc*)getVtbl_ObjectJc(&mainData.data.object, sign_Vtbl_DynCall_ExampleJc);
  if(vtbl !=null && vtbl->head.sign == sign_Vtbl_DynCall_ExampleJc) { vtbl->execute(&mainData.data, 2); }

  Vtbl_Ifc_ExampleJc* vtbl2 = (Vtbl_Ifc_ExampleJc*)getVtbl_ObjectJc(&mainData.data.object, sign_Vtbl_Ifc_ExampleJc);
  if(vtbl2 !=null) { vtbl2->execute(&mainData.implIfc.object, 2); }

  
}





#include "DynCall_ObjectJc.crefl"


#include <stdio.h>
void message_zI_Fwc(char const* file, int line, char const* text, int value)
{ //NOTE: printf is not thread safe!
  printf("stop at %d in %s: %8.8x %s\n", line, file, value, text); 
}
