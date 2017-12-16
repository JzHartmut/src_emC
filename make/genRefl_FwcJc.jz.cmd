JZtxtcmd.bat %0 %1

exit /B

==JZtxtcmd==

include $ZBNFJAX_HOME/jzTc/Cheader2Refl.jztxt.cmd;
currdir=scriptdir;

Fileset headers = 
( source:Jc/FormatterJc.h);

main()
{
  mkdir T:/header/Jc;
  zmake "../genRefl/*.crefl" := genReflection(..&headers, html="T:/header"); 
  
  <+out>success<.+n>

}

