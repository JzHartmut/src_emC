#include <emC/Jc/ReflectionJc.h>
#include <emC/Jc/FileIoJc.h>
#include <emC/Jc/FileSystemJc.h>
#include <emC/Base/MemC_emC.h>


/**internal method (private).
 * @set ythis->errorRelocationExtRefl is 0 of no error occurs. 
 * @return the readed and maybe corrected data.
 */
Data_ExtReflectionJc* correctContent_ExtReflectionJc(ExtReflectionJc_s* ythis, MemC buffer, int headerOffset, ThCxt* _thCxt)
{
  Data_ExtReflectionJc* extReflectionData = (Data_ExtReflectionJc*)(PTR_MemC(buffer, MemUnit) + headerOffset);
  /**The max. exclusive index in buffer*/ 
  int maxBuffer = size_MemC(buffer) - headerOffset;
  void const* minAddr= extReflectionData; 
  void const* maxAddr = ((MemUnit*)extReflectionData) + maxBuffer;
  intptr_t baseHead;
  void const* addrBaseClasses;
  bool bOk = true;
  intptr_t offsClassArray, offsReflData;
	STACKTRC_TENTRY("correctContent_ExtReflectionJc");
  
  /**relocate all relative addresses to absolute addresses:*/
  /**first the reference of arrayClasses. */
  baseHead = (intptr_t)(extReflectionData);
  offsClassArray = *(intptr_t*)(&extReflectionData->arrayClasses);
	extReflectionData->arrayClasses = (ClassJc_YP const*)(offsClassArray + baseHead);
	offsReflData = *(intptr_t*)(&extReflectionData->classDataBlock);
  extReflectionData->classDataBlock = (ClassJc const*)(offsReflData + baseHead); 
  if(!inRange_MemAreaC(extReflectionData->arrayClasses, minAddr, maxAddr)) {
    bOk = false;
    ythis->errorRelocationExtRefl = -2;
  }
  if(!inRange_MemAreaC(extReflectionData->classDataBlock, minAddr, maxAddr)) {
    bOk = false;
    ythis->errorRelocationExtRefl = -2;
  }

  /**The address of begin of block to the classDataBlock. It is the base for several pointers..*/
  addrBaseClasses = (extReflectionData->classDataBlock);
  if(bOk) {

    /**Relocate all references to the classes in extReflectionData->arrayClasses. */
    { int ixClass;
      int nrofClasses =  extReflectionData->arrayClasses->head.length;
      for(ixClass = 0; bOk && ixClass < nrofClasses; ixClass++)
      { ClassJc const*const* pClass = &extReflectionData->arrayClasses->data[ixClass];
        *(ClassJc const**)pClass = (ClassJc const*)addOffset_MemAreaC(addrBaseClasses, *(int*)pClass);
        if(!inRange_MemAreaC(*pClass, minAddr, maxAddr)) {
          bOk = false;
          ythis->errorRelocationExtRefl = -3;
        }
      }
    }
  }
  if(bOk) {
    /**Relocate all references in the class and field data. */
    { int ixReloc;
      int maxIx = offset_MemAreaC(addrBaseClasses, maxAddr) - sizeof(void*);
      int nrofReloc =  extReflectionData->nrofRelocEntries;
      for(ixReloc = 0; bOk && ixReloc < nrofReloc; ixReloc++)
      { int posReloc = extReflectionData->relocateAddr[ixReloc];
        /**Check: the index have to reference a position inside the buffer. */
        if(posReloc >=0 && posReloc <= maxIx) {
          /**Calculate the address of the memory location which should be changed.
           * because it is a pointer of different types, it should be addressed as void**. But a int** is better to debug. */
          int* addrReloc = (int*)addOffset_MemAreaC(addrBaseClasses, posReloc);
          int offsReloc = *addrReloc;  //The value in the bin file is the offset from the own address to the destination.
          /**The new value at memory location is the location itself + its content (the relative address value): */
          intptr_t addrdst = (intptr_t)addOffset_MemAreaC(addrReloc, offsReloc); //The address of the really destination
          if (inRange_MemAreaC(addrdst, minAddr, maxAddr)) {
            *addrReloc = addrdst;
          } else {
            /**Because the ixInClassDatas is checked already, this conditions shouldn't met any time: */
            bOk = false;
            ythis->errorRelocationExtRefl +=1;
          }
        } else {
          ythis->errorRelocationExtRefl +=1;
        }         
      }
    }
  }
  STACKTRC_LEAVE;
  return extReflectionData;  //returns always the data.

}

char const* load_ExtReflectionJc(ExtReflectionJc_s* ythis, StringJc fileName, int headerOffset)
{ 
  char const* sError = null;
	/**Use a FileJc for access properties of file, its the layer above OSAL, sys/stat isn't available in any C environment. */
  FileJc_s file;
  
  int zFile;
  
  MemC buffer;
  
  STACKTRC_ENTRY("loadExtReflection_Inspc");
  
  init_ObjectJc(&file.base.object, sizeof(file), 0);  //init stack instance in the way like Jc  
  ctorO_FileJc(&file.base.object, fileName, _thCxt);  //adequate new File(fileName)
  if(exists_FileJc(&file)) {
      Data_ExtReflectionJc* extReflectionData;
      /**File is exiting: */
      zFile = length_FileJc(&file);
      ALLOC_MemC(ythis->extReflectionBuffer, zFile);
      buffer = ythis->extReflectionBuffer;
      { /**Read the content. */

	MemC retMem = readBinFile_FileSystemJc(&file, buffer); //Note: retMem isn't use, only for null-test. read into buffer
	if(PTR_MemC(retMem, void) == null){
	    sError = "reflection-bin-file read error";
	}
      }
      if(sError == null){
	  extReflectionData = correctContent_ExtReflectionJc(ythis, buffer, headerOffset, _thCxt);

	  if(ythis->errorRelocationExtRefl == 0){
	      /**Save the results. */
	      extReflectionClasses_ReflectionJc[0] = extReflectionData->arrayClasses; //Note: intend more as one external file
	      ythis->extReflection = extReflectionData->arrayClasses;
	  } else {
	      sError = "reflection-bin-file content error";
	  }
	  ythis->extReflectionData = extReflectionData;  //only for inspect.
      }
  } else {
      sError = "reflection-bin-file not found";
  }
  STACKTRC_LEAVE; return sError;
}




