/**Test StringJc-Functions in a C environment. */


#include "Jc/StringJc.h"
#include "Jc/DateJc.h"
#include <stdio.h>

StringJc s1 = NULL_StringJc;
StringJc s2 = CONST_z_StringJc("Text");
StringJc s3 = CONST_StringJc("Text", 4); //number of chars hard coded, do not use strlen(...), it doesn't work in C, only in C++

char buffer4[20];
StringJc s4 = CONST_StringJc(buffer4, sizeof(buffer4));

/**This String have to be persistant, because it may be used anywhere other. */
StringJc sPersistentString;

static char bufferForPersistentString[50];

/**This buffer stores the persistent String of a formatting action. */
char bufferSetFormat[100];


#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
struct staticBuilder1_t
  { StringBuilderJcpp u; char _b[400]; 
    staticBuilder1_t():u(true, 400){ memset(_b, 0, sizeof(_b)); }  //constructor for this data initializes the builder.
  } staticBuilder1;

class staticBuilder_t: public StringBuilderJcpp { char _b[400]; 
    public: staticBuilder_t():StringBuilderJcpp(true, 400){ memset(_b, 0, sizeof(_b)); }  //constructor for this data initializes the builder.
  } staticBuilder;
#else
  struct{StringBuilderJc u; char _b[400];} staticBuilder = { CONST_addSize_StringBuilderJc(&staticBuilder.u, 400), {0}};
#endif

/**This is a simple example for a subroutine, which uses a StringJc called per value as parameter. */
int testStringJcParam(StringJc param)
{
  return length_StringJc(param);
}



/**Demonstrates the build and usage of a simple constant StringJc. */
void testSimpleConstStringJc()
{

  /**A String may be a constant in memory, it may be read-only-memory. 
   * The compiler initializes it in a CONST segment. The stringLiteral is one constant,
   * The StringJc is another constant. */
  static const StringJc stringLiteral = CONST_StringJc("stringLiteral", 13);

  /**Variant without given size, but the size is calculate in Runtime when using. */
  static const StringJc otherStringLiteral = CONST_z_StringJc("other string-literal");


  /**Usage of a const StringJc: */
  testStringJcParam(stringLiteral);

  /**Convert a simple stringliteral to a StringJc inline. The StringJc-instance exists in Stack only:*/
  testStringJcParam(z_StringJc("stringLiteral"));

#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)

  /**A String may be a constant in memory, it may be read-only-memory. 
   * The compiler initializes it in a CONST segment. The stringLiteral is one constant,
   * The StringJc is another constant. */
  static const StringJcpp stringLiteralCpp = StringJcpp("stringLiteral", 13);


  /**Usage of a StringJcpp for a StringJc-value-Parameter. 
   * Note: Debug in assembler-level to check how it works. */
  testStringJcParam(stringLiteralCpp);

  /**Convert a simple stringliteral to a StringJc inline. The StringJc-instance exists in Stack only:*/
  testStringJcParam(StringJcpp("stringLiteral"));


#endif
}

