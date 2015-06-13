/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#include "Ipc2c/InterProcessCommFactorySocket_Ipc.h"
#include <string.h>  //because using memset()
#include <Jc/ReflectionJc.h>   //Reflection concept 
#include <Fwc/fw_Exception.h>  //basic stacktrace concept
#include "Ipc/InterProcessCommSocket.h"  //new object
#include "Jc/ObjectJc.h"  //reference-association: IntegerJc
#include "Jc/StringJc.h"  //embedded type in class data


/* J2C: Forward declaration of struct ***********************************************/
struct InterProcessCommSocket_t;


const char sign_Mtbl_InterProcessCommFactorySocket_Ipc[] = "InterProcessCommFactorySocket_Ipc"; //to mark method tables of all implementations

typedef struct MtblDef_InterProcessCommFactorySocket_Ipc_t { Mtbl_InterProcessCommFactorySocket_Ipc mtbl; MtblHeadJc end; } MtblDef_InterProcessCommFactorySocket_Ipc;
 extern MtblDef_InterProcessCommFactorySocket_Ipc const mtblInterProcessCommFactorySocket_Ipc;

/*Constructor *//**J2C: autogenerated as default constructor. */
struct InterProcessCommFactorySocket_Ipc_t* ctorO_InterProcessCommFactorySocket_Ipc(ObjectJc* othis, ThCxt* _thCxt)
{ InterProcessCommFactorySocket_Ipc_s* thiz = (InterProcessCommFactorySocket_Ipc_s*)othis;  //upcasting to the real class.
  STACKTRC_TENTRY("ctorO_InterProcessCommFactorySocket_Ipc");
  checkConsistence_ObjectJc(othis, sizeof(InterProcessCommFactorySocket_Ipc_s), null, _thCxt);  
  //J2C:super Constructor
  ctorO_InterProcessCommFactoryAccessor(/*static*/othis, _thCxt);
  setReflection_ObjectJc(othis, &reflection_InterProcessCommFactorySocket_Ipc_s, sizeof(InterProcessCommFactorySocket_Ipc_s));  
  //j2c: Initialize all class variables:
  {
  }/*J2C:No body for constructor*/

  STACKTRC_LEAVE;
  return thiz;
}



/**Destroy a instance of InterProcessComm.*/
struct InterProcessComm_t* create_S_InterProcessCommFactorySocket_Ipc_F(ObjectJc* ithis, StringJc protocolAndOwnAddr, ThCxt* _thCxt)
{ InterProcessCommFactorySocket_Ipc_s* thiz = (InterProcessCommFactorySocket_Ipc_s*)ithis;
  Mtbl_InterProcessCommFactorySocket_Ipc const* mtthis = (Mtbl_InterProcessCommFactorySocket_Ipc const*)getMtbl_ObjectJc(&thiz->base.object, sign_Mtbl_InterProcessCommFactorySocket_Ipc);
  
  STACKTRC_TENTRY("create_S_InterProcessCommFactorySocket_Ipc_F");
  
  { 
    struct InterProcessComm_t* obj; 
    
    
    obj = mtthis->InterProcessCommFactory.create_Port(&((& ((* (thiz)).base.InterProcessCommFactory))->base.object), protocolAndOwnAddr, -1, _thCxt);
    { STACKTRC_LEAVE;
      return obj;
    }
  }
  STACKTRC_LEAVE;
}

/*J2C: dynamic call variant of the override-able method: */
struct InterProcessComm_t* create_S_InterProcessCommFactorySocket_Ipc(ObjectJc* ithis, StringJc protocolAndOwnAddr, ThCxt* _thCxt)
{ Mtbl_InterProcessCommFactory const* mtbl = (Mtbl_InterProcessCommFactory const*)getMtbl_ObjectJc(ithis, sign_Mtbl_InterProcessCommFactory);
  return mtbl->create(ithis, protocolAndOwnAddr, _thCxt);
}


