#@echo off
#REM start problem: The batch needs the zbnf.jar File. Either the ZBNFJAX_HOME environment variable is set already,
#REM or it is set via a found setZBNFJAX_HOME.bat, or it is on D:\vishia... or you should adapt it.
#call setZBNFJAX_HOME.bat
#if "%ZBNFJAX_HOME%" == "" set ZBNFJAX_HOME=../../zbnfjax

#It is the path if this sources are part of test_emC
if test -f ../../../../libs/vishiaBase.jar; then export JAR=../../../../libs/vishiaBase.jar; fi
if test -f ../../../../../../libs/vishiaBase.jar; then export JAR=../../../../../../libs/vishiaBase.jar; fi

java -cp $JAR org.vishia.jztxtcmd.JZtxtcmd $0
exit                  
                                                                                                
==JZtxtcmd==                                                                                           

include ../../make/scriptsCommon/Cheader2Refl.jztxt.cmd; 
currdir=<:><&scriptdir><.>;
                                        
Fileset headers = 
( emC/Base/Time_emC.h
##, emC/Base/EventQu_emC.h  ##TODO use it but some currection necessary.
##, emC/Base/ClassJc_FullReflection_emC.h
, emC/Base/DefPortTypes_emC.h
##, emC/Base/Event_emC.h
##, emC/Base/Exception_emC.h
##, emC/Base/ExcThCxtBase_emC.h
##, emC/Base/ExcThreadCxt_emC.h
##, emC/Base/Formatter_emC.h
##, emC/Base/Handle_ptr64_emC.h
##, emC/Base/Handle_ptr64_TimeMeas_emC.h
, emC/Base/LogMessage_emC.h
##, emC/Base/MemC_emC.h
##, emC/Base/ObjectJcVtbl_emC.h
##, emC/Base/ObjectRefl_emC.h
##, emC/Base/ObjectSimple_emC.h
##, emC/Base/Object_emC.h
##, emC/Base/ParseArgs_emC.h
##, emC/Base/Readline_emC.h
, emC/Base/RingBuffer_emC.h
##, emC/Base/SimpleC_emC.h
, emC/Base/StateMachine_emC.h
##, emC/Base/StringBase_emC.h
##, emC/Base/String_emC.h
##, emC/Base/SystemInit_emC.h
##, emC/Base/Timeconversions_emC.h
, emC/Base/VaArgBuffer_emC.h
##, emC/Base/Va_list_emC.h
);

main()                                                                                                  
{
  //mkdir T:/header;
  zmake "genRefl/*.crefl" := genReflection(../../:&headers); //, html="T:/header");
  <+out>success<.+n>

}

