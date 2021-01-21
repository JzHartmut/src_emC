REM the following batch file should be adapted to the position of zbnfjax on hard disk. Template see zbnfjax/batch_template/jztxtcmd.bat
JZtxtcmd.bat %0 %1 %2
REM alternatively:
::set ZBNFJAX_HOME=D:/vishia/ZBNF/zbnfjax
::java -cp %ZBNFJAX_HOME%/zbnf.jar org.vishia.jztxtcmd.JZtxtcmd  %0 %1 %2

exit /B                                      
                                                                   
==JZtxtcmd==

##jzTc script to generate a Reflection.crefl file from some struct of Header.
##invoke this batch with 2 arguments: path/to/headerfile.h path/to/dst.crefl 
##made by Hartmut Schorrig, www.vishia.org, 2018-08-11  
##
##History:
##2017-06: created, used instead Java-core-programmed reflection generation. Advantage: pattern-oriented, 
##2018-08-12: Fine adjustments to new Sources of emC.  
##2018-08-11: 
##  * Now supports unnamed or named embedded struct or union. Before: compiler error for such constructs
##  * Generates the super class not as attribute.
##  * writes now the field in ClassOffset_idxVtblJc:
##  ** It is valid for new sources of emC, especially emC/Object_emC.h for definition of ClassOffset_idxVtblJc
##  with element field, and for Jc/ReflectionJc.h: The definition of FieldJc is moved to emC/Object_emC.h.
##  ** For older sources it runs if superclasses are not used.


##Class reflStructDefinition = org.vishia.header2Reflection.CheaderParser$StructDefinition;


String openBB = "{";   ##openBlockBracket use indirect
String closeBB = "}";


Obj headerTranslator = java new org.vishia.header2Reflection.CheaderParser(console);

Map reflStdReplacement = {
  String MemUnit = "OS_PtrValue";
};

Map reflSimpleTypes = {
  String void = "REFLECTION_void";
  String uint = "REFLECTION_int";
  String int = "REFLECTION_uint";
  String char16 = "REFLECTION_uint16";
  String char_T = "REFLECTION_uint8";
  String char = "REFLECTION_uint8";
  String uint32_T = "REFLECTION_uint32";
  String uint32_t = "REFLECTION_uint32";
  String uint32 =   "REFLECTION_uint32";
  String int32_T =  "REFLECTION_int32";
  String int32_t =  "REFLECTION_int32";
  String int32 =    "REFLECTION_int32";
  String intptr_t =    "REFLECTION_int32";
  String uint16_t = "REFLECTION_uint16";
  String Uint16 =   "REFLECTION_uint16";
  String uint16 =   "REFLECTION_uint16";
  String int16_t =  "REFLECTION_int16";
  String int16 =    "REFLECTION_int16";
  String uint8_t =  "REFLECTION_uint8";
  String Uint8 =    "REFLECTION_uint8";
  String uint8 =    "REFLECTION_uint8";
  String int8_t =   "REFLECTION_int8";
  String int8 =     "REFLECTION_int8";
  String real32_T =    "REFLECTION_float";
  String float =    "REFLECTION_float";
  String double =   "REFLECTION_double";
  String int32BigEndian =    "REFLECTION_int32";
  String int16BigEndian =    "REFLECTION_int16";
};  

Map bytesSimpleTypes = {
  ##String void =     "4";  ##void is a reference usual. Not a primitive type.
  String int =      "4";
  String char16 =   "2";
  String char_T =   "1";
  String char =     "1";
  String uint32_T = "4";
  String uint32_t = "4";
  String uint32 =   "4";
  String int32_T =  "4";
  String int32_t =  "4";
  String int32 =    "4";
  String intptr_t = "4";
  String uint16_t = "2";
  String Uint16 =   "2";                                        
  String int16_t =  "2";
  String int16 =    "2";
  String uint8_t =  "1";
  String Uint8 =    "1";
  String uint8 =    "1";
  String int8_t =   "1";
  String int8 =     "1";
  String real32_T =    "4";
  String float =    "4";
  String double =   "8";
  String int32BigEndian =    "4";
  String int16BigEndian =    "2";
};  

