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
 * @content This file contains the implementation of os_file.h for MS-Windows 
 *          using the lo-level un-buffered file-routines.
 * @author Hartmut Schorrig www.vishia.org
 * @version 0.94
 * list of changes:
 * 2010-05-23: JcHartmut creation from os_Windows/os_file.c, from the fopen-routines.
 *
 ****************************************************************************/
#include <os_file.h>

#include <os_error.h>



#include <sys/stat.h>
#include <fcntl.h>
//#include <io.h>
#include <string.h> //memset

int os_initFileDescription(FileDescription_OSAL* ythis, int addPathLength, char const* filepath, int zFilepath)
{
  int error = 0;
  ythis->flags = 0; 
  if(addPathLength < 0) { addPathLength = 0; }
  if(zFilepath >= (int)(sizeof(ythis->absPath) + addPathLength)) {
    error = OS_INVALID_PARAMETER;
    os_NotifyError(error, "file path to long", zFilepath, sizeof(ythis->absPath) + addPathLength -1); 
    zFilepath = sizeof(ythis->absPath) + addPathLength -1;
  }
  memset(ythis->absPath, sizeof(ythis->absPath) + addPathLength, 0);
  strncpy(ythis->absPath,filepath, zFilepath); 
  return error;
}





FileDescription_OSAL* refresh_FileDescription_OSAL(FileDescription_OSAL* ythis)
{
  struct stat statData;
  int ok = stat(ythis->absPath, &statData);
  if(ok == 0)
  { 
    ythis->fileLength = statData.st_size;
    //TODO check read and write ability from stat
    ythis->flags = mExist_FileDescription_OSAL | mCanRead_FileDescription_OSAL;
    { //st_mtime is the time of last changed, seconds after 1970 in UTC. MS-Visual studio: Its a long.
      int32 timeLastChanged = statData.st_mtime;
      setUTC_OS_TimeStamp(ythis->timeChanged, timeLastChanged, 0);
    }
  }
  else
  { ythis->flags &= ~mExist_FileDescription_OSAL;
  }
  ythis->flags |= mTested_FileDescription_OSAL;
  return ythis;
}





/**Open a file to read. The file should be exist. 
 * @return null if the file doesn't exist. Elsewhere the handle, which is able to use for read.
 */ 
OS_HandleFile os_fopenToRead(char const* filename)
{ return (OS_HandleFile)open(filename, O_RDONLY);
}

/**Open a file to write. This open action follows the convention of java.io.FileOutputStream.ctor(). 
 * If the file should be read simultaneously, the file should be opened to read too with an extra call.
 * The os layer itself may support such actions or not.
 * @return null if the file isn't able to write or create. Elsewhere the handle, which is able to use for write.
 */
OS_HandleFile os_fopenToWrite(char const* filename, bool append)
{ return (OS_HandleFile)open(filename, O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC));
}


int os_fclose(OS_HandleFile file)
{ int success = close( (int) file);
  if(success == 0) { return 0; }
  else { return -1; }
}


int os_fflush(OS_HandleFile file)
{ //fflush((FILE*)file);
  return 0;
}



/**Reads bytes from file.
 * @return if >=0, than the number of bytes which are read. It is <= maxNrofbytes, depending of available bytes.
 * This method may be delayed (thread switch is possible), if the conditions to read are met, but it needs some time.
 * The method doesn't block of no content is available. Either -1 is returned (end of file) or 0. 
 * @return If >=-1 than the total number of bytes read into the buffer, or -1 if there is no more data because the end of the file has been reached.
 *         It is the same convention like java.io.FileInputStream.read(...)
 *         If <=-2, than the writing process was faulty.
 */
int os_fread(OS_HandleFile fileP, void* buffer, int maxNrofbytes)
{ //the description of FileSystem-Segger doesn't contain anything about behaviour at end of file while OS_Read().
  //FILE* file = (FILE*) fileP;
  //int ret = fread(buffer, 1, maxNrofbytes, file);
  int ret = read((int)fileP, buffer, maxNrofbytes);
  return ret;  //it is maxNrofbytes
}


/**Skips over and discards n bytes of data from the input stream. 
 * The skip method may, for a variety of reasons, end up skipping over some smaller number of bytes, possibly 0. 
 * If n is negative, an IOException is thrown, even though the skip method of the InputStream superclass does nothing in this case. 
 * The actual number of bytes skipped is returned. 
 *
 * This method may skip more bytes than are remaining in the backing file. 
 * This produces no exception and the number of bytes skipped may include some number of bytes that were beyond the EOF of the backing file. Attempting to read from the stream after skipping past the end will result in -1 indicating the end of the file. 
 * @param nrofbytes - the number of bytes to be skipped. 
 * @return the actual number of bytes skipped. 
 */
int os_fskip(OS_HandleFile file, int32_t nrofbytes)
{ return -1; //TODO
}

/**Writes bytes to file.
 * @return if >=0, than all the bytes are written. <0 on error.
 * This method may be delayed (thread switch is possible), if the conditions to write are met, 
 * but the write process requires a delaying. 
 */
int os_fwrite(OS_HandleFile fileP, void const* buffer, int nrofbytes)
{ //FILE* file = (FILE*) fileP;
  //int ret = fwrite(buffer, 1, nrofbytes, file);
  int ret = write((int)fileP, buffer, nrofbytes);
  return ret;  //it is maxNrofbytes
}
