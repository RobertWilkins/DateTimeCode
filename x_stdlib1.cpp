
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




/// test mktime() and localtime() together 
int test_localtime(int year, int month, int day)
{
time_t bigintval  ;
struct tm info ;
struct tm * struct_ptr ;
char buffer[20] ;
char buffer2[20] ;
info.tm_year = year - 1900 ;
info.tm_mon  = month - 1 ;
info.tm_mday = day ;
info.tm_hour = 3 ;
info.tm_min  = 0 ;
info.tm_sec  = 0 ;
info.tm_isdst = -1 ;

bigintval = mktime(&info) ;
struct_ptr = localtime(&bigintval) ;

cout << "Year=" << year << "  Month=" << month << "  Day=" << day << '\n' ;

cout << "strftime(1st) is:  " ;
strftime(buffer,sizeof(buffer),"%Y-%m-%d",&info) ;
printf(buffer,"%s\n");

cout << "mktime() returns " << bigintval << '\n' ;

cout << "strftime(2nd) is:  " ;
strftime(buffer2,sizeof(buffer2),"%Y-%m-%d",struct_ptr) ;
printf(buffer2,"%s\n");

return 0 ;
}    /// end test_localtime()