/**Creates a InterProcessComm from a parameter String*/
struct InterProcessComm_t* create_Si_InterProcessCommFactorySocket_Ipc_F(ObjectJc* ithis, StringJc protocolAndOwnAddr, int32 nPort, ThCxt* _thCxt)
{ InterProcessCommFactorySocket_Ipc_s* thiz = (InterProcessCommFactorySocket_Ipc_s*)ithis;
  
  STACKTRC_TENTRY("create_Si_InterProcessCommFactorySocket_Ipc_F");
  
  { 
    struct InterProcessComm_t* ipc = null; 
    int32 posSocketAddr = -1; 
    
    
    /*no initvalue*/
    posSocketAddr = -1;
    if(startsWith_StringJc(protocolAndOwnAddr, s0_StringJc("UDP:"))) 
    { 
      
      posSocketAddr = 4;
    }
    else if(startsWith_StringJc(protocolAndOwnAddr, s0_StringJc("Socket:"))) 
    { 
      
      posSocketAddr = 7;
    }
    if(posSocketAddr >= 0) 
    { 
      struct Address_InterProcessComm_t* ownAddr; 
      
      ObjectJc *newObj2_1=null; /*J2C: temporary Objects for new operations
      */
      ownAddr = createAddressSocket_InterProcessCommFactorySocket_Ipc(/*static*/null_StringJc, protocolAndOwnAddr, nPort, _thCxt);
      ipc = ((/*J2C:cast from InterProcessCommSocket_s*/InterProcessComm_i*)(ctorO_InterProcessCommSocket(/*static*/(newObj2_1 = alloc_ObjectJc(sizeof_InterProcessCommSocket_s, 0, _thCxt)), ((/*J2C:cast from Address_InterProcessComm_s*/Address_InterProcessComm_s*)(ownAddr)), _thCxt)));
      activateGC_ObjectJc(newObj2_1, null, _thCxt);
    }
    else 
    { 
      
      ipc = null;
    }
    { STACKTRC_LEAVE;
      return ipc;
    }
  }
  STACKTRC_LEAVE;
}

/*J2C: dynamic call variant of the override-able method: */
struct InterProcessComm_t* create_Si_InterProcessCommFactorySocket_Ipc(ObjectJc* ithis, StringJc protocolAndOwnAddr, int32 nPort, ThCxt* _thCxt)
{ Mtbl_InterProcessCommFactory const* mtbl = (Mtbl_InterProcessCommFactory const*)getMtbl_ObjectJc(ithis, sign_Mtbl_InterProcessCommFactory);
  return mtbl->create_Port(ithis, protocolAndOwnAddr, nPort, _thCxt);
}

struct InterProcessComm_t* create_AddrIpc_InterProcessCommFactorySocket_Ipc_F(ObjectJc* ithis, struct Address_InterProcessComm_t* addr, ThCxt* _thCxt)
{ InterProcessCommFactorySocket_Ipc_s* thiz = (InterProcessCommFactorySocket_Ipc_s*)ithis;
  
  STACKTRC_TENTRY("create_AddrIpc_InterProcessCommFactorySocket_Ipc_F");
  
  { 
    
    if( instanceof_ObjectJc(& ((* (addr)).base.object), &reflection_Address_InterProcessComm_s)) 
    { 
      struct InterProcessCommSocket_t* obj = null; 
      
      ObjectJc *newObj2_1=null; /*J2C: temporary Objects for new operations
      */
      
      obj = ctorO_InterProcessCommSocket(/*static*/(newObj2_1 = alloc_ObjectJc(sizeof_InterProcessCommSocket_s, 0, _thCxt)), ((/*J2C:cast from Address_InterProcessComm_s*/Address_InterProcessComm_s*)(addr)), _thCxt);
      { STACKTRC_LEAVE;
        activateGC_ObjectJc(newObj2_1, obj, _thCxt);
        return ((/*J2C:cast from InterProcessCommSocket_s*/InterProcessComm_i*)(obj));
      }
    }
    else 
    { 
      
      { throw_s0Jc(ident_IllegalArgumentExceptionJc, "only Socket-Implementation, fault type of address:", 0, &_thCxt->stacktraceThreadContext, __LINE__); return 0; };
    }
  }
  STACKTRC_LEAVE;
}