##
##The here associated numbers are the indices in const ClassJc* simpleTypes_ClassJc[...] in the emC C sources.
##
Map idSimpleTypes = {
  Num void =     1;
  Num int =      4;
  Num char16 =   7;
  Num char_T =  14;
  Num char =    14;
  Num uint32_T = 5;
  Num uint32_t = 5;
  Num uint32 =   5;
  Num int32_T =  4;
  Num int32_t =  4;
  Num int32 =    4;
  Num intptr_t = 4;
  Num uint16_t = 7;
  Num Uint16 =   7;                                        
  Num int16_t =  6;
  Num int16 =    6;
  Num uint8_t =  9;
  Num Uint8 =    9;
  Num uint8 =    9;
  Num int8_t =   8;
  Num int8 =     8;
  Num real32_T =12;
  Num float =    12;
  Num int64 =    2;
  Num int64_t =  2;
  Num uint64 =   3;
  Num uint64_t = 3;
  Num boolean_T =     15;
  Num boolean =     15;
  Num bool =     15;
  Num float_complex =   20;
  Num double_complex =  21;
  Num ObjectJc =     25;
  Num StringJc =     29;
  Num OS_PtrValue =  30;
  Num int32BigEndian =    4;
  Num int16BigEndian =    6;
};  



##
##Generates the reflection of one type (struct, class).
##It is invoked as subtext call.
##
sub genReflStruct(Obj struct, Obj fileBin, Obj fileOffsTypetable) 
{ Num nrElements = 0;
  String structBasename = struct.baseName("_s");
  String structReflname = java org.vishia.header2Reflection.CheaderParser.prepareReflName(structBasename);
  for(entry:struct.entries){if(entry.name) {
    nrElements = nrElements +1;
  } }
  if(!fileBin) {
    <:>
====
====//forward declaration of the following definition necessary because extern_C definition. 
====extern_C const ClassJc refl_<&structBasename>;
====
====#ifdef DEF_REFLECTION_OFFS_FILE  //experience: ReflOffs h-file-related
====int32 const reflectionOffset_<&struct.baseName("_s")>[] =
===={ 123  //< &nrClass>   //index of class in Offset data<: >
    <.>
    <:>
====}; 
====    
====#else  //DEF_REFLECTION_FULL
====
    <.>
    for(entry:struct.entries) { if(entry.name && entry.type) { ##Note a type is not present for a #define inside a struct.
      Obj typeRefl;
      if(entry.description.reflType) {
        typeRefl = entry.description.reflType;
      } elsif(entry.type) {
        typeRefl = entry.type;
      }
      if(not reflSimpleTypes.get(typeRefl.name)) { 
        String sTypename = typeRefl.baseName("_s", "_t");
        <:>
  ======extern_C const ClassJc refl_<&sTypename>;  //used for field <&entry.name>
        <.>      
      }
  } }}
  if(!fileBin) {
    Num hasSuperclass = 0;
    if(struct.superclass) {
      Num accessLevel = 0;
      if(struct.superclass.description) {                                  
        accessLevel = struct.superclass.description.accLevel;
      }
      String reflSuperName = <:>refl_<&struct.superclass.type().baseName("_s", "_T")><.>;
      <:>  
======
======extern_C const ClassJc <&reflSuperName>;  //the super class here used.
======const struct SuperClasses_<&struct.name>_ClassOffset_idxVtblJcARRAY_t  //Type for the super class
======{ ObjectArrayJc head;
======  ClassOffset_idxVtblJc data[1];
======}  superClasses_<&struct.name> =   //reflection instance for the super class
======{ INIZ_ObjectArrayJc(superClasses_<&struct.name>, 1, ClassOffset_idxVtblJc, refl_ClassOffset_idxVtblJc, ID_refl_ClassOffset_idxVtblJc)
======  , { &<&reflSuperName>                                   
======    , 0 //TODO Index of mtbl of superclass
======      //The field which presents the superclass data in inspector access.
======    , { "super"              ##<&struct.superclass.name>"     
======      , 0 //arraysize
======      , &<&reflSuperName>  //type of super                                                                                         
======      , kEmbedded_Modifier_reflectJc //hint: embd helps to show the real type.
======        | (<&accessLevel><< kBitAccessLevel_Modifier_FieldJc)  //access level
======        | (7<< kBitChangeLevel_Modifier_FieldJc)  //never change
======      , 0 //offsetalways 0 (C++?)
======      , 0  //offsetToObjectifcBase
======      , &<&reflSuperName>  
======      }
======    }
======};                                                                                  
======<.>
  } }
  String sClassNameShow = struct.name();  ##TODO shorten
  if(fileBin) {
    Num posSuperClassAddr;
    if(struct.superclass) {
      posSuperClassAddr = fileBin.addSuperclass(struct.superclass.type().baseName("_s", "_t"));
    }
    Num nrClass = fileBin.addClass(struct.baseName("_s"), sClassNameShow);
    if(struct.superclass) {
      fileBin.setClassSuperclass(posSuperClassAddr); 
    }
    fileOffsTypetable.add(<:>refl_<&struct.baseName("_s")><.>); 
    <:>
====int32 const reflectionOffset_<&struct.baseName("_s")>[] =
===={ <&nrClass>   //index of class in Offset data<: >
    <.>
  }//fileBin
  String sFieldsInStruct = "null";
  ##if(struct.entries.size() > hasSuperclass) { ##hasSuperclass is 1 if the first entry is the superclass.
  if(struct.attribs.size() > 0) { ##hasSuperclass is 1 if the first entry is the superclass.
    sFieldsInStruct = <:>(FieldJcArray const*)&refl_Fields_<&struct.name><.>;
    Stringjar wrFields;  ##the container for the generated field data
    Map retEntries;
    ##                                                                                  
    ## generates all fields:
    ##
    retEntries = call attribs_struct(wr = wrFields, fileBin = fileBin, struct = struct);
    ##
    if(!fileBin) {                                                         
      <:>
======const struct Reflection_Fields_<&struct.name>_t
======{ ObjectArrayJc head;
======  FieldJc data[<&retEntries.nrofEntries>];
======} refl_Fields_<&struct.name> =
======{ INIZ_ObjectArrayJc(refl_Fields_<&struct.name>, <&retEntries.nrofEntries>, FieldJc, refl_FieldJc, ID_refl_FieldJc)
======, {  
      <&wrFields>
======} }; 
====== 
      <.>  
    }
  }  
  ##The class:
  String classModif;
  String sizeName;               
  if(struct.implicitName !=null) { sizeName = <:>((<&struct.parent.name>*)0x1000)-><&struct.implicitName><.>; }
  else { sizeName = struct.name; }
  if(!fileBin) {
    <:>
====#define DEFINED_refl_<&structBasename>    
====const ClassJc   refl_<&structBasename> =
===={ INIZ_objReflId_ObjectJc(refl_<&structBasename>, refl_ClassJc, ID_refl_ClassJc)
====, "<&structReflname>"
====, 0
====, sizeof(<&sizeName>)
====, <&sFieldsInStruct>  //attributes and associations
====, null  //method      
====, <:if:reflSuperName>&superClasses_<&struct.name>.head.object<:else>null<.if>  //superclass  
====, null  //interfaces  ##TODO check first union
====, <:if:struct.isBasedOnObjectJc>mObjectJc_Modifier_reflectJc<:else>0<.if>   ## if union{ ObjectJc obj, ...} or 1. element ObjectJc
====#ifdef DEF_ClassJc_Vtbl  
====, <:if:struct.description.vtbl>&<&struct.description.vtbl>.tbl.head<:else>null<.if>  //virtual table
====#endif
====};
====
====#endif //DEF_REFLECTION_FULL
====<.>
  } 
  if(fileBin) {
    if(struct.isBasedOnObjectJc){ fileBin.setClassBasedOnObjectJc(); }
    fileBin.closeAddClass();
      <:>
======<&closeBB>;
======
======extern_C ClassJc const refl_<&struct.baseName("_s")>; //forward declaration because extern "C" 
======ClassJc const refl_<&struct.baseName("_s")> = 
======{ <&nrClass>   //index of class in Offset data    //sizeof(reflectionOffset_<&struct.baseName("_s")>)
======  #ifndef DEF_NO_StringJcCapabilities
======, "<&struct.baseName("_s")>"##Hint: the baseName without _s
======  #endif
======, &reflectionOffset_<&struct.baseName("_s")>[0]
======};
      <.>
  }
}

                                                                          




                

##
##Subroutine writes the C-code for an entry of a struct.
##Regards bitfields
##
sub attribs_struct(Obj wr, Obj fileBin, Obj struct)
{ Num return.nrofEntries = 0;
  String offset = "0";    ##initial value, keep it on bitfields
  String sizetype = "0";  ##initial, no element before 1. bitfield
  if(struct.superclass) {
    sizetype = <:>sizeof(<&struct.superclass.type().name>)<.>;
  }
  Bool bitfield = 0;
  Num bitPosition = 0;
  String structBasename = struct.baseName("_s");

  ##for(entry:struct.entries) { 
  for(entry:struct.attribs) { 
    if(!entry.name || entry.description.noRefl) {
      ##unnamed entry, especially on inner struct, do nothing. The inner struct is handled already.
      ##unnamed entry on bitfields, do nothing don't show it.
    } else {
      String sTypeRefl;
      String bytesType;
      String modifier = "0";
      Num mModifier = 0;                                
      Obj typeRefl;
      ##
      ## sTypeRefl
      ##
      if(entry.description.reflType) {  ##from annotation in comment, CHeader.zbnf: @refl: <type?reflType> 
        typeRefl = entry.description.reflType;
      } elsif(entry.type) {
        typeRefl = entry.type;  ##from parsed type
      }
      
      if(typeRefl) { ##not set on a macro based entry
        ##
        String typename = typeRefl.baseName("_s", "_t");  ##name ends on _s then without _s, forward ends on _t then without
        String typenameReplace = reflStdReplacement.get(typename);
        if(typenameReplace) { typename = typenameReplace; }                   ##simple replacement
        ##
        bytesType = bytesSimpleTypes.get(typename);
        if(bytesType){ 
          modifier = <:>(<&bytesType><<kBitPrimitiv_Modifier_reflectJc)<.>;
          Num nBytesType = bytesType;  //conversion to numeric
          mModifier = Num.shBits32To(nBytesType, %org.vishia.byteData.Class_Jc.kBitPrimitiv_Modifier, 3);
        } else { modifier = "0"; }
        ##
        if(reflReplacement) {                           
          sTypeRefl = reflReplacement.get(typename);
          if(!sTypeRefl) { 
            sTypeRefl = <:>&refl_<&typename><.>; 
          }
        } else {
          sTypeRefl = reflSimpleTypes.get(typename); ##check whether the type is known as simple type
          if(!sTypeRefl) { ##not a simple type
            sTypeRefl = <:>&refl_<&typename><.>; 
          }
        }
      }
      ##
      String arraysize;
      ##
      Num zPointer = 0;
      if(typeRefl.pointer_) { zPointer = typeRefl.pointer_.size();}
      if(zPointer >0){ 
        modifier = <:><&modifier> | kReference_Modifier_reflectJc<.>;   ##reference type, from primitive or class type. 
        mModifier = mModifier + %org.vishia.byteData.Class_Jc.kReference_Modifier;
      }
      if(entry.description && entry.description.accLevel >0) {
        modifier = <:><&modifier> | (<&entry.description.accLevel> << kBitAccessLevel_Modifier_FieldJc)<.>;
        mModifier = mModifier + &entry.description.accLevel *1024;
      }
      if(entry.description && entry.description.chgLevel >0) {
        modifier = <:><&modifier> | (<&entry.description.chgLevel> << kBitChangeLevel_Modifier_FieldJc)<.>;
        mModifier = mModifier + &entry.description.chgLevel * 8192;
      }
      if(entry.bOS_HandlePointer) { 
        //debug "OS_HandlePointer";
        modifier = <:><&modifier> | kHandlePtr_Modifier_reflectJc<.>;
        mModifier = mModifier + %org.vishia.byteData.Class_Jc.kHandlePtr_Modifier;
      }
      if(entry.arraysize.value) {
        arraysize = <:><&entry.arraysize.value> //nrofArrayElements<.>;
        modifier = <:><&modifier> | kStaticArray_Modifier_reflectJc<.>;
        mModifier = mModifier + %org.vishia.byteData.Class_Jc.kStaticArray_Modifier;
      } else {
        arraysize = "0   //no Array, no Bitfield";
      }
      if(entry.bitField) {
        arraysize = <:>(uint16)(<&bitPosition> + (<&entry.bitField> << kBitNrofBitsInBitfield_FieldJc))<.>;
        bitPosition = bitPosition + entry.bitField;
        sTypeRefl = "REFLECTION_BITFIELD";
        modifier = <:><&modifier> | kBitfield_Modifier_reflectJc<.>;
        mModifier = mModifier + %org.vishia.byteData.Class_Jc.kBitfield_Modifier;
        if(!bitfield) {   ##the first bitfield:
          offset = <:><&offset> + <&sizetype>/* offset on bitfield: offset of element before + sizeof(element before) */<.>;
          bitfield = 1;
        } ##else: further bitfields: keep offset string 
      } elsif(sTypeRefl) { ##don't set offset = ... for an entry which is not used (espec. #define)
        if((entry.arraysize || not bytesType) && not typeRefl.pointer_) {
          modifier = <:><&modifier>|kEmbedded_Modifier_reflectJc<.>;
          mModifier = mModifier + %org.vishia.byteData.Class_Jc.kEmbedded_Modifier_reflectJc;
        }
        ##
        String sElement;
        if(struct.implicitName) { ##it is an implicitely struct
          if(struct.arraysize !=null) {
            String sImplArray = <:>[0]<.>; ##offset inside first element.
          } else {
            String sImplArray = "";
          }
          String structParentName = struct.parent.name;
          if(structParentName == null) { structParentName = <:>struct <&struct.parent.tagname><.>; } ##on struct tagname{...}; definition kind.
          sElement = <:>((<&structParentName>*)(0x1000))-><&struct.implicitName><&sImplArray>.<&entry.name><.>;
          offset = <:>(int16)( ((intptr_t)(&<&sElement>)) <: >
                              - ((intptr_t)(&((<&structParentName>*)(0x1000))-><&struct.implicitName>)) )  /*implicit struct*/<.>;
        } else {
          String structName = struct.name;
          if(structName == null) { structName = <:>struct <&struct.tagname><.>; } ##on struct tagname{...}; definition kind.
          sElement = <:>((<&structName>*)(0x1000))-><&entry.name><.>;
          offset = <:>(int16)( ((intptr_t)(&<&sElement>)) -0x1000 )<.>;
        }
        sizetype = <:>sizeof(<&sElement>)<.>;
        ##
        ##if(entry.type) {
        ##  sizetype = <:>sizeof(<&entry.type().name>)<.>;
        ##} else {                                              
        ##  sizetype = "4-4 /*unknown type*/";
        ##}
        bitfield = 0;  ##detect a next bitfield, for offset calculation.
      }
      if(sTypeRefl) { ##else: a #define
        return.nrofEntries = return.nrofEntries +1;
        String nameRefl = java org.vishia.header2Reflection.CheaderParser.prepareReflName(<:><&entry.name><.>);
        if(!fileBin) {
          <+wr><:><:indent:2=>
==========    { "<&nameRefl>"
==========    , <&arraysize>                           
==========    , <&sTypeRefl>                                                                                            
==========    , <&modifier> //bitModifiers
==========    , <&offset>
==========    , 0  //offsetToObjectifcBase                                                            
==========    , &refl_<&structBasename>
==========    }
==========  <:hasNext>, <.hasNext><: >
          <.><.+>
        }
        if(fileBin) {
          Num idType = idSimpleTypes.get(typename);  ##stores 0 if not found.
          if(idType ==0) { idType = -1; }  ##to signal, unknown type
          if(return.nrofEntries == 1) { fileBin.addFieldHead(); }
          Num typeAddress = -1;
          Num nArraySize = entry.arraysize.value;
          fileBin.addField(nameRefl, idType, typename, mModifier,nArraySize); ##modifier, arraysize); 
          <:>
==========, ((<&sizetype><<16) | (<&offset>))<: >          
          <.>       
        }//!fileBin
      } //sTypeRefl, a field  
  } } //if for
}







################################################################################################################
##
##This routine is called from a user's script.  
##
sub genReflection(Obj target: org.vishia.cmd.ZmakeTarget, String fileBin = null, String fileOffs, String html = null)
{
  call genDstFiles(target = target, html=html, sfileBin = fileBin, sfileOffs = fileOffs, genRoutine="genReflectionHeader", fileExt=".crefl");
}




################################################################################################################
##
##The routine to generate reflection files, one file per header file.
##It parses all header files one after another, then generates reflection
##
sub genDstFiles(Obj target: org.vishia.cmd.ZmakeTarget, String sfileBin, String sfileOffs, String genRoutine, String fileExt, String html = null)
{

  <+out>currdir=<&currdir><.+n>
  List inputs = target.allInputFiles();
  for(input:inputs)
  { <+out>files: <&input.absfile()><.+n>
  }
  List inputsExpanded = target.allInputFilesExpanded();
  Obj fileBin;
  if(sfileBin) {
    Bool endian = false;  ##Note: depends on the target processor, false for PC platform.
    fileBin = new org.vishia.header2Reflection.BinOutPrep(sfileBin, <:><&sfileBin>.lst<.>, endian, false, 0);
    Obj fileOffsTypetable = new java.util.LinkedList();
  } else {
    Obj fileOffsTypetable;
  }
  if(fileBin) {
    Openfile fileOffs = <:><&sfileOffs>.c<.>;
    Openfile fileOffsH = <:><&sfileOffs>.h<.>;
    <+fileOffs><: >
    <:>/**This file is generated by Cheaer2Refl.jzTc mady by Hartmut Schorrig Version 2020-04-26
==== */
====#include <applstdef_emC.h>  //may/should contain following compilerswitch:
====#ifdef DEF_REFLECTION_OFFS  //compile this only if DEF_REFLECTION_OFFS should be used 
====#include <emC/InspcTargetSimple/Target2Proxy_Inspc.h>  //declares reflectionOffsetArrays
====#define protected public    //The access also to private and protected members should be 
====#define private public      //  possible here, to calculate its offset.
====
    <.><.+>
    <+fileOffsH><: >
    <:>#ifndef HGUARD_REFLECTION_OFFS
====#define HGUARD_REFLECTION_OFFS    
====/**This file is generated by Cheaer2Refl.jzTc mady by Hartmut Schorrig Version 2020-04-26
==== * It contains all defines for generated reflection. 
==== */
====#if !defined(DEF_REFLECTION_FULL) && !defined(DEF_REFLECTION_OFFS)
====  #define DEF_REFLECTION_OFFS
====#endif
====
    <.><.+>
    ##Note: write all in one file, it is for the specific target.
  } else {
    Obj fileOffs = null;
    ##Note: create one file per header. It is commonly able to use for a more complex system.
  }
  for(headerfile: inputsExpanded)
  { String outfile;
    if(target.output.allTree()) {
      outfile = headerfile.localname();
    } else {
      outfile = headerfile.name();
    }  
    String fileDst = <:><&target.output.absdir()>/<&outfile><&fileExt><.>;
    <+out><&headerfile.absfile()> => >><&fileDst><<<.+n>
    String fileDst1;
    if(fileBin) {
      fileDst1 = sfileOffs; ##generates reflOffs.c
    } else {
      fileDst1 = fileDst;
    }
    ##invocation per header file. 
    call genDstFile(filepath = headerfile, fileBin = fileBin, fileRefl = fileOffs, fileOffsTypetable = fileOffsTypetable
      , fileDst = fileDst1, genRoutine=genRoutine, html = html);
  }
  if(fileBin) {
    fileBin.postProcessBinOut();
    fileBin.close();
    ##debug;
    ##Openfile fileOffs = sfileOffs;
    Num id_refl = 1;
    for(entry: fileOffsTypetable) {
      <+fileOffsH><: >
      <:>
======#define ID_<&entry> <&id_refl>
======#define DEFINED_<&entry><.><.+>      
      id_refl = id_refl +1;
    }##for
    ##
    <+fileOffs><: >
    <:>
====
====/**Array of pointer to all refl_Type definition.
==== * The order of the pointer matches to the ClassJc#index
==== * The target2proxy service accesses the correct ClassJc by given index in communication.
==== */
====ClassJc const* const reflectionOffsetArrays[] =
===={ null  //index 0 left free <: >
    <.><.+>
    for(entry: fileOffsTypetable) {
      <+fileOffs><: >
      <:>
======, &<&entry><: >
      <.><.+>
    }//for
    <+fileOffs>
    <:>
====};
====
====#endif //DEF_REFLECTION_OFFS
====<.><.+>
    fileOffs.close();
    <+fileOffsH><:n><:n>#endif //HGUARD_REFLECTION_OFFS<.+n>
    fileOffsH.close();
  }
}




##################################################################################################################
##
##Generates one file for the given header.
##args:
## * genRoutine: It determines which sub routine is used for the file content.
##
sub genDstFile(Obj filepath :org.vishia.cmd.JZtxtcmdFilepath, Obj fileBin, Obj fileRefl, Obj fileOffsTypetable, String fileDst, String genRoutine, String html = null)
{
  ##java org.vishia.util.DataAccess.debugMethod("setSrc");
  Obj args = java new org.vishia.header2Reflection.CheaderParser$Args();
  args.addSrc(filepath.absfile(), filepath.localname());

  ##args.setDst(target.output.absfile());
  
  args.setZbnfHeader(<:><&scriptdir>/Cheader.zbnf<.>);
  
        
  Obj headers = headerTranslator.execute(args);               ##This parses one header in this Java class

  for(headerfile: headers.files){
    <+out>generate <&headerfile.fileName> <.+n>
    ##Only to help change the script, output all parsed data:
    if(html !=null && html.length()>0) {
      <+out>html: <&html>/<&headerfile.fileName><.+n>
      mkdir <:><&html>/<&headerfile.fileName>'<.>;
      test.dataHtml(headers, File:<:><&html>/<&headerfile.fileName>.html<.>);
    }
    call &genRoutine(headerfile = headerfile, fileBin = fileBin, fileRefl = fileRefl, fileOffsTypetable = fileOffsTypetable, fileDst = fileDst);
  }
} 









################################################################################################################
##
##The routine to generate reflection files, one file per header file.
##It parses all header files one after another, then generates reflection
##
sub genReflectionHeader(Obj headerfile, Obj fileBin, Obj fileRefl, Obj fileOffsTypetable, String fileDst)
{
  FileSystem.mkDirPath(fileDst);  ##Note: makes only the directory, because fileDst does not end with /
  if(fileRefl) {
    Obj outRefl = fileRefl;
  } else {  
    Openfile outRefl = fileDst;                                               
  }
    <+outRefl>
    <:>
====#include <<&headerfile.fileName>.h>  ##it comes from args.addSrc(...,input.localname())
    <.><.+>
  for(classC: headerfile.listClassC) {           ##listClassC are the divisions /*@ CLASS_C or only '-outside-'
    call genEntries(headerBlock = classC, outRefl = outRefl, fileOffsTypetable = fileOffsTypetable, fileBin=fileBin);
  }
  if(not fileRefl) {
    outRefl.close();
  }
}


sub genEntries(Obj headerBlock, Obj outRefl, Obj fileBin, Obj fileOffsTypetable)
{
  for(entry: headerBlock.entries) {            ##all stuff in this division
    ##                                         ##select somewhat from the stuff:
    if( entry.whatisit == "#ifdef") {          ##conditional block
      call genEntries(headerBlock = entry, outRefl = outRefl, fileOffsTypetable = fileOffsTypetable, fileBin=fileBin);
    } 
    elsif( (  entry.whatisit == "structDefinition" 
           || entry.whatisit == "unionDefinition"
           || (entry.whatisit == "classDef" && not entry.isClassOfStruct())
           ) 
        && not entry.description.noReflection
        && not(entry.name >= "Mtbl")
        && not(entry.name >= "Vtbl")
      ) {
      ##
      ##check whether a Bus should be generated.
      ##
      <+outRefl><:call:genReflStruct:struct=entry, fileOffsTypetable = fileOffsTypetable, fileBin=fileBin><.+>
    }
    if(entry.whatisit == "unionDefinition") {
      <+>  union <.n+>                                          
      for(variant: entry.attribs) {
        if(variant.struct) {
          <+>  :struct <&variant.struct.tagname>  <.+n>  
          
        }
      }
    }
  }
}



##    elsif( (  entry.whatisit == "structDefinition" 
##           || entry.whatisit == "unionDefinition"
##           || entry.whatisit == "classDef"
##           )  
##         && not entry.description.noReflection
##         && not(entry.name >= "Mtbl")
##         && not(entry.name >= "Vtbl")
##      ) {