/**Demonstrates some simple String methods. */
int testSomeSimpleStringMethods()
{ int ret;
  int pos;
  bool bOk;
  char cc;


#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
  
  const StringJcpp s0 = StringJcpp("abcdecde", 8);   //it is a simple constant
  const StringJcpp s1p = StringJcpp("abcdecde");   //it is a simple constant
  const StringJcpp s2p = StringJcpp("abc");   
  const StringJcpp s3p = StringJcpp("de");          //calculated at runtime, but const because it is an initializer
  STACKTRC_ENTRY("testSomeSimpleStringMethods");
  
  cc = s0.charAt(3);
  bOk = cc == 'd';
  bOk = bOk && !s0.equals(s2p);
  bOk = bOk && s0.equals(s1p);
  bOk = bOk && s0.equals("abcdecde");
  bOk = bOk && s0.equals(StringJcpp("abcdecde", 8));
  bOk = bOk && s3p.equals(s1p.substring(3, 5));

  bOk = bOk && s0.startsWith(s2p);
  bOk = bOk && s0.startsWith("ab");   //is true
  
  bOk = bOk && s0.endsWith("cde");     //is true 
  bOk = bOk && s0.endsWith(s3p);     //is true 

  ASSERT(bOk);

  ret = pos = s1p.indexOf('c');
  ret += pos = s1p.indexOf('c', 2);  //pos = 2, same as above, but seach from position 2 only  
  ret += pos = s1p.indexOf('c', 3);  //pos = -1 because not found. 

  ret = pos = s1p.indexOf("de");
  ret += pos = s1p.indexOf("de", 2);  //pos = 3, same as above, but seach from position 2 only  
  ret += pos = s1p.indexOf("de", 4);  //pos = -1 because not found. 

  ret += pos = s1p.indexOf("de", 99);  //pos = -1 because not found. Not an exception
  ret += pos = s1p.indexOf("de", -1);  //pos = -1 because not found. Not an exception

  ret = pos = s1p.indexOf(s3p);
  ret += pos = s1p.indexOf(s3p, 2);  //pos = 3, same as above, but seach from position 2 only  
  ret += pos = s1p.indexOf(s3p, 4);  //pos = -1 because not found. 

  ret += pos = s1p.indexOf(s3p, 99);  //pos = -1 because not found. 

  ret = pos = s1p.lastIndexOf('c');
  ret += pos = s1p.lastIndexOf('c', 2);  //pos = 2, same as above, but seach from position 2 only  
  ret += pos = s1p.lastIndexOf('c', 3);  //pos = -1 because not found. 

  ret = pos = s1p.lastIndexOf("de");
  ret += pos = s1p.lastIndexOf("de", 2);  //pos = 3, same as above, but seach from position 2 only  
  ret += pos = s1p.lastIndexOf("de", 4);  //pos = -1 because not found. 

  ret += pos = s1p.lastIndexOf("de", 99);  //pos = -1 because not found. Not an exception
  ret += pos = s1p.lastIndexOf("de", -1);  //pos = -1 because not found. Not an exception

  ret = pos = s1p.lastIndexOf(s3p);
  ret += pos = s1p.lastIndexOf(s3p, 2);  //pos = 3, same as above, but seach from position 2 only  
  ret += pos = s1p.lastIndexOf(s3p, 4);  //pos = -1 because not found. 

  ret += pos = s1p.lastIndexOf(s3p, 99);  //pos = -1 because not found. 

  
#else //simple C  
  
  const StringJc s0 = CONST_StringJc("abcdecde", 8);   //it is a simple constant
  const StringJc s1 = z_StringJc("abcdecde");   //it is a simple constant
  const StringJc s2 = CONST_z_StringJc("abc");   
  const StringJc s3 = z_StringJc("de");          //calculated at runtime, but const because it is an initializer
  STACKTRC_ENTRY("testSomeSimpleStringMethods");
  
  cc = charAt_StringJc(s0, 3);
  bOk = cc == 'd';
  bOk = bOk && !equals_StringJc(s0, s2);
  bOk = bOk && equals_StringJc(s0, s1);
  bOk = bOk && equals_z_StringJc(s0, "abcdecde");
  bOk = bOk && equals_zI_StringJc(s0, "abcdecde", 8);
  bOk = bOk && equals_StringJc(s3, substring_StringJc(s1, 3, 5, _thCxt));

  bOk = bOk && startsWith_StringJc(s0, s2);
  bOk = bOk && startsWith_z_StringJc(s0, "ab");   //is true
  
  bOk = bOk && endsWith_z_StringJc(s0, "cde");     //is true 
  bOk = bOk && endsWith_StringJc(s0, s3);     //is true 

  ASSERT(bOk);

  ret = pos = indexOf_C_StringJc(s1, 'c');
  ret += pos = indexOf_CI_StringJc(s1, 'c', 2);  //pos = 2, same as above, but seach from position 2 only  
  ret += pos = indexOf_CI_StringJc(s1, 'c', 3);  //pos = -1 because not found. 

  ret = pos = indexOf_z_StringJc(s1, "de");
  ret += pos = indexOf_zI_StringJc(s1, "de", 2);  //pos = 3, same as above, but seach from position 2 only  
  ret += pos = indexOf_zI_StringJc(s1, "de", 4);  //pos = -1 because not found. 

  ret += pos = indexOf_zI_StringJc(s1, "de", 99);  //pos = -1 because not found. Not an exception
  ret += pos = indexOf_zI_StringJc(s1, "de", -1);  //pos = -1 because not found. Not an exception

  ret = pos = indexOf_s_StringJc(s1, s3);
  ret += pos = indexOf_sI_StringJc(s1, s3, 2);  //pos = 3, same as above, but seach from position 2 only  
  ret += pos = indexOf_sI_StringJc(s1, s3, 4);  //pos = -1 because not found. 

  ret += pos = indexOf_sI_StringJc(s1, s3, 99);  //pos = -1 because not found. 

  ret = pos = lastIndexOf_C_StringJc(s1, 'c');
  ret += pos = lastIndexOf_CI_StringJc(s1, 'c', 2);  //pos = 2, same as above, but seach from position 2 only  
  ret += pos = lastIndexOf_CI_StringJc(s1, 'c', 3);  //pos = -1 because not found. 

  ret = pos = lastIndexOf_z_StringJc(s1, "de");
  ret += pos = lastIndexOf_zI_StringJc(s1, "de", 2);  //pos = 3, same as above, but seach from position 2 only  
  ret += pos = lastIndexOf_zI_StringJc(s1, "de", 4);  //pos = -1 because not found. 

  ret += pos = lastIndexOf_zI_StringJc(s1, "de", 99);  //pos = -1 because not found. Not an exception
  ret += pos = lastIndexOf_zI_StringJc(s1, "de", -1);  //pos = -1 because not found. Not an exception

  ret = pos = lastIndexOf_s_StringJc(s1, s3);
  ret += pos = lastIndexOf_sI_StringJc(s1, s3, 2);  //pos = 3, same as above, but seach from position 2 only  
  ret += pos = lastIndexOf_sI_StringJc(s1, s3, 4);  //pos = -1 because not found. 

  ret += pos = lastIndexOf_sI_StringJc(s1, s3, 99);  //pos = -1 because not found. 

#endif

  ASSERT(ret == 0x0e);
  STACKTRC_LEAVE; return ret;
}


