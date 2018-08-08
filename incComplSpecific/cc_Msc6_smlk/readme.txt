This is the adaption of the Visual Studio 6 (from 1998) compiler to the OSAL os/compilerindependent concept.
It is intended to use with sources generated from the simulink coder.
Therefor the directory .../CRJ/incComplSpecific/smlk_32bit should be a part of the include path too.
It is because the simulink coder defines its own types for fix sized integer, in opposite to the C99 standard.
This types should be used in the whole project for the non-generated sources too 
for the os/compilerindependent types int16 etc. to assert type compatibility. 
Therefore the rtwtypes.h from simulink is included here.
