#ifndef __Inspc__CheckPwd_Inspc_h__
#define __Inspc__CheckPwd_Inspc_h__
#include <applstdef_emC.h>


/**Returns The access levels for the given password. 
 * The pwd may/should depend on the whole telegram content. It shold be encrypted, to prevent shown as is.
 * Therefore the whole telegram content is given to check.
 * 
 * The return value contains the resulting access level 0..4
 * * in bit 7..3 for change
 * * in bit 3..0 for access
 * The levels are:
 * * 0 no access or common access for everyone, never change anything.
 * * 1 access for the customer to detect state or change customer parameter.
 * * 2 access for the maintenance of the customer.
 * * 3 access for maintenance of service, only with special know how
 * * 4 developer access to all.
 * It is possible to have developer access to all, but not for change. 
 * In the combination of all there are 15 different passwords.
 * Because the passwords should be a combination of public key for access and private key inside the target,
 * more password combinations are possible.
 */
int check_CheckPwd_Inspc(MemC telg, int32 pwd);

#define mAccessLevel_CheckPwd_Inspc 0xf0
#define kBitAccessLevel_CheckPwd_Inspc 4

#define mChangeLevel_CheckPwd_Inspc 0x0f
#define kBitChangeLevel_CheckPwd_Inspc 0

#define kFreeAccess_CheckPwd_Inspc 0
#define kCustomerAccess_CheckPwd_Inspc 1
#define kCustMaintAccess_CheckPwd_Inspc 2
#define kMaint_CheckPwd_Inspc 3
#define kDevlpAccess_CheckPwd_Inspc 4

#define kReadOnly_CheckPwd 0
#define kCustomerChange_CheckPwd 1
#define kCustomerMainChange_CheckPwd 2
#define kMaintChange_CheckPwd 3
#define kDevlpChange_CheckPwd 4
#define kNeverChange_CheckPwd 7


#endif   //__Inspc__CheckPwd_Inspc_h__
