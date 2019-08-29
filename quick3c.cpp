
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

int test_date_print(int,int,int);


int main(int argc,char ** argv)
{
test_date_print(2017,2,29);
test_date_print(2017,5,-1);
test_date_print(2016,2,29);
test_date_print(2000,2,29);
test_date_print(2001,2,29);
test_date_print(2004,2,29);
test_date_print(1996,2,29);
test_date_print(2005,3,32);
test_date_print(2005,3,31);
test_date_print(2005,3,0);
test_date_print(2005,2,28);
test_date_print(2005,2,29);
test_date_print(2005,-1,-1);
}



int test_date_print(int year, int month, int day)
{
int ret ;
struct tm info ;
char buffer[20] ;
info.tm_year = year - 1900 ;
info.tm_mon  = month - 1 ;
info.tm_mday = day ;
info.tm_hour = 3 ;
info.tm_min  = 0 ;
info.tm_sec  = 0 ;
info.tm_isdst = -1 ;

ret = mktime(&info) ;
cout << "mktime() returns " << ret << '\n' ;
strftime(buffer,sizeof(buffer),"%Y-%m-%d",&info) ;
printf(buffer,"%s");
cout << "   and Year=" << year << " Month=" << month << " Day=" << day << '\n' ;


return 0 ;
  
}
