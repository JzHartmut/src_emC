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
 * list of changes:
 * 2006-05-00: www.vishia.de creation
 *
 ****************************************************************************/

#ifndef __DateJc_h__
#define __DateJc_h__
#include "Jc/StringJc.h"
#include "os_time.h"

struct TextFieldPositionJc_t;
struct TimeZoneJc_t;


/*@CLASS_C DateValuesJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This struct contains the core data of a timestamp. It is contained in DateJc_s.
 */
typedef struct DataValueJc
{

  /** Nanoseconds, the resolution depends on the hardware.
    * It is possible to count realy in milliseconds step if the system not supports a finer resolution.
    * The nanoseconds should be in canonical form, it means less than 999999999.
  */
  int32 time_nsec;

  /**Nur die folgenden Bits in nanoseconds werden als Nanosekunden verwendet. */
  #define mNanoSeconds_DateValueJc 0x3FFFFFFF

  /**Wenn in seconds die Schaltsekunden mitgezählt sind (also keine lineare Abbildung 3600*24 Sekunden pro Tag),
   * dann soll das folgenden Bit gesezt sein:
   */
  #define mLeapSeconds_DateValueJc 0x80000000


  /** Seconds after January, 1. 1970 */
  int32 time_sec;

}DateValuesJc;


/**Sets the timestamp to invalid.
 */
#define setInvalid_DateValuesJc(THIS) { (THIS)->nanoSeconds = -1; (THIS)->seconds = -1; }


/*@CLASS_C DateJc_s @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/** This class holds a absolute time with nanoseconds resolution.
  */
typedef struct DateJc_t
{ /** it based on Object, accessable from Reflection.*/
  union{ ObjectJc object; } base;

  /**The reference of the core values of timestamp may be contented everywhere.*/
  OS_TimeStamp val;

  /** This string is filled on toString-Operation. Not otherwise used.
    */
  //StringJc sTime__;

  /** Buffer, because the timestring should be saved localy Thread-safe.*/
  //char timeString__[32];
}DateJc_s;

/**sizeof-definition necessary for allocation, which may be done without knowledge of the struct for a private struct. */
#define sizeof_DateJc_s sizeof(DateJc_s)

/**This macro defines a C-constant (with {..}) for initializing a StringBuffer instance with its static size.
 * @param OBJP Pointer to the instance itself. It is used to store the OWNADDRESS for the ObjectJc-part.
 */
#define CONST_DateJc(OBJP) { CONST_ObjectJc(sizeof(DateJc), &(OBJP)->object, null), 0, sizeof(DateJc), 0 }

