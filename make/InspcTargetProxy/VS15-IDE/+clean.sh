#REM remove the libs too, it should be build only on demand if necessary
echo cleanup in:
pwd

if test -d lib; then rm -r -d -f lib/*; fi #let lib empty existing

if test -d debug; then rm -r -d -f debug/*; rm -d debug; fi
if test -d dbgC1; then rm -r -d -f dbgC1/*; rm -d dbgC1; fi
if test -d x64; then rm -r -d -f x64/*; rm -d x64; fi
if test -d x32; then rm -r -d -f x32/*; rm -d x32; fi
if test -d .vs; then rm -r -d -f .vs/*; rm -d .vs; fi
rm /S/Q -f *.db
rm /S/Q -f *.sdf