/*J2C: dynamic call variant of the override-able method: */
struct InterProcessComm_t* create_AddrIpc_InterProcessCommFactorySocket_Ipc(ObjectJc* ithis, struct Address_InterProcessComm_t* addr, ThCxt* _thCxt)
{ Mtbl_InterProcessCommFactory const* mtbl = (Mtbl_InterProcessCommFactory const*)getMtbl_ObjectJc(ithis, sign_Mtbl_InterProcessCommFactory);
  return mtbl->create_Addr(ithis, addr, _thCxt);
}


/**Creates an address information for the InterProcessComm from a parameter String.*/
struct Address_InterProcessComm_t* createAddress_Si_InterProcessCommFactorySocket_Ipc_F(ObjectJc* ithis, StringJc protocolAndOwnAddr, int32 nPort, ThCxt* _thCxt)
{ InterProcessCommFactorySocket_Ipc_s* thiz = (InterProcessCommFactorySocket_Ipc_s*)ithis;
  
  STACKTRC_TENTRY("createAddress_Si_InterProcessCommFactorySocket_Ipc_F");
  
  { 
    struct Address_InterProcessComm_t* addr = null; 
    
    
    /*no initvalue*/
    if(startsWith_StringJc(protocolAndOwnAddr, s0_StringJc("Socket:"))) 
    { 
      StringJc sAddr; 
      
      
      sAddr = substring_I_StringJc(protocolAndOwnAddr, 7, _thCxt)/*J2C:non-persistent*/;
      addr = createAddressSocket_InterProcessCommFactorySocket_Ipc(/*static*/null_StringJc, protocolAndOwnAddr, nPort, _thCxt);
    }
    else if(startsWith_StringJc(protocolAndOwnAddr, s0_StringJc("UDP:"))) 
    { 
      StringJc sAddr; 
      
      
      sAddr = substring_I_StringJc(protocolAndOwnAddr, 4, _thCxt)/*J2C:non-persistent*/;
      addr = createAddressSocket_InterProcessCommFactorySocket_Ipc(/*static*/null_StringJc, protocolAndOwnAddr, nPort, _thCxt);
    }
    else if(startsWith_StringJc(protocolAndOwnAddr, s0_StringJc("TCP:"))) 
    { 
      StringJc sAddr; 
      
      
      sAddr = substring_I_StringJc(protocolAndOwnAddr, 4, _thCxt)/*J2C:non-persistent*/;
      addr = createAddressSocket_InterProcessCommFactorySocket_Ipc(/*static*/null_StringJc, protocolAndOwnAddr, nPort, _thCxt);
    }
    else 
    { 
      
      addr = null;
    }
    { STACKTRC_LEAVE;
      return addr;
    }
  }
  STACKTRC_LEAVE;
}

/*J2C: dynamic call variant of the override-able method: */
struct Address_InterProcessComm_t* createAddress_Si_InterProcessCommFactorySocket_Ipc(ObjectJc* ithis, StringJc protocolAndOwnAddr, int32 nPort, ThCxt* _thCxt)
{ Mtbl_InterProcessCommFactory const* mtbl = (Mtbl_InterProcessCommFactory const*)getMtbl_ObjectJc(ithis, sign_Mtbl_InterProcessCommFactory);
  return mtbl->createAddress_Port(ithis, protocolAndOwnAddr, nPort, _thCxt);
}


/**Creates an address for InterProcesscommunication with given description.*/
struct Address_InterProcessComm_t* createAddress_S_InterProcessCommFactorySocket_Ipc_F(ObjectJc* ithis, StringJc protocolAndAddr, ThCxt* _thCxt)
{ InterProcessCommFactorySocket_Ipc_s* thiz = (InterProcessCommFactorySocket_Ipc_s*)ithis;
  Mtbl_InterProcessCommFactorySocket_Ipc const* mtthis = (Mtbl_InterProcessCommFactorySocket_Ipc const*)getMtbl_ObjectJc(&thiz->base.object, sign_Mtbl_InterProcessCommFactorySocket_Ipc);
  