/**This routine uses the return thread-buffer to concatenate a String and returns it. 
 * It works with C and with C++
 */
StringJc concatStringThreadBuffer(int value)
{ 
  StringJc ret;
  STACKTRC_ENTRY("returnConcatStringThreadBuffer");

#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
  
  StringBuilderJcpp* sBuffer;
  sBuffer = StringBuilderJcpp::threadBuffer(_thCxt);
  
  ret =( *sBuffer 
       + " <returnConcatStringThreadBuffer value = "
       + 24
       + " hex = 0x18"
       + " >"
       ).toString();  //NOTE: without Paranthesis: dot-operator is higher prior as operator+

#else //simple C variant


  { StringBuilderJc* sBuffer;

    sBuffer = threadBuffer_StringBuilderJc(_thCxt);
  
    append_z_StringBuilderJc(sBuffer, " { concatThreadBuffer value = ", _thCxt); 
    append_I_StringBuilderJc(sBuffer, value, _thCxt); 
    append_z_StringBuilderJc(sBuffer, " hex = ", _thCxt); 
    insert_Ir_StringBuilderJc(sBuffer, length_StringBuilderJc(sBuffer), value,16, _thCxt); 
    append_z_StringBuilderJc(sBuffer, " } ", _thCxt); 
  
    ret = toString_StringBuilderJc(&sBuffer->base.object, _thCxt);
  }
#endif
  
  STACKTRC_LEAVE; return ret;  //use StringJc-base class and return it per value.
}




/**This routine uses a Stack instance to concatenate, calls returnConcatStringThreadBuffer thereby
 * and returns all it in the Thread buffer.
 */
