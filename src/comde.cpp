/* Name: Anand Sundar
Assignment: Phase 3
Date: 4 DEC, 2015
Purpose: This file contains the main (brain) of the program.
*/

#include "../hdr/comde.h"
#include "../hdr/phase2.h"
comde::comde()
{
	//constructor
	originalName="";
	duplicateName="";
	name_gz="";
}

comde::~comde()
{
	//destructor

}

//asks user what he/she wants to do?
int backup_compress()
{
	char inp;
//	cout<<"Do you want to (B)ackup or (C)ompress"<<endl;
	cout<<"Enter \"B\" for backup or \"C\" for compress or \"D\" for decompress or \"N\" to navigate through the file system"<<endl;
	cin>>inp;
	while(!(inp == 'c' || inp == 'b' || inp == 'C' || inp == 'B' || inp == 'd' || inp == 'D' || inp == 'n' || inp == 'N'))
	{
		cout<<"Please enter \"B\" for backup or \"C\" for compress or \"D\" for decompress"<<endl;
		cout<<"or \"N\" to navigate through the file system"<<endl;
		cin>>inp;
	}
	if(tolower(inp) == 'c') //if the user wants to compress return 1
	{
		return 1;
	}else if(tolower(inp) == 'd') //if the user want to decompress return 2
	{
		return 2;
	}else if(tolower(inp) == 'n') //if the user want to navigate through the filesystem return 4
	{
		return 4;
	}
	else if(tolower(inp) == 'b') //if the user wants to backup files and folders return 3
	{
		return 3; //if the person wants to backup return false
	}

   return 0;
	
}

void comde::comde_userinput_1()
{
	
	cout<<"Please enter a name of the file you want to compress (eg): ~/foo/bar/foo_bar.txt"<<endl;
	cin>>originalName;
	cout<<"Please enter a name for your compressed file (eg): ~/foo/bar/foo_bar"<<endl;
	cin>>name_gz;
	
}

void comde::comde_userinput_2()
{
	cout<<"Please enter the name of the file to decompress (eg): ~/foo/bar/foo_bar.gz"<<endl;
	cin>>name_gz;
	cout<<"Please enter a name for your decompressed file (eg): ~/foo/bar/foo_bar.txt"<<endl;
	cin>>duplicateName;

}

bool comde::gzip(const char *plainfile, const char *zipfile)
{
   // attempt to open the input file,
   //    quit if unsuccessful
   FILE *fpin = fopen(plainfile, "rb");
   if (!fpin) {
      printf("unable to open input file %s\n", plainfile);
      return false;
   }

   // attempt to open the output file (the .gz file)
   //    and if unsuccessul close the input file before quitting
   gzFile fpout = gzopen(zipfile, "wb");
   if (!fpout) {
      printf("unable to open output file for compression, %s\n", zipfile);
      gzclose(fpout);
      return false;
   }
   
   // process the file one line at a time
   char inputLine[MaxLineLength];
   char charsRead = 0;
   do {
      // get the next line and uncompress it
      fgets(inputLine, MaxLineLength, fpin);
      charsRead = strlen(inputLine);
      if (!feof(fpin)) {
         // if there was anything there write it to the output
         gzwrite(fpout, inputLine, charsRead);
      }
   } while (!feof(fpin));
   
   // close both files and return the final size
   fclose(fpin);
   gzclose(fpout);
   return true;
}

