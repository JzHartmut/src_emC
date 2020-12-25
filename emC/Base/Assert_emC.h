#ifndef HEADERGUARD_emC_Base_Assert_emC_h
#define HEADERGUARD_emC_Base_Assert_emC_h

#ifdef ASSERT_IGNORE_emC
   /**The assertion is fully ignored. An if-Block is always true.*/
   #define ASSERT_emC(COND, TEXT, VAL1, VAL2)

  /**This variant of assertion enables the execution of a following code only if the assertion mets.
   * Because the assertions are ignored here, the construct is simple:
   * Pattern:<pre>
   * IF_ASSERT_emC(condition, "failure description", value1, value2) {
   *   //execute only if met.
   * }</pre>
   * creates:<pre>
   * {
   *   //execute only if met.
   * }</pre>
   * */
  #define IF_ASSERT_emC(COND, TEXT, VAL1, VAL2)

  #define CHECK_ASSERT_emC(COND, TEXT, VAL1, VAL2) true

  #define ASSERTJc_MIN(VAR, MIN) { if(VAR <(MIN)) VAR = MIN; }

  #define ASSERTJc_MAX(VAR, MAX) { if(VAR >(MAX)) VAR = MAX; }

  #define ASSERTJc_EXCLMAX(VAR, MAX) { if(VAR >=(MAX)) VAR = (MAX)-1; }


#else
  /**Check the assertion.
   * It may be a target special implementation. It should be invoke THROW if Exception handling is used.
   * @return cond for if construct.
   *
   */
  extern_C bool assert_s_emC(bool cond, char const* text, int val1, int val2, char const* file, int line);

  /**The assertion will be checked. If it is false, the called routine invokes THROW
   * depending on implementation of assert_s_emC(...)
   * Depending on THROW implementation either it is thrown (C++ Exception handling)
   * or a log will be written. 
   */
  #define ASSERT_emC(COND, TEXT, VAL1, VAL2) { if(!(COND)) { assert_s_emC(false, TEXT, VAL1, VAL2, __FILE__, __LINE__); } }


  /**This variant of assertion enables the execution of a following code only if the assertion mets.
   * Pattern:<pre>
   * IF_ASSERT_emC(condition, "failure description", value1, value2) {
   *   //execute only if met.
   * }</pre>
   * */
  #define IF_ASSERT_emC(COND, TEXT, VAL1, VAL2) if(!(COND)) { assert_s_emC(false, TEXT, VAL1, VAL2, __FILE__, __LINE__) } else

  /**This variant of assertion enables the execution of a following code only if the assertion mets
   * and contains a branch for faulty assertion.
   * Pattern:<pre>
   * if(CHECK_ASSERT_emC(condition, "failure description", value1, value2)) {
   *   //execute only if met.
   * } else {
   *   //alternative if the assertion does not met. 
   * }</pre>
   * */
  #define CHECK_ASSERT_emC(COND, TEXT, VAL1, VAL2) ((COND) || assert_s_emC(false, TEXT, VAL1, VAL2, __FILE__, __LINE__) )

  

  #define ASSERTJc_MIN(VAR, MIN) { if(!(VAR >=(MIN))){ ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW_s0(RuntimeException, "assertion", 0,0); VAR = MIN; } }

  #define ASSERTJc_MAX(VAR, MAX) { if(!(VAR <(MAX))){ ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW1_s0(RuntimeException, "assertion", 0); VAR = MAX; } }

  #define ASSERTJc_EXCLMAX(VAR, MAX) { if(!(VAR <(MAX))) { ThCxt* _thCxt = getCurrent_ThreadContext_emC(); THROW1_s0(RuntimeException, "assertion", 0); VAR = (MAX)-1; } }


#endif

#define ASSERTs_emC ASSERT_emC

//ASSERT is commonly valid, it may be defined anywhere other too.
#ifndef ASSERT
  #define ASSERT(COND) ASSERT_emC(COND, "Assertion", 0,0)
#endif



#endif //HEADERGUARD_emC_Base_Assert_emC_h

