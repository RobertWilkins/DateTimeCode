
/// bool parseYMD0(const string & s, int & year1, int & month1, int & day1) ;
/// bool is_illogical_date(int y, int m, int d);

int num_days_since_1970(int y, int m, int d);
bool reverse_days_since_1970(const int bigintval, int & y, int & m, int & d);


/// const static int month_accum_days[] = {0,31,59, 90,120,151, 181,212,243, 273,304,334};

/// const static int days_each_month[] = {31,28,31, 30,31,30, 31,31,30, 31,30,31} ;

const int missing_dt_1970 = -99999*365 ;   

////////////////////////////////////////////////////////////////////////


/// From year,month, day to days since Jan 1 1970, and the reverse direction
/// for the moment, omit hours,minutes,seconds, deal with that later.
/// This means that the integer values this function returns will be smaller by
/// a factor of 24*60*60, relative to function in C standard library.

/// This function may need more code to check for bad input data
/// The input data: month and day are not input as 0 , month is 1-12 and day is 1-31

int num_days_since_1970(int y, int m, int d)
{
const static int month_accum_days[] = {0,31,59, 90,120,151, 181,212,243, 273,304,334};
int y1 = 1969  , y0=1970 , days_since_1970 , y3 , leap ;

if (m<1 || m>12) return -99999*365 ;  // avoid seg-fault for now, more detail later

/// y1 is set to 1969, and not 1970, so that if 1970 were a leap year, we 
///  would not accidentally cancel it out (when counting leap years).
/// However, 1970 is not a leap year, so whether y1 is set to 1969 or 1970 does
/// not matter.

if   (m>=3)   y3 = y ;
else          y3 = y-1 ; 

/// this is a count of leap days (counting occurrences of February 29)
/// it does appear you can use the same formula for years after 1970 and for years before 1970
leap = (y3/4 - y3/100 + y3/400) - (y1/4 - y1/100 + y1/400)   ;

days_since_1970 = d-1  + month_accum_days[m-1]  +  leap  + 365*(y-y0)   ;

return days_since_1970 ;
}   //// end num_days_since_1970()


/// Here's the arithmetic logic that supports this algorithm:
/// (obviously, integer division, not floating-point, assume m and k are positive )
/// m/k = j    ...  m = jk + b , 0<=b<k   
/// So the sequence to visualize is:  0, k, 2k, 3k, .... , jk , m , (j+1)k
/// whereas m is definitely less than (j+1)k  (but might be equal to jk )
/// And so: m/k is the number of multiples of k , between 0 and m, not including
///  0, but possibly including m ( if m itself is a multiple of k).

/// Assuming g is a positive year (beyond Jesus Christ),
/// g/4 - g/100 + g/400 , is always the number of leap years between 0 and g, 
///  not including 0, but possibly including g (if g is itself a leap year).
/// Now, is that statement true ? The following observation helps:
/// g/4 - g/100 + g/400 is equal to
/// The number of multiples of 4, between 0 and g  (including g, possibly, but not 0)
/// minus
/// The number of multiples of 100, between 0 and g  (including g, but not 0)
/// plus
/// The number of multiples of 400, between 0 and g  (including g, but not 0)

/// And so, the variable "leap", in above function is the number of leap years up 
/// the year in question, subtracting the number of leap years up to 1969. That 
/// allows me to count the leap days that must be included. Obviously, must adjust 
/// for whether the month is Jan/Feb, or later ( y3 above includes that adjustment).

/// Oddly enough, the same exact formula works for dates BEFORE 1970. 
/// In any case, these functions are super easy to run through tests.

///////////////////////////////////////////////////////////////////

/// The first section of code in reverse_days_since_1970() is to find a year, Y, 
/// such that:  Jan 1, Y   <=   bigintval   <   Jan 1, Y+1
/// which is to say that bigintval is for a date during that year
/// once you have found the correct year, find the correct month and day.

