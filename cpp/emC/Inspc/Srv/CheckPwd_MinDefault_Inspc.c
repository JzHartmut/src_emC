#include <emC/Inspc/Srv/CheckPwd_Inspc.h>




int const accessRights[][3] =
{ { 0,  0, 0 }  //0
, { 11, 1, 0 }  //1
, { 22, 2, 0 }  //2
, { 33, 3, 0 }  //3
, { 44, 4, 0 }  //4
, { 111, 1, 1 }  //5
, { 221, 2, 1 }  //6
, { 331, 3, 1 }  //7
, { 441, 4, 1 }  //8
, { 222, 2, 2 }  //9
, { 332, 3, 2 }  //10
, { 442, 4, 2 }  //11
, { 333, 3, 3 }  //12
, { 443, 4, 3 }  //13
, { 444, 4, 4 }  //14
};


int check_CheckPwd_Inspc(MemC telg, int32 pwd) {
  int ix = 0;
  for( ix = 0; ix < ARRAYLEN_emC(accessRights); ++ix){
    if(pwd == accessRights[ix][0]) {
      break;  //found.
    }
  }
  if(ix < ARRAYLEN_emC(accessRights)){ return (accessRights[ix][1] << kBitAccessLevel_CheckPwd_Inspc) + ((accessRights[ix][2]<<kBitChangeLevel_CheckPwd_Inspc)); }
  else return 0;  //standard rights.
  //else return 0;  
}

int XXXcheck_CheckPwd_Inspc(MemC telg, int32 pwd) {
  int pwdChg = -1;
  if (pwd > 44) return 0;  //faulty
  while (pwd >= 0) {
    pwd -= 10;
    pwdChg += 1;
  }
  int pwdAcc = pwd + 10;  //last subtract was too much.
  if (pwdAcc >4) return 0;
  return pwdChg << kBitChangeLevel_CheckPwd_Inspc | pwdAcc << kBitAccessLevel_CheckPwd_Inspc;
  //if(pwd >=0 && pwd <= 14){ return accessRights[pwd][0] + (accessRights[pwd][1]<<4); }
  //else return 0;  
}