bool comde::gunzip(const char *zipfile, const char *plainfile)
{
	long size=0;
   // open the compressed file for reading (binary),
   //    quit if the open fails
//cout<<*zipfile<<endl;
   gzFile fpin = gzopen(zipfile, "rb");
   if (!fpin) {
      printf("unable to open zipped file %s\n", zipfile);
      return false;
   }

   // open the output file for writing the uncompressed version
   //    if the open fails close the input file and quit
   FILE *fpout = fopen(plainfile, "wb");
   if (!fpout) {
      printf("unable to open output file %s\n", plainfile);
      gzclose(fpin);
      return false;
   }
   
   // process the file contents one line at a time
   char inputLine[MaxLineLength];
   int charsRead = 0;
   do {
      // get the next line and uncompress it
      charsRead = gzread(fpin, inputLine, MaxLineLength);
      if (charsRead > 0) {
         // if there was anything there write it to the output
         //    and update the total size written
         fputs(inputLine, fpout);
         size += charsRead;
      }
   } while (charsRead > 0); 


   // close both files and return the uncompressed size
   gzclose(fpin);
   fclose(fpout);
   return true;
}

//fucntion to compress the source file to destination
bool comde::source_file_desti_file_compress(string sourceName, string destiName,char sName[],char dName[])
{	 
	 int sourceLength = sourceName.length();
	 vector<string> dirContents = vector<string>();
	 int slash_final = 0; //make a note of the array index of the last slash so that it can
	 //be replaced by \0
	 string temp_Name; // stores the entire desti path without file name

	 store_dirName(temp_Name,destiName.c_str(),slash_final); // finds the desti dir name
	 getContents(temp_Name,dirContents); // gets the files stored in dir 
     destiListt(dirContents); // stores the file names in an array
     s_file_count = 0;
     s_chfile_existance(sName,sourceLength); //isolates the filename and stores in a variable
     //string temp = s_filename;
     s_chfile_existance(dName,destiName.length()); // isolates the destination filename to check for overwrite 
     s_filename = s_filename; //i am storing the destination file name in the source filename to check for the same file in
     						// the desti folder
     bool over_write_status = check_same_files(dirContents);
     char answer; // gets Y/N from user
     string s_fname;
     if(over_write_status == true)
     {
        // ask for confirmation
        s_fname = s_filename;
        usinp_yn(answer,s_fname);

        if(answer == 'y' || answer == 'Y')
        {
           //overwrite
           //temp_Name is the destination filepath here
 			bool flag = gzip(sourceName.c_str(), destiName.c_str());
 			if(flag == false)
 			{
 				return false;
 			}       	
           calc_file_size(sourceName);
           cout<<"Source: "<<s_fname<<"====== "<<file_size<<" Bytes"<<endl;
           calc_file_size(destiName);
           cout<<"Destination: "<<s_fname<<"====== "<<file_size<<" Bytes"<<endl;
           cout<<"Completed backing up your file(s)"<<endl;
           cout<<"Terminating Program"<<endl;
        }else if (answer == 'n' || answer == 'N')
        {
           // do not overwrite, leave the file alone
           cout<<"Terminating Program"<<endl;    
           return false;
        }else
        {
           cout<<"You have entered an invalid character"<<endl;
           cout<<"Terminating program"<<endl;
           return false;
        }
     }else
     {
        //do the backup. copy file to destination
        //create_file(sName,temp_Name); //creates a file in the destination and copies
        bool flag = gzip(sourceName.c_str(), destiName.c_str());
		if(flag == false)
		{
			return false;
		} 
        calc_file_size(sourceName);//calculates the size of the file
        cout<<"Source: "<<s_fname<<"====== "<<file_size<<" Bytes"<<endl;
        calc_file_size(destiName); //calculates the size of the file
        cout<<"Destination: "<<s_fname<<"====== "<<file_size<<" Bytes"<<endl;
        cout<<"Completed backing up your file(s)"<<endl;
        cout<<"Terminating Program"<<endl;
     } 
     clearVector(dirContents); //(delets the data in vector data 
     return true;
}

