/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this software-package the LGPL Lesser General Public License, 
 * published by the Free Software Foundation is valid at first. 
 * This is valid, if no other special licence contract is agreed. It means: 
 * 1. You can use this source without any restriction for any desired purpose.  
 * 2. You can redistribute copies of this source to everybody.  
 * 3. Every user of this source, also the user of redistribute copies with or without payment, 
 *    must accept this license for further using.  
 * 4. But the LPGL ist not appropriate for a whole software product, 
 *    if this source is only a part of them. It means, the user must publish this part of source, 
 *    but don't need to publish the whole source of the own product.  
 * 5. You can study and modify (improve) this source for own using or for redistribution, 
 *    but you have to license the modified sources likewise under this LGPL Lesser General Public License.  
 * 6. You mustn't delete this Copyright/Copyleft inscription in this software package and in all source files. 
 *    If you need only a part of this software-package, you must place this Copyright/Copyleft inscription 
 *    at an easily noticeable position in the adequate file tree. 
 * 7. If you are changing and publishing the content of source files, 
 *    you mustn't delete the Copyright/Copyleft inscription inclusive the first author(s) in the source files. You have to write your changes and your name additionally in the description part for changes in the source files. If you use a part from source files as copy in your own files only, you have to name the author of that part of the sources in your sources. Furthermore you have to declare the usage of sources of the author in your product. 
 * Special licence agreements:
 *
 * If this software or a part of them will be used in a comprehensive software-package 
 * without free publishing of its content or usage, 
 * then a special licence agreement in any other form is possible and necessary. 
 * All developers and users of this software-package should agree to it, 
 * with subscribing a contract, which is stored by both partners in paper-written form. 
 * The state of existence of such a contract doesn't need to be published.
 * But a proper hint to the special licence agreement have to be stored at a position in the file-tree, 
 * which is able to visit from outside, if the content of the files are able to visit from outside too. 
 * If the sources and its usage and the licence is secrecy, it is okay too.
 *
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

#include <applstdef_emC.h>
#include <emC/OSAL/os_time.h>

struct FileLock_OSAL_t;

/**The ANSI-C doesn't define the sys/stat.h, only POSIX-Standard. Therefore not all platforms implement this features.
 * This file supplies a commonly useable interface.
 */ 


/**Structure is filled on call of os_getFileDescription(...).
 */ 
C_TYPE typedef struct FileDescription_OSAL_t
{
  /**Files which are longer as 2 GByte aren't supported. */
  int32_t fileLength;

  /**Some flag bits. Use macros to request it. */
  int32_t flags;

  #define mExist_FileDescription_OSAL        1
  #define mCanRead_FileDescription_OSAL      2
  #define mCanWrite_FileDescription_OSAL     4
  #define mHidden_FileDescription_OSAL    0x08
  #define mDirectory_FileDescription_OSAL 0x10
  #define mFile_FileDescription_OSAL      0x20
  
  #define mAbsPathTested_FileDescription_OSAL 0x10000 
  #define mTested_FileDescription_OSAL        0x20000 

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
  int16_t posNameInPath;

	/**Position of the start of given relative path while creating this structure.
	 * It is 0 if an absolute path is given on call, and if the absolute path isn't built. */
  int16_t posRelatPathInPath;

  /**absolute path. It is stored in the form like the filesystem needs it. 
   * It means, it may have / or \ as separator and maybe a drive or other prefix.
	 * The parameter kMaxPathLength_FileDescription_OSAL for the length have to be defined in the os_types_def.h
	 */
  char absPath[kMaxPathLength_FileDescription_OSAL];   
  
} FileDescription_OSAL;




/**Fills the given instance ythis with the given file path. No os-functionality will be called.
* @param addPathLength number of additional chars of the file path. It may be 0 normally.
*                      The struct FileDescription_OSAL contains 224 chars for the absolute file path.
*                      If this parameter is >0, an additional memory space after the dst spaces should be given.
* @param filepath path and file of the file. It may be a relativ path. It need not be 0-terminated.
*        It need not be persistent.
*        Hint: In a multithread system the current directory to build the absolute path should be a property of the thread.
*              Therefore an internal thread context is necessary.
* @param zFilepath number of chars of the filepath-string.
* @return 0 on success, OS_INVALID_PARAMETER if the zFilepath is greater than the (internal buffer + addPathLength).
*/
extern_C int init_FileDescription_OSAL(FileDescription_OSAL* ythis, int addPathLength, char const* filepath, int zFilepath);

