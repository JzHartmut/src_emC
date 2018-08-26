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
 * @content
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 * @changes
 * 2010-01-21 Hartmut: All accesses to file system uses the OSAL-Layer, OS_HandleFile instead FILE. This was necessary because not any embedded system supports all standard-C-routines.
 *
 * @version 0.83
 */
#include <applstdef_emC.h>  //Note: define before include-guards because applstdef_emC,h may include this file too.
//The following include guard prevent twice include especially if appöstdefJc.h includes this file already.
#ifndef __Jc_FileIoJc_h__
#define __Jc_FileIoJc_h__
#include "Jc/ObjectJc.h"
#include "OSAL/os_file.h"
//#include <fw_Platform_Conventions.h>

struct ThreadContext_emC_t;
struct StringBuilderJc_t;

/*@CLASS_C FileJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


typedef struct FileJc_t
{ union{ ObjectJc object; } base;
  FileDescription_OSAL fileDescription;

  char _additionalBuffer_[kMaxPathLength_FileJc - kMaxPathLength_FileDescription_OSAL];
} FileJc_s;

/**Finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_FileJc_F(ObjectJc* othis, ThCxt* _thCxt);



FileJc_s* ctorO_FileJc(ObjectJc* othis, StringJc name, ThCxt* _thCxt);

/**Initializes the instance with the given name.
 * This opreation doesn't cause os-activity.
 */
void init_FileJc(FileJc_s* ythis, StringJc name, ThCxt* _thCxt);

int32 lastModified_FileJc(FileJc_s* ythis);

int32 length_FileJc(FileJc_s* ythis);

bool exists_FileJc(FileJc_s* ythis);

/**Gets the name part with extension of the path to the file. 
 * It is done without any action with the operation system.
 * It means the path is not checked whether the file exists.
 * @return the text of the name is zero-terminated.
 */
StringJc getName_FileJc(FileJc_s const* ythis);

/**Gets the path of the file. 
 * It is done without any action with the operation system.
 * It means the path is not checked whether the file exists.
 * @return the text of the name is zero-terminated.
 */
StringJc getPath_FileJc(FileJc_s const* ythis);

/*@CLASS_C OutputStreamJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This struct is the implementation of org.vishia.FileWriter. That class is a wrapper arround java.io.FileWriter.
 * The originally java.lang.FileWriter isn't useable well, because no static instance can be made.
 */
typedef struct OutputStreamJc_t
{ union { ObjectJc object;} base;
  
}OutputStreamJc_s;

extern_C struct ClassJc_t const reflection_OutputStreamJc_s;

typedef TYPE_EnhancedRefJc(OutputStreamJc);


/**The method type, which is able to implement the run method. */
typedef void MT_write_OutputStreamJc(ObjectJc* ithis, int byte, ThCxt* _thCxt);
/** Call of the method at this class level, executes a dynamic call of the override-able method: */
METHOD_C void write_OutputStreamJc(ObjectJc* ithis, int byte, ThCxt* _thCxt);


/* Method table contains all dynamic linked (virtual) methods
 * of the class and all super classes and interfaces. */
extern const char sign_Mtbl_OutputStreamJc[]; //marker for methodTable check
typedef struct Mtbl_OutputStreamJc_t
{ MtblHeadJc head;
  MT_write_OutputStreamJc* write;
  Mtbl_ObjectJc ObjectJc;
} Mtbl_OutputStreamJc;



/*@CLASS_C FileOutputStreamJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This struct is the implementation of org.vishia.FileWriter. That class is a wrapper arround java.io.FileWriter.
 * The originally java.lang.FileWriter isn't useable well, because no static instance can be made.
 */
typedef struct FileOutputStreamJc_t
{ union { ObjectJc object; OutputStreamJc_s super; } base;
  
  /**It may be a C-standard FILE* handle, but it is casting to support other embedded systems. 
   * @refl: void*. 
   */
  OS_HandleFile file;
}FileOutputStreamJc_s;

extern_C struct ClassJc_t const reflection_FileOutputStreamJc_s;

