
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

void run_strptime_test_good_dates() ;
void run_strptime_test_bad_dates() ;
void test_strptime(const char *) ;
/// THIS FILE, WHAT I WANT IS TO TEST STRPTIME , (and maybe strftime too)

int main()
{
run_strptime_test_good_dates();
cout << "\n\n" ;
run_strptime_test_bad_dates();
}

void run_strptime_test_good_dates()
{
test_strptime("2017-1-1");
test_strptime("2017-1-31");
test_strptime("2017-2-28");
test_strptime("2017-03-01");
test_strptime("1969-06-06");
test_strptime("1969-06-30");
test_strptime("1969-03-01");
test_strptime("1969-02-28");
test_strptime("1970-02-28");
test_strptime("1970-03-31");
test_strptime("1970-12-31");
test_strptime("1970-12-1");
test_strptime("1980-02-28");
test_strptime("1980-02-29");
test_strptime("1980-03-01");
test_strptime("1980-12-01");
test_strptime("2000-02-29");
test_strptime("2000-03-01");
test_strptime("2000-01-01");
test_strptime("2000-12-31");
test_strptime("2008-02-28");
test_strptime("2008-03-01");
test_strptime("2008-1-1");
test_strptime("2008-12-31");
test_strptime("1900-02-28");
test_strptime("1900-03-01");
}          //// end run_strptime_test_good_dates()



void run_strptime_test_bad_dates()
{
test_strptime("1900-02-29");
test_strptime("1905-02-29");
test_strptime("1969-02-29");
test_strptime("1970-02-29");
test_strptime("1971-02-29");
test_strptime("1981-02-29");
test_strptime("1998-02-29");
test_strptime("2010-02-29");
test_strptime("2017-02-29");
test_strptime("1804-2-30");
test_strptime("2000-2-30");
test_strptime("1997-03-32");
test_strptime("2004-2-34");
test_strptime("2010-12-33");
test_strptime("2017-11-99");
test_strptime("2017--");
test_strptime("2004-7-");
test_strptime("2004--7");
}           ////  end run_strptime_test_bad_dates()

//////////////////////////////////////////////////////////////////////


void test_strptime(const char * inputstr)
{
char * pointer1 ;
char buffer[15] = "abc" ;
struct tm timeholder ;
timeholder.tm_year  = -1 ;
timeholder.tm_mon = -1 ;
timeholder.tm_mday   = -1 ;

pointer1 = strptime(inputstr,"%Y-%m-%d",&timeholder) ;
strftime(buffer,sizeof(buffer),"%Y-%m-%d",&timeholder) ;

if (pointer1==NULL) cout << "RetNULL, " ; 

cout << inputstr << "   Y,M,D=" << timeholder.tm_year+1900 << "," << 
     timeholder.tm_mon+1 << "," << timeholder.tm_mday    << 
     "    " <<   buffer  << "\n" ;
}          /// end test_strptime()


//// the upshot: strptime() does just fine with CORRECT dates, as expected.
//// as far as detecting incorrect dates, it is hit and miss.
//// strptime() consistently fails to correct incorrect leap dates
//// other types of incorrect dates, it sometimes detects and sometimes passes
//// on as valid dates.
//// AMAZINGLY, strptime() processes "2017-11-99" and passes it on as
////   2017-11-09, which is, frankly, pretty bad.
//// It also sometimes fails to detect February 30. 
//// You cannot use strptime() to detect illogical dates.

//// (The main reason why you decided to develop date functions from scratch is 
////  because the C standard libary does not appear to have reliable functions
////  for capturing incorrect dates (typically due to data entry errors).)