/**Fills the given instance with the given file path based on a given directory. No os-functionality will be called.
* @param addPathLength number of additional chars of the file path. It may be 0 normally.
*                      The struct FileDescription_OSAL contains 224 chars for the absolute file path.
*                      If this parameter is >0, an additional memory space after the dst spaces should be given.
* @param dir a given directory, should be tested already.
* @param filepath relative path of the file to the given dir. It need not be 0-terminated.
*        It need not be persistent.
* @param zFilepath number of chars of the filepath-string.
* @return 0 on success, OS_INVALID_PARAMETER if the zFilepath is greater than the (internal buffer + addPathLength).
*/
extern_C int initDir_FileDescription_OSAL(FileDescription_OSAL* ythis, int addPathLength, FileDescription_OSAL* dir, char const* filepath, int zFilepath);




/**Accesses the file in the file system with the given description. 
 * Filles the properties of the file. It is possible and ok, that the file doesn't exists.
 * Then the properties are set adequate to that state.
 * NOTE: old name: os_getFileDescription
 * @return the instance itself to use in concatenated expressions.
 */
extern_C FileDescription_OSAL* refresh_FileDescription_OSAL(FileDescription_OSAL* ythis);
//int os_getFileDescription(FileDescription_OSAL* dst, int addPathLength, const char* filepath); 

/**Returns true if the file exists. 
 * The proposition whether the file is existing is valid in the moment of calling [[os_getFileDescription(...)]].
 * It may be possible that the file was deleted meanwhile.
 */
#define exists_FileDescription_OSAL(YTHIS) ( ((YTHIS)->flags & mTested_FileDescription_OSAL ? YTHIS : refresh_FileDescription_OSAL(YTHIS))->flags & mExist_FileDescription_OSAL)

 /**Returns true if the file able to read and it exists. 
 * The proposition whether the file is existing is valid in the moment of calling [[os_getFileDescription(...)]].
 * It may be possible that the file was deleted meanwhile.
 */
#define canRead_FileDescription_OSAL(YTHIS) ( ((YTHIS)->flags & mTested_FileDescription_OSAL ? YTHIS : refresh_FileDescription_OSAL(YTHIS))->flags & mCanRead_FileDescription_OSAL)

/**Returns true if the file is able to write. The file may be existing or not. 
 * This proposition is valid in the moment of calling [[os_getFileDescription(...)]].
 * It may be possible that the file was deleted meanwhile.
 */
#define canWrite_FileDescription_OSAL(YTHIS) ( ((YTHIS)->flags & mTested_FileDescription_OSAL ? YTHIS : refresh_FileDescription_OSAL(YTHIS))->flags & 0x4)

/**Returns the timestamp of the file. It is the last-modify-timestamp. */
#define getTimestamp_FileDescription_OSAL(THIS) ( ((YTHIS)->flags & mTested_FileDescription_OSAL ? YTHIS : refresh_FileDescription_OSAL(YTHIS))->timeChanged )






/*@CLASS_C OS_HandleFile @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**Handle to a file. The internal data structure is not known here. 
 * A ,,OS_HandleFile,, may be the FILE* pointer like in Standard C. 
 * It is also possible that it is a simple integer, which is converted to this pointer type.
 */
struct OS_HandleFile_t;
typedef struct OS_HandleFile_t* OS_HandleFile;


/**Open a file to read. The file should be exist. 
 * @return null if the file doesn't exist. Elsewhere the handle, which is able to use for read.
 */ 
extern_C OS_HandleFile os_fopenToRead(char const* filename); 

/**Open a file to write. This open action follows the convention of java.io.FileOutputStream.ctor(). 
 * If the file should be read simultaneously, the file should be opened to read too with an extra call.
 * The os layer itself may support such actions or not.
 * @return null if the file isn't able to write or create. Elsewhere the handle, which is able to use for write.
 */
extern_C OS_HandleFile os_fopenToWrite(char const* filename, bool append); 

/**Open a file to read and write (random access).
 * This open action follows the convention of java.io.RandomAccessFile.ctor().
 * The os layer itself may support such actions or not. If the file should only opened either for read or for write
 * use os_fopenToRead() or os_fopenToWrite instead.
 * @return null if the file isn't able to write or create. Elsewhere the handle, which is able to use for the access.
 */