/**Finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_DateJc_F(ObjectJc* othis, ThCxt* _thCxt);


  /**Constructs an instance with given time.*/
  METHOD_C DateJc_s* ctor_Date_iJc(DateJc_s* ythis, int64 time);

  /**Constructs an instance with the system time.*/
  METHOD_C DateJc_s* ctor_DateJc(DateJc_s* ythis);

  METHOD_C DateJc_s* ctorO_DateJc(ObjectJc* othis, ThCxt* _thCxt);

  METHOD_C DateJc_s* ctorO_I_DateJc(ObjectJc* othis, int64 milliSecAfter1970, ThCxt* _thCxt);

  /**Constructs an instance with reference to timestamp values. */
  METHOD_C DateJc_s* ctor_Date_zJc(DateJc_s* ythis, DateValuesJc* val);

  /**Constructs an instance with given seconds and nanoseconds.
   * @param nanoseconds The bit mLeapSeconds_DateValueJc may be setted in nanoseconds
   */
  METHOD_C DateJc_s* ctor_Date_iiJc(DateJc_s* ythis, int32 seconds, uint32 nanoseconds);


  /**new-operator C or C++-like */
  //#define new_DateJc() ctor_DateJc((DateJc_s*)malloc(sizeof(DateJc_s)))


  /** Returns the number of milliseconds sinde January 1, 1970, 00:00 GMT. This method is java-compatible.*/
  #define getTime_DateJc(THIS) (int64)( 1000*((int64)((THIS)->val.time_sec)) + ((THIS)->val.time_nsec)/1000000)

  /** gets the seconds after 1970. This method is enhanced from standard java.*/
  #define getSeconds_DateJc(THIS) ((THIS)->val.time_sec)

  /** gets the nanoSeconds inside a second. This method is enhanced from standard java.*/
  #define getNanoSeconds_DateJc(THIS) ((THIS)->val.time_nsec)

  /** Returns > 0 if after, = 0 if equal, < 0 if before this. Javalike.*/
  METHOD_C int compareTo_DateJc(DateJc_s* ythis, DateJc_s* when);

  /** Javalike: true if when is after this.*/
  #define after_DateJc(THIS, when) ( compareTo_DateJc(THIS, when) > 0 )

  /** Javalike: true if when is before this.*/
  #define before_DateJc(THIS, when) ( compareTo_DateJc(THIS, when) < 0 )

  /** Javalike: true if when is before this.*/
  #define equals_DateJc(THIS, when) ( compareTo_DateJc(THIS, when) == 0 )

  /** Sets the system time in the moment of calling to the Date object.
    * This method is Java-enhanced. In Java only the constructor sets the system time into.
    * In C it is necessarry to use not a new object but a static allocated object instead.
    * The realization of this method is platform-depended.
    */
  METHOD_C void setSystemTime_DateJc(DateJc_s* ythis);


  /** Java-compatible method to set the time. @see setTimeNanoseconds_DateJc */
  METHOD_C void setTime_DateJc(DateJc_s* ythis, int64 milliseconds);

  /** Sets a time, may be kept by hardware.*/
  METHOD_C void setTimeNanoseconds_DateJc(DateJc_s* ythis, int32 seconds, int32 nanoSeconds);

/**Converts a simple date to milliseconds since 1970.
* 
* @javalike: [[[[sunJavadoc/java/util/Date#UTC(int, int, int, int, int, int)]]:
*   In java, this method is depreaceted, because it doesn't regard timezones etc. 
*   But for a simple conversion, it is need, in Java too!
*/
METHOD_C int64 UTC_DateJc(int year, int month, int day, int hour, int minut, int second);

  /** Returns the date and time in form "dow mon dd hh:mm:ss zzz yyyy".*/
  METHOD_C StringJc toString_DateJc(DateJc_s* ythis);

  /**This method convers the timestamp to a readable format. It is enhanced respectively java.lang.Date, to simplify using.
   * In Java this function is provided using a SimpleDateFormat(format) object calling String sDate = object.format(dateObject).
   * The format characters are the same as java.text.SimpleDateFormat, but not all from there:
   * * yyyy Year with 4 digits like 1970 or 2007
   * * yy   Year with 2 digits like 70 or 07
   * * MMMM   Month in english full word like January, July, December
   * * MMM    Month in english short word like Jan, Jul, Dec
   * * M, MM  Month with 2 digits like 01, 07, 12
   * * D..DDD Day in the year from 1 o 366 using at least the number of D letters as digits, leading 0.
   * * d..dd  Day in the month from 1 o 31 using at least the number of D letters as digits, leading 0.
   * * F      Day of week from 1 o 7.
   * * EEEE   Day in Week
   * * EEE    Day in Week Mon, Tue
   * * a      Am/pm marker
   * * HH     Hour in Day 0..23
   * * kk     Hour in Day 1..24
   * * hh      Hour in am/pm 0..11
   * * kk      Hour in am/pm 1..12
   * * mm     Minute in hour
   * * ss     Second in minute
   * * SS     10 Millisecond in second.
   * * SSS    Millisecond in second.

   *
   * @param format String to determine the positions of the parts of readable date.
   * @param timeZoneAdjustHours Anzahl der Stunden für die Zeitzonenverschiebung.
                                Es wird davon ausgegangen, dass intern nach Greenwich Mean Time gespeichert ist.
                Die Angabe von 1 bedeutet eine Verschiebung in Richtung MEZ (Winter).
   * @param mBuffer a memory location to write the information in. If it is a null, a memory location in heap is created inside.
   *                The formatted String representation of the Date will be store there. 
   *                The content of the MemC-location is not changed at start of operation, only the generated chars are setted.
   *                Therefore it is possible to write inside a part of a StringBuffer.
   *                This memory location is returned as referenced string in the returned StringJc-Object. 
   *                It is also possible to use a char[xx]-area to write and get the result by supplying its reference and length in mBuffer.
   *                The return-StringJc may be overlooked in that case. 
   * @return the String represantation of the result.
   */
  METHOD_C StringJc toStringFormat_DateJc(DateJc_s* ythis, StringJc const format, int timeZoneAdjustHours, MemC mBuffer );



