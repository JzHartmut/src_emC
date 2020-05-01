#ifndef __ASSERTJc__
#define __ASSERTJc__

#ifndef __os_types_def_common_h__
  //defines extern_C
  #include <types_def_common.h>
#endif  


#define ASSERTJc(COND)
#define ASSERTJc_TEST(COND) 



#define ASSERTJc_MIN(VAR, MIN) { if(VAR <(MIN)) VAR = MIN; }

#define ASSERTJc_MAX(VAR, MAX) { if(VAR >(MAX)) VAR = MAX; }

#define ASSERTJc_EXCLMAX(VAR, MAX) { if(VAR >=(MAX)) VAR = (MAX)-1; }


#define ASSERTJc_RET(COND, RETVAL) { if(!(COND)){ return RETVAL; } }

#define ASSERTJc_RETVOID(COND) { if(!(COND)){ return; } }

#define ASSERTJc_IF(COND) if(COND)

#define ASSERTJc_CORR(COND) if(!(COND))

#define ASSERTJc_THROW(COND) { if(!(COND)) THROW1_s0(RuntimeException,"Assertion",0); }

#define ASSERT(COND) ASSERTJc_TEST(COND)


#define ASSERT_s0_Jc(cond, TEXT, VALUE) 

#define #define ASSERTsn_emC(cond, TEXT, VALUE1, VALUE2)

#endif //#define __ASSERT_Jc__
