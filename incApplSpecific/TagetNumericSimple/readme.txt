This directory should be part of the include path of the compiler if the system:
* won't use try-throw-catch 
* is well tested, an exception log should be stored only in a maintenance area.
* No Runtimeheap will be used, Allocation only on startup of the application
* No StringJc-processing, only constant text messages.
