This directory contains some sub directories.
One of FwConv... and one of os_... should be part of the include path to find the follwing files
in an application or platform specific kind:

* os_types_def.h
Contains some basic definitions compiler- and platform specific.


* fw_assert.h
Definition of some assertion macros.

* fw_Platform_conventions.h
Definition of some more platform behaviour.


*alignbyt.h
*alignopt.h
Two variants of alignment pragmas. That files can be included in application sources if necessary.

* BlockHeap_PlatformSpec.h
Definition of Blockheap usage, should be only present if blockheap is used in generally.


An application can copy and adapt that files and store in any other directories 
of the application- and target specific include path. This directories here are used as include directories 
in the examples of CRuntimeJavalike and as an standard setting. 