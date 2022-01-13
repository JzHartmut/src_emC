#ifndef HGUARD_applstdef_emC
  #include <applstdef_emC.h>
#endif 

#ifndef HGUARD_emC_Base__Object_emC
#define HGUARD_emC_Base__Object_emC

/**Include Object_emC in the proper way: */
#ifndef DEF_NO_ObjectJc_emC
  #if defined(DEF_ObjectSimple_emC)
    #include <emC/Base/ObjectSimple_emC.h>
  #else
    #define DEF_ObjectJc_FULLCAPABILITY   //to compile content of ObjectRefl_emC.c
    #include <emC/Base/ObjectRefl_emC.h>
  #endif
#endif


#endif //HGUARD_emC_Base__Object_emC
