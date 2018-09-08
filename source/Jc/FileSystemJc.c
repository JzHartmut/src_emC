/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this source the LGPL Lesser General Public License,
 * published by the Free Software Foundation is valid.
 * It means:
 * 1) You can use this source without any restriction for any desired purpose.
 * 2) You can redistribute copies of this source to everybody.
 * 3) Every user of this source, also the user of redistribute copies
 *    with or without payment, must accept this license for further using.
 * 4) But the LPGL ist not appropriate for a whole software product,
 *    if this source is only a part of them. It means, the user
 *    must publish this part of source,
 *    but don't need to publish the whole source of the own product.
 * 5) You can study and modify (improve) this source
 *    for own using or for redistribution, but you have to license the
 *    modified sources likewise under this LGPL Lesser General Public License.
 *    You mustn't delete this Copyright/Copyleft inscription in this source file.
 *
 * This source may be used also with another licence, if the author 
 * and all other here named co-authors have agreed to this contract.
 * Especially a company can use a copy of this sources in its products without publishing.
 * The user should have a underwritten contract therefore.
 *
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content File access Java-like in C
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 * @changes
 * 2010-01-21 Hartmut: All accesses to file system use now the os_file..() routines.
 *
 * @version 0.83
 */
#include "Jc/FileSystemJc.h"
#include "Jc/FileIoJc.h"
#include "Jc/ReflectionJc.h"
#include "string.h" //memset
#include "os_file.h"
extern ClassJc const reflection_FileWriterJc_s;



/*@CLASS_C FileSystemJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

MemC readBinFile_FileSystemJc(FileJc_s* file, MemC buffer)
{
  int bytes;
  int zFile;
  OS_HandleFile f1 = null;
  STACKTRC_ENTRY("readBinFile_FileSystemJc");
  TRY {
    if(PTR_MemC(buffer, void) == null){
      /**create the buffer here, detect the file size: */
      zFile = length_FileJc(file);
      buffer = alloc_MemC(zFile);
    } else {
      zFile = size_MemC(buffer); 
    }
    f1 = os_fopenToRead(file->fileDescription.absPath);
    if(f1 == null) {
      set_MemC(buffer, 0, null);
    } else {
      bytes = os_fread(f1, PTR_MemC(buffer, void), zFile);
      if(bytes <=0) {
        set_MemC(buffer, 0, null);  //no bytes read or error: return a null-buffer.
      }
    }
  }_TRY
  //forward any exception
  //CATCH(Exception, exc) {

  //}
  FINALLY{
    if(f1) os_fclose(f1);
  }
  END_TRY
  STACKTRC_RETURN buffer;
}





int writeBinFile_FileSystemJc(FileJc_s* file, int8_Y* buffer, struct ThreadContext_emC_t* _thCxt)
{
  OS_HandleFile f1;
  f1 = os_fopenToWrite(file->fileDescription.absPath, false);  //write new
  if(f1 != null) {
    os_fwrite(f1, buffer->data, buffer->head.length);
    os_fclose(f1);
  }
  return 0;
}
      













