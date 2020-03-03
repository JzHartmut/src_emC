This folder contains headerfiles which may be included in <applstdef_emC.h> by the user for several conventions. 
This folder must not be a part of the include path! Use #include <sourceApplSpecific/applConv/file.h> to include it,
recommended only in <applstdef_emC.h>.
This headers must not be included outside of the <applstdef_emC.h>. S

This folder contains some specific C sources for different behavior due to platform conventions.
Use one of alternative sources for your convention.

