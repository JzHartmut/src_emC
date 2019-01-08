#include <emC/DefPortTypes_emC.h>
#include <Jc/StringJc.h>


char const cTypes_DefPortTypes_emC[] = "DFJISBCZUWVdfjisb";
int8 const lenTypes_DefPortTypes_emC[] = { 8, 4, 8, 4, 2, 1, 1, 1, 4, 2, 1, 16, 8, 16, 8, 4, 2};

ClassJc const* const reflTypes_DefPortTypes_emC[] = 
{
  &reflection__doubleJc
  , &reflection__floatJc
  , &reflection__int64Jc
  , &reflection__int32Jc
  , &reflection__int16Jc
  , &reflection__int8Jc
  , &reflection__charJc
  , &reflection__booleanJc
  , &reflection__uint32Jc
  , &reflection__uint16Jc
  , &reflection__uint8Jc
  , &reflection_double_complex
  , &reflection_float_complex
  , null
  , null
  , null
  , null
};




char const* parse_Entry_DefPortType_emC  (  Entry_DefPortType_emC* thiz, StringJc typeName, ThCxt* _thCxt)
{ STACKTRC_TENTRY("parse_Entry_DefPortType_emC");
  char const* err = null;
  int pos = 0;
  int posFound = 0;
  int zDim = 0;
  thiz->type = '?'; //default dynamically typed
  thiz->sizeType = 0; //default;
  int nrType;
  char cType;
  StringJc type = extractType_TypeName_emC(typeName, _thCxt);
  int zType = length_StringJc(type);
  if (zType == 0) {
    thiz->type = '?';  //no type given: dynamically typed.
    thiz->sizeType = 0; //default;
  }
  else {
    const char* sType = PTR_StringJc(type);
    if ((posFound = indexOf_CI_StringJc(type, '*', pos)) >= 0) {
      //it is a pointer type, the used type for Simulink is a handle. The pointer type will be evaluate anywhere other
      thiz->type = 'U';
      pos += posFound + 1;  //after '*'
    }
    else if ((nrType = searchChar_emC(cTypes_DefPortTypes_emC, -20, cType = sType[pos])) >= 0) {
      thiz->type = cType;                    //type char
      thiz->sizeType = lenTypes_DefPortTypes_emC[nrType];
      pos += 1;
      while (pos < zType) {
        char cType = sType[pos];
        if (strchr(" [,]", cType) != null) {  //structure char for arrays
          pos += 1;
        }
        else if (cType >= '0' && cType <= '9') {  //number
          int sizeDim = 0;
          thiz->sizeArray[thiz->dimensions] = parseIntRadix_emC(sType + pos, zType, 10, &sizeDim);
          thiz->dimensions += 1;
          pos += sizeDim;
        }
      }
    }
    else {
      STACKTRC_RETURN "parse_Entry_DefPortType_emC(): unexpected format char";
    }
    if (err == null) { thiz->newDefined = 1; }
  }
  STACKTRC_RETURN err;
}



//
//The name is the last identifier string in the name_param after any other designation
//
StringJc extractName_TypeName_emC(StringJc name_param, ThCxt* _thCxt) {
  STACKTRC_TENTRY("extractName_TypeName_emC");
  int pos = length_StringJc(name_param) - 1;
  char cc;
  while ((cc = charAt_StringJc(name_param, pos)) == ' ') { pos -= 1; }  //spaces on end
  int posend = pos + 1; //pre-decrement, posend after identifier
  while (pos >= 0 && isIdentifierPart_CharacterJc(cc = charAt_StringJc(name_param, pos))) { pos -= 1; }
  //maybe pos = -1, char before identifier
  STACKTRC_RETURN substring_StringJc(name_param, pos + 1, posend, _thCxt);  //name starts after * or ':'
}


//
//The name is the last identifier string in the name_param after any other designation
//
StringJc extractAccessPath_TypeName_emC(StringJc name_param, ThCxt* _thCxt) {
  STACKTRC_TENTRY("extractAccessPath_TypeName_emC");
  int pos = length_StringJc(name_param);
  char cc;
  while ((cc = charAt_StringJc(name_param, pos)) == ' ') { pos -= 1; }  //spaces on end
  while (pos >= 0 && isIdentifierPart_CharacterJc(cc = charAt_StringJc(name_param, pos-1))) { pos -= 1; }
  //maybe pos = -1, char before identifier
  int posEnd = pos; //pre-decrement, posend after identifier
  while (pos >= 0 && (isIdentifierPart_CharacterJc(cc = charAt_StringJc(name_param, pos-1))
                     || cc == '-' || cc == '>' || cc == '.'
        )            ) { 
    pos -= 1; 
  }
  if (pos > 0 && pos < posEnd) {
    STACKTRC_RETURN substring_StringJc(name_param, pos + 1, posEnd, _thCxt);  //
  }
  else {
    STACKTRC_RETURN null_StringJc;
  }
}