/*@CLASS_C SimpleDateFormatJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This class helps to convert OS_TimeStamp in a readable text form.
 */
typedef struct SimpleDateFormatJc_t
{ union{ ObjectJc object;} base;
  /**The format string. */
  StringJc sFormat;
  int32 timeZoneAdjustHours;
}SimpleDateFormatJc_s;

/**sizeof-definition necessary for allocation, which may be done without knowledge of the struct for a private struct. */
#define sizeof_SimpleDateFormatJc_s sizeof(SimpleDateFormatJc_s)

#define DATE_FIELD_SimpleDateFormatJc 3

METHOD_C SimpleDateFormatJc_s* ctorO_SimpleDateFormatJc(ObjectJc* othis, ThCxt* _thCxt);

METHOD_C SimpleDateFormatJc_s* ctorO_s_SimpleDateFormatJc(ObjectJc* othis, StringJc sFormat, ThCxt* _thCxt);

METHOD_C void setTimeZone_SimpleDateFormatJc(SimpleDateFormatJc_s* ythis, struct TimeZoneJc_t* timeZone, ThCxt* _thCxt);

METHOD_C void applyPattern_SimpleDateFormatJc(SimpleDateFormatJc_s* ythis, StringJc pattern, ThCxt* _thCxt);

METHOD_C StringJc format_SimpleDateFormatJc(SimpleDateFormatJc_s* ythis, OS_TimeStamp timeStamp, ThCxt* _thCxt);

METHOD_C void format_u_SimpleDateFormatJc(SimpleDateFormatJc_s* ythis, DateJc_s* timeStamp, StringBuilderJc* sBuffer, struct TextFieldPositionJc_t* field, ThCxt* _thCxt);

METHOD_C void format_tu_SimpleDateFormatJc(SimpleDateFormatJc_s* ythis, OS_TimeStamp timeStamp, StringBuilderJc* sBuffer, struct TextFieldPositionJc_t* field, ThCxt* _thCxt);



/*@CLASS_C TextFieldPositionJc_s @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This class is a dummy to emulate java.txt.FieldPosition.
 */
typedef struct TextFieldPositionJc_t
{ union { ObjectJc object;} base;
  
  int x;
}TextFieldPositionJc_s;

/**sizeof-definition necessary for allocation, which may be done without knowledge of the struct for a private struct. */
#define sizeof_TextFieldPositionJc_s sizeof(TextFieldPositionJc_s)


METHOD_C TextFieldPositionJc_s* ctorO_TextFieldPositionJc(ObjectJc* othis, int field, ThCxt* _thCxt);


#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)

class DateJcpp: public DateJc_s
{
  public: DateJcpp(){ STACKTRC_ENTRY("DateJcpp::DateJcpp"); init_ObjectJc(&this->base.object, sizeof(DateJc_s), 0); ctorO_DateJc(&this->base.object, _thCxt); }
};


class SimpleDateFormatJcpp: public SimpleDateFormatJc_s
{
  public: SimpleDateFormatJcpp(StringJcpp sFormat)
  { STACKTRC_ENTRY("SimpleDateFormatJcpp::SimpleDateFormatJcpp"); 
    init_ObjectJc(&this->base.object, sizeof(SimpleDateFormatJcpp), 0); 
    ctorO_s_SimpleDateFormatJc(&this->base.object, sFormat, _thCxt); 
  }

  public: StringJc format(DateJc_s const* date){ return format_SimpleDateFormatJc(this, date->val, null); }

};

#endif //__CPLUSPLUSJcpp

#endif  //__DateJc_h__
