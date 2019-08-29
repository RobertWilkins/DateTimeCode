
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


int main(int argc,char ** argv)
{
char buff[21] ;
long numchar ;
long i1=7, i2=13 , i3=144 , i4=-2 , i5=-22 ;

numchar = sprintf(buff,"%li",i1);
cout << buff << '\n' ;

numchar = sprintf(buff,"%04li",i1);
cout << buff << '\n' ;
numchar = sprintf(buff,"%04li",i2);
cout << buff << '\n' ;
numchar = sprintf(buff,"%04li",i3);
cout << buff << '\n' ;
numchar = sprintf(buff,"%04li",i4);
cout << buff << '\n' ;
numchar = sprintf(buff,"%04li",i5);
cout << buff << '\n' ;
}





