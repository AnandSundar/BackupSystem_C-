// example showing the use of command line arguments in C/C++
// when run, it will display the executable name
//    and all the command line arguments supplied,
// e.g. if run as "codeExample3 foo 205 etc"
//    the output will be:
//       This executable is named codeExample3 and the supplied arguments are:
//          foo
//          205
//          etc

#include <cstdio>

using namespace std;

int main(int argc, char *argv[])
{
   printf("This executable is named %s and the supplied arguments are:\n", argv[0]);
   for (int i = 1; i < argc; i++) 
       printf("   %s\n", argv[i]);
   return 0;
}

