#include <emC/Base/Object_emC.h>


ObjectJcpp::ObjectJcpp()
#ifndef DEF_ObjectJc_SIMPLE
  : significance_ObjectifcBase(kSignificance_ObjectifcBase)
  //, significanceAddress_ObjectifcBase(this)  NOTE: note possible because this is not accessible here! 
  #endif
{ //NOTE the significanceAddress_ObjectifcBase is const void* to prevent change outside,
  //     but it can't set in constructor list with this.
  #ifndef DEF_ObjectJc_SIMPLE
  *(void**)(&significanceAddress_ObjectifcBase) = this;
  #endif
}

