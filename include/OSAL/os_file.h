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
 * @maintainer: Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @changes
 * 2011-01-07 Hartmut improved
 * 2010-06-01 Hartmut chg: separation of os_initFileDescription() from os_getFileDescription():
 *                    Concept: init doesn't access to the os-file system.
 * 2010-01-21 Hartmut creation: os_routines for all file accesses.
 **************************************************************************************************/
#ifndef __OSAL_os_file_h__
#define __OSAL_os_file_h__

#include <os_time.h>
#include <os_types_def.h>

/**The ANSI-C doesn't define the sys/stat.h, only POSIX-Standard. Therefore not all platforms implement this features.
 * This file supplies a commonly useable interface.
 */ 


/**Structure is filled on call of os_getFileDescription(...).
 */ 
typedef struct OS_FileDescription_t
{
  /**Files which are longer as 2 GByte aren't supported. */
  int32 fileLength;

  /**Some flag bits. Use macros to request it. */
  int32 flags;

  #define mExist_OS_FileDescription        1
  #define mCanRead_OS_FileDescription      2
  #define mCanWrite_OS_FileDescription     4
  #define mHidden_OS_FileDescription    0x08
  #define mDirectory_OS_FileDescription 0x10
  #define mFile_OS_FileDescription      0x20
  
  #define mAbsPathTested             0x10000 
  #define mFileDescriptionTested     0x20000 

  OS_TimeStamp timeChanged;
  
  /**Special pointer to any internal structure. */
  void* ptr1;
  
	/**Some operation systems doesn't support the full-C-compatible handling with pathes.
	 * To select a directory (may be only 1 level), the start-position of the file name
	 * in the absPath can be stored here. The separation character between path and name
	 * should be a valid path separator. That is '/' be default or '\' for windows-like.
	 * If a \0 is written as separator, the usage of a 0-terminated String is possible
	 * to select the directory path internally. But then the method getAbsolutePath_FileJc()
	 * returns this 0-character in its String. */ 
  int16 posNameInPath;

	/**Position of the start of given relative path while creating this structure.
	 * It is 0 if an absolute path is given on call, and if the absolute path isn't built. */
  int16 posRelatPathInPath;

  /**absolute path. It is stored in the form like the filesystem needs it. 
   * It means, it may have / or \ as separator and maybe a drive or other prefix.
	 * The parameter kMaxPathLength_OS_FileDescription for the length have to be defined in the os_types_def.h
	 */
  char absPath[kMaxPathLength_OS_FileDescription];   
  
} OS_FileDescription;




/**Fills the given instance ythis with the given file path. No os-functionality will be called.
 * @param addPathLength number of additional chars of the file path. It may be 0 normally. 
 *                      The struct OS_FileDescription contains 224 chars for the absolute file path.
 *                      If this parameter is >0, an additional memory space after the dst spaces should be given.
 * @param filepath path and file of the file. It may be a relativ path. It need not be 0-terminated. 
 *        It need not be persistent.
 *        Hint: In a multithread system the current directory to build the absolute path should be a property of the thread. 
 *              Therefore an internal thread context is necessary. 
 * @param zFilepath number of chars of the filepath-string. 
 * @return 0 on success, OS_INVALID_PARAMETER if the zFilepath is greater than the (internal buffer + addPathLength).
 */
int os_initFileDescription(OS_FileDescription* ythis, int addPathLength, char const* filepath, int zFilepath);




/**Accesses the file in the file system with the given description. 
 * Filles the properties of the file. 
 * @return 0 if ok, negative number on a system error. But it is ok, if the file doesn't exist.
 */
int os_getFileDescription(OS_FileDescription* ythis); 
//int os_getFileDescription(OS_FileDescription* dst, int addPathLength, const char* filepath); 

/**Returns true if the file exists. 
 * The proposition whether the file is existing is valid in the moment of calling [[os_getFileDescription(...)]].
 * It may be possible that the file was deleted meanwhile.
 */
#define os_exists_FileDescription(YTHIS) (os_getFileDescription(YTHIS)->flags & 0x1) 

 /**Returns true if the file able to read and it exists. 
 * The proposition whether the file is existing is valid in the moment of calling [[os_getFileDescription(...)]].
 * It may be possible that the file was deleted meanwhile.
 */
#define os_canRead_FileDescription(YTHIS) (os_getFileDescription(YTHIS)->flags & 0x2) 

/**Returns true if the file is able to write. The file may be existing or not. 
 * This proposition is valid in the moment of calling [[os_getFileDescription(...)]].
 * It may be possible that the file was deleted meanwhile.
 */
#define os_canWrite_FileDescription(YTHIS) (os_getFileDescription(YTHIS)->flags & 0x4) 


/**Handle to a file. The internal data structure is not known here. 
 * A ,,OS_HandleFile,, may be the FILE* pointer like in Standard C. 
 * It is also possible that it is a simple integer, which is converted to this pointer type.
 */
typedef struct OS_HandleFile_t* OS_HandleFile;


/**Open a file to read. The file should be exist. 
 * @return null if the file doesn't exist. Elsewhere the handle, which is able to use for read.
 */ 
OS_HandleFile os_fopenToRead(char const* filename); 

/**Open a file to write. This open action follows the convention of java.io.FileOutputStream.ctor(). 
 * If the file should be read simultaneously, the file should be opened to read too with an extra call.
 * The os layer itself may support such actions or not.
 * @return null if the file isn't able to write or create. Elsewhere the handle, which is able to use for write.
 */
OS_HandleFile os_fopenToWrite(char const* filename, bool append); 


int os_fclose(OS_HandleFile file);


int os_fflush(OS_HandleFile file);


/**Reads bytes from file.
 * @return if >=0, than the number of bytes which are read. It is <= maxNrofbytes, depending of available bytes.
 * This method may be delayed (thread switch is possible), if the conditions to read are met, but it needs some time.
 * The method doesn't block of no content is available. Either -1 is returned (end of file) or 0. 
 * @return If >=-1 than the total number of bytes read into the buffer, or -1 if there is no more data because the end of the file has been reached.
 *         It is the same convention like java.io.FileInputStream.read(...)
 *         If <=-2, than the writing process was faulty.
 */
int os_fread(OS_HandleFile file, void* buffer, int maxNrofbytes);


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
int os_fskip(OS_HandleFile file, int nrofbytes);


/**Writes bytes to file.
 * @return if >=0, than all the bytes are written. <0 on error.
 * This method may be delayed (thread switch is possible), if the conditions to write are met, 
 * but the write process requires a delaying. 
 */
int os_fwrite(OS_HandleFile file, void const* buffer, int nrofbytes);


/**Locks or unlocks a region or the whole file.
 * @param cmd ones of lock, sharedLock, checkLock, unlock TODO enum-def
 * @param len number of bytes to lock from the current position, or -1 for file-lock
 */
int os_flock(OS_HandleFile file, int cmd, int len);




#endif //__OSAL_os_file_h__
