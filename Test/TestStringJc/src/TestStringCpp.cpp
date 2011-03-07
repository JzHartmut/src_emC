/**Test StringJc-Functions in a C++ environment. */

#include "Jc/StringJc.h"
#include "Jc/DateJc.h"
#include <stdio.h>
#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)


static StringJc testInsertDelete();


static StringJc s1p = NULL_StringJc;
static StringJc s2p = CONST_z_StringJc("Text");
static StringJc s3p = CONST_StringJc("Text", 4); //number of chars hard coded, do not use strlen(...), it doesn't work in C, only in C++

static char buffer4[20];
static StringJc s4 = CONST_StringJc(buffer4, sizeof(buffer4));

/**This String have to be persistant, because it may be used anywhere other. */
static StringJc sPersistentString;

static char bufferForPersistentString[50];

/**This buffer stores the persistent String of a formatting action. */
static char bufferSetFormat[100];

/**This is a simple example for a subroutine, which uses a StringJc called per value as parameter. 
 * Note: don't use a StringJcpp as parameter, because the copy-constructor calls set_StringJc
 */
static int testStringJcParam(StringJc param)
{
  return length_StringJc(param);
}



/**Demonstrates the build and usage of a simple constant StringJc. */
static void testSimpleConstStringJc()
{


}


/**This routine uses the return thread-buffer to concatenate a String and returns it. 
 * It works with C and with C++
 */
static StringJc returnConcatStringThreadBuffer()
{ 
}


/**This routine returns a String in the Thread buffer. */
static StringJc testFormat(int value, float fValue)
{
  StringJc result;
  STACKTRC_ENTRY("testFormat");
  result = format_za_StringJc("format intVal=%d floatVal=%3.4f test", "IF", value, fValue, _thCxt);
  STACKTRC_LEAVE; return result;
}


static void setPersistentFormat(int value, float fValue)
{
  StringJc result;
  //int zResult;
  STACKTRC_ENTRY("testFormat");
  /**Result is non-persistent, the string is in thread-contenxt-buffer. */ 
  result = format_za_StringJc("format intVal=%d floatVal=%3.4f test", "IF", value, fValue, _thCxt);
#ifdef NO_DYNAMICALLY_MEMORY 
  { StringJc resultPersistent;
    /**Copy the string in a buffer, which is designated as persistent. */
    zResult = copyToBuffer_StringJc(result, bufferSetFormat, sizeof(bufferSetFormat));
    clear_StringJc(&result);
    /**The resultPersistent is a StringJc, which is designated as reference ot a persistent string.*/
    resultPersistent = zI_StringJc(bufferSetFormat, zResult);
    /**Set an global visible String with set_String(...), to check whether it is persistent. */
    set_StringJc(&sPersistentString, resultPersistent);
  }
#else
  /**Because the system knows dynamically memory, the copy to a persistent String is done inside: */
  set_StringJc(&sPersistentString, result);
#endif
  clear_StringJc(&result);
  STACKTRC_LEAVE;
}





/**Example to show how to work with a String, that should be returned 
 * but it uses a returned String in the thread context.
 * Therefore the String is built in stack buffer and than
 * copied to the thread buffer.
 */
static StringJc concatStringThreadBuffer()
{
#ifdef __cplusplus
/**This routine uses the temporary thread-buffer to concatenate a String and output it. */
  //class xx:public StringBuilderJcpp{ public: xx(){ StringBuilderJcpp(true, 236); } char _b[236]; }sBuffer();
  StringBuilder240Jcpp sBuffer(true);

  STACKTRC_ENTRY("concatStringThreadBuffer");

  /**Because 2 operands uses the thread context buffer for return, it should not written
   * in 1 expression. The C++-compiler is authorized to caclulate the operands first,
   * before connecting it. Than the thread-context-buffer is used twice.
   */
  //it fails: StringJc str = sBuffer + testInsertDelete() + "value=" + 5 + ", " + returnConcatStringThreadBuffer();
  //correct:
  sBuffer + testInsertDelete();  //concatenation in sBuffer
  StringJc str = sBuffer + "value=" + 5 + ", " + returnConcatStringThreadBuffer();
  
  printf(chars_StringBuilderJc(&sBuffer));

  STACKTRC_LEAVE; return str;
#else
  struct{ StringBuilderJc buffer; char _b[236]; } sBuffer = { CONST_addSizeStack_StringBuilderJc(&sBuffer.buffer, 236), {0}};
  StringJc str;
  STACKTRC_ENTRY("concatStringThreadBuffer");

  //sBuffer = threadBuffer_StringBuilderJc();
  str =  
  ( setLength_StringBuilderJc(&sBuffer.buffer, 0, _thCxt) 
  , append_z_StringBuilderJc(&sBuffer.buffer, "value = ", _thCxt) 
  , append_I_StringBuilderJc(&sBuffer.buffer, 5, _thCxt) 
  , append_z_StringBuilderJc(&sBuffer.buffer, ", ", _thCxt) 
  , append_s_StringBuilderJc(&sBuffer.buffer, returnConcatStringThreadBuffer(), _thCxt) 
  , toString_StringBuilderJc(&sBuffer.buffer.base.object, _thCxt)
  );
  //append_s_StringBuilderJc(sBuffer, returnStringThreadBuffer2(), _thCxt); 
  printf(chars_StringBuilderJc(&sBuffer.buffer));
  
  { //save string in the threadBuffer instead, to return it:
	StringBuilderJc* threadBuffer =  threadBuffer_s_StringBuilderJc(str, _thCxt);
    str = toString_StringBuilderJc(&threadBuffer->base.object, _thCxt);
  }
  STACKTRC_LEAVE; return str;
#endif
}