StringJc concatStringStack_RetThreadBuffer(int value)
{
  StringJc ret;
  STACKTRC_ENTRY("concatStringStackRetThreadBuffer");
	
#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
  StringBuilder240Jcpp buffer(true);
  buffer + "{concatStack: value = " + value + '}';
  ret = toStringInThreadCxt_StringBuilderJc(&buffer, _thCxt);

#else //simple C variant
  { struct { StringBuilderJc u; char _[50]; } buffer = { CONST_addSizeStack_StringBuilderJc(&buffer.u, 50), {0}};
    append_z_StringBuilderJc(&buffer.u, "{concatStack: value = ", _thCxt);
    append_I_StringBuilderJc(&buffer.u, value, _thCxt);
    append_C_StringBuilderJc(&buffer.u, '}', _thCxt);
    ret = toStringInThreadCxt_StringBuilderJc(&buffer.u, _thCxt);
  }
#endif
  STACKTRC_LEAVE; return ret;
}



/**This routine uses an static instance to concatenate, calls returnConcatStringThreadBuffer thereby
 * and returns all it in the Thread buffer.
 */
StringJc concatStringStaticBuilder_RetThreadBuffer(int value)
{
  StringJc ret;
  STACKTRC_ENTRY("concatStringStaticBuilder_RetThreadBuffer");
	
#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
  ret = staticBuilder.clear() + "<concatStatic value = " + value + '>';

#else //simple C variant
  clear_StringBuilderJc(&staticBuilder.u);
  append_z_StringBuilderJc(&staticBuilder.u, "<concatStatic value = ", _thCxt);
  append_I_StringBuilderJc(&staticBuilder.u, value, _thCxt);
  append_C_StringBuilderJc(&staticBuilder.u, '>', _thCxt);
  ret = toStringInThreadCxt_StringBuilderJc(&staticBuilder.u, _thCxt);
#endif
  STACKTRC_LEAVE; return ret;
}





/**Example to show how to work with a String, that should be returned 
 * but it uses a returned String in the thread context.
 * Therefore the String is built in stack buffer and than
 * copied to the thread buffer.
 */
StringJc concatStringTwiceThreadBuffer()
{
  StringJc ret;
  StringBuilderJc* stackBuilder;
  STACKTRC_ENTRY("concatStringTwiceThreadBuffer");
#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
  /**This routine uses the temporary thread-buffer to concatenate a String and output it. */
  StringBuilder240Jcpp sBuffer(true);  //true: it is in Stack
  stackBuilder = &sBuffer;


  /**Because 2 operands uses the thread context buffer for return, it should not written
   * in 1 expression. The C++-compiler is authorized to caclulate the operands first,
   * before connecting it. Than the thread-context-buffer is used twice.
   */
  //it fails: StringJc sBuffer + testInsertDelete() + "value=" + 5 + ", " + returnConcatStringThreadBuffer();
  //correct:
  sBuffer + concatStringStack_RetThreadBuffer(234);  //concatenation in sBuffer
  sBuffer + "value=" + 5 + ", " + concatStringThreadBuffer(789);
  /**use the char const* for printf, automatic type conversion calling operator char const*: */
  printf(chars_StringBuilderJc(&sBuffer));

#else
  { struct{ StringBuilderJc buffer; char _b[236]; } sBuffer = { CONST_addSizeStack_StringBuilderJc(&sBuffer.buffer, 236), {0}};
    stackBuilder = &sBuffer.buffer;

    //sBuffer = threadBuffer_StringBuilderJc();
    setLength_StringBuilderJc(&sBuffer.buffer, 0, _thCxt); 
    append_z_StringBuilderJc(&sBuffer.buffer, "value = ", _thCxt); 
    append_I_StringBuilderJc(&sBuffer.buffer, 5, _thCxt); 
    append_z_StringBuilderJc(&sBuffer.buffer, ", ", _thCxt); 
    append_s_StringBuilderJc(&sBuffer.buffer, concatStringThreadBuffer(789), _thCxt); 
    printf(chars_StringBuilderJc(&sBuffer.buffer));
  }
#endif
  ret = toStringInThreadCxt_StringBuilderJc(stackBuilder, _thCxt);
  STACKTRC_LEAVE; return ret;
}


/**This routine returns a String in the Thread buffer. */
StringJc testFormat(int value, float fValue)
{
  StringJc result;
  STACKTRC_ENTRY("testFormat");
  result = format_za_StringJc("format intVal=%d floatVal=%3.4f test", "IF", value, fValue);
  STACKTRC_LEAVE; return result;
}


void setPersistentFormat(int value, float fValue)
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





