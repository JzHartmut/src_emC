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
 * @content java-like java/util/Locale.
 *
 * @author Hartmut Schorrig
 * @version 0.92
 * list of changes:
 * 2010-08-18: Hartmut creation
 *
 ****************************************************************************/
#ifndef __LocaleJc_h__
#define __LocaleJc_h__

#include <Jc/ObjectJc.h>

/*@CLASS_C LocaleJc @@@@@@@@@@@@@@@@@@@@@@@@*/

/**This struct represents an interface adequat to ,,java.lang.Runnable,,. 
 * It contains only a struct ObjectJc, it is to use in a ,,union{...},, commonly with the ,,ObjectJc,,-base of any struct.
 */
typedef struct LocaleJc_t
{ 
  union { ObjectJc object; } base; 
  const char* language;
  const char* country;
} LocaleJc_s;

extern_C const struct ClassJc_t reflection_LocaleJc;


/* Enhanced references *********************************************************/
#ifndef LocaleJcREFDEF
  #define LocaleJcREFDEF
  typedef TYPE_EnhancedRefJc(LocaleJc);
  //Should be compatible with non-enhanced ref using. typedef struct LocaleJcREF_t { ObjectRefValuesJc refbase; struct LocaleJc_t* ref; } LocaleJcREF;
#endif


#define CONST_LocaleJc(OBJP, language, country, variant) { { CONST_ObjectJc(sizeof(LocaleJc_s), OBJP, &reflection_LocaleJc) }, language, country};


/**Commonly localization information, neutral.
 */
extern LocaleJc_s ROOT_LocaleJc;


#endif  //__LocaleJc_h__
