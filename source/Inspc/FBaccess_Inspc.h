#ifndef __FBaccess_Inspc_h__
#define __FBaccess_Inspc_h__

struct FBaccessNode_Inspc_t;
struct FBaccess_Inspc_t;
struct ObjectJc_t;

typedef struct FBaccessNode_Inspc_t* P_FBaccessNode_Inspc;
typedef struct FBaccess_Inspc_t* P_FBaccess_Inspc;

/**Allocates memory for one node of a instance tree. 
 * 
 * @param thizp The initialized instance will be returned here. Reference to output variable
 * @param nrofObjects size of the array which stores references to other nodes or user instances
 */
void alloc_FBaccessNode_Inspc(struct FBaccess_InspcNode_t** thizp, int nrofObjects);

struct FBaccessNode_Inspc_t* ctor_FBaccessNode_Inspc(struct ObjectJc_t* thizo, int nrofObjects);


void free_FBaccessNode_Inspc(struct FBaccess_Inspc_t* thiz);

void registerReflection_FBaccessNode_Inspc(struct FBaccessNode_Inspc_t* thiz, struct ObjectJc_t* obj);

void registerRefl_FBaccessNode_Inspc(struct FBaccessNode_Inspc_t* thiz, void* obj, char const* name, struct ClassJc_t const* refl);


#define ptr_FBaccessNode_Inspc(THIZ, THIZP) { *(THIZP) = THIZ; } 
//void ptr_FBaccess_Inspc(struct FBaccess_Inspc_t* thiz);


/**Allocates memory for one node of a the reflection access service. 
 * 
 * @param thizp The initialized instance will be returned here. Reference to output variable
 * @param nrofObjects size of the array which stores references. Size of the root.
 */
void alloc_FBaccess_Inspc(struct FBaccess_Inspc_t** thizp, int nrofObjects);

/**Allocates memory for one node of a the reflection access service but with a abbreviated root node for the inspector.
 * In this case the data structure should manage that the rootNode of this structure is visible. 
 * 
 * @param thizp The initialized instance will be returned here. Reference to output variable
 * @param nrofObjects size of the array which stores references. Size of the root.
 * @param rootInspc The root node for the inspector. If null is given, the internal rootNode will be used as root.
 *   That is the same behavior as calling [[alloc_FBaccess_Inspc(...)]]
 */
void allocSetRoot_FBaccess_Inspc(struct FBaccess_Inspc_t** thizp, int nrofObjects, struct ObjectJc_t* rootInspc);

struct FBaccess_Inspc_t* ctor_FBaccess_Inspc(struct ObjectJc_t* thizo, struct FBaccessNode_Inspc_t* rootNode, struct ObjectJc_t* rootInspc);

void free_FBaccess_Inspc(struct FBaccess_Inspc_t* thiz);

//#define ptrNode_FBaccess_Inspc(THIZ, NODEP) { *(NODEP) = &((THIZ)->data); } 
void ptrNode_FBaccess_Inspc(struct FBaccess_Inspc_t* thiz, struct FBaccessNode_Inspc_t** p_node);
//void ptr_FBaccess_Inspc(struct FBaccess_Inspc_t* thiz);



#endif //__FBaccess_Inspc_h__
