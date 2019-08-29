
/// date_run_test2, as opposed to date_run_test, is for running tests through 
///  a huge loop, using gmtime() to convert the counter variable to y/m/d.

//#include <cconio>
#include <cmath>
#include <cctype>
#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
using namespace std ;
#include <cstring>
#include <climits>
#include <ctime> 
// #include <sys/types.h>
// #include <sys/stat.h> 
// #include <unistd.h> 

#include </home/robert/code_test/c_code_datetime/parseymd.cpp>
#include </home/robert/code_test/c_code_datetime/day1970.cpp>

bool compare_consecutive_days(int year1, int month1, int day1, int year2, int month2, int day2);
void gmtime_huge_loop(int start_year, int stop_year, int years_how_skip=0, int month_print=2, int day_print=28);
void test_this_date(int year, int month, int day, int verbose=1);

int main()
{
//// this test program is used in following manner:
//// multiple calls to gmtime_huge_loop() in main(), 
//// but within main, comment out all but one so output easier to digest 
gmtime_huge_loop(1960,1980);
gmtime_huge_loop(1890,2130);
gmtime_huge_loop(1959,2021,1);   /// Print Feb 28 every year, 1959-2021

gmtime_huge_loop(1994,2021,4,12,30);
gmtime_huge_loop(1958,1980,3,6,30);
}

/// verbose print will do this:
/// 1999-02-28   1999-03-01   1999-03-02         bigintval (for first day)
/// 2000-02-28   2000-02-29   2000-03-01
/// 2001-02-28   2001-03-01   2001-03-02
/// extra newline



/// gmtime_huge_loop(start_year, stop_year, years_how_skip, month_print, day_print)

/// min, max are years, so rescale
/// verbose_print=true false   years_how_skip=1,5,10
/// day_of_year_to_print   Default = feb 28
/// min=1965 min= 1970-min   * 366

/// 2 modes: run huge number of dates, no print, or print last/first date 
/// or
/// print scattered dates even when no errors

/// IF years_how_skip=0, then do not do a verbose print at all



////////////////////////////////////////////////////////////////////////////

//// return false if dates differ by one day, and no errors
//// return true if error (not consecutive days)
//// NOTE: this testing code is not for before year 1800 or after year 2200
bool compare_consecutive_days(int year1, int month1, int day1, int year2, int month2, int day2)
{
static int days_each_month[] = {31,28,31, 30,31,30, 31,31,30, 31,30,31 } ;
bool is_leap_year ;

if (year1<0 || year1>3000 || year2<0 || year2>3000) return true ;
if (month1<1 || month1>12 || month2<1 || month2>12) return true ;
if (day1<1 || day1>31 || day2<1 || day2>31) return true ;
if (month1!=2 && day1>days_each_month[month1-1]) return true ;
if (month2!=2 && day2>days_each_month[month2-1]) return true ;

if (month1==2 && day1>29) return true ;
if (month2==2 && day2>29) return true ;

if (year1!=year2)  /// special end year check
{ if (year2==year1+1 && month1==12 && month2==1 && day1==31 && day2==1) return false;
  else return true ;
}    /// rest of code: know year1 and year2 are equal.
if (month2!=month1 && month2!=month1+1) return true ;  /// do not do this too early


if (month1==2)
{ 
  if (month2!=2 && month2!=3) return true ;
  if (day1<=27)
    { if (month2==2 && day2==day1+1) return false ; else return true ; }
  if (day1>29) return true ;
  /// at this stage, know month1=2(Feb) and day1 is 28 or 29
  ///                and month2 is either Feb or March
  is_leap_year=false ;
  if (year1 % 4 == 0) is_leap_year=true ;
  if (year1==2000) is_leap_year=true ;
  if (year1==1900 || year1==1800 || year1==2100 || year1==2200) is_leap_year=false ;
  if (is_leap_year==false && day1==29) return true ;  /// error->return true 
  if (is_leap_year==true)
  { if (month1==2 && month2==2 && day1==28 && day2==29) return false ;
    if (month1==2 && month2==3 && day1==29 && day2==1) return false ;
    return true ;  /// something is wrong 
  }
  else  /// not leap year 
  { if (month1==2 && month2==3 && day1==28 && day2==1) return false ;
    else return true ;  /// something is wrong
  }
}  /// end of February section 
//// after this, know month1 is not February

if (month2==month1)
   { if (day2==day1+1) return false ;  else return true ; } 
else if (month2==month1+1)
{ if (day1==days_each_month[month1-1] && day2==1) return false; else return true;}
else return true ;
}     //// end compare_consecutive_days() 

