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
#include "Jc/FileIoJc.h"
#include "Jc/ReflectionJc.h"
#include "string.h" //memset
#include "os_file.h"
extern_C ClassJc const reflection_FileWriterJc_s;

/*@CLASS_C FileJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


FileJc_s* ctorO_FileJc(ObjectJc* othis, StringJc name, ThCxt* _thCxt)
{
  FileJc_s* ythis = (FileJc_s*)othis;
  int sizeObj = getSizeInfo_ObjectJc(othis);
  extern const ClassJc reflection_FileJc;
  STACKTRC_TENTRY("ctorO_FileJc");
  checkConsistence_ObjectJc(othis, sizeof(FileJc_s), null/*&reflection_FileJc*/, _thCxt);  
  memset(&ythis->fileDescription, 0, sizeof(ythis->fileDescription));
  if(!isNull_StringJc(name))
  { init_FileJc(ythis, name, _thCxt);
  }
  STACKTRC_LEAVE; return ythis;
}


void init_FileJc(FileJc_s* ythis, StringJc sFileName, ThCxt* _thCxt)
{
  //char ssFileName[120];
  char const* ssFileName;
  int len;
  int addPathlen = kMaxPathLength_FileJc - kMaxPathLength_FileDescription_OSAL;
  STACKTRC_TENTRY("init_FileJc");
  //len = copyToBuffer_StringJc(sFileName, ssFileName, sizeof(ssFileName));  //not necessary, because may be inpersistent. 
  ssFileName = getCharsAndLength_StringJc(&sFileName, &len);

  init_FileDescription_OSAL(&ythis->fileDescription, addPathlen, ssFileName, len);

}



void finalize_FileJc_F(ObjectJc* othis, ThCxt* _thCxt)
{ FileJc_s* ythis = (FileJc_s*)othis;  //upcasting to the real class.
  STACKTRC_TENTRY("finalize_FileJc_F");
  finalize_ObjectJc_F(&ythis->base.object, _thCxt);      //finalizing the superclass.
  STACKTRC_LEAVE;
}




StringJc getPath_FileJc(FileJc_s const* ythis)
{ //assume that the refresh_FileDescription_OSAL is called.
  //maybe os_initFileDescription TODO
  return z_StringJc(ythis->fileDescription.absPath);
}


int32 lastModified_FileJc(FileJc_s* ythis)
{ if((ythis->fileDescription.flags & mTested_FileDescription_OSAL) == 0){
    refresh_FileDescription_OSAL(&ythis->fileDescription);
  }
  return ythis->fileDescription.timeChanged.time_sec;
}

bool exists_FileJc(FileJc_s* ythis)
{ if((ythis->fileDescription.flags & mTested_FileDescription_OSAL) == 0){
    refresh_FileDescription_OSAL(&ythis->fileDescription);
  }
  return ythis->fileDescription.flags & mExist_FileDescription_OSAL;
}


int32 length_FileJc(FileJc_s* ythis)
{ if((ythis->fileDescription.flags & mTested_FileDescription_OSAL) == 0){
    refresh_FileDescription_OSAL(&ythis->fileDescription);
  }
  return ythis->fileDescription.fileLength;
}



