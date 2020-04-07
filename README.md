# This git Archive contains common useable sources for C and C++ programming, named "emC"

## emC

emC is embedded multiplatform C. The approach:

* C and C++ are platform-independent languages from view of the algorithm.
* A user application can run on PC for test and simulation as well as on several platforms.
* The adaption to operation system access is done by the OSAL layer (Operation System Adaption)
* This OSAL is not a hard standard, it is flexible for your application,
  but some common approaches are regarded.
* The adaption to hardware access should be done by user by adequate wrapper routines, 
  whereby the calculation time is not ineffective if inline keyword is used.
* The language style and standards should be a intersection (subset) of all common possibilities,
  this subset is enough productive. Do not use special featuers which has not really an advantage.
* Use an ObjectOriented approach! It is possible in C too.
* Combine C and C++ in a well kind. Define pure data primary in C with typedef struct
  and integrate that via inheritance in C++ classes for C++ usage.
* Keep core algorithm in C if it is conceivable that C is need for a target platform;
  use C++ for more complex software structures which do never run on simple C only targets.
  Whereby call the C core routines with a simple C++ wrapping. C++ is usually better readable.
* ObjectJc: The origin of this set of sources had been a Runtime system for Java-translated
  C-codes. Java has a well infrastructure with a common base class java.lang.Object, 
  a reflection system for type test and symbolic access and some more.
  This approach is able to use for C/C++ too. The core access to this approach
  is the struct ObjectJc.

## directory organisation and sub modules

General sources:

* emC/... with some sub directories for different approaches are the general sources
  One do not need all sources to compile in each application, select it.
* emC/Base are the core of common sources. 
* emC/Blockheap: An algorithm with blocks with constant size in heap, less used and tested yet, 
  but present since more as 10 years.
* emC/Ctrl: Some control algorithm
* emC/Inspc: The inspector concept, sources for a rich target
* emC/InspcTargetSimple: The inspector concept, for a small target (need InspcTargetProxy)
* emC/Ipc: System for InterprocessCommunication
* emC/Ipc2c: InterprocessCommunication primary translated from Java, adequate sources
  in srcJava_vishiaRun/org/vishia/communication/*
* emC/J1c: contains sources which are primary translated from Java for general appoaches.
  Especially StringPartJc and StringPartScanJc are often used for simple parsing of texts.
  The adqequates can be located in srcJava_vishiaBase/org/vishia/util/*.java.
* emC/Jc: That were the originally counterparts to some java core classes 
  for Java2C translated sources. They can be used for ordinary C applications too.
  Some parts are moved meanwhile to emC/Base because emC/Base contains the real general things.
* emC/MsgDisp: A message dispatcher as adequate to srcJava_vishiaBase/org/vishia/msgDispatch/*.java.
* emC/OSAL: Definition of all OSAL access possibilities, not their implementation.
* emC/StateM: Core sources for state machine processing
* emC/Test: Simple routines for test organization (Unit test)

Special sources, it is for several target systems, several running conditions,
as pattern for other target systems.

* emC_inclApplSpec: Some possible application specific definitions, 
  contains variants of applstdef_emC.h
* emC_inclComplSpec: Some possible compiler/operation system specific definitions,
  contains variants of compl_adaption.h
* emC_srcApplSpec: Some variants of sources for application specific decision of common approaches
* emC_srcOSALspec: Sources for some OSAL operation system adaption layer.

Make, build, applications:

* make/scriptsCommon: Especially for reflection generation and build
* make/libs: Libraries from internet downloaded here, especially vishiaBase.jar
* make/mklib: Some library make systems for all common sources of emC
* make/InspcTargetProxy: It is an application, the bridge between the Inspector tool
  for symbolic access via Ethernet/Socket communication and a less target.
* make/Java2c: scripts to run Java2C (yet not maintained, some years old, but should run)


  

## usage, test and build

The project on github: test_emC contains some projects in Eclipse CDT, Visual Studio
and Code Composer Studio for Texas Instruments too, which can visit and used.

A common test organized in gradle uses gcc and g++ compiler which is present on MS-Windows
with a MinGW installation for example. It runs in Linux and Windows.

The sources have traditionally grown. There may be some discrepancy and old versions. 
You should use the sources only in your own responsibity.

The improvement and more tests will be done.

## Libraries

Because of emC is not for a specific system, it is for embedded Control, 
there is not a universal library. For usage under Windows (for test of sources
for embedded Control) a project make/mklib/VS15-IDE/libMsc15_emC.sln
for Microsoft visual Studio 15 is given. 

It is proper to use a library from emC, because the linker selects the necessary Objects
from the given library automatically, for compact code. But you should build the library
for yourself, for your special project.



