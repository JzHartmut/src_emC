#ifndef HEADERGUARD_emC_Base_Assert_emC_h
#define HEADERGUARD_emC_Base_Assert_emC_h

#ifdef ASSERT_IGNORE_emC
 /**The assertion is fully ignored. An if-Block is always true.*/
 #define ASSERT_emC(COND, TEXT, VAL1, VAL2) true
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
  inline bool ASSERT_emC(bool cond, char const* text, int val1, int val2) {
    if(!cond) { assert_s_emC(cond, text, val1, val2); }
    return cond;
  }

#endif

#define ASSERTs_emC ASSERT_emC

#endif //HEADERGUARD_emC_Base_Assert_emC_h

