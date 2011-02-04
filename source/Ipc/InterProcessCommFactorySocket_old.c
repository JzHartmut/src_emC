#include <Ipc/InterprocessComm.h>
#include <Jc/ReflectionJc.h>


extern ClassJc const reflection_InterProcessCommFactoryImpl;

InterProcessCommFactory_i singletonData_InterProcessCommFactoryImpl =
{ {CONST_ObjectJc(sizeof(singletonData_InterProcessCommFactoryImpl)
                 , &singletonData_InterProcessCommFactoryImpl
                 , &reflection_InterProcessCommFactoryImpl)
} };



InterProcessCommFactory_i* getInstance_InterProcessCommFactoryAccessor()
{ return &singletonData_InterProcessCommFactoryImpl;
}


Address_InterProcessComm_s* createAddress_InterProcessCommFactoryImpl_F(ObjectJc* ithis, StringJc protocolAndOwnAddr, ThCxt* _thCxt)
{
  return null;
}

Address_InterProcessComm_s* createAddress_Port_InterProcessCommFactoryImpl_F(ObjectJc* ithis, StringJc protocolAndOwnAddr, int32 port, ThCxt* _thCxt)
{
  return null;
}

InterProcessComm_i* create_InterProcessCommFactoryImpl_F(ObjectJc* ithis, StringJc protocolAndOwnAddr, ThCxt* _thCxt)
{
  return null;
}

InterProcessComm_i* create_Port_InterProcessCommFactoryImpl_F(ObjectJc* ithis, StringJc protocolAndOwnAddr, int32 port, ThCxt* _thCxt)
{
  return null;
}

InterProcessComm_i* create_Addr_InterProcessCommFactoryImpl_F(ObjectJc* ithis, Address_InterProcessComm_s* ownAddress, ThCxt* _thCxt)
{
  return null;
}





typedef struct MtblDef_InterProcessCommFactory_t { Mtbl_InterProcessCommFactory mtbl; MtblHeadJc end; } MtblDef_InterProcessCommFactory;
 extern MtblDef_InterProcessCommFactory const mtblInterProcessCommFactoryImpl;




MtblDef_InterProcessCommFactory const mtblInterProcessCommFactoryImpl = {
//Mtbl_InterProcessComm const mtbl_InterProcessCommSocket =
{ { sign_Mtbl_InterProcessCommFactory
  , (struct Size_Mtbl_t*)sizeof(Mtbl_InterProcessCommFactory)
  }
, createAddress_InterProcessCommFactoryImpl_F
, createAddress_Port_InterProcessCommFactoryImpl_F
, create_InterProcessCommFactoryImpl_F
, create_Port_InterProcessCommFactoryImpl_F
, create_Addr_InterProcessCommFactoryImpl_F
}, { signEnd_Mtbl_ObjectJc, null } }; //Mtbl


ClassJc const reflection_InterProcessCommFactoryImpl =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ObjectJc, &reflection_ClassJc) 
, "InterProcessCommFactoryImpl"
,  0 //position of ObjectJc
, sizeof(InterProcessCommFactory_i)
, null //(FieldJcArray const*)&reflection_Fields_InterProcessCommSocket_s
, null //method
, null //(ClassOffset_idxMtblJcARRAY*)&superclasses_InterProcessCommSocket_s //superclass
, null //interfaces
, 0    //modifiers
, &mtblInterProcessCommFactoryImpl.mtbl.head
};
