/* Name: Anand Sundar
Assignment: Phase 3
Date: 4 DEC, 2015
Purpose: This file contains the main (brain) of the program.
*/

#ifndef PHASE2
#define PHASE2 1

// including different libraries to make my program work
#include "/usr/include/zlib.h"
#include <iostream>
#include <cctype>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <pwd.h>
#include <cstring>
#include <vector>
#include <fstream>
#include <gtk/gtk.h>

using namespace std;
const int length = 256; //const used to create the size of the array 
const string wsource = "-s"; //const used in cla to describe the following is a source path
const string wdesti = "-d"; // const used in cla to describe the followin is a desti path
const string wzip = "-z"; // const used in cla to describe the following is zipped or unzipped file
const string home = "/home"; //const to replace ~ with /home
const string slash = "/"; // const to add slash in the source and destination path
class phase1{
   public:
      phase1();//constructor
      ~phase1();//destructor
      int s_dir,s_file,d_file,d_dir;//holds status of the file or dir
      int s_file_count;//total files in the source dir
      int d_file_count;//total files in the desti dir
      int file_size;// holds the size of the source and destination file
      string s_filename;//source file name
      string d_filename;//destination filename
      string *sourceList;//pointer to a source string array
      string *destiList;//pointer to a desti string array
      void sourceListt(vector<string> &contentsList);//gets the list of source files
      void destiListt(vector<string> &contentsList);//gets the list of destifiles
      void sourceInput(string &sourceName);//get s the user input
      void destiInput(string &destiName);
      void errorChecking1(string name);//checks if the path is less than 256 chars
      void errorChecking1_1(string &name);//replace ~ with a /home
      void errorChecking1_2(int Length, char array[], string name); //stores the path in a char array
      bool check_desti_directory(string destiName,bool &dir_status);// checks and creates the destination dir if not present
      bool validating_source(string sourceName);// checks if the source exists
      void usinp_yn(char &answer, string s_fname);// gets user input Y/N
      //copy source file to desti dir
      bool source_file_desti_dir(string sourceName, string destiName, char d_Name[], char s_Name[]);
      //copy source file to desti file
      bool source_file_desti_file(string sourceName, string destiName, char d_Name[], char s_Name[]);
      //copy source dir to desti dir
      bool source_dir_desti_dir(string sourceName, string destiName, bool dir_status);
      int fileChecking(const char *name);//checks if its a file
      int dirChecking(const char *name);//checks if its a dir
      int storeStatus();
      int getContents(string temp, vector<string> &contentsList);// gets the contents of the dir
      string addToPath(string dirname, const char *fname);//adds slash and adds the file name to the end of the path
      void checkContents(string temp, vector<string> contentsList);//checks the cpntents of the dir and stores the names in a vector
      void s_chfile_existance(char s_name[], int sourceLength);//checks to see if the file already exists
      bool check_same_files(vector<string> contentsList);//checks to see if the desti and source has the ssame file
      void overwrite_file(string s_Name, string d_Name);// overwrites the file
      void create_file(string s_Name, string d_Name);//creates  a new file
      bool check_dir_exist(string d_Name);//checks to see if the dir exists
      void remove_dir(string destiName);//remove the existing dir in the destination
      void overwrite_dir(const string sourceName, const string destiName,float &percent);//overwrites the dir
      void calc_file_size(string filename); // calcs the file size
      char ask_overwrite_confirmation(); //confirms with the user before overwriting
      string nofile_path(string destiName, char temp_desti [], int len);//stores the path without filename
      void clearVector(vector<string> &contentsList); // clear the vector contents
      void store_dirName(string &temp_Name,string d_Name,int &slash_final);//store the dir name 
      bool check_permission(const char *fname); //function to check for access permission
/****************************************************************************************************************/
      //gtk functions
      void gui_source_dir_desti_dir(string sourceName,string destiName,float &percent);



   private:
      string dirName; //string to store the dirName

};

#endif
