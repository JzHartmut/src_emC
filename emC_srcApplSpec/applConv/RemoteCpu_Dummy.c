/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this source the LGPL Lesser General Public License,
 * published by the Free Software Foundation is valid.
 * It means:
 * 1) You can use this source without any restriction for any desired purpose.
 * 2) You can redistribute copies of this source to everybody.
 * 3) Every user of this source, also the user of redistribute copies
 *    with or without payment, must accept this license for further using.
 * 4) But the LPGL ist not appropriate for a whole software product,
 *    if this source is only a part of them. It means, the user
 *    must publish this part of source,
 *    but don't need to publish the whole source of the own product.
 * 5) You can study and modify (improve) this source
 *    for own using or for redistribution, but you have to license the
 *    modified sources likewise under this LGPL Lesser General Public License.
 *    You mustn't delete this Copyright/Copyleft inscription in this source file.
 *
 * This source may be used also with another licence, if the author 
 * and all other here named co-authors have agreed to this contract.
 * Especially a company can use a copy of this sources in its products without publishing.
 * The user should have a underwritten contract therefore.
 *
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content empty routines for a remote access to another memory area.
 *          This source should be linked only if no other remote access is intended.
 *          A remote access is to be programmed in a hardware specific way.
 * @version 0.92
 * list of changes:
 * 2010-01-23: Hartmut created, because a remote access was built in in the ReflectionJc.c for a special application.
 *
 ****************************************************************************/
#include <emC/InspcTargetSimple/IfcTargetProxy_Inspc.h>
#include <applstdef_emC.h>


/**Gets any info from a remoteCPU, which has max. 4 byte return value. 
 * @param cmd the action to do.
 * @param device the remote device (it comes from a segment number in MemSegmentJc).
 * @param A address in the memory area in remote device. 
 *        The address is returned sometimes from other calls of this method and it is never changed.
 * @param input some additional parameter depends on cmd.
 */
#ifndef __INSPC_REMOTE_ACCESS___
int32 accessTarget_Inspc(Cmd_InspcTargetProxy_e cmd, int device, RemoteAddress_Inspc_emC address, int32 input)
{
 return 0;
}
#endif //#ifndef __INSPC_REMOTE_ACCESS___



/**Gets any info from a remoteCPU, which has max. 8 byte return value. */
#ifndef __INSPC_REMOTE_ACCESS___
int64 accessTarget64_Inspc(Cmd_InspcTargetProxy_e cmd, int device, RemoteAddress_Inspc_emC address, int64 input)
{
	return 0;
}	
#endif //#ifndef __INSPC_REMOTE_ACCESS___



