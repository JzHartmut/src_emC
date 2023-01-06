/*Alignment in Daten auf Byte-Grenze setzen, compilerspezifisch
  Dieser File sollte includiert werden, damit dies Problem zielsystemunabhaengig 
  geloest ist, die pragmas sind zielsystemabhaengig (compilerabhaengig)
  made by Hartmut Schorrig, 2001.1011
*/
#pragma warning(disable:4103)  //Verwendet #pragma pack zur Aenderung der Ausrichtung 
#pragma pack(1)