bool reverse_days_since_1970(const int bigintval, 
                                   int & year, int & month, int & day)
{
const static int month_accum_days[] = {0,31,59, 90,120,151, 181,212,243, 273,304,334};
/// compare the above to {-,31,28, 31,30,31, 30,31,31, 30,31,30}, and you get the idea
/// watch carefully, in code below, for adjustments for a possible February 29th

int year0, g0 , y1, y2 , days1, m1 , days2 , adjust=0 ;
year0 = bigintval/365+1970 ;
g0 = num_days_since_1970(year0,1,1) ;

if ( g0 <= bigintval )
  { while (g0<=bigintval)  { year0++;  g0 = num_days_since_1970(year0,1,1); }
    y1=year0-1;   y2=year0; }
else     /// means g0>bigintval, to start with 
  { while (g0>bigintval)   { year0--;  g0 = num_days_since_1970(year0,1,1); }
    y1=year0;     y2=year0+1; }

/// and now: Jan 1, Y1  <= bigintval  <  Jan 1, Y2

days1 = bigintval - num_days_since_1970(y1,1,1) ;   /// if days1 is 0, that's Jan 1

//// note: days1~59 is for either February 29th or March 1st (is it a leap year?)

if (days1<=58)                 //// days1~58 is for February 28th 
    { if (days1<=30) m1=0; else m1=1 ; }
else     //// processing for beyond Feb 28th of the year
{ if      (y1 % 4 != 0)   adjust=0 ;
  else if (y1 % 100 != 0) adjust=1 ;     /// leap year: divisible by 4, not century
  else if (y1 % 400 != 0) adjust=0 ;     /// 1900, 2100 not leap years
  else                    adjust=1 ;     /// 2000 is a leap year 
  /// m1, month is range 0-11, NOT 1-12, until calculation is finished 
  /// following is integer division, always round down
  m1 = days1/31 ;
  if (m1<11 && days1 >= month_accum_days[m1+1] + adjust ) m1++ ;
  /// without the next line of code, will have a subtle bug for Feb 29th, careful here
  ///  because, once have determined it is February, not March, do not need adjust factor afterwards
  if (m1<2) adjust=0 ;
}    /// end large else block (beyond Feb 28th)

if (m1<0 || m1>11) return false ;   /// avoid seg-fault, but this should not happen

/// here, if m1 is 0 or 1, adjust HAS to be 0, even if it is a leap year 
///   carelessness on that point can cause bug for February 29th
days2 = days1 - (month_accum_days[m1] + adjust) + 1 ;  /// gives day of month 
m1++ ;   /// switch from 0-11 to 1-12 range, do not do this too soon 
/// at this point, values to return are y1, m1, and days2 
year = y1; month=m1; day=days2 ;
}   //// end reverse_days_since_1970()





/////////////////////////////////////////////////////////////
/// Suppose bigintval ~ Jan 1, then days1=0
/// Suppose bigintval ~ Feb 1, then days1=31
/// Suppose bigintval ~ Mar 1, then days1=59 or 60       add 28 or 29
/// Suppose bigintval ~ Apr 1, then days1=90 or 91       add 31
/// Suppose bigintval ~ May 1, then days1=120 or 121     add 30
/// Suppose bigintval ~ Jun 1, then days1=151 or 152     add 31

/// Suppose bigintval ~ Jul 1, then days1=181 or 182     add 30
/// Suppose bigintval ~ Aug 1, then days1=212 or 213     add 31
/// Suppose bigintval ~ Sep 1, then days1=243 or 244     add 31

/// Suppose bigintval ~ Oct 1, then days1=273 or 274     add 30
/// Suppose bigintval ~ Nov 1, then days1=304 or 305     add 31
/// Suppose bigintval ~ Dec 1, then days1=334 or 335     add 30

/// Suppose bigintval ~ Dec 31, then days1=364 or 365    add 30 (not 31)
/// Suppose bigintval ~ Jan 1, following year, then you have an error

/// days1 can be:
/// 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 364
/// So m1 = days1/31 + 1 will be:
/// 1,  2,  2,  3,   4,   5,   6,   7,   8,   9,  10,  11,  12
/// And so m1 is the right value or too small by 1