/*@CLASS_C FileOutputStreamJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


FileOutputStreamJc_s* ctorO_sB_FileOutputStreamJc(ObjectJc* othis, StringJc name, bool append, ThCxt* _thCxt)
{
  FileOutputStreamJc_s* ythis = (FileOutputStreamJc_s*)othis;
  STACKTRC_TENTRY("ctorO_sB_FileOutputStreamJc");
  checkConsistence_ObjectJc(othis, sizeof(FileOutputStreamJc_s), &reflection_FileOutputStreamJc_s, _thCxt); 
  
  STACKTRC_LEAVE; return ythis;
}

FileOutputStreamJc_s* ctorO_fB_FileOutputStreamJc(ObjectJc* othis, FileJc_s* file, bool append, ThCxt* _thCxt)
{
  FileOutputStreamJc_s* ythis = (FileOutputStreamJc_s*)othis;
  OS_HandleFile hFile;
  StringJc fileName;
  STACKTRC_TENTRY("ctorO_fB_FileOutputStreamJc");
  checkConsistence_ObjectJc(othis, sizeof(FileOutputStreamJc_s), &reflection_FileOutputStreamJc_s, _thCxt); 
  fileName = getPath_FileJc(file);  //the path like given in ctor_FileJc, it may be relative.
  ASSERT(isZeroTerminated_StringJc(fileName)); //a known property assumed.
  hFile = os_fopenToWrite(PTR_StringJc(fileName), append);
  ythis->file = hFile;
  if(file == null)
  { //Standard-C doesn't know any difference (errno?)
    THROW(FileNotFoundException, fileName, 0);
  }
  STACKTRC_LEAVE; return ythis;
}


void finalize_FileOutputStreamJc_F(ObjectJc* othis, ThCxt* _thCxt)
{ FileOutputStreamJc_s* ythis = (FileOutputStreamJc_s*)othis;  //upcasting to the real class.
  STACKTRC_TENTRY("finalize_FileOutputStreamJc_F");
  finalize_ObjectJc_F(&ythis->base.object, _thCxt);      //finalizing the superclass.
  STACKTRC_LEAVE;
}




void write_BY_FileOutputStreamJc(FileOutputStreamJc_s* ythis, int8_Y* data, ThCxt* _thCxt)
{
}

void write_FileOutputStreamJc(FileOutputStreamJc_s* ythis, void* data, int offset, int len, ThCxt* _thCxt)
{
  int nrofBytesWritten;
  STACKTRC_TENTRY("write_FileOutputStreamJc");
  nrofBytesWritten = os_fwrite(ythis->file, addOffset_MemUnit(data, offset), len);
  if(nrofBytesWritten != len){
    THROW_s0(IOException, "writing file", (int)ythis);

  }
  STACKTRC_LEAVE;
}


void write_B_FileOutputStreamJc(FileOutputStreamJc_s* ythis, int8 byte, ThCxt* _thCxt)
{
}





void flush_FileOutputStreamJc(FileOutputStreamJc_s* ythis, struct ThreadContextFW_t* _thCxt)
{
  STACKTRC_TENTRY("close_FileWriterJc");
  if(ythis->file != null)
  { os_fflush(ythis->file);
    ythis->file = null;
  }
  STACKTRC_LEAVE; 

}


void close_FileOutputStreamJc_F(FileOutputStreamJc_s* ythis, struct ThreadContextFW_t* _thCxt)
{
  STACKTRC_TENTRY("close_FileWriterJc");
  if(ythis->file != null)
  { os_fclose(ythis->file);
    ythis->file = null;
  }
  STACKTRC_LEAVE; 

}



/*@CLASS_C FileWriterJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


FileWriterJc_s* ctorO_FileWriterJc(ObjectJc* othis, ThCxt* _thCxt)
{
  FileWriterJc_s* ythis = (FileWriterJc_s*)othis;
  STACKTRC_TENTRY("ctorO_FileWriterJc");
  checkConsistence_ObjectJc(othis, sizeof(FileWriterJc_s), &reflection_FileWriterJc_s, _thCxt); 
  
  STACKTRC_LEAVE; return ythis;
}

int open_FileWriterJc(FileWriterJc_s* ythis, StringJc fileName, bool append, ThCxt* _thCxt)
{
  OS_HandleFile file;
  int error = 0; 
  //char const* openmode;
  char bufferFilename[200];
  STACKTRC_TENTRY("open_FileWriterJc");
  copyToBuffer_StringJc(fileName, bufferFilename, sizeof(bufferFilename));
  { char cc; int ii =0; char* ptr = bufferFilename;
    while(ii < sizeof(bufferFilename) && (cc = *ptr++) != 0)
    { if(cc == '/') 
      { cc = '\\'; 
      }
    }
  }
  //openmode: a+ is append and read-able, w+b is write new, readable (+) and binary. 
  //openmode = append ? "a+b" : "w+b";
  file = os_fopenToWrite(bufferFilename, append);
  ythis->file = file;
  if(file == null)
  { //Standard-C doesn't know any difference (errno?)
    error = kFileNotFound_FileWriterJc;
  }
  STACKTRC_LEAVE; return error;
}

bool isOpen_FileWriterJc(FileWriterJc_s* ythis)
{ return ythis->file != null;
}

void write_FileWriterJc(FileWriterJc_s* ythis, StringJc text, ThCxt* _thCxt)
{
  int nrofChars;
  int error;
  const char* sText;
  STACKTRC_TENTRY("write_FileWriterJc");
  sText = getCharsAndLength_StringJc(&text, &nrofChars);
  error = os_fwrite(ythis->file, sText, nrofChars);
  if(error < 0){ THROW_s0(IOException, "writing file", (int)ythis);}
  STACKTRC_LEAVE; 
}


void flush_FileWriterJc(FileWriterJc_s* ythis, ThCxt* _thCxt)
{
  STACKTRC_TENTRY("flush_FileWriterJc");
  if(ythis->file != null)
  { os_fflush(ythis->file);
  }
  STACKTRC_LEAVE; 

}

void close_FileWriterJc(FileWriterJc_s* ythis, ThCxt* _thCxt)
{
  STACKTRC_TENTRY("close_FileWriterJc");
  if(ythis->file != null)
  { os_fclose(ythis->file);
    ythis->file = null;
  }
  STACKTRC_LEAVE; 

}


/*@CLASS_C FileReaderJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/




FileReaderJc_s* ctorO_FileReaderJc(ObjectJc* othis, OS_HandleFile file, ThCxt* _thCxt)
{ 
  FileReaderJc_s* ythis = (FileReaderJc_s*)othis;
  int sizeObj = getSizeInfo_ObjectJc(othis);
  extern const ClassJc reflection_FileReaderJc_s;
  STACKTRC_TENTRY("ctor_FileReaderJcF");
  checkConsistence_ObjectJc(othis, sizeof(FileReaderJc_s), null/*&reflection_BufferedReaderJc_s*/, _thCxt);  
  ythis->file_ = file;
  ythis->bEof_ = 0;
  ythis->modCount_ = -1;
  STACKTRC_LEAVE; return ythis;
}


