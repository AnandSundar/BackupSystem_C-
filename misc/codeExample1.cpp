// program that allows the user to select a directory,
//    and the program then lists the contents of the
//    directory and displays relevant information about
//    each file or subdirectory it contains

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>

// note that it uses opendir to open the file,
//    readdir to read the next entry, and
//    closedir to close the file
// if the opendir attempt fails then an error code
//    is generated in a variable named errno
// when an entry is read, a pointer is returned to
//    a dirent struct that includes a number of fields,
//    including
//        unsigned char d_type;     // the type of file 
//        char d_name[256];          // the name of the file
// the stat(filename, &st) call allows us to obtain the
//    permission settings associated with the file,
//    and a variety of flags can be checked against its
//    st_mode field to see which ones are set

using namespace std;

// create and return a string that includes both the
//   filename and the path to it, e.g.
//   "someDir" + "someFile" becomes "someDir/someFile"
string addToPath(string dirname, const char *fname);

// display permission information about the named file
void displayInfo(const char *fname);

// given the path/name for a directory as a string
//    obtain a list of its contents, placing them in the
//    contentsList vector as strings
// returns a status code based on the attempt to read the
//    directory (0 if successful)
int getContents(string dirname, vector<string> &contentsList);

// display the contents of the directory
void showContents(string dirname, vector<string> contentsList);

// get the name of a directory from the user and return it
string getDirectory();

int main()
{
   string targetDir = getDirectory();
   vector<string> dirContents = vector<string>();
   int statusCode = getContents(targetDir, dirContents);
   if (statusCode == 0) 
      showContents(targetDir, dirContents);
   return 0;
}

// create and return a string that includes both the
//   filename and the path to it, e.g.
//   "someDir" + "someFile" becomes "someDir/someFile"
string addToPath(string dirname, const char *fname)
{
    string fullname = dirname;
    fullname += "/";
    fullname += string(fname);
    return fullname;
}

// given the path/name for a directory as a string
//    obtain a list of its contents, placing them in the
//    contentsList vector as strings
// returns a status code based on the attempt to read the
//    directory (0 if successful)
int getContents(string dirname, vector<string> &contentsList)
{
   printf("\n... in getContents ...\n");
   DIR *dirPtr;
   dirPtr = opendir(dirname.c_str());
   if (dirPtr == NULL) {
      printf("   Error %d when opening directory %s\n", errno, dirname.c_str());
      return errno;
   }
   struct dirent *dirContentPtr;
   printf("   ... directory opened successfully ...\n");
   do {
      dirContentPtr = readdir(dirPtr);
      if (dirContentPtr != NULL) {
         string fullname = addToPath(dirname, dirContentPtr->d_name);
         displayInfo(fullname.c_str());
         contentsList.push_back(string(dirContentPtr->d_name));
      }
   } while (dirContentPtr != NULL);
   printf("... now closing directory ...\n");
   closedir(dirPtr);
   return 0;
}

// display permission information about the named file
void displayInfo(const char *fname)
{
   printf("\n   ... in displayInfo for %s ...\n", fname);
   struct stat st;
   int ret = stat(fname,&st);
   if (ret != 0) {
     printf("      bad entry\n");
   } else {
      if ((st.st_mode & S_IFSOCK) == S_IFSOCK) 
         printf("       it is a socket\n");
      if ((st.st_mode & S_IFLNK) == S_IFLNK) 
         printf( "       it is a link\n");
      if ((st.st_mode & S_IFREG) == S_IFREG) 
         printf( "       it is a file\n");
      if ((st.st_mode & S_IFBLK) == S_IFBLK) 
         printf( "       it is a block\n");
      if ((st.st_mode & S_IFDIR) == S_IFDIR) 
         printf( "       it is a directory\n");
      if ((st.st_mode & S_IRUSR) == S_IRUSR) 
         printf( "      owner has read permission\n");
      if ((st.st_mode & S_IWUSR) == S_IWUSR) 
         printf( "      owner has write permission\n");
      if ((st.st_mode & S_IXUSR) == S_IXUSR) 
         printf( "      owner has execute permission\n");
      if ((st.st_mode & S_IRGRP) == S_IRGRP) 
         printf( "      group has read permission\n");
      if ((st.st_mode & S_IWGRP) == S_IWGRP) 
         printf( "      group has write permission\n");
      if ((st.st_mode & S_IXGRP) == S_IXGRP) 
         printf( "      group has execute permission\n");
      if ((st.st_mode & S_IROTH) == S_IROTH) 
         printf( "      other has read permission\n");
      if ((st.st_mode & S_IWOTH) == S_IWOTH) 
         printf( "      other has write permission\n");
      if ((st.st_mode & S_IXOTH) == S_IXOTH) 
         printf( "      other has execute permission\n");
   }
   printf( "   ... end of file info ...\n");
}

// display the contents of the directory
void showContents(string dirname, vector<string> contentsList)
{
   printf( "\n... in showContents ...\n");
   printf( "   The contents of directory %s are:\n", dirname.c_str());
   for (unsigned int entryNum = 0; entryNum < contentsList.size(); entryNum++) {
       printf( "      %s\n", contentsList[entryNum].c_str());
   }
   printf( "... end of contents ...\n");
}

// get the name of a directory from the user and return it
string getDirectory()
{
   char userDir[256];
   printf( "Please enter the name of the directory you wish to examine\n");
   fgets(userDir, 256, stdin);  
   userDir[strlen(userDir)-1] = '\0';
   return string(userDir);
}

