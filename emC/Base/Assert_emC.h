#ifndef HEADERGUARD_emC_Base_Assert_emC_h
#define HEADERGUARD_emC_Base_Assert_emC_h

#ifdef ASSERT_IGNORE_emC
 /**The assertion is fully ignored. An if-Block is always true.*/
 #define ASSERT_emC(COND, TEXT, VAL1, VAL2) true
#define ASSERTJc_MIN(VAR, MIN) { if(VAR <(MIN)) VAR = MIN; }

#define ASSERTJc_MAX(VAR, MAX) { if(VAR >(MAX)) VAR = MAX; }

#define ASSERTJc_EXCLMAX(VAR, MAX) { if(VAR >=(MAX)) VAR = (MAX)-1; }


#else
  /**The assertion will be checked. If it is false, the called routine invokes THROW.
   * Depending on THROW implementation either it is thrown (C++ Exception handling)
   * or a log will be written. 
   * It is possible to write
   * if(ASSERTs_emC(cond, "text", 123,456)) {
   *   //code will be executed only if assertion is given
   * }
   * 
   */
  extern_CCpp bool assert_s_emC(bool cond, char const* text, int val1, int val2);

  #define ASSERT_emC(COND, TEXT, VAL1, VAL2) ( COND ? true : assert_s_emC(false, TEXT, VAL1, VAL2) )

  //Note: The inline variant does not work in some C environments.
  //inline bool ASSERT_emC(bool cond, char const* text, int val1, int val2) {
  //  if(!cond) { assert_s_emC(cond, text, val1, val2); }
  //  return cond;
  //}


  #define ASSERTJc_MIN(VAR, MIN) { if(!(VAR >=(MIN))){ ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW_s0(RuntimeException, "assertion", 0,0); VAR = MIN; } }

  #define ASSERTJc_MAX(VAR, MAX) { if(!(VAR <(MAX))){ ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW1_s0(RuntimeException, "assertion", 0); VAR = MAX; } }

  #define ASSERTJc_EXCLMAX(VAR, MAX) { if(!(VAR <(MAX))) { ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW1_s0(RuntimeException, "assertion", 0); VAR = (MAX)-1; } }


#endif

#define ASSERTs_emC ASSERT_emC

#endif //HEADERGUARD_emC_Base_Assert_emC_h

