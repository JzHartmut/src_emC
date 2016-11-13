
#define __TRYCPPJc



METHOD_C void debug__IndexOutOfBoundsException_OSALUserEXCEPT(char const* msg, int nr);

METHOD_C void stop_IndexOutOfBoundsException_OSALUserEXCEPT(int ix);

METHOD_C void exec_DEBUGOUT2_OSALUserDEBUG(char const* STR, int32 VAL);


#define throw_IndexOutOfBoundsException_OSALUserEXCEPT(MSG, NR) { debug__IndexOutOfBoundsException_OSALUserEXCEPT(MSG, NR); }

/**Checks the IX. IF <0 or >=MAX then set to 0 and invoke [[stop_IndexOutOfBoundsException_UserEXCEPT(...)]]. */ 
#define checkIndexOutOfBounds_OSALUserEXCEPT(IX, MAX) { if((IX) < 0 || (IX) >= (MAX)) { stop_IndexOutOfBoundsException_OSALUserEXCEPT(IX); (IX) = 0; } }


/**This is a macro which can be redirected to a printf output or to any log system to support debugging on runtime. 
 * For non debugging this macro should be empty. 
 */
#define DEBUGOUT2_OSALUserDEBUG(STR, VAL) exec_DEBUGOUT2_OSALUserDEBUG(STR, VAL); 
