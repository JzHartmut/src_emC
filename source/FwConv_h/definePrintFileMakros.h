#include <stdio.h>  //printf

extern_C FILE* debugPRINTF;
#define DEFINE_debugPRINTF

#define PRINTF_OPEN(PATH) { debugPRINTF = fopen(PATH, "wb"); } 
#define PRINTF_CLOSE() { if(debugPRINTF) { fclose(debugPRINTF); debugPRINTF = null; } } 


#define PRINTF2(S, A)           { if(debugPRINTF) { fprintf(debugPRINTF, S, A); fflush(debugPRINTF); }}
#define PRINTF3(S, A, B)        { if(debugPRINTF) { fprintf(debugPRINTF, S, A,B); fflush(debugPRINTF); }}
#define PRINTF4(S, A, B,C)      { if(debugPRINTF) { fprintf(debugPRINTF, S, A,B,C); fflush(debugPRINTF); }}
#define PRINTF5(S, A,B,C,D)     { if(debugPRINTF) { fprintf(debugPRINTF, S, A,B,C,D); fflush(debugPRINTF); }}
#define PRINTF6(S, A,B,C,D,E)   { if(debugPRINTF) { fprintf(debugPRINTF, S, A,B,C,D,E); fflush(debugPRINTF); }}