//
//Syntax of name: [{-###|!}:] [F:|U:|I:|...|TYPE*[:]] (cast)datpath->name 
//The type is the string after any -19!: as identifier
//
StringJc extractType_TypeName_emC(StringJc name_param, ThCxt* _thCxt) {
  STACKTRC_TENTRY("extractType_TypeName_emC");
  int pos = 0;
  int posmax = length_StringJc(name_param);
  char cc;
  while ((cc = charAt_StringJc(name_param, pos)) == '-' || (cc >= '0' && cc <= '9') || cc == '!' || cc == ' ' || cc == ':') {
    pos += 1;  //skip over all -09!: 
  }
  //pos is after -22!: 
  int posend = pos;
  while (posend < posmax && isIdentifierPart_CharacterJc(cc = charAt_StringJc(name_param, posend))) { posend += 1; }
  while (posend < posmax && ((cc = charAt_StringJc(name_param, posend)) == '[' || (cc >= '0' && cc <= '9') || cc == ',' || cc == ']')) {
    posend += 1;  //all [1,2] are parts of the type (array size) 
  }
  int pos2 = posend;  //check whether a identifier follows, anything should follow after type. 
  while (pos2 < posmax && (cc = charAt_StringJc(name_param, pos2)) == ' ') { pos2 += 1; } //skip over space 
  if (pos2 < posmax) {
    //only if the posend is not the end of the last identifier, it is the type identifier: 
    STACKTRC_RETURN substring_StringJc(name_param, pos, posend, _thCxt);  //name starts after * or ':'
  }
  else STACKTRC_RETURN null_StringJc;
}



//
//Syntax of name: [{-###|!}:] [F:|U:|I:|...|TYPE*[:]] (cast)datpath->name 
//The type is the string after any -19!: as identifier
//
StringJc extractStructType_TypeName_emC(StringJc name_param, ThCxt* _thCxt) {
  STACKTRC_TENTRY("extractStructType_TypeName_emC");
  int pos = indexOf_C_StringJc(name_param, '(');
  int posend = 0;
  if (pos >= 0) {
    posend = indexOf_CI_StringJc(name_param, ')', pos);
  }
  if (posend < pos) {
    STACKTRC_RETURN null_StringJc;
  }
  char cc;
  while (posend > pos && !isIdentifierPart_CharacterJc(cc = charAt_StringJc(name_param, posend))) {
    posend -= 1;  //firstly skip before '(', then skip before '*', skip over spaces
  }
  if (posend >= pos) {
    //only if any identifier is given
    STACKTRC_RETURN substring_StringJc(name_param, pos, posend + 1, _thCxt);  //name starts after * or ':'
  }
  else STACKTRC_RETURN null_StringJc;  //(  ) or ( *) or such
}



char extractInitialize_TypeName_emC(StringJc name_param, ThCxt* _thCxt) {
  STACKTRC_TENTRY("extractInitialize_TypeName_emC");
  if (indexOf_C_StringJc(name_param, '!') >= 0) {
    int posType = indexOf_C_StringJc(name_param, '*');
    int posStructType = indexOf_C_StringJc(name_param, '(');
    if (posType < posStructType || posStructType < 0) {
      STACKTRC_RETURN 'i';  //it is an Tinit connection for the handle.
    }
    else {
      STACKTRC_RETURN '!'; //an initial value for set_DataStruct_Inspc access, not a handle.
    }
  }
  else {
    STACKTRC_RETURN ' ';  //not an only-initial value.
  }
}



int extractAccessRights_TypeName_emC(StringJc name_param, ThCxt* _thCxt) {
  STACKTRC_TENTRY("extractAccessRights_TypeName_emC");
  int pos = 0;
  int posmax = length_StringJc(name_param);
  int accessRigths = 0;
  char cc = charAt_StringJc(name_param, pos);
  while (pos < posmax && (cc = charAt_StringJc(name_param, pos)) != '-' && cc == ':') { pos += 1; } //search - 
  if (cc == '-') {
    while (pos < posmax && (cc = charAt_StringJc(name_param, ++pos)) >= '0' && cc <= '9') {
      accessRigths = accessRigths * 10 + (cc - '0');
    }
  }
  STACKTRC_RETURN accessRigths;
}







bool checkType_Entry_DefPortType_emC(Entry_DefPortType_emC* thiz, ClassJc const* reflectionType) {
  char nrType = searchChar_emC(cTypes_DefPortTypes_emC, -20, thiz->type);
  if(nrType < 0 || nrType >= ARRAYLEN_emC(reflTypes_DefPortTypes_emC)) return false;
  ClassJc const* reflTypeCmp = reflTypes_DefPortTypes_emC[nrType];
  if(reflTypeCmp == reflectionType) return true; 
  //Note: compare names, the reflection instances can be differ.
  else return 0 == strncmp(reflTypeCmp->name, reflectionType->name, sizeof(reflTypeCmp->name));
}