int open_FileReaderJcF(FileReaderJc_s* ythis, StringJc sFileName, ThCxt* _thCxt)
{ //char const* sFileName1; int zFileName;
  char ssFileName[120];
  int len;
  int ii;
  STACKTRC_TENTRY("open_FileReaderJcF");
  if(ythis->file_ != null)
  { THROW_s0(IllegalArgumentException, "fault time of call, file is opened", ythis->lenFile_);
  }
  len = copyToBuffer_StringJc(sFileName, ssFileName, sizeof(ssFileName)); 
  for(ii=0; ii<len; ii++){ if(ssFileName[ii] == '/'){ ssFileName[ii] = '\\'; } }
  ythis->file_ = os_fopenToRead(ssFileName);
  if(ythis->file_ != null)
  { ythis->lenFile_ = 0;
    ythis->bEof_ = false;
    ythis->modCount_ +=1;
  }
  STACKTRC_LEAVE; return 0;
}


bool isOpen_FileReaderJcF(FileReaderJc_s* ythis)
{ return ythis->file_ != null;
}

bool ready_FileReaderJcF(FileReaderJc_s* ythis)
{ return ythis->file_ != null && ythis->bEof_ == 0;
}



int close_FileReaderJcF(FileReaderJc_s* ythis, ThCxt* _thCxt)
{ //char const* sFileName1; int zFileName;
  STACKTRC_TENTRY("close_BufferedReaderJcF");
  if(ythis->file_ != null){ os_fclose(ythis->file_); }
  ythis->file_ = null;
  ythis->bEof_ = false;
  ythis->lenFile_ = -1;
  ythis->modCount_ +=1;
  STACKTRC_LEAVE; return 0;
}




