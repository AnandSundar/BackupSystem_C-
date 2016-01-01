#include "unistd.h"
#include <cstdio>

const int MaxNameLen = 256;

int main()
{
    // have an array to hold the current path/directory info
    char directoryName[MaxNameLen];

    // use getcwd to look up the current working directory (where the program is running)
    //     and store it in the array
    getcwd(directoryName, MaxNameLen);
    printf("Current directory is: %s\n\n", directoryName);

    // use chdir to change the current working directory to go "up" one level
    printf("changing to parent directory\n");
    chdir("..");
    getcwd(directoryName, MaxNameLen);
    printf("Current directory is: %s\n\n", directoryName);

    // change the current working directory to the root of the system
    printf("changing to root directory\n");
    chdir("/");
    getcwd(directoryName, MaxNameLen);
    printf("Current directory is: %s\n\n", directoryName);
 
}

