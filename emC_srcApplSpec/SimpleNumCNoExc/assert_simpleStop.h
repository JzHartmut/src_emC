#ifndef __ASSERTJc__
#define __ASSERTJc__

#ifndef __os_types_def_common_h__
  //defines extern_C
  #include <types_def_common.h>
#endif  

//This routine should be linked. It should stop the application in a while loop 
//to set a break point in debugger.
extern_C bool stop_AssertJc();  //have to return true


#define ASSERTJc(COND) if(!(COND)) { stop_AssertJc(); }
#define ASSERTJc_TEST(COND) { if(!(COND)) { stop_AssertJc(); }}


#define ASSERTJc_MIN(VAR, MIN) { if(!(VAR >=(MIN))){ stop_AssertJc(); VAR = MIN; } }

#define ASSERTJc_MAX(VAR, MAX) { if(!(VAR <(MAX))){ stop_AssertJc(); VAR = MAX; } }

#define ASSERTJc_EXCLMAX(VAR, MAX) { if(!(VAR <(MAX))) { stop_AssertJc(); VAR = (MAX)-1; } }

#define ASSERTJc_RANGE(VAR, MIN, MAX) { if(!(VAR >=(MIN) && VAR<=(MAX))){ stop_AssertJc(); VAR = VAR > (MAX) ? (MAX) : (MIN); } }



#define ASSERTJc_RET(COND, RETVAL) { if(!(COND)){ stop_AssertJc(); return RETVAL; } }

#define ASSERTJc_RETVOID(COND) { if(!(COND)){ stop_AssertJc(); return; } }

#define ASSERTJc_IF(COND) if(!(COND)) { stop_AssertJc(); } else 

#define ASSERTJc_CORR(COND) if(!(COND) && stop_AssertJc())

#define ASSERTJc_THROW(COND) { if(!(COND)) THROW1_s0(RuntimeException,"compareAndSet-fail",0); }


#define ASSERT(COND) ASSERTJc_TEST(COND)


#define ASSERT_s0_Jc(cond, TEXT, VALUE) { if(!(cond)) { stop_AssertJc(); } }


#endif //#define __ASSERT_Jc__
