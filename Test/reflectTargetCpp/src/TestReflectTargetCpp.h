#ifndef __TestReflectTargetCpp_h__
#define __TestReflectTargetCpp_h__
#include <Jc/ObjectJc.h>

class SubData
{ private: 
  int x,y;
  float a,b;
  
  void execute(float input);


};


class Main: public SubData, public ObjectJc
{
  private:
  class SubData* sibling;
  
  class Data2* data2;
  
  int i,j,k;
  
  public: Main();
  
  public: void execute();

};




class Data2
{ private:
  int m,n;
  float e,f;
  double g;
  
  void execute2(float input);


};


#endif //__TestReflectTargetCpp_h__
