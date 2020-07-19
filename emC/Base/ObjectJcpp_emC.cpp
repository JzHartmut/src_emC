#include <emC/Base/Object_emC.h>

#ifdef DEF_ObjectJc_FULLCAPABILITY
ObjectJcpp::ObjectJcpp()
#ifdef DEF_ObjectJc_OWNADDRESS
  //: significance_ObjectifcBase(kSignificance_ObjectifcBase)
  //, significanceAddress_ObjectifcBase(this)  NOTE: note possible because this is not accessible here! 
#endif
{ //NOTE the significanceAddress_ObjectifcBase is const void* to prevent change outside,
  //     but it can't set in constructor list with this.
  #ifdef DEF_ObjectJc_OWNADDRESS
  //*(void**)(&significanceAddress_ObjectifcBase) = this;
  #endif
}
#endif // DEF_ObjectJc_FULLCAPABILITY

