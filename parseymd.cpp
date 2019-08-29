
/// August 2017, repairing damage done to date/time code when your hard drive 
///  failed last month.
/// parseYMD() parses "9999-31-04", and must use other utility functions :
///   is date missing, partially missing, illogical ?

bool parseYMD0(const string & s, int & year1, int & month1, int & day1);
bool is_illogical_date(int y, int m, int d);
bool date_partially_missing(int y, int m, int d);
bool date_completely_missing(int y, int m, int d);
bool date_missing(int y, int m, int d);
int date_status_check(int y, int m, int d);

/// code for missing in context of of date/time work dt~date/time
/// used to indicate day is missing, or year is missing, or month is missing
const int missing_dt=-99999 ;   
/// following 4 status codes indicate, 
/// 0 - date is in good shape, not at all missing
/// 1 - date is completely missing, year,month, and day 
///      this includes dates where year is missing
/// 2 - date is partially missing (month or day or both) but not illogical
/// 3 - date is illogical (whether year/month/day all non-missing or not)
const int DATE_IS_GOOD          = 0 ;
const int DATE_IS_MISSING       = 1 ;
const int DATE_IS_PART_MISSING  = 2 ;
const int DATE_IS_NOT_LOGICAL   = 3 ;

/// parseYMD0() expects format "1999-02-19"
/// parseYMD0 does not call illogical_date() or missing_date(), does a minimum of work
/// because parseYMD0() does the minimum of work necessary, may need another parse function 
/// for public use.
/// set to completely missing if one of the following: one of the two dashes is missing (also
/// if foreign characters present before parse complete), or year/month/day all missing, or
///  year is missing (if year is missing, set month and day to missing too), or if year or month
///  or day has too many digits (more than 4 or 2 digits).

bool parseYMD0(const string & s, int & year1, int & month1, int & day1) 
{
bool founddash1=false , founddash2=false ;
char *tmp ;
int k, k2 ;
string year_str, month_str, day_str ;

k2 = k = 0 ;
while (k<s.size() && isspace(s[k])) ++k ;
k2 = k ;
while (k<s.size() && isdigit(s[k])) ++k ;
if (k>k2) year_str = s.substr(k2,k-k2) ;

while (k<s.size() && isspace(s[k])) ++k ;
if (k<s.size() && s[k]=='-') { founddash1=true ; k++ ; }
while (k<s.size() && isspace(s[k])) ++k ;

k2 = k ;
while (k<s.size() && isdigit(s[k])) ++k ;
if (k>k2) month_str = s.substr(k2,k-k2) ;

while (k<s.size() && isspace(s[k])) ++k ;
if (k<s.size() && s[k]=='-') { founddash2=true ; k++ ; }
while (k<s.size() && isspace(s[k])) ++k ;

k2 = k ;
while (k<s.size() && isdigit(s[k])) ++k ;
if (k>k2) day_str = s.substr(k2,k-k2) ;

if ( founddash1==false || founddash2==false )
  { year1=month1=day1=missing_dt ; return false ; }
if (year_str == "") 
  { year1=month1=day1=missing_dt ; return false ; }
if (year_str.size()>4 || month_str.size()>2 || day_str.size()>2 )
  { year1=month1=day1=missing_dt ; return false ; }

if (year_str != "")   year1  = (int) strtol(year_str.c_str(),&tmp,10)  ;
  else year1 = missing_dt ;
if (month_str != "")  month1 = (int) strtol(month_str.c_str(),&tmp,10)  ;
  else month1 = missing_dt ;
if (day_str != "")    day1   = (int) strtol(day_str.c_str(),&tmp,10)  ;
  else day1 = missing_dt ;

if (year1==missing_dt && month1==missing_dt && day1==missing_dt) return false ;
return true ;  /// indicates successful parse, not completely missing 
//// don't forget: this function does not check for illogical: March 32nd, etc.
}   //// parseYMD0()


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

//// pay attention, if year missing, is_illogical_date() returns what?
//// if year is missing, treat as "completely missing" and "illogical" status
//// any year before 0 A.D. is not allowed, treat as illogical
//// note: always check for missing BEFORE checking for 0 or negative
////  otherwise missing values can be accidentally swept up in checks for <=0
////  a value that is not missing_dt and not non-nonsensical , 
////  such as day=-7 or day=37, is a BAD VALUE, which should not happen.

