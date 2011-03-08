#include "TestFileJc.h"

#include <Jc/FileIoJc.h>

void test1()
{

  FileJc_s file = {0};
  
  FileOutputStreamJc_s out = {0};
  STACKTRC_ENTRY("test1");

  init_ObjectJc(&file.base.object, sizeof(file),0);
  init_ObjectJc(&out.base.object, sizeof(out),0);

  ctorO_FileJc(&file.base.object, z_StringJc("test.txt"), _thCxt);
  ctorO_fB_FileOutputStreamJc(&out.base.object, &file, false, _thCxt);

  /**write the own data. */
  write_FileOutputStreamJc(&out, &out, 0, sizeof(out), _thCxt);

  flush_FileOutputStreamJc(&out, _thCxt);
  close_FileOutputStreamJc_F(&out, _thCxt);
  STACKTRC_LEAVE;
}