/**Example to show how to work with a pure temporary String, 
 * but it uses a returned String in the thread context.
 */
static FILE* exampleOpenAssembledFilenameWithDate(StringJc sPath, int identNumber)
{ FILE* retFile = null;
  StringJc sPathOsSpecific;
  struct{ StringBuilderJc buffer; char _b[236]; } sBuffer = { CONST_addSizeStack_StringBuilderJc(&sBuffer.buffer, 236), {0}};
  //StringJc str;
  DateJc_s date = {0}; // CONST_Instance_ObjectJc(date); //CONST_DateJc(date);
  SimpleDateFormatJc_s dateFormat = {0}; // CONST_Instance_ObjectJc(dateFormat);
  StringJc sDateString;
  STACKTRC_ENTRY("exampleAssembleFilenameWithDate");
  /**The parameterless constructor of DateJc initializes the current time. */
  ctorO_DateJc(&date.base.object, _thCxt);    
  /**The constructor of SimpleDateFormat saves the format String, no more. */
  ctorO_s_SimpleDateFormatJc(&dateFormat.base.object, z_StringJc("yy_MMM_dd_HHmmss_SS"), _thCxt);
  /**Build the filename. Attention: routines, which returns the String in threadcontext,
   * should call immediately before the result is used. 
   * Because the thread buffer will be overwritten from the next call. */
  sPathOsSpecific = replace_StringJc(sPath, '/', '\\', _thCxt);
  append_s_StringBuilderJc(&sBuffer.buffer, sPathOsSpecific, _thCxt); 
  /**Conversion routine of given Date with the given format. */
  sDateString = format_SimpleDateFormatJc(&dateFormat, date.val, _thCxt);
  append_z_StringBuilderJc(&sBuffer.buffer, "file_", _thCxt); 
  append_I_StringBuilderJc(&sBuffer.buffer, identNumber, _thCxt); 
  append_z_StringBuilderJc(&sBuffer.buffer, "_", _thCxt); 
  append_s_StringBuilderJc(&sBuffer.buffer, sDateString, _thCxt); 
  /**Open the file: */
  { /**The buffer contains the filename, it is \0-terminated. */
    char* sFileName = chars_StringBuilderJc(&sBuffer.buffer);
    retFile = fopen(sFileName, "wb");
  }
  STACKTRC_LEAVE;
  return retFile;
}



static void testTruncateOrException(bool bTruncate)
{
  struct { StringBuilderJc b; char _[50]; } buffer = { CONST_addSizeStack_StringBuilderJc(&buffer.b, 50), {0}};
  STACKTRC_ENTRY("testTruncateOrException");
	
  setTruncateMode_StringBuilderJc(&buffer.b, bTruncate);
  append_z_StringBuilderJc(&buffer.b, "abcdefghijklmnopqrstuvwxyz1234", _thCxt);
  append_z_StringBuilderJc(&buffer.b, "abcdefghijklmnopqrstuvwxyz", _thCxt);  //there are 56 chars, max is 53
  printf(chars_StringBuilderJc(&buffer.b));
	STACKTRC_LEAVE;
}