  STACKTRC_TENTRY("createAddress_S_InterProcessCommFactorySocket_Ipc_F");
  
  { 
    struct Address_InterProcessComm_t* obj; 
    
    
    obj = mtthis->InterProcessCommFactory.createAddress_Port(&((& ((* (thiz)).base.InterProcessCommFactory))->base.object), protocolAndAddr, -1, _thCxt);
    { STACKTRC_LEAVE;
      return obj;
    }
  }
  STACKTRC_LEAVE;
}

/*J2C: dynamic call variant of the override-able method: */
struct Address_InterProcessComm_t* createAddress_S_InterProcessCommFactorySocket_Ipc(ObjectJc* ithis, StringJc protocolAndAddr, ThCxt* _thCxt)
{ Mtbl_InterProcessCommFactory const* mtbl = (Mtbl_InterProcessCommFactory const*)getMtbl_ObjectJc(ithis, sign_Mtbl_InterProcessCommFactory);
  return mtbl->createAddress(ithis, protocolAndAddr, _thCxt);
}

struct Address_InterProcessComm_t* createAddressSocket_InterProcessCommFactorySocket_Ipc(/*static*/ StringJc type, StringJc addr, int32 nPort, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("createAddressSocket_InterProcessCommFactorySocket_Ipc");
  
  { 
    struct Address_InterProcessComm_t* addrSocket = null; 
    
    ObjectJc *newObj1_1=null; /*J2C: temporary Objects for new operations
    */
    if(type.ptr__== null) 
    { 
      int32 posAddr; 
      
      
      posAddr = indexOf_C_StringJc(addr, ':');
      type = substring_StringJc(addr, 0, posAddr, _thCxt)/*J2C:non-persistent*/;
      addr = substring_I_StringJc(addr, posAddr + 1, _thCxt)/*J2C:non-persistent*/;
    }
    ASSERT(/*static*/length_StringJc(addr) > 0);
    if(nPort <= 0) 
    { 
      int32 posPort; 
      
      StringJc _temp2_1; /*J2C: temporary references for concatenation */
      
      posPort = indexOf_C_StringJc(addr, ':');
      if(posPort < 0) { throw_s0Jc(ident_IllegalArgumentExceptionJc, "param addr needs a port in form \"URL:port\" where port is a number or hexNumber with \"0x\"-prefix.", 0, &_thCxt->stacktraceThreadContext, __LINE__); return 0; };
      if(
        ( _temp2_1= substring_I_StringJc(addr, posPort + 1, _thCxt)
        , startsWith_StringJc(_temp2_1, s0_StringJc("0x"))
        )) 
      { 
        
        nPort = parseInt_radix_IntegerJc(/*static*/substring_I_StringJc(addr, posPort + 3, _thCxt), 16);
      }
      else 
      { 
        
        nPort = parseInt_IntegerJc(/*static*/substring_I_StringJc(addr, posPort + 1, _thCxt));
      }
      addr = substring_StringJc(addr, 0, posPort, _thCxt)/*J2C:non-persistent*/;
    }
    
    addrSocket = ctorO_ssI_Address_InterProcessComm(/*static*/(newObj1_1 = alloc_ObjectJc(sizeof_Address_InterProcessComm_s, 0, _thCxt)), type, addr, nPort, _thCxt);
    { STACKTRC_LEAVE;
      activateGC_ObjectJc(newObj1_1, addrSocket, _thCxt);
      return ((/*J2C:cast from Address_InterProcessComm_s*/Address_InterProcessComm_s*)(addrSocket));
    }
  }
  STACKTRC_LEAVE;
}



