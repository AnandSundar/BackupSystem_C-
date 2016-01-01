#ifndef COMDE
#define COMDE 1

#include "phase2.h"

using namespace std;
const long MaxNameLength = 256; //used in creating the size of the array
const long MaxLineLength = 256; //used in creating the size of the array
const int MaxNameLen = 256; 
const string zip = "-z"; // const used in cpmmand line function
const string dir_var = "D_"; // const used to show namse that belong to directory 
const string file_var = "F_";// const used to show names that belong to file

class comde : public phase1 {

	public:
		comde(); //constructor to initialise the variables declared in class
		~comde(); //destructor to free dynamic memory when the program ends
		string originalName; 
		string duplicateName;
		string name_gz;
		char directoryName[MaxNameLen];// char array to store the entire dir path
		void comde_userinput_1(); //gets the user input for compressing
		void comde_userinput_2(); //gets user input for decompressing
		bool gzip(const char *plainfile, const char *zipfile); //function to zip a file
		bool gunzip(const char *zipfile, const char *plainfile);// function to unzip a file
		//function to compress source file and save it in destination
      bool source_file_desti_file_compress(string sourceName, string destiName,char sName[],char dName[]);
		//function to decompress the source file and save it in destination
      bool source_file_compress_desti_file(string sourceName, string destiName,char sName[],char dName[]);
		bool navigation_protocol();// activates the navigation protocol
		bool user_input(string cwd, vector<string>&contents);//user input to get the users input (b or c or n or d)
		int list_directory_contents(string cwd,vector<string>&contents);//list all the contents in a directory 
		void go_into_dir(int num, vector<string>&contents);// function to go into a different directory according to user input
		bool compress_input();// function to get the input if the user wants to compress a file
		bool decompress_input(); // function to get the input if the user wants to decompress a file

};

#endif
