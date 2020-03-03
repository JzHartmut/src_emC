#include <applstdef_emC.h>
#include <emC/Base/ParseArgs_emC.h>
//#include <emC/SimpleC_emC.h>
#include <emC/Base/String_emC.h>
#include <stdio.h>




void printhelp_ParseArgs ( Ctrl_ParseArgs const ctrl[], int zCtrl ) {
  printf("%s\n", ctrl[0].help);
  printf("  --help - outputs this help text\n");
  printf("  ---anyArg - ignored arg\n");
  for (int ixCheck = 1; ixCheck < zCtrl; ++ixCheck) {
    Ctrl_ParseArgs const* argCheck = &ctrl[ixCheck];
    printf("  %s%s\n", argCheck->option, argCheck->help);
  }
}


void eval_ParseArgs ( Ctrl_ParseArgs const ctrl[], int zCtrl, char const* const* argsCmd, int nArgs) {
  CharArray20 const* args = (CharArray20 const*) argsCmd;             //Defined array, the same functionality.
  if (nArgs <= 1) {
    printhelp_ParseArgs(ctrl, zCtrl);
  }
  for (int ix = 1; ix < nArgs; ++ix) {
    bool bFound = false;
    if (strncmp(args->args[ix], "--help", 6) == 0) {
      bFound = true;
      printhelp_ParseArgs(ctrl, zCtrl);
    }
    else if(strncmp(args->args[ix], "---", 3) == 0) {
      bFound = true; //ignore cmd
    } else {
      for (int ixCheck = 0; ixCheck < zCtrl; ++ixCheck) {
        Ctrl_ParseArgs const* argCheck = &ctrl[ixCheck];
        int zArg = strnlen_emC(argCheck->option, 20);
        if (strncmp(args->args[ix], argCheck->option, zArg) == 0) {
          //arg found:
          bFound = true;
          if (argCheck->dst != null) {
            *argCheck->dst = args->args[ix] + zArg;
          }
          break;
        }
      }//for check
    }
    if (!bFound) {
      printf("unknown arg: %s\n", args->args[ix]);
    }
  }
}