static void testPersistence(int nException)
{ //instance in Stack to concatenate:
  struct { StringBuilderJc b; char _[50]; } buffer = { CONST_addSizeStack_StringBuilderJc(&buffer.b, 50), {0}};
  STACKTRC_ENTRY("testPersistence");
	
  append_z_StringBuilderJc(&buffer.b, "Test", _thCxt);
  append_I_StringBuilderJc(&buffer.b, 345, _thCxt);

  { /**The building of a StringJc to a buffer in Stack is admissible. 
     * It is able to use at example for parameter of called methods. */
    StringJc str = toString_StringBuilderJc(&buffer.b.base.object, _thCxt);
    testStringJcParam(str);  //use, but not save persistently.

    /**The next statement causes an error, because in this running environment,
     * dynamic memory isn't present. Therefore it is set under if.
     * Note that an adequate error in Standard-C, referencing a String in Stack, 
     * causes a difficult visible fatal error elsewhere.
     */
    if(nException & 2){
      set_StringJc(&sPersistentString, str);
    }
  }
  /**This call doesn't build a persistant String. It is inadmissible! 
   * The StringJc is dedicated with a non-persistant flag-bit, so the error is able to detect. */
  sPersistentString = toString_StringBuilderJc(&buffer.b.base.object, _thCxt);

  { /**Any persistant Buffer is necessary! Copy to temporary String to it! 
     * The location of the buffer should controlled individually. */
    int nrofChars = copyToBuffer_StringBuilderJc(&buffer.b, bufferForPersistentString, sizeof(bufferForPersistentString));
    /**This statement doesn't check whether the String is persistent, 
     * but because z_StringJc supplies an non-persistent String always, the result is designated a non-persistant.
     * You should not use this assignment. */
    sPersistentString = z_StringJc(bufferForPersistentString);
    /**The next assignement checks, whether the source is persistent. 
     * If a persistent String is necessary, the ,,set_StringJc(...),,-Method should use anyway,
     * a eyes-check of source should found them.
  	 * The input String is declared as persistent by using the named routine, it uses the persistent buffer.*/
    set_StringJc(&sPersistentString, zI_StringJc(bufferForPersistentString, nrofChars));
  }
  if(nException & 0x4){
    /**This appends something to a StringBuilder, which was referenced by a String already.
     * It is not admissible, because the String may be used furthermore and it should be non-changed.
     * Because the StringBuilderJc-instance is dedicated with the bit _mStringBuilt_StringBuilderJc
     * set while toString() were processed, an exception is thrown.*/
    append_z_StringBuilderJc(&buffer.b, "second", _thCxt);
  }

  /**If it is assured, that the buffered String isn't used any more, the same instance can be used
   * to concatenate furthermore. To communicate this fact, the release... method is called. 
   * The correctness of calling this method is responsed by the programmer.*/
  releaseStringBuilt_StringBuilderJc(&buffer.b);
  append_z_StringBuilderJc(&buffer.b, "second", _thCxt);

  /**The next statements saves the changed String in the same buffer for persistence like before.
   * It may be okay, because only one String uses the buffer. 
   * But it may be able too, that the String is referenced any other where. The manually data structure
   * in the C-language Project should be complied to decide whether it is okay or not.
   * In an universal system a dynamically allocation prevents all problems.
   * But this simple examples doesn't assume a dynamically system.
   */
  { int nrofChars = copyToBuffer_StringBuilderJc(&buffer.b, bufferForPersistentString, sizeof(bufferForPersistentString));
    set_StringJc(&sPersistentString, zI_StringJc(bufferForPersistentString, nrofChars));
  }

  STACKTRC_LEAVE;

}


static StringJc testInsertDelete()
{
  struct { StringBuilderJc b; char _[50]; } buffer = { CONST_addSizeStack_StringBuilderJc(&buffer.b, 50), {0}};
  StringJc ret;
  STACKTRC_ENTRY("testInsertDelete");
	
  append_z_StringBuilderJc(&buffer.b, "abcdefghijklmnopqrstuvwxyz", _thCxt);
  insert_C_StringBuilderJc(&buffer.b, 23, '_', _thCxt);  //before 'x'
  insert_C_StringBuilderJc(&buffer.b, 23, charAt_StringBuilderJc(&buffer.b, 23, _thCxt), _thCxt);  //insert the same char.
  ret = toStringInThreadCxt_StringBuilderJc(&buffer.b, _thCxt);
  STACKTRC_LEAVE; return ret;
}


static StringBuilderJc testX = CONST_StringBuilderJc(&testX);
  


#endif