bool is_illogical_date(int y, int m, int d)
{
static int days_each_month[] = {31,28,31, 30,31,30, 31,31,30, 31,30,31 } ;

// if date is completely missing, treat as logical 
if (y==missing_dt && m==missing_dt && d==missing_dt) return false ;
if (y==missing_dt) return true ;   // if year is missing, return true
if (y<0 || y>9999) return true ;   // no sci-fi dates, no prehistoric dates 
 
if (m==missing_dt || d==missing_dt)
  { // at this point: month is missing, or day is missing, or both missing
    if (m==missing_dt && d==missing_dt) return false ;       // missing, but not illogical
    if (m!=missing_dt) return (m<=0 || m>12) ;  /// here, know day must be missing
    if (d!=missing_dt) return (d<=0 || d>31) ;  /// here, know month must be missing 
  }   //// after this block, know date is completely non-missing
//// rest of code, year and month and day not missing 

/// note: check for negative or zero AFTER check for missing, fail to do that
///       and could have subtle bug!
if (m<=0 || d<=0) return true ;    // month or day: range 1-12 and 1-31
if (m>12) return true ;
if (d>31) return true ;
if (m!=2) return ( d > days_each_month[m-1] ) ;

//// at this stage, month has to be 2 (February) 
if (d<=28) return false ;
if (d>29) return true ;
if (d==29)
 { if      ( y % 4   != 0 ) return true ;   // not divisible by 4, not leap year
   else if ( y % 100 != 0 ) return false ;  // divisible by 4, but not 100, leap year
   else if ( y % 400 != 0 ) return true ;   // 1900, 2100 not leap years
   else return false ;                      // 2000 is a leap year
 }
return false ; /// everything checks out 
}  /// end is_illogical_date() 




////////////////////////////////////////////////////
////////////////////////////////////////////////////


/// if illogical, then treat as "completely missing", NOT partially missing
///  HOWEVER, if year is missing, also treat as completely missing.
bool date_partially_missing(int y, int m, int d)
{
if (is_illogical_date(y,m,d)) return false ; 
if (y<0) return false ;  /// if year is missing, treat as "completely missing" 
if (m==-1 || d==-1) return true ;
return false ;
}

bool date_completely_missing(int y, int m, int d)
{
if (is_illogical_date(y,m,d)) return true ; 
if (y<0) return true ;    /// whether missing-code or bad value
return false ;     /// if year not missing, then not completely missing
} 

bool date_missing(int y, int m, int d)
{
if (is_illogical_date(y,m,d)) return true ; 
if (y<0) return true ;   /// whether missing-code or bad value
if (m==-1 || d==-1) return true ;
return false ;
}


int date_status_check(int y, int m, int d)
{
/// if year is missing, treat as completely missing, don't care whether illogical
if (y==missing_dt) return DATE_IS_MISSING ;
if (is_illogical_date(y,m,d)) return DATE_IS_NOT_LOGICAL ;
if (y!=missing_dt && m!=missing_dt && d!=missing_dt) return DATE_IS_GOOD ;
if (y==missing_dt && m==missing_dt && d==missing_dt) return DATE_IS_MISSING ;
  /// yes, know above is partly redundant, but clarifies the chosen logic.

/// at this stage, month or day (or both) are missing. Year is not missing.
/// year not missing, both day/month missing, treat as partially missing.
if (m==missing_dt && d==missing_dt) return DATE_IS_PART_MISSING ;
/// at this point, day or month (but not both) are missing.
return DATE_IS_PART_MISSING ;
}
/// above code is tricky: if both month and day are missing, treat as partially 
///  missing, but if only year is non-missing could make a good case that date
///  is completely missing


// this date/time code is a big (and frankly rather tedious) step towards establishing
// a suitable replacement for the SAS programming language, in terms of affordability, 
// suitable learning curve, and productivity, acknowledging that the monopoly of the 
// SAS programming language is somewhat bad news for biopharma shareholders and really 
// bad news for Medicare taxpayers.
// It is unfortunate that I have not gotten any political support whatsoever from technical 
// specialists in the pharmaceutical industry on this venture.


