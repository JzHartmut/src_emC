#include <emC/Base/DefPortTypes_emC.h>
#include <string.h> //memset
#include "emC/Base/genRefl/DefPortTypes_emC.crefl"
#include <emC/Base/Object_emC.h>


void ctor_DefPortTypes_emC(DefPortTypes_emC* thiz, int nrofAdditionalElements) {
  int bytes = sizeof(*thiz) + nrofAdditionalElements * sizeof(thiz->entries[0]);
  memset(thiz, 0, bytes);
  thiz->zEntries = (int16)(ARRAYLEN_emC(thiz->entries) + nrofAdditionalElements);
  thiz->pEntries = (Entry_DefPortType_emC_20_s*)&thiz->entries[0];
}




void set_DefPortTypes_emC(DefPortTypes_emC* thiz, int ix, char cType, char const* sName, ClassJc const* refl, char const* sType, int zArray, EPortType_Entry_DefPortType_emC io) {
  thiz->entries[ix].type = cType;
  thiz->entries[ix].refl = refl;  //may be null, only used for buses.
  if(zArray <0){ thiz->entries[ix].dimensions = -1; }
  else if(zArray ==0){ thiz->entries[ix].dimensions = 1; thiz->entries[ix].sizeArray[0] = 1; }
  else { thiz->entries[ix].dimensions = 1; thiz->entries[ix].sizeArray[0] = zArray; }
  thiz->entries[ix].newDefined_Tstep_Tinit |= io;
  thiz->entries[ix].sName = sName;
  thiz->entries[ix].sType = sType;
  int32 mBitInp = 1<<ix;
  int32 mBitOut = 1<< (ix - thiz->nrofInputs);
  bool bOutput = false;
  //write to common values:
  switch (io) {
  case mStepOut_Entry_DefPortType_emC:    thiz->mOutputInit |= mBitOut;     bOutput = true; break;
  case mStepIn_Entry_DefPortType_emC:     thiz->mInputInit |= mBitInp; break;
  case mOutputFnCall_Entry_DefPortType_emC: bOutput = true; break;
  case mOutputThizInit_Entry_DefPortType_emC: thiz->mOutputInit |= mBitOut; bOutput = true; break;
  case mOutputThizStep_Entry_DefPortType_emC: thiz->mOutputStep |= mBitOut; bOutput = true; break;
  case mOutputInit_Entry_DefPortType_emC: thiz->mOutputInit |= mBitOut;     bOutput = true; break;
  case mOutputStep_Entry_DefPortType_emC: thiz->mOutputStep |= mBitOut;     bOutput = true; break;
  case mInputInit_Entry_DefPortType_emC:  thiz->mInputInit  |= mBitInp; break;
  case mInputUpd_Entry_DefPortType_emC:   thiz->mInputUpd   |= mBitInp; break;
  case mInputStep_Entry_DefPortType_emC:  thiz->mInputStep  |= mBitInp; break;
  }
  if (!bOutput && ix >= thiz->nrofInputs) {
    thiz->nrofInputs = ix+1;  //for succesive writing
  }
  if (bOutput && ix >= (thiz->nrofInputs + thiz->nrofOutputs)) {
    thiz->nrofOutputs = ix+1 - thiz->nrofInputs;
  }
}


