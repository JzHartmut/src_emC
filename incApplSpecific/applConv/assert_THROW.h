#ifndef __ASSERTJc__
#define __ASSERTJc__

#ifndef __applstdef_emC_h__
  #include <applstdef_emC.h>  //This file should be included there.
#endif  


#define ASSERTJc(COND) if(!(COND)) { ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW_s0(RuntimeException, "assertion", 0) }
#define ASSERTJc_TEST(COND) { if(!(COND)) { ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW_s0(RuntimeException, "assertion", 0)} }


#define ASSERTJc_MIN(VAR, MIN) { if(!(VAR >=(MIN))){ ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW_s0(RuntimeException, "assertion", 0); VAR = MIN; } }

#define ASSERTJc_MAX(VAR, MAX) { if(!(VAR <(MAX))){ ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW_s0(RuntimeException, "assertion", 0); VAR = MAX; } }

#define ASSERTJc_EXCLMAX(VAR, MAX) { if(!(VAR <(MAX))) { ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW_s0(RuntimeException, "assertion", 0); VAR = (MAX)-1; } }

#define ASSERTJc_RANGE(VAR, MIN, MAX) { if(!(VAR >=(MIN) && VAR<=(MAX))){ ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW_s0(RuntimeException, "assertion", 0); VAR = VAR > (MAX) ? (MAX) : (MIN); } }



#define ASSERTJc_RET(COND, RETVAL) { if(!(COND)){ ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW_s0(RuntimeException, "assertion", 0); return RETVAL; } }

#define ASSERTJc_RETVOID(COND) { if(!(COND)){ ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW_s0(RuntimeException, "assertion", 0); return; } }

#define ASSERTJc_IF(COND) if(!(COND)) { ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW_s0(RuntimeException, "assertion", 0) } else 

#define ASSERTJc_THROW(COND) { if(!(COND)) ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW_s0(RuntimeException,"assertion",0); }


#define ASSERT(COND) ASSERTJc_TEST(COND)


#define ASSERT_s0_Jc(cond, TEXT, VALUE) { if(!(cond)) THROW_s0(RuntimeException, "assertion", 0) }


#endif //#define __ASSERT_Jc__