/**Example to show how to work with a pure temporary String, 
 * but it uses a returned String in the thread context.
 */
FILE* exampleOpenAssembledFilenameWithDate(StringJc sPath, int identNumber)
{ FILE* retFile = null;
  StringJc sDateString;
  StringBuilderJc* bufferName;
  STACKTRC_ENTRY("exampleAssembleFilenameWithDate");
  #if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
    StringBuilder240Jcpp sBuffer(true);
    bufferName = &sBuffer;
    DateJcpp date;
    SimpleDateFormatJcpp dateFormat("yy_MMM_dd_HHmmss_SS");
    //sPathOsSpecific = replace_StringJc(sPath, '/', '\\', _thCxt);
    sBuffer(sPath).replace('/', '\\') + "file_";
    sDateString = dateFormat.format(&date);
    sBuffer + identNumber + "_" + sDateString; 

  #else
  { struct{ StringBuilderJc buffer; char _b[236]; } sBuffer = { CONST_addSizeStack_StringBuilderJc(&sBuffer.buffer, 236), {0}};
    DateJc_s date = {0}; 
    SimpleDateFormatJc_s dateFormat = {0};
    bufferName = &sBuffer.buffer;
    /**The parameterless constructor of DateJc initializes the current time. */
    ctorO_DateJc(&date.base.object, _thCxt);    
    /**The constructor of SimpleDateFormat saves the format String, no more. */
    ctorO_s_SimpleDateFormatJc(&dateFormat.base.object, z_StringJc("yy_MMM_dd_HHmmss_SS"), _thCxt);
    /**Build the filename. Attention: routines, which returns the String in threadcontext,
     * should call immediately before the result is used. 
     * Because the thread buffer will be overwritten from the next call. */
    append_s_StringBuilderJc(bufferName, sPath, _thCxt); 
    replace_CC_StringBuilderJc(bufferName, '/', '\\');
    append_z_StringBuilderJc(bufferName, "file_", _thCxt); 
    append_I_StringBuilderJc(bufferName, identNumber, _thCxt); 
    append_z_StringBuilderJc(bufferName, "_", _thCxt); 
    /**Conversion routine of given Date with the given format. */
    sDateString = format_SimpleDateFormatJc(&dateFormat, date.val, _thCxt);
    append_s_StringBuilderJc(bufferName, sDateString, _thCxt); 
  }
  #endif
  /**Open the file: */
  { /**The buffer contains the filename, it is \0-terminated. */
    char* sFileName = chars_StringBuilderJc(bufferName);
    retFile = fopen(sFileName, "wb");
  }
  STACKTRC_LEAVE;
  return retFile;
}



void testTruncateOrException(bool bTruncate)
{
  struct { StringBuilderJc u; char _[50]; } buffer = { CONST_addSizeStack_StringBuilderJc(&buffer.u, 50), {0}};
  STACKTRC_ENTRY("testTruncateOrException");
	
  setTruncateMode_StringBuilderJc(&buffer.u, bTruncate);
  append_z_StringBuilderJc(&buffer.u, "abcdefghijklmnopqrstuvwxyz1234", _thCxt);
  append_z_StringBuilderJc(&buffer.u, "abcdefghijklmnopqrstuvwxyz", _thCxt);  //there are 56 chars, max is 53
  printf(chars_StringBuilderJc(&buffer.u));
	STACKTRC_LEAVE;
}