extern_C OS_HandleFile os_fopenToRandomAccess(char const* filename);

/**Returns the channel handle which is related to the standard output of the associated console 
 * of this application.
 *
 */
extern_C OS_HandleFile os_getStdOut();

/**Returns the channel handle which is related to the standard output 
 * of the associated command-line stream of this application.
 *
 */
extern_C OS_HandleFile os_getStdErr();

/**Returns the channel handle which is related to the standard error output 
 * of the associated command-line stream of this application.
 *
 */
extern_C OS_HandleFile os_getStdIn();


#define getFILE_os_file_emC(HANDLE) ((FILE*)HANDLE)


extern_C int os_fclose(OS_HandleFile file);


extern_C int os_fflush(OS_HandleFile file);


/**Reads bytes from file.
 * @return if >=0, than the number of bytes which are read. It is <= maxNrofbytes, depending of available bytes.
 * This method may be delayed (thread switch is possible), if the conditions to read are met, but it needs some time.
 * The method doesn't block of no content is available. Either -1 is returned (end of file) or 0. 
 * @return If >=-1 than the total number of bytes read into the buffer, or -1 if there is no more data because the end of the file has been reached.
 *         It is the same convention like java.io.FileInputStream.read(...)
 *         If <=-2, than the writing process was faulty.
 */
extern_C int os_fread(OS_HandleFile file, void* buffer, int maxNrofbytes);


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
extern_C int os_fskip(OS_HandleFile file, int32_t nrofbytes);


/**Sets the current position to read or write to the given position countered from start of the file.
 * The offset may be set beyond the end of the file. Setting the offset beyond the end of the file does not change the file length.
 * The file length will change only by writing after the offset has been set beyond the end of the file.
 * @param position 0 is the start position.
 * @return 0 if successfull.
 */
extern_C int os_fseek(OS_HandleFile file, int32_t position);

/**Sets the length of the file.
 * @param newlength If this parameter is greater than the current length, the file will be extended.
 * The content of the new ranges may be undefined, if there isn't any write operation to it.
 * This operation reserves space on the file medium.
 *        If this parameter is less than the current length, the file will be truncated.
 */
extern_C int os_fsetLength(OS_HandleFile file, int32_t newlength);


/**Writes bytes to file.
 * @param buffer any address which content is written. It may be a 0-terminated char const* too.
 * @param nrofbytes If >0 then this number of bytes will be written in any case.
 *        If <0 then the strnlen_emC(buffer, -nrofbytes) determines the nrof bytes to write.
 *        It means the negavive value is the maximal length of the 0-terminated string referenced with buffer.
 *        If ==0 no write is done.
 * @return if >=0, than all the bytes are written. <0 on error.
 * This method may be delayed (thread switch is possible), if the conditions to write are met, 
 * but the write process requires a delaying. 
 */
extern_C int os_fwrite(OS_HandleFile file, void const* buffer, int nrofbytes);


/**Locks or unlocks a region or the whole file.
 * @param cmd ones of lock, sharedLock, checkLock, unlock TODO enum-def
 * @param len number of bytes to lock from the current position, or -1 for file-lock
 * See for example https://gavv.github.io/articles/file-locks/  
 * File locks may not be supported wide ranged (files in network etc.).
 * It seems to be better using messages for data exchange (Sockets ...) as universal solution.
 * The file locking mechanism were supported in the older systems, for processes on the same PC, etc.
 */
extern_C int os_flock(OS_HandleFile file, struct FileLock_OSAL_t* lockObj);


/**Tells the current position in the file. 
 * @return the current position. 
 */
extern_C int32_t os_ftell(OS_HandleFile file);


/*@CLASS_C FileLock_OSAL @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


C_TYPE typedef struct FileLock_OSAL_t
{
  /**The file which is related to the lock. @refl: int. */
  OS_HandleFile hFile_;
	/**Any pointer or int-type if any other information is need to relate the file. */
	void* ptr_;
	/**The position of lock region. 0 on file-lock. */
	int32_t position_;
	/**The size of the lock. -1 = file-lock. */
	int32_t size_;
	/**Some flags, see defines. */
	int32_t flags_;
#define mValid_FileLock_OSAL   0x0001
#define mSharded_FileLock_OSAL 0x0010
}FileLock_OSAL;


void init_FileLock_OSAL(FileLock_OSAL* _this, int32_t position, int32_t size, bool shared);




#endif //__OSAL_os_file_h__