/////////////////////////////////////////////////////////////////////////////

///  you still don't know what you want gmtime_huge_loop() to do ?
///  1: Run over huge number of years & days, printing nothing if all goes well
///  2: Printing out small number of scattered dates if all goes well

/////////////////////////////////////////////////////////////////////////////
void gmtime_huge_loop(int start_year, int stop_year, int years_how_skip, int month_print, int day_print)
{
///   HUGE LOOP WITH DAY-COUNTER: day-counter  -->  convert to seconds  -->  via gmtime(), struct tm (time structure)  --> 
///   year,month,day  -->  "yyyy-mm-dd"  -->  via parseYMD0()  -->  year,month,day 
///    -->  via num_days_since_1970()  -->  bigintval  -->  via reverse_days_since_1970()
///    -->  back to year,month,day   --> and verify it is a clean result

char char_buff[20] ;
int year1, month1, day1, year2, month2, day2, year3, month3, day3 , ticker=0 ;
bool chk1 , chk4 , first_pass=true ;
long day_ctr , min, max , bigintval , day_old, year_old, month_old ;
struct tm *tm_ptr ;
time_t second_ctr ;
min = (start_year-1970)*365 - 90 ;
max = (stop_year-1970)*365 + 90 + 365 ;
for (day_ctr=min;day_ctr<=max;++day_ctr)
{ second_ctr = day_ctr*24*60*60 ;         //// apparently, C stdlib, no leap seconds
  tm_ptr = gmtime(&second_ptr) ;
  year1=tm_ptr->tm_year+1900; month1=tm_ptr->tm_mon+1; day1=tm_ptr->tm_mday;
  sprintf(char_buff,"%04d-%02d-%02d",year1,month1,day1);

  chk1 = parseYMD0(char_buff,year2,month2,day2); 
  if (year1!=year2 || month1!=month2 || day1!=day2)
    cout << "parseYMD0 fail: " << year1 << "/" << month1 << "/" << day1 << "   " << year2 << "/" << month2 << "/" << day2 << "\n" ;

  bigintval = num_days_since_1970(year2,month2,day2) ;
  reverse_days_since_1970(bigintval,year3,month3,day3) ;

  if (bigintval != day_ctr) cout << "Day(since 1970) has two values: " << day_ctr << "   " << bigintval << "\n" ;

  if (year2!=year3 || month2!=month3 || day2!=day3)
    cout << "1970 fail: " << year2 << "/" << month2 << "/" << day2 << "   " << year3 << "/" << month3 << "/" << day3 << "\n" ;
  
  if (first_pass==false)
   { chk4 = compare_consecutive_days(year_old,month_old,day_old,year3,month3,day3) ;
     if (chk4==true) 
       cout << "NOT CONSECUTIVE: " << year_old << "-" << month_old << "-" << day_old << "    " << year3 << "-" << month3 << "-" << day3 << '\n' ;
   }
  /// use this code if doing small number of tests (print out results regardless)
  if ( years_how_skip>0    && (year3 % years_how_skip == 0) && 
       month3==month_print &&  day3==day_print ) 
     ticker=3 ;
  if (ticker>=1)
  { cout << year3 << "-" << month3 << "-" << day3 <<  "    " ;
    ticker--;
    if (ticker==0) cout << "\n" ;
  }     /// end section using ticker 
  first_pass = false ; year_old=year3 ; month_old=month3; day_old=day3 ;
}     /// end main for loop 
}     /// end gmtime_huge_loop() 