/**Finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_FileOutputStreamJc_F(ObjectJc* othis, ThCxt* _thCxt);



#define ctorO_f_FileOutputStreamJc(YTHIS, file, _THC) ctorO_fB_FileOutputStreamJc(YTHIS, file, false, _THC)

FileOutputStreamJc_s* ctorO_fB_FileOutputStreamJc(ObjectJc* othis, FileJc_s* file, bool append, ThCxt* _thCxt);

#define ctorO_s_FileOutputStreamJc(YTHIS, name, _THC) ctorO_sB_FileOutputStreamJc(YTHIS, name, false, _THC)

FileOutputStreamJc_s* ctorO_sB_FileOutputStreamJc(ObjectJc* othis, StringJc name, bool append, ThCxt* _thCxt);

METHOD_C void write_BY_FileOutputStreamJc(FileOutputStreamJc_s* ythis, int8_Y* data, ThCxt* _thCxt);

METHOD_C void write_FileOutputStreamJc(FileOutputStreamJc_s* ythis, void* data, int offset, int len, ThCxt* _thCxt);

METHOD_C void write_B_FileOutputStreamJc(FileOutputStreamJc_s* ythis, int8 byte, ThCxt* _thCxt);

METHOD_C void flush_FileOutputStreamJc(FileOutputStreamJc_s* ythis, struct ThreadContext_emC_t* _thCxt);

METHOD_C void close_FileOutputStreamJc_F(FileOutputStreamJc_s* ythis, struct ThreadContext_emC_t* _thCxt);


/*@CLASS_C FileWriterJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This struct is the implementation of org.vishia.FileWriter. That class is a wrapper arround java.io.FileWriter.
 * The originally java.lang.FileWriter isn't useable well, because no static instance can be made.
 */
typedef  struct FileWriterJc_t
{ union { ObjectJc object;} base;
  
  /**It may be a C-standard FILE* handle, but it is casting to support other embedded systems. 
   * @refl: void*. 
   */
  OS_HandleFile file;
}FileWriterJc_s;


#ifndef FileWriterJcREFDEF
  #define FileWriterJcREFDEF
  typedef TYPE_EnhancedRefJc(FileWriterJc);
#endif



#define kFileNotFound_FileWriterJc -1

#define kFileOpenError_FileWriterJc -2

/**Finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_FileWriter_F(ObjectJc* othis, ThCxt* _thCxt);



METHOD_C FileWriterJc_s* ctorO_FileWriterJc(ObjectJc* othis, struct ThreadContext_emC_t* _thCxt);

METHOD_C int open_FileWriterJc(FileWriterJc_s* ythis, StringJc fileName, bool append, struct ThreadContext_emC_t* _thCxt);

METHOD_C bool isOpen_FileWriterJc(FileWriterJc_s* ythis);

METHOD_C void write_FileWriterJc(FileWriterJc_s* ythis, StringJc text, struct ThreadContext_emC_t* _thCxt);

METHOD_C void flush_FileWriterJc(FileWriterJc_s* ythis, struct ThreadContext_emC_t* _thCxt);

METHOD_C void close_FileWriterJc(FileWriterJc_s* ythis, struct ThreadContext_emC_t* _thCxt);



/*@CLASS_C FileReaderJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


typedef struct FileReaderJc_t
{ ObjectJc object;

  /**It may be a C-standard FILE* handle, but it is casting to support other embedded systems. 
   * @refl: void*. 
   */
  OS_HandleFile file_;
  int32 lenFile_;
  int32 bEof_;
  /**Incremented on any open/close action. */
  int modCount_;
  
}FileReaderJc_s;

/**Finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_FileReaderJc_F(ObjectJc* othis, ThCxt* _thCxt);


FileReaderJc_s* ctorO_FileReaderJc(ObjectJc* othis, OS_HandleFile file, ThCxt* _thCxt);

int open_FileReaderJcF(FileReaderJc_s* ythis, CharSeqJc sFileName, ThCxt* _thCxt);

bool isOpen_FileReaderJcF(FileReaderJc_s* ythis);

bool ready_FileReaderJcF(FileReaderJc_s* ythis);

int close_FileReaderJcF(FileReaderJc_s* ythis, ThCxt* _thCxt);





/*@CLASS_C BufferedReaderJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct BufferedReaderJc_t
{ ObjectJc object;

  int32 lenBuffer;
  int32 lenLine;
  int32 bFinish;
  MemC buffer;

  /**The aggregated input reader. TODO use ReaderJc with C-interfacing. */
  FileReaderJc_s* input;

  /**To compare with input->modCount, */
  int32 modCountInput;

}BufferedReaderJc_s;


/**Finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_BufferedReaderJc_F(ObjectJc* othis, ThCxt* _thCxt);

BufferedReaderJc_s* ctorO_BufferedReaderJc(ObjectJc* othis, FileReaderJc_s* input, MemC buffer, ThCxt* _thCxt);

StringJc readLine_BufferedReaderJc(BufferedReaderJc_s* ythis, ThCxt* _thCxt);



/*@CLASS_C FileSystemJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
//see extra FileSystemJc.h
//MemC readBinFile_FileSystemJc(FileJc_s* file, MemC buffer);

//METHOD_C int writeBinFile_FileSystemJc(FileJc_s* file, int8_Y* buffer, struct ThreadContext_emC_t* _thCxt);
      

#endif //__Jc_FileIoJc_h__
