#@echo off
#REM start problem: The batch needs the zbnf.jar File. Either the ZBNFJAX_HOME environment variable is set already,
#REM or it is set via a found setZBNFJAX_HOME.bat, or it is on D:\vishia... or you should adapt it.
#call setZBNFJAX_HOME.bat
#if "%ZBNFJAX_HOME%" == "" set ZBNFJAX_HOME=../../zbnfjax

#It is the path if this sources are part of test_emC
if test -f ../../../../tools/vishiaBase.jar; then export JAR=../../../../tools/vishiaBase.jar; fi
if test -f ../../../../../../../tools/vishiaBase.jar; then export JAR=../../../../../../../tools/vishiaBase.jar; fi

java -cp $JAR org.vishia.jztxtcmd.JZtxtcmd $0
exit                  
                                                                                                
==JZtxtcmd==                                                                                           

include ../../../make/scriptsCommon/Cheader2Refl.jztxt.cmd; 
currdir=<:><&scriptdir><.>;
                                        
Fileset headers = 
( emC/Inspc/TargetProxy/*.h);

main()                                                                                                  
{
  //mkdir T:/header;
  zmake "genRefl/*.crefl" := genReflection(../../../:&headers); //, html="T:/header");
  <+out>success<.+n>

}