/**J2C: Reflections and Method-table *************************************************/
const MtblDef_InterProcessCommFactorySocket_Ipc mtblInterProcessCommFactorySocket_Ipc = {
{ { sign_Mtbl_InterProcessCommFactorySocket_Ipc//J2C: Head of methodtable.
  , (struct Size_Mtbl_t*)((0 +2) * sizeof(void*)) //size. NOTE: all elements are standard-pointer-types.
  }
, { { sign_Mtbl_InterProcessCommFactoryAccessor//J2C: Head of methodtable.
    , (struct Size_Mtbl_t*)((0 +2) * sizeof(void*)) //size. NOTE: all elements are standard-pointer-types.
    }
  , { { sign_Mtbl_ObjectJc//J2C: Head of methodtable.
      , (struct Size_Mtbl_t*)((5 +2) * sizeof(void*)) //size. NOTE: all elements are standard-pointer-types.
      }
    , clone_ObjectJc_F //clone
    , equals_ObjectJc_F //equals
    , finalize_ObjectJc_F //finalize
    , hashCode_ObjectJc_F //hashCode
    , toString_ObjectJc_F //toString
    }
  }
  /**J2C: Mtbl-interfaces of InterProcessCommFactorySocket_Ipc: */
, { { sign_Mtbl_InterProcessCommFactory//J2C: Head of methodtable.
    , (struct Size_Mtbl_t*)((5 +2) * sizeof(void*)) //size. NOTE: all elements are standard-pointer-types.
    }
  , createAddress_S_InterProcessCommFactorySocket_Ipc_F //createAddress
  , createAddress_Si_InterProcessCommFactorySocket_Ipc_F //createAddress_Port
  , create_S_InterProcessCommFactorySocket_Ipc_F //create
  , create_Si_InterProcessCommFactorySocket_Ipc_F //create_Port
  , create_AddrIpc_InterProcessCommFactorySocket_Ipc_F //create_Addr
  }
}, { signEnd_Mtbl_ObjectJc, null } }; //Mtbl


 extern_C struct ClassJc_t const reflection_InterProcessCommFactoryAccessor;
 static struct superClasses_InterProcessCommFactorySocket_Ipc_s_t
 { ObjectArrayJc head;
   ClassOffset_idxMtblJc data[1];
 }superclasses_InterProcessCommFactorySocket_Ipc_s =
 { CONST_ObjectArrayJc(ClassOffset_idxMtblJc, 1, OBJTYPE_ClassOffset_idxMtblJc, null, null)
 , { {&reflection_InterProcessCommFactoryAccessor, OFFSET_Mtbl(Mtbl_InterProcessCommFactorySocket_Ipc, InterProcessCommFactoryAccessor) }
   }
 };

 extern_C struct ClassJc_t const reflection_InterProcessCommFactory_i;
 static struct ifcClasses_InterProcessCommFactorySocket_Ipc_s_t
 { ObjectArrayJc head;
   ClassOffset_idxMtblJc data[1];
 }interfaces_InterProcessCommFactorySocket_Ipc_s =
 { CONST_ObjectArrayJc(ClassOffset_idxMtblJc, 1, OBJTYPE_ClassOffset_idxMtblJc, null, null)
, { {&reflection_InterProcessCommFactory_i, OFFSET_Mtbl(Mtbl_InterProcessCommFactorySocket_Ipc, InterProcessCommFactory) }
  }
};

const ClassJc reflection_InterProcessCommFactorySocket_Ipc_s = 
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ObjectJc, &reflection_ClassJc) 
, "InterProcessCommFa_ket_Ipc_s"
, (int16)((int32)(&((InterProcessCommFactorySocket_Ipc_s*)(0x1000))->base.object) - (int32)(InterProcessCommFactorySocket_Ipc_s*)0x1000)
, sizeof(InterProcessCommFactorySocket_Ipc_s)
, null //attributes and associations
, null //method
, (ClassOffset_idxMtblJcARRAY*)&superclasses_InterProcessCommFactorySocket_Ipc_s //superclass
, (ClassOffset_idxMtblJcARRAY*)&interfaces_InterProcessCommFactorySocket_Ipc_s //interfaces
, mObjectJc_Modifier_reflectJc
, &mtblInterProcessCommFactorySocket_Ipc.mtbl.head
};
