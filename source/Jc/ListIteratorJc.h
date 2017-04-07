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
 * @content
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 *
 * @version 0.83
 *
 * @content Implementation of a LinkedList like java.util.LinkedList.
 *
 * @author JcHartmut www.vishia.org
 * @version 0.83
 * list of changes:
 * 2007-05-00: JcHartmut creation
 *
 ****************************************************************************/
#ifndef __ListIteratorJc_h__
#define __ListIteratorJc_h__



#if defined(__CPLUSPLUS_Jcpp) && defined(__cplusplus)
class IteratorJcpp: public ObjectifcBaseJcpp
{
  public: virtual bool hasNext()=0;
  public: virtual ObjectJc* next()=0;
  public: virtual void remove()=0;
  public: virtual operator IteratorJc*()=0;

};

/**The reflection information is supplied in a global variable, setted in code.*/
//extern const Class_Jc* REFLECTION_IteratorJc;



class  ListIteratorJcpp: public IteratorJcpp
{ public: virtual bool hasPrevious()=0;
  public: virtual ObjectJc* previous()=0;
  public: virtual int nextIndex()=0;
  public: virtual int previousIndex()=0;
  public: virtual void set(ObjectJc obj)=0;
  public: virtual void add(ObjectJc obj)=0;
};
/**The reflection information is supplied in a global variable, setted in code.*/
//extern const Class_Jc* REFLECTION_IteratorJc;


#else
//C-Variante
#endif  //__CPLUSPLUS_Jcpp

#endif //__ListIteratorJc_h__
