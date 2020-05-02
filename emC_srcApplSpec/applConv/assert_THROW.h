#ifndef __ASSERTJc__
#define __ASSERTJc__
//#error assert_THROW.h
#ifndef __applstdef_emC_h__
  #include <applstdef_emC.h>  //This file should be included there.
#endif  


#define ASSERTJc(COND) CALLINE; if(!(COND)) { THROW1_s0(RuntimeException, "assertion", 0); } 



#define ASSERTJc_RANGE(VAR, MIN, MAX) { if(!(VAR >=(MIN) && VAR<=(MAX))){ ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW1_s0(RuntimeException, "assertion", 0); VAR = VAR > (MAX) ? (MAX) : (MIN); } }



#define ASSERTJc_RET(COND, RETVAL) { if(!(COND)){ ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW1_s0(RuntimeException, "assertion", 0); return RETVAL; } }

#define ASSERTJc_RETVOID(COND) { if(!(COND)){ ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW1_s0(RuntimeException, "assertion", 0); return; } }

#define ASSERTJc_IF(COND) if(!(COND)) { ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW1_s0(RuntimeException, "assertion", 0) } else 

#define ASSERTJc_THROW(COND) { if(!(COND)) ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW1_s0(RuntimeException,"assertion",0); }


#define ASSERT(COND) if(!(COND)){ ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW1_s0(RuntimeException, "assertion", 0); }


#define ASSERT_s0_Jc(cond, TEXT, VALUE) { if(!(cond)) THROW1_s0(RuntimeException, TEXT, VALUE); }

/**Assertion with additional String and 2 values. They are evaluated only if cond==false. */ 
//#define ASSERTs_emC(cond, TEXT, VALUE1, VALUE2) { if(!(cond)) THROW_s0(RuntimeException, TEXT, VALUE1, VALUE2); }

/**Assertion without necessity of an thread context. The Thread context is gotten in the throw routine if necessary. */
#define ASSERTsn_emC(cond, TEXT, VALUE1, VALUE2) { if(!(cond)) THROW_s0n(RuntimeException, TEXT, VALUE1, VALUE2); }


#endif //#define __ASSERT_Jc__
