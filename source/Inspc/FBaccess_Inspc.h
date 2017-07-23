#ifndef __FBaccess_Inspc_h__
#define __FBaccess_Inspc_h__
#include <applstdefJc.h>
#include <Inspc/DataNode_Inspc.h>
struct DataNode_Inspc_t;
struct FBaccess_Inspc_t;
struct ObjectJc_t;
struct ClassJc_t;

typedef struct DataNode_Inspc_t* P_FBaccessNode_Inspc;

//Compatibility to older sources, it is a renaminig:
#define FBaccessNode_Inspc_t DataNode_Inspc_t
#define FBaccessNode_Inspc DataNode_Inspc


typedef struct FBaccess_Inspc_t* P_FBaccess_Inspc;


//extern_C const struct ClassJc_t reflection_FBaccessNode_Inspc;




/**Allocates memory for one node of a instance tree. 
 * 
 * @param thizp The initialized instance will be returned here. Reference to output variable
 * @param nrofObjects size of the array which stores references to other nodes or user instances
 */
void alloc_FBaccessNode_Inspc(struct DataNode_Inspc_t** thizp, int nrofObjects);

#define ctor_FBaccessNode_Inspc(OTHIZ, NR) ctor_DataNode_Inspc(OTHIZ, NR)


void free_FBaccessNode_Inspc(struct DataNode_Inspc_t* thiz);

//void registerReflection_FBaccessNode_Inspc(struct DataNode_Inspc_t* thiz, struct ObjectJc_t* obj);



#define ptr_FBaccessNode_Inspc(THIZ, THIZP) { *(THIZP) = THIZ; } 
//void ptr_FBaccess_Inspc(struct FBaccess_Inspc_t* thiz);


/**Allocates memory for one node of a the reflection access service. 
 * 
 * @param thizp The initialized instance will be returned here. Reference to output variable
 * @param nrofObjects size of the array which stores references. Size of the root.
 */
void alloc_FBaccess_Inspc(struct FBaccess_Inspc_t** thizp, int nrofObjects, const char* sIp);

void alloc_FBaccess_Inspc_vorlaeufig_in_Simulink(struct FBaccess_Inspc_t** thizp, int nrofObjects);

/**Allocates memory for one node of a the reflection access service but with a abbreviated root node for the inspector.
 * In this case the data structure should manage that the rootNode of this structure is visible. 
 * 
 * @param thizp The initialized instance will be returned here. Reference to output variable
 * @param nrofObjects size of the array which stores references. Size of the root.
 * @param rootInspc The root node for the inspector. If null is given, the internal rootNode will be used as root.
 *   That is the same behavior as calling [[alloc_FBaccess_Inspc(...)]]
 */
void allocSetRoot_FBaccess_Inspc(struct FBaccess_Inspc_t** thizp, int nrofObjects, struct DataNode_Inspc_t* rootInspc, const char* sIp);

/**Constructs and starts the Inspector service for Function Block access with allocated memory from thizo. 
 * @param rootNode The root node for all FB access. Should be given and intialized.
 * @param rootInspc The root struct for all access. It can be the same as rootNode, it can be another struct. Should be given and initialized. 
 */
struct FBaccess_Inspc_t* ctor_FBaccess_Inspc(struct ObjectJc_t* thizo, struct DataNode_Inspc_t* rootNode, struct ObjectJc_t* rootInspc, const char* sIp);

void free_FBaccess_Inspc(struct FBaccess_Inspc_t* thiz);

/**Returns the reference to the root node from the Inspc service. */
void ptrRootNode_FBaccess_Inspc(struct FBaccess_Inspc_t* thiz, struct DataNode_Inspc_t** p_node);

/**Set the simulation time in the main structure. */
void setTime_FBaccess_Inspc(struct FBaccess_Inspc_t* thiz, double seconds);




#endif //__FBaccess_Inspc_h__
