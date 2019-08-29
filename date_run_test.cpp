
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

void run_tests_in_big_loop();
void test_this_date(int year, int month, int day, int verbose=1);

int main()
{
test_this_date(1969,12,31);
test_this_date(1970,1,1);
test_this_date(1970,1,31);
test_this_date(1970,2,1);
test_this_date(2017,11,12);
test_this_date(1900,2,28);
test_this_date(1900,3,1);
test_this_date(1980,2,29);
test_this_date(1980,3,1);
test_this_date(2000,2,29);
test_this_date(2000,3,1);

cout << "\n" ;
test_this_date(1900,2,29);
test_this_date(1999,2,29);
test_this_date(2017,11,31);
}

//////////////////////////////////////////////////////////////////////////


///  DO THE TEST RUNS FOR DATES HERE, IN A SEPARATE FILE.

void run_tests_in_big_loop()
{
int year , month, day , adjust ;
bool is_leap_year ;
static int days_each_month[] = {31,28,31, 30,31,30, 31,31,30, 31,30,31 } ;
/// HERE, you have two choices, run a big loop, and go through a lot of years, or just 
///   pick say 10 examples to start off with.
for (year=1960;year<=1980;year++)
for (month=1;month<=12;month++)
  {  if (year % 4 == 0) is_leap_year=true ; else is_leap_year=false; 
     if (month==2 && is_leap_year==true) adjust=1; else adjust=0 ;
     for(day=1;day<=days_each_month[month-1]+adjust;day++)
       test_this_date(year,month,day,0);   /// the 0 value means non-verbose 
  }

}   /// end run_tests_in_big_loop() 

////////////////////////////////////////////////////////////////////////////

void test_this_date(int year, int month, int day, int verbose)    /// verbose-default=1
{
///   year,month,day  -->  "yyyy-mm-dd"  -->  via parseYMD0()  -->  year,month,day 
///    -->  via num_days_since_1970()  -->  bigintval  -->  via reverse_days_since_1970()
///    -->  back to year,month,day   --> and verify it is a clean result

char char_buff[20] ;
int year2, month2, day2, year3, month3, day3 , bigintval ;
bool chk1 ;

sprintf(char_buff,"%04d-%02d-%02d",year,month,day);
chk1 = parseYMD0(char_buff,year2,month2,day2);
if (year!=year2 || month!=month2 || day!=day2)
  cout << "parseYMD0 fail: " << year << "/" << month << "/" << day << "   "
       << year2 << "/" << month2 << "/" << day2 << "\n" ;

///bool reverse_days_since_1970(const int bigintval, 
///                                   int & year, int & month, int & day)
///num_days_since_1970(y,m,d) 

bigintval = num_days_since_1970(year2,month2,day2) ;
reverse_days_since_1970(bigintval,year3,month3,day3) ;

if (year2!=year3 || month2!=month3 || day2!=day3)
  cout << "1970 fail: " << year2 << "/" << month2 << "/" << day2 << "   "
       << year3 << "/" << month3 << "/" << day3 << "\n" ;

/// use this code if doing small number of tests (print out results regardless)
if (verbose==1)
   cout << "Input & output: " << year << "-" << month << "-" << day << "     "
        << year3 << "-" << month3 << "-" << day3 << "\n" ;
}   /// end test_this_date() 


