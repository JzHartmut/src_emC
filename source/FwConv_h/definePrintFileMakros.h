#include <stdio.h>  //printf

extern_C char const* debugPRINTF[10];
#define DEFINE_debugPRINTF

#define PRINTF_OPEN(PATH) { debugPRINTF[0] = fopen(PATH, "wb"); } 
#define PRINTF_CLOSE() { if(debugPRINTF[0]) { fclose(debugPRINTF[0]); debugPRINTF[0] = null; } } 


#define PRINTF2(S, A)           { if(debugPRINTF[0]) { fprintf(debugPRINTF[0], S, A); fflush(debugPRINTF[0]); }}
#define PRINTF3(S, A, B)        { if(debugPRINTF[0]) { fprintf(debugPRINTF[0], S, A,B); fflush(debugPRINTF[0]); }}
#define PRINTF4(S, A, B,C)      { if(debugPRINTF[0]) { fprintf(debugPRINTF[0], S, A,B,C); fflush(debugPRINTF[0]); }}
#define PRINTF5(S, A,B,C,D)     { if(debugPRINTF[0]) { fprintf(debugPRINTF[0], S, A,B,C,D); fflush(debugPRINTF[0]); }}
#define PRINTF6(S, A,B,C,D,E)   { if(debugPRINTF[0]) { fprintf(debugPRINTF[0], S, A,B,C,D,E); fflush(debugPRINTF[0]); }}



/*For Multithreading: Use NR for only one thread!*/
#define PRINTX_OPEN(NR, PATH) { if(NR >=0 && NR < 10) { debugPRINTF[NR] = PATH; } } 
#define PRINTX_CLOSE(NR) { if(NR >=0 && NR < 10 && debugPRINTF[NR]) { debugPRINTF[NR] = null; } } 


#define PRINTX(NR, S)               { if(NR >=0 && NR < 10 && debugPRINTF[NR]) { FILE* f = fopen(debugPRINTF[NR], "wb"); if(f) { fprintf(f, S); fclose(f); }}}
#define PRINTX2(NR, S, A)           { if(NR >=0 && NR < 10 && debugPRINTF[NR]) { FILE* f = fopen(debugPRINTF[NR], "wb"); if(f) { fprintf(f, S, A); fclose(f); }}}
#define PRINTX3(NR, S, A, B)        { if(NR >=0 && NR < 10 && debugPRINTF[NR]) { FILE* f = fopen(debugPRINTF[NR], "wb"); if(f) { fprintf(f, S, A,B); fclose(f); }}}
#define PRINTX4(NR, S, A, B,C)      { if(NR >=0 && NR < 10 && debugPRINTF[NR]) { FILE* f = fopen(debugPRINTF[NR], "wb"); if(f) { fprintf(f, S, A,B,C); fclose(f); }}}
#define PRINTX5(NR, S, A,B,C,D)     { if(NR >=0 && NR < 10 && debugPRINTF[NR]) { fprintf(debugPRINTF[NR], S, A,B,C,D); fflush(debugPRINTF[NR]); }}
#define PRINTX6(NR, S, A,B,C,D,E)   { if(NR >=0 && NR < 10 && debugPRINTF[NR]) { fprintf(debugPRINTF[NR], S, A,B,C,D,E); fflush(debugPRINTF[NR]); }}

