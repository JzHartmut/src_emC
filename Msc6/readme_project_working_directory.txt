This folder contains a Microsoft Visual Studio 6 project file. 
You can import that projectfile for a higher version of Visual studio.

==Using Visual Studio 6==
On the other hand you can work with Visual Studio 6. It runs under Windows-7 till Windows-10 too. 
It produces 32-bit code which is yet compatible with the 64-bit Windows platform.
Visual Studio 6 works proper as copy from any installation (an older PC) without installation.
Only a few paths should be set on startup. The batchfile 

 msc6_template.bat

contains the template.

==Using a temporary works space==
Only the project file *.dsp is necessary between sessions.
The Visual Studio produces some more files *.dsw, *.ncb etc. which are not necessary between sessions.
Because they should not occupy space in this folder, the project working directory is outside.
The file 

 start_Mscdsp_*.bat
 
copies the *.dsp to the temporary project working directory. The 

 pull_Mscdsp_*.bat
 
copies a changed dsp-file back to here. The temporary project working directory may be located on a RAM disk too,
or on any scratch path on your hard disk. 

Because the temporary project working directory is on another drive, 
respectively it is not the same directory as the sources, the source directory is mounted as S: drive.
On windows using of 'subst' may be seen as replacement for a linked folder in UNIX. 
The Visual Studio 6 project file uses this S: drive. 

If the S: drive is not available as free for subst, you have to replace all source entries in the dsp file.
That is not recommended. If you are in experience, you can close a network connection to S: or work
with a virtual environment (such as VMware).




 

