
#include <iostream>

using namespace std;


void EXPECT_TRUEmsg(bool val, char const* msg) {
  if(!val) {
    cerr<<endl<<msg;
  }
}


void EXPECT_FALSEmsg(bool val, char const* msg) {
  if(val) {
    cerr<<endl<<msg;
  }
}


bool EXPECT_TRUEmsg1(bool val, char const* sfile, int line) {
  if(!val) {
    cerr << endl << sfile << "@" << line << ": ";
    return true;
  }
  else return false;
}


void EXPECT_FALSEmsg1(bool val, char const* sfile, int line) {
  if(val) {
    cerr << endl << sfile << "@" << line << ": ";
  }
}
