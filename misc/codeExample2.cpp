// program showing the use of various functions from
//    cstdio and sys/stat.h libraries to manipulate
//    file and directory contents,
// specifically:
//    mkdir to create a directory
//    rename to move or rename a file or directory
// and an example of copying a file

#include <sys/stat.h>
#include <string>
#include <cstdio>

using namespace std;

void copy(string infile, string outfile);

int main()
{
   // a few sample filenames to play with
   string original = "test1";
   string duplicate = "test2";
   string triplicate = "test3";
   string renamed = "test3";

   // status flag used to check result of various operations
   int status;

   // example of creating a directory where permissions are
   //    read,write,execute for owner
   //    read,execute for group
   //    execute for other
   status = mkdir("myNewDir", (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IXOTH));
   printf("mkdir result: %d\n", status);
 
   // examples of copying a file one char at a time
   copy(original, duplicate);
   copy(duplicate, triplicate);

   // example of removing a file
   status = remove(duplicate.c_str());
   printf("remove result: %d\n", status);

   // example of renaming a file
   status = rename(triplicate.c_str(), renamed.c_str());
   printf("rename result: %d\n", status);

   
   return 0;
}

void copy(string infile, string outfile)
{
   FILE *fpin = fopen(infile.c_str(), "r");
   if (!fpin) return;
   FILE *fpout = fopen(outfile.c_str(), "w");
   if (!fpout) {
      fclose(fpin);
      return;
   }
   while (!feof(fpin)) {
      char c = fgetc(fpin);
      if (!feof(fpin)) fputc(c, fpout);
   }
   fclose(fpin);
   fclose(fpout);
   
}

