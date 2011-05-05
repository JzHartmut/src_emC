#include <Jc/StringJc.h>
#include <BlockHeap/BlockHeapJc_admin.h>
#include <J1c/StringPartJc.h>


typedef struct 
{ int32 value_A;
  float value_B;
  double value_C;
  int32 value_D[20];
  int ixValue_D;
} ExcampleScannedValues;

#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
void testScan(StringJc src, ExcampleScannedValues* values)
{
  bool scanOk;
  STACKTRC_ENTRY("testCpp");  
  StringPartJc sp(src);  //in stack, call ctor
  sp.setIgnoreWhitespaces(true);
  do {
		if(scanOk = sp.scan("value_A").scan("=").scanInteger().scan(";").scanOk()){
			values->value_A = (int32)sp.getLastScannedIntegerNumber();
		}
		else if(scanOk = sp.scan(z_StringJc("value_B")).scan(z_StringJc("=")).scanFloatNumber().scan(z_StringJc(";")).scanOk()){
			values->value_B = (float)sp.getLastScannedFloatNumber();
		}
		else if(scanOk = sp.scan(z_StringJc("value_C")).scan(z_StringJc("=")).scanFloatNumber().scan(z_StringJc(";")).scanOk()){
			values->value_C = sp.getLastScannedFloatNumber();
		}
		else if(scanOk = sp.scan(z_StringJc("value_D")).scan(z_StringJc("=")).scanHexOrDecimal(8).scan(z_StringJc(";")).scanOk()){
      if(values->ixValue_D < ARRAYLEN(values->value_D)){
        values->value_D[values->ixValue_D++] = (int)sp.getLastScannedIntegerNumber();
      } else { /*overflow of user array. */ }
		}
  } while(scanOk);
  STACKTRC_LEAVE;
}

#else //__CPLUSPLUSJcpp


void testScan(StringJc src, ExcampleScannedValues* values)
{
  bool scanOk;
  StringPartJc_s sp = CONST_StringPartJc(&sp);
  STACKTRC_ENTRY("testCpp");  
  ctorO_S_StringPartJc(&sp.base.object, src, _thCxt);
  setIgnoreWhitespaces_StringPartJc(&sp,true, _thCxt);
  do {
		if( scan_StringPartJc_F(&sp, z_StringJc("value_A"), _thCxt)
      , scan_StringPartJc_F(&sp, z_StringJc("="), _thCxt)
      , scanInteger_StringPartJc_F(&sp, _thCxt)
      , scan_StringPartJc_F(&sp, z_StringJc(";"), _thCxt)
      , scanOk = scanOk_StringPartJc_F(&sp, _thCxt)
      ){
			values->value_A = (int32)getLastScannedIntegerNumber_StringPartJc(&sp, _thCxt);
		}
		else 
    if( scan_StringPartJc_F(&sp, z_StringJc("value_B"), _thCxt)
      , scan_StringPartJc_F(&sp, z_StringJc("="), _thCxt)
      , scanFloatNumber_StringPartJc_F(&sp, _thCxt)
      , scan_StringPartJc_F(&sp, z_StringJc(";"), _thCxt)
      , scanOk = scanOk_StringPartJc_F(&sp, _thCxt)
      ){
			values->value_B = (float)getLastScannedFloatNumber_StringPartJc_F(&sp, _thCxt);
		}
		else 
    if( scan_StringPartJc_F(&sp, z_StringJc("value_C"), _thCxt)
      , scan_StringPartJc_F(&sp, z_StringJc("="), _thCxt)
      , scanFloatNumber_StringPartJc_F(&sp, _thCxt)
      , scan_StringPartJc_F(&sp, z_StringJc(";"), _thCxt)
      , scanOk = scanOk_StringPartJc_F(&sp, _thCxt)
      ){
			values->value_C = getLastScannedFloatNumber_StringPartJc_F(&sp, _thCxt);
		}
		else 
    if( scan_StringPartJc_F(&sp, z_StringJc("value_D"), _thCxt)
      , scan_StringPartJc_F(&sp, z_StringJc("="), _thCxt)
      , scanHexOrDecimal_StringPartJc_F(&sp, 8, _thCxt)
      , scan_StringPartJc_F(&sp, z_StringJc(";"), _thCxt)
      , scanOk = scanOk_StringPartJc_F(&sp, _thCxt)
      ){
      if(values->ixValue_D < ARRAYLEN(values->value_D)){
        values->value_D[values->ixValue_D++] = (int32)getLastScannedIntegerNumber_StringPartJc_F(&sp, _thCxt);
      } else { /*overflow of user array. */ }
		}
  } while(scanOk);
  STACKTRC_LEAVE;
}

#endif //__CPLUSPLUSJcpp


void testStringPart()
{
  StringJc input = s0_StringJc("  value_A = 234; value_B = 234.5e3; value_D=0x123abcd; value_D=1000; ");
  ExcampleScannedValues values = {0};
  STACKTRC_ENTRY("testStringPart");  
  testScan(input, &values);
  
  STACKTRC_LEAVE;
}







//BlockHeapJc blockHeap;
    

void main()
{
  STACKTRC_ENTRY("main");
  //os_initLib();
  { struct LogMessageFW_t* log = null;
    //MemC mem_blockHeap = build_MemC(&blockHeap, sizeof(blockHeap));
    //MemC memHeap = alloc_MemC(0x4000);
    //ctor_BlockHeapJc(mem_blockHeap, memHeap, 0x400, 0x7C);
    //setCurrent_BlockHeapJc(&blockHeap, _thCxt);
    //init-pass
    //setRunMode_BlockHeapJc(&blockHeap, log, 2001, 2002, 2003);
    testStringPart();
  }
  STACKTRC_LEAVE;

}


