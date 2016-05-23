jzcmd genXmi13.jz.bat
exit /B



==JZcmd==

##!checkJZcmd=<:><:scriptdir>/result/CHECK_<&scriptfile>.zgen<.>;

include $ZBNFJAX_HOME/zmake/Cheader2Xmi.jzcmd;

currdir=scriptdir;


Fileset inputHeader =
( 
  include/Fwc/*.h
, include/Jc/*.h
, include/BlockHeap/*.h
, include/OSAL/*.h
);


Filepath xmlHeader1 = D:/vishia.tmp/Jc/CRuntimeJavalike/xmlHeader;
Filepath xmlHeader = T:/tmp/Jc/CRuntimeJavalike/xmlHeader;



main(){
  
  zmake ../../../Java2C.doc/CRuntimeJavalike.doc/rpy/CRuntimeJavalike.xmi := cheader2XMI(..:&inputHeader, tmpxml=xmlHeader);
  onerror{
    <+out>ERROR: <&error><.+n>
  }
}


==endJZcmd==

