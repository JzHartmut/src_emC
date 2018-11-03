#include <emC/DefPortTypes_emC.h>
#include <Jc/StringJc.h>

#include "genRefl/emC/DefPortTypes_emC.crefl"


char const cTypes_DefPortTypes_emC[] = "DFJISBCZUWVdfjisb";
int8 const lenTypes_DefPortTypes_emC[] = { 8, 4, 8, 4, 2, 1, 1, 1, 4, 2, 1, 16, 8, 16, 8, 4, 2};

ClassJc const* const reflTypes_DefPortTypes_emC[] = 
{
  &reflection__doubleJc
  , &reflection__floatJc
  , &reflection__int64Jc
  , &reflection__int32Jc
  , &reflection__int16Jc
  , &reflection__int8Jc
  , &reflection__charJc
  , &reflection__booleanJc
  , &reflection__uint32Jc
  , &reflection__uint16Jc
  , &reflection__uint8Jc
  , &reflection_double_complex
  , &reflection_float_complex
  , null
  , null
  , null
  , null
};


char const* parse_Entry_DefPortType_emC  (  Entry_DefPortTypeJc* thiz, StringJc type, StringJc name, int* posStartName, ThCxt* _thCxt)
{ STACKTRC_TENTRY("parse_Entry_DefPortType_emC");
  char const* err = null;
  if (type.ref == null) {
    int posSep = indexOf_C_StringJc(name, ':');
    if (posSep > 0) {
      type = substring_StringJc(name, 0, posSep, _thCxt);
      if (posStartName) { *posStartName = posSep +1; }
    }
    else {
      if(posStartName){ *posStartName = 0; }
      type = NULL_StringJc;  //especially length is 0.
      //return("parse_Entry_DefPortType_emC(): type is null, name does not contain a ':'");
    }
  }
  int zType = length_StringJc(type);
  const char* sType = PTR_StringJc(type);
  int pos = 0;
  int zDim = 0;
  thiz->type = 'F'; //default
  thiz->sizeType = 4; //default;
  while(pos < zType) {
    char cType = sType[pos];
    char nrType = searchChar_emC(cTypes_DefPortTypes_emC, -20, cType);
    if ( nrType >=0) {
      thiz->type = cType;                    //type char
      thiz->sizeType = lenTypes_DefPortTypes_emC[nrType];
      pos +=1;
    }
    else if (strchr("[,]", cType) != null) {  //structure char for arrays
      pos +=1;
    }
    else if (cType >= '0' && cType <= '9') {  //number
      int sizeDim =0; 
      thiz->sizeArray[thiz->dimensions] = parseIntRadix_emC(sType+pos, zType, 10, &sizeDim);
      thiz->dimensions +=1;
      pos += sizeDim;
    }
    else {
      STACKTRC_RETURN "parse_Entry_DefPortType_emC(): unexpected format char";
    }
  }
  if(err == null){ thiz->newDefined =1; }
  STACKTRC_RETURN err;
}


bool checkType_Entry_DefPortType_emC(Entry_DefPortTypeJc* thiz, ClassJc const* reflectionType) {
  char nrType = searchChar_emC(cTypes_DefPortTypes_emC, -20, thiz->type);
  if(nrType < 0 || nrType >= ARRAYLEN_emC(reflTypes_DefPortTypes_emC)) return false;
  ClassJc const* reflTypeCmp = reflTypes_DefPortTypes_emC[nrType];
  if(reflTypeCmp == reflectionType) return true; 
  //Note: compare names, the reflection instances can be differ.
  else return 0 == strncmp(reflTypeCmp->name, reflectionType->name, sizeof(reflTypeCmp->name));
}
