#include <emC/DefPortTypes_emC.h>
#include <string.h> //memset
#include "genRefl/emC/DefPortTypes_emC.crefl"


void ctor_DefPortTypes_emC(DefPortTypes_emC* thiz, int nrofAdditionalElements) {
  int bytes = sizeof(*thiz) + nrofAdditionalElements * sizeof(thiz->entries[0]);
  memset(thiz, 0, bytes);
  thiz->zEntries = (int16)(ARRAYLEN_emC(thiz->entries) + nrofAdditionalElements);
  thiz->pEntries = (Entry_DefPortType_emC_20_s*)&thiz->entries[0];
}

