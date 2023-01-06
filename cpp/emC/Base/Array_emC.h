#ifndef HGUARD_emC_Base_Array_emC
#define HGUARD_emC_Base_Array_emC
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
* @content Definition of array access routines. 
*
* @author Hartmut Schorrig
* @version 2.0
* 2020-05-16: Hartmut creation 
*
************************************************************************************************/




#ifndef NO_PARSE_ZbnfCheader  //template definition missing yet.
#ifdef __cplusplus

/**class definition which wrapps a simple 1-dimensional array with fix length. 
 * @arg T any type of the array elements, may be a simple type, or a complex or pointer type
 * @arg n a constant (literal) value of size. 
 */
template<typename T, int n>
class Array_emC {
  T array[n+1];

  /**The access operator for read and write returns the address.
   * @hrows ArraxIndexOutOfBoundsExeption on faulty index. 
   * For working without exception handling on faulty index an additional dummy element will be accessed.
   */
  public: T& operator[](uint ix) { 
    if(ix < n) return array[ix];
    else {
      THROW_s0n(ArrayIndexOutOfBoundsException, "", ix, n);
      return array[n];
  } }

  /**The access operator for read and write returns the address.
   * It should be only used if the index is secure by static code analyzes 
   */
  public: T& uncheckedAccess(uint ix) { return this->array[ix]; }
};

/**Macro able to use in C or C++ for the same approach. 
 * @arg TYPE any type of an array element, simple, struct or pointer
 * @arg SIZE integer literal for a fix size
 * @arg NAME name of the array. 
 */
#define ARRAY_emC(TYPE, SIZE, NAME) Array_emC<TYPE, SIZE> NAME 

#define UNCHECKED_ACCESS_Array_emC(ARRAY, IX) (ARRAY).uncheckedAccess(IX)


/**class definition which wrapps a pointer to a simple 1-dimensional array with variable length. 
 * @arg T any type of the array elements, may be a simple type, or a complex or pointer type
 */
template<typename T>
class ArrayVarsize_emC {
  STRUCT_AddrVal_emC(arrayVarSize_emC, T); 
  
  /**Constructor with given pointer to an array and its real size.
   */
  public: ArrayVarsize_emC(T* array, int size) { 
    this->arrayVarSize_emC.addr = array; 
    arrayVarSize_emC.val = size; 
  }

 /**The access operator for read and write returns the address.
  * @hrows ArraxIndexOutOfBoundsExeption on faulty index. 
  * For working without exception handling on faulty index the last element will be accessed.
  */
  public: T& operator[](uint ix) { 
    if(ix < (uint)arrayVarSize_emC.val) return arrayVarSize_emC.addr[ix];
    else {
      THROW_s0n(ArrayIndexOutOfBoundsException, "", ix, arrayVarSize_emC.val);
      return arrayVarSize_emC.addr[arrayVarSize_emC.val-1];
  } }

  /**The access operator for read and write returns the address.
   * It should be only used if the index is secure by static code analyzes 
   */
  public: T& uncheckedAccess(uint ix) { return arrayVarSize_emC.addr[ix]; }
};


/**Macro able to use in C or C++ for the same approach. 
 * @arg TYPE any type of an array element, simple, struct or pointer
 * @arg NAME name of the array. 
 * @arg REF pointer to the array, often allocated in heap. 
 * @arg SIZE of the array (number of elements) proper to data range.
 */
#define ARRAYVAR_emC(TYPE, NAME, REF, SIZE) ArrayVarsize_emC<TYPE> NAME = ArrayVarsize_emC<TYPE>(REF, SIZE) 




#else //__cplusplus

//Simple variant unchecked for C approach in well tested environments
#define ARRAY_emC(TYPE, SIZE, NAME) TYPE NAME[SIZE] 




#endif //__cplusplus
#endif//NO_PARSE_ZbnfCheader




#endif //HGUARD_emC_Base_Array_emC
