#ifndef HGUARD_specific_OSemC
#define HGUARD_specific_OSemC

struct Thread_OSemC_T;

//tag::Mutex[]
#define DEF_Mutex_OSemC  // do not use the common definition.
typedef struct Mutex_OSemC_T{
  int16 maskIntr;   //:bits which system-interrupt should be disabled.
}Mutex_OSemC_s;
//end::Mutex[]




#endif //HGUARD_specific_OSemC
