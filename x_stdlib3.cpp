
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

///// test functions from C std lib for date/time 
///// test mktime() and localtime() , back and forth  time_t  <->  struct tm

/////For x_stdlib3.cpp, some testing for both localtime() and gmtime() 



int test_localtime(int,int,int);

int main(int argc,char ** argv)
{
test_localtime(1970,1,2);
test_localtime(2017,2,20);
}

//// here are the standard library functions you are testing
//// time_t mktime( struct tm * time_ptr ) ;
//// struct tm *  localtime( const time_t * timer ) ;
//// struct tm *  gmtime( const time_t * timer ) ;


/// be careful with localtime() and gmtime(), they return a pointer to a 
///  struct tm data structure than can be written over with later calls to 
///  localtime()/gmtime(), so print results before calling library function again

/// test mktime() and localtime() and gmtime() together 
int test_localtime(int year, int month, int day)
{
time_t bigintval  ;
struct tm info ;
struct tm * struct_ptr ;
char buffer[60] ;
char buffer2[60] ;
char buffer3[60] ;
info.tm_year = year - 1900 ;
info.tm_mon  = month - 1 ;
info.tm_mday = day ;
info.tm_hour = 0 ;
info.tm_min  = 0 ;
info.tm_sec  = 0 ;
info.tm_isdst = -1 ;

bigintval = mktime(&info) ;


cout << "Year=" << year << "  Month=" << month << "  Day=" << day << '\n' ;

cout << "strftime(1st) is:  " ;
strftime(buffer,sizeof(buffer),"%c",&info) ;
printf("%s\n",buffer);

cout << "mktime() returns " << bigintval << "     /24*60*60 "  <<
     bigintval/(24*60*60)  <<  "     %24*60*60 "    <<  bigintval % (24*60*60)   << '\n'  ;

struct_ptr = localtime(&bigintval) ;
cout << "strftime(2nd, from localtime) is:  " ;
strftime(buffer2,sizeof(buffer2),"%c",struct_ptr) ;
printf("%s\n",buffer2);

struct_ptr = gmtime(&bigintval) ;
cout << "strftime(3rd, from gmtime) is:  " ;
strftime(buffer3,sizeof(buffer2),"%c",struct_ptr) ;
printf("%s\n",buffer3);


return 0 ;
}    /// end test_localtime()


