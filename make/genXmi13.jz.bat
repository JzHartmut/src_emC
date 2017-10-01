jztxtcmd %0
exit /B



==JZtxtcmd==

##!checkJZcmd=<:><:scriptdir>/result/CHECK_<&scriptfile>.zgen<.>;

include $ZBNFJAX_HOME/zmake/Cheader2Xmi.jzcmd;

currdir=scriptdir;


Fileset inputHeader =
( 
  source/Fwc/*.h
, source/Jc/*.h
, source/BlockHeap/*.h
, source/OSAL/*.h
);


Filepath xmlHeader1 = D:/vishia.tmp/Jc/CRuntimeJavalike/xmlHeader;
Filepath xmlHeader = T:/tmp/Jc/CRuntimeJavalike/xmlHeader;



main(){
  
  ##zmake ../../../Java2C.doc/CRuntimeJavalike.doc/rpy/CRuntimeJavalike.xmi := cheader2XMI(..:&inputHeader, tmpxml=xmlHeader);
  zmake ../../../Jc/rpy/CRJ.xmi := cheader2XMI(..:&inputHeader, tmpxml=xmlHeader);
  onerror{
    <+out>ERROR: <&error><.+n>
  }
}


==endJZcmd==