bool comde::source_file_compress_desti_file(string sourceName, string destiName,char sName[],char dName[])
{
	 int sourceLength = sourceName.length(); //store the length of the source path
	 vector<string> dirContents = vector<string>();
	 int slash_final = 0; //make a note of the array index of the last slash so that it can
	 //be replaced by \0
	 string temp_Name; // stores the entire desti path without file name

	 store_dirName(temp_Name,destiName.c_str(),slash_final); // finds the desti dir name
	 getContents(temp_Name,dirContents); // gets the files stored in dir 
     destiListt(dirContents); // stores the file names in an array
     s_file_count = 0;
     s_chfile_existance(sName,sourceLength); //isolates the filename and stores in a variable
     s_chfile_existance(dName,destiName.length()); // isolates the destination filename to check for overwrite 
     s_filename = s_filename; //i am storing the destination file name in the source filename to check for the same file in
     						// the desti folder
     bool over_write_status = check_same_files(dirContents);
     char answer; // gets Y/N from user
     string s_fname;
     if(over_write_status == true)
     {
        // ask for confirmation
        s_fname = s_filename;
        usinp_yn(answer,s_fname);

        if(answer == 'y' || answer == 'Y')
        {
           //overwrite
           //temp_Name is the destination filepath here
 			bool flag = gunzip(sourceName.c_str(), destiName.c_str());
 			if(flag == false)
 			{
 				return false;
 			}       	
           calc_file_size(sourceName); //calculate the file size
           cout<<"Source: "<<s_fname<<"====== "<<file_size<<" Bytes"<<endl;
           calc_file_size(destiName); //calculate the file size
           cout<<"Destination: "<<s_fname<<"====== "<<file_size<<" Bytes"<<endl;
           cout<<"Completed backing up your file(s)"<<endl;
           cout<<"Terminating Program"<<endl;
        }else if (answer == 'n' || answer == 'N')
        {
           // do not overwrite, leave the file alone
           cout<<"Terminating Program"<<endl;    
           return false;
        }else //invalid input
        {
           cout<<"You have entered an invalid character"<<endl;
           cout<<"Terminating program"<<endl;
           return false;
        }
     }else
     {
        //uncompress the compressed source file to desination
        bool flag = gunzip(sourceName.c_str(), destiName.c_str());
		if(flag == false)
		{
			return false;
		} 
        calc_file_size(sourceName); //calculate the soure file size
        cout<<"Source: "<<s_fname<<"====== "<<file_size<<" Bytes"<<endl;
        calc_file_size(destiName); //calculate the detination file size
        cout<<"Destination: "<<s_fname<<"====== "<<file_size<<" Bytes"<<endl;
        cout<<"Completed backing up your file(s)"<<endl;
        cout<<"Terminating Program"<<endl;
     } 
     clearVector(dirContents); //(delets the data in vector data 
     return true;	

}

//function helps the user to navigate through the file system
bool comde::navigation_protocol()
{
	string cwd;
	vector<string>contents; //vector array to store the contents of the directory
	
    getcwd(directoryName, MaxNameLen); //gets the current working directory
    cwd = directoryName;
    printf("\nCurrent directory is: %s\n\n", directoryName);
    cout<<"Listing directory contents\n"<<endl;
	list_directory_contents(cwd,contents); //function lists the directory contents
	contents.clear(); //clears the vector array
	bool flag = user_input(cwd,contents); 
	if(flag == false)
	{
		return false;
	}
	return true;
	
}