void testPersistence(int nException)
{ //instance in Stack to concatenate:
  struct { StringBuilderJc u; char _[50]; } buffer = { CONST_addSizeStack_StringBuilderJc(&buffer.u, 50), {0}};
  STACKTRC_ENTRY("testPersistence");
	
  append_z_StringBuilderJc(&buffer.u, "Test", _thCxt);
  append_I_StringBuilderJc(&buffer.u, 345, _thCxt);

  { /**The building of a StringJc to a buffer in Stack is admissible. 
     * It is able to use at example for parameter of called methods. */
    StringJc str = toString_StringBuilderJc(&buffer.u.base.object, _thCxt);
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
  sPersistentString = toString_StringBuilderJc(&buffer.u.base.object, _thCxt);

  { /**Any persistant Buffer is necessary! Copy to temporary String to it! 
     * The location of the buffer should controlled individually. */
    int nrofChars = copyToBuffer_StringBuilderJc(&buffer.u, bufferForPersistentString, sizeof(bufferForPersistentString));
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
    append_z_StringBuilderJc(&buffer.u, "second", _thCxt);
  }

  /**If it is assured, that the buffered String isn't used any more, the same instance can be used
   * to concatenate furthermore. To communicate this fact, the release... method is called. 
   * The correctness of calling this method is responsed by the programmer.*/
  releaseStringBuilt_StringBuilderJc(&buffer.u);
  append_z_StringBuilderJc(&buffer.u, "second", _thCxt);

  /**The next statements saves the changed String in the same buffer for persistence like before.
   * It may be okay, because only one String uses the buffer. 
   * But it may be able too, that the String is referenced any other where. The manually data structure
   * in the C-language Project should be complied to decide whether it is okay or not.
   * In an universal system a dynamically allocation prevents all problems.
   * But this simple examples doesn't assume a dynamically system.
   */
  { int nrofChars = copyToBuffer_StringBuilderJc(&buffer.u, bufferForPersistentString, sizeof(bufferForPersistentString));
    set_StringJc(&sPersistentString, zI_StringJc(bufferForPersistentString, nrofChars));
  }

  STACKTRC_LEAVE;

}


StringJc testInsertDelete()
{
  StringJc ret;
  //struct { StringBuilderJc u; char _[50]; } buffer = { CONST_addSizeStack_StringBuilderJc(&buffer.u, 50), {0}};
#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
  StringBuilder240Jcpp buffer(true);
  STACKTRC_ENTRY("testInsertDelete");
  buffer.append("abcdefghijklmnopqrstuvwxyz");
  buffer.insert(23, '_');
  buffer.insert(23, buffer.charAt(23));
  ret = buffer.toStringInThreadCxt();
#else
  INSTACK_StringBuilderJc(buffer, 50);
  STACKTRC_ENTRY("testInsertDelete");
	
  append_z_StringBuilderJc(&buffer.u, "abcdefghijklmnopqrstuvwxyz", _thCxt);
  insert_C_StringBuilderJc(&buffer.u, 23, '_', _thCxt);  //before 'x'
  insert_C_StringBuilderJc(&buffer.u, 23, charAt_StringBuilderJc(&buffer.u, 23, _thCxt), _thCxt);  //insert the same char.
  ret = toStringInThreadCxt_StringBuilderJc(&buffer.u, _thCxt);
#endif
  STACKTRC_LEAVE; return ret;
}


int testParseNumbers()
{ int ret = 0;

  ret = parseInt_IntegerJc(z_StringJc("-123456"));
  ret += parseInt_radix_IntegerJc(z_StringJc("cafe"), 16);
  return ret;
}


StringBuilderJc testX = CONST_StringBuilderJc(&testX);
  


/**Test main routine. */
void main()
{ StringJc ret;
  StringBuilderJc test = CONST_StringBuilderJc(&test);
  STACKTRC_ENTRY("main");
  setRunMode_ObjectJc(_thCxt);
  setCheckingUserBuffer_ThreadContextFw(_thCxt, true);
  testSomeSimpleStringMethods();
  ret = testInsertDelete();
  clear_StringJc(&ret); //because used Threadbuffer
  testPersistence(0);
  { StringJc result = testFormat(123, 3.16F);
    clear_StringJc(&result);
  }
  setPersistentFormat(456, 1.23456F);
  testParseNumbers();  
//testSimpleConstStringJc();
  //concatStringThreadBuffer();
  //concatString();
  //concatStringBuffer();

  { FILE* file = null;
    file = exampleOpenAssembledFilenameWithDate(s0_StringJc("./"), 123);
    if(file != null) {
      fclose(file);
    }
  }

  testTruncateOrException(true); //this call will printf a truncated String. 
  TRY{
    testTruncateOrException(false);  //this call doesn't printf, because it is aborted 
  }_TRY CATCH(Exception, exc){
    printStackTrace_ExceptionJc(exc, null);  //helper to debug error cause.
  }END_TRY

  
  
	
	STACKTRC_LEAVE;
}
