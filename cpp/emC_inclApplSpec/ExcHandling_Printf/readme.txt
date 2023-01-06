This directory should be part of the include path of the compiler if the system:
* won't use try-throw-catch 
* is well tested, an exception should be send a printf to the console instead.
* No Runtimeheap will be used, Allocation only on startup of the application
* StringJc-processing is supported.
This is especially for debugging an simple numeric application or a modultest on PC.
Especially the feature of printf is proper for PC, but only for simple applications.
