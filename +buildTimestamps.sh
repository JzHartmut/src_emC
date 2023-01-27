echo build the timestamp in .filelist from all files:
Filemask="[**/[~#*|~*#]|~_*]"
currdir="$(dirname $0)"
if test -f $currdir/../../tools/vishiaBase.jar; then 
  java -cp $currdir/../../tools/vishiaBase.jar org.vishia.util.FileList L -l:$currdir/.filelist -d:$currdir "-m:$Filemask"
else  
  ~/cmds/javavishia.sh org.vishia.util.FileList L -l:$currdir.filelist -d:$currdir "-m:$Filemask"
fi

