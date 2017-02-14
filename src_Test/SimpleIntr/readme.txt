This directory contains some C-Files for usage the CRuntimeJavalike in simple interrupt driven applications.
The characteristic is, that errors should never block the process. The interrupt should be end in a deterministic time!
On fatal errors the execution of the interrupt should be end. 

Errors are stored in simple data structures which can be read out by another process.
The Exception handling and the stacktrace are particularry not used or used.

Threads are not used. Thread execution may be organized outside.