bool comde::user_input(string cwd, vector<string>&contents)
{
	char element;
	cout<<"Please enter: "<<endl;
	cout<<"A - go into a different directory\nB - up one level\nC - compress a file \nD - decompress a file \nE - Exit program"<<endl;
	cin>>element;
	while(!(tolower(element) == 'a' || tolower(element) == 'b' || tolower(element) == 'c' 
		|| tolower(element) == 'd' || tolower(element) == 'e'))
	{
		cout<<"Please enter: "<<endl;
		cout<<"A - go into a different directory\nB - up one level\nC - compress a file\nD- decompress a file \nE - Exit program"<<endl;
		cin>>element;
	}
	if(tolower(element) == 'a') //go to directory
	{
		int total = list_directory_contents(cwd,contents); //function call to list the directory contents
		go_into_dir(total-1,contents); //function call to go into the dir	
	}else if(tolower(element) == 'e') //exit the program
	{
		return false;
	
	}else if(tolower(element) == 'b') //go up one level
	{
		chdir("..");
   		getcwd(directoryName, MaxNameLen); //gets the current working directory
   		cwd = directoryName;
		printf("Current directory is: %s\n\n", directoryName);
		cout<<"Listing directory contents\n"<<endl;
		list_directory_contents(cwd,contents);//lists the directory contents
		contents.clear();//clears the vector array
		user_input(cwd,contents);
	}else if(tolower(element) == 'c') //start compressing
	{
		//how to do this??
		bool flag = compress_input(); //calls the compress fucntion
		if(flag == false)
		{
			return false;
		}

	}else if(tolower(element) == 'd') //start decompression
	{
		bool flag = decompress_input(); //calls the decompress function
		if(flag == false)
		{
			return false;
		}
	}
	return true;
}

//funtion uses the gunzip to decompress the data
bool comde::decompress_input()
{
	string cwd;
	getcwd(directoryName, MaxNameLen);//gets the current working directory
   cwd = directoryName;
	string sfile;
	string dpath;
	cout<<"Please enter the compressed file name excluding \"F_\""<<endl;
	cin>>sfile;
	//checks to see if the source file is a .gz or not
	while(!(sfile[sfile.length()-1] == 'z' && sfile[sfile.length()-2] == 'g' && sfile[sfile.length()-3 == '.']))
	{
		cout<<"Please enter the filename in the right format (eg) foo.gz"<<endl;
		cin>>sfile;
	}
	while(!(dirChecking(sfile.c_str()))) //checks if the source file is a directory
	{
		cout<<"Please enter a compressed directory name"<<endl;
		cin>>sfile;

	}
	cwd += "/" + sfile; //concatenates the current address path with the file name 
	sfile = cwd;

	cout<<"Please enter the destination path with filename (eg) ~/temp/foo.txt"<<endl;
	cin>>dpath;
	
	errorChecking1(dpath); //checks to see if the given string is <256
	errorChecking1_1(dpath); //replaces ~ with /home
	char temp_desti[dpath.length()];
	// calcs the total no.of slashes and stores the entire path without file name
	string temp_dpath = nofile_path(dpath,temp_desti,dpath.length());
	bool dir_status;
	bool check = check_desti_directory(temp_dpath,dir_status); //checks if the entire path is valid
	//if not creates the folders
	if(check == false) //if the checking has been cancelled
	 {
	    return 0; //end the program
	 }
	 char sName[sfile.length()];
     errorChecking1_2(sfile.length(),sName,sfile); //stores the path in a char array
     char dName[dpath.length()];
     errorChecking1_2(dpath.length(),dName,dpath);//store the destination path in a char array

	 bool stat = source_file_compress_desti_file(sfile, dpath,sName,dName); //decompress the file

    if(stat == false)
    {
       return 0;
    }
	 return true;
}