/*@CLASS_C BufferedReaderJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/




BufferedReaderJc_s* ctorO_BufferedReaderJc(ObjectJc* othis, FileReaderJc_s* inputReader, MemC buffer, ThCxt* _thCxt)
{ 
  BufferedReaderJc_s* ythis = (BufferedReaderJc_s*)othis;
  int sizeObj = getSizeInfo_ObjectJc(othis);
  extern const ClassJc reflection_BufferedReaderJc_s;
  STACKTRC_TENTRY("ctorO_BufferedReaderJc");
  checkConsistence_ObjectJc(othis, sizeof(BufferedReaderJc_s), null/*&reflection_BufferedReaderJc_s*/, _thCxt);  
  ythis->lenLine = -1;
  ythis->lenBuffer = 0;
  ythis->bFinish = 0;
  ythis->modCountInput = inputReader->modCount_;
  ythis->input = inputReader;
  ythis->buffer = buffer;
  STACKTRC_LEAVE; return ythis;
}





StringJc readLine_BufferedReaderJc(BufferedReaderJc_s* ythis, ThCxt* _thCxt)
{ char cc;
  StringJc line;
  char* fileBuffer1 = PTR_MemC(ythis->buffer,char);
  STACKTRC_TENTRY("readLine_BufferedReader");
  if(ythis->modCountInput != ythis->input->modCount_)
  { /**re-init because the input was closed and opend again. */
    ythis->lenLine = -1;
    ythis->lenBuffer = 0;
    ythis->bFinish = 0;
    ythis->modCountInput = ythis->input->modCount_;
  }
  if(ythis->lenLine >=0)
  { //a line is returned before, now delete it:
    while(ythis->lenLine < ythis->lenBuffer && ((cc=fileBuffer1[ythis->lenLine]) == 0x0a  || cc== 0x0d)){ ythis->lenLine++; } //after 0x0a
    if(ythis->lenLine < ythis->lenBuffer)
    { memmove(fileBuffer1, fileBuffer1 + ythis->lenLine, ythis->lenBuffer - ythis->lenLine);
    }
    else
    { ythis->bFinish = true;
    }
    ythis->lenBuffer -= ythis->lenLine;
  }
  ythis->lenLine = 0;
  if(ythis->input->bEof_ == 0)
  { //read next chars into buffer, there is space now:
    int zBuffer = size_MemC(ythis->buffer);
    int nrofBytesRead = os_fread(ythis->input->file_, fileBuffer1 + ythis->lenBuffer, zBuffer - ythis->lenBuffer );
    if(nrofBytesRead == 0)
    { //no more bytes read, eof.
      ythis->input->bEof_ = 1;
    }
    else if(nrofBytesRead <0)
    { //Dateilesefehler
      ythis->input->bEof_ = 1;
    }
    else
    { ythis->lenBuffer += nrofBytesRead;
    }
  }
  /**determine the lenght of the line in buffer, it is without 0d 0r 0a */
  while(ythis->lenLine < ythis->lenBuffer && (cc = fileBuffer1[ythis->lenLine]) != 0x0a && cc != 0x0d){ ythis->lenLine +=1; }
  /**Store in StringJc and return: */
  if(  ythis->lenLine >0    //a non-empty line is found 
    || ythis->lenBuffer >0  //if the line is empty, but there are some more lines, return empty string with length 0,
    )
  { INIT_StringJc(line, fileBuffer1, ythis->lenLine | mNonPersists__StringJc);
    //NOTE: the file buffer can't be designated as persistent, because it is overwritten on next read.
  }
  else
  { //no more lines
    line = null_StringJc;
  }
  STACKTRC_LEAVE; return line;    
}




