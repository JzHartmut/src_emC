#include <emC/OSAL/Environment_OSALemC.h>

int replace_Environment_OSALemC(char* dst, int zdst, char const* src) {
  int ixDst = 0;
  int ix = 0;
  char cc;
  while( ixDst < zdst && (cc = src[ix++]) !=0) {
    if(cc == '$') {
      int ixDstEnv = ixDst;
      char const* nameSrc = &dst[ixDstEnv];  //use dst as buffer for 0-terminated name
      while( ((cc = src[ix]) >='A' && cc <= 'Z') || (cc  >='a' && cc <= 'z')) {
        ix +=1;
        dst[ixDst++] = cc;
      }
      dst[ixDst] = 0;
      char const* envValue = getEnvironment_OSALemC(nameSrc);
      if(envValue !=null) {
        ixDst = ixDstEnv;
        while( (cc = *envValue++) !=0 && ixDst < zdst) {
          dst[ixDst++] = cc;
        }
      }
    }
    else if(cc !=0) {
      dst[ixDst++] = cc;
    }
  }
  if(ixDst < zdst) {
    dst[ixDst] = 0;
  }
  return ixDst;
}