//compress the source file to destination
bool comde::compress_input()
{
	string cwd;
	getcwd(directoryName, MaxNameLen);
   cwd = directoryName;
	string sfile;
	string dpath;
	cout<<"Please enter the file name excluding \"F_\""<<endl;
	cin>>sfile;
	while(!(fileChecking(sfile.c_str()))) //check to see if  the file is a file and not a directory
	{
		cout<<"Please enter a file name"<<endl;
		cin>>sfile;

	}
	cwd += "/" + sfile; //concatenates the current address path with the directory name 
	sfile = cwd;
	cout<<"Please enter the destination path with filename (eg) ~/temp/foo.gz"<<endl;
	cin>>dpath;
	//checks to see if the provided name is a .gz or not
	while(!(dpath[dpath.length()-1] == 'z' && dpath[dpath.length()-2] == 'g' && dpath[dpath.length()-3 == '.']))
	{
		cout<<"Please enter the filename in the right format (eg) ~/temp/foo.gz"<<endl;
		cin>>dpath;
	}
	errorChecking1(dpath); //checks to see if the given string is <256
	errorChecking1_1(dpath); //replaces ~ with /home
	char temp_desti[dpath.length()];
	// calcs the total no.of slashes and stores the entire path without file name
	string temp_dpath = nofile_path(dpath,temp_desti,dpath.length());
	bool dir_status;
	bool check = check_desti_directory(temp_dpath,dir_status); //checks if the entire path is valid
	//if not creates the folders
	if(check == false) //if the checking has been cancelled
	 {
	    return 0; //end the program
	 }
	 char sName[sfile.length()];
     errorChecking1_2(sfile.length(),sName,sfile); //stores the source path in a char array
     char dName[dpath.length()];
     errorChecking1_2(dpath.length(),dName,dpath); //storess the destination path in a char array

	 bool stat = source_file_desti_file_compress(sfile, dpath ,sName,dName); //calls the function to compress a file

    if(stat == false)
    {
       return 0;
    }
	 return true;
}

//function list all the contents of the directory
int comde::list_directory_contents(string cwd,vector<string>&contents)
{
	int num = 1;
	DIR *dir;
	struct dirent *ent;
	string dist;
	
	if((dir = opendir (cwd.c_str())) != NULL ) //pointer pointing to the opened directory
	{
		/*print all the file and folders in the directory*/
		cout<<"Directory names starts with \"D_\" and filenames starts with \"F_\" \n"<<endl;
		while ((ent = readdir (dir)) != NULL) //read the contents of the directoryone by one
		{
			dist = ent->d_name;
			if(fileChecking(dist.c_str())) //check to see if the destiantion is a file
			{
				cout<<num<<". "<<file_var<<dist<<endl; //display the contents 
				contents.push_back(dist); //store it in the vector array
				num++;
			}else if(dirChecking(dist.c_str())) //checks for the .. and .. directory pointers
			{
				if(dist == ".." || dist == ".")
				{
					//skip it
				}else
				{
					cout<<num<<". "<<dir_var<<dist<<endl; //displays the contents
					contents.push_back(dist);// add the name to the end of the vector array
					num++;
				}
			}
		}
		cout<<endl;	
		closedir (dir); //close the opened directory when the pointer is null
		return num; //return the total num of contents in the directory
	}else
	{
		/*directory cannot be opened*/
		perror("");
		cout<<"Directory cannot be opened, please try again"<<endl;
		list_directory_contents(cwd,contents); //list the current directory contents
		return 0;
	}

}

//function to go into the directory
void comde::go_into_dir(int num, vector<string>&contents)
{
	int val=0;
	string cwd;
	getcwd(directoryName, MaxNameLen); //get the current working directory
	cwd = directoryName; //used in if block for error checking
	cout<<"Please enter the integer associated with the directory name to navigate."<<endl;
	cin>>val;
	while(val < 1 || val > num) //does not accept if the value is not in the given range
	{
		cout<<"Please enter the right value"<<endl;
		cin>>val;
	}
	
	for(int i=0; i<=(int)contents.size();i++)
	{
		if(val == i)
		{
			string change = contents[i-1];
			if(fileChecking(change.c_str())) //if the user selected a file instead of a dir
       		{
       			cout<<"ERROR!!!\n"<<endl;
       			cout<<cwd<<endl;
       			list_directory_contents(cwd,contents); //display the contents of the current dire
       			user_input(cwd,contents);
       		}else
       		{
				chdir(change.c_str()); //chang the directory to user choice
       			getcwd(directoryName, MaxNameLen);
       			contents.clear(); //clear the vectory array
       			cwd = directoryName;
       			cout<<cwd<<endl;
       			list_directory_contents(cwd,contents); //list directory contents
       			user_input(cwd,contents);
       		}
		}
	}
}
