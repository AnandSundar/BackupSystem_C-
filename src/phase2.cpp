/* Name: Anand Sundar
Assignment: Phase 3
Date: 4 DEC, 2015
Purpose: This file contains the main (brain) of the program.
*/

#include "../hdr/phase2.h"
#include "../hdr/comde.h"

phase1::phase1()
{
   //constructor
   sourceList = NULL;
   destiList = NULL;
   s_dir = 2; //dummy value
   s_file = 2;//dummy value
   d_file = 2;
   d_dir = 2;
   file_size=0;
   s_file_count = 0,d_file_count = 0;

}
//destructor
phase1::~phase1()
{
   if(sourceList != NULL)
   {
      delete [] sourceList;
   }
   if(destiList != NULL)
   {
      delete [] destiList;
   }
 
}
//source file input
void phase1::sourceInput(string &sourceName)
{
   cout<<"if your source is a directory end it with a slash (/) (eg) ~/foo/bar/ - where bar is folder"<<endl;
   cout<<"Please enter the name of the source file or directory (eg: ~/home/foo)"<<endl;
   cin>>sourceName;
}
//destination file input
void phase1::destiInput(string &destiName)
{
   cout<<"if your source is a directory end it with a slash (/) (eg) ~/foo/bar/ - where bar is folder"<<endl;

   cout<<"Please enter the name of the destination file or directory (eg: ~/home/blah)"<<endl;
   cin>>destiName;

}

void phase1::errorChecking1(string name)
{
   int x= 0;
   char ch;
   int count = 0;

   while(name[count] != '\0')
   {
      count++;  // counts the length of the string to validate
   }
   cout<<count<<endl;
   if(count > length || count == 0)
   {
      cout<<"The file or directory name you entered is too big, please enter a name that is"<<endl;
      cout<<"less than or equal to 256 characters."<<endl;		
      cin>>name;
      errorChecking1(name);
   } 


   while(name[x] != '\0')
   {
      ch = name[x];
      if(isalnum(ch) || ch == '.' || ch == '/' || ch == '_' || ch == '~') //checks for valid char
      {
         x++;		
      }else{
         cout<<"The file or directory name that you entered is invalid. Please try again.."<<endl;	
         cin>>name;
         errorChecking1(name);
      }
   }					

}

string phase1::nofile_path(string destiName, char temp_desti [], int len)
{
	int num = 0;
	for(int i =0;i < len;i++)
	{
	 if (destiName[i] == '/')
	 {
	    num++; //calculates the total number of slashes in the path
	 }
	}
	int count = 0, j = 0;
	
	for(j=0;j<len;j++)
	{
	 if(destiName[j] == '/')
	 {
	    count++;
	 }
	 if(num != count)
	 {
	    temp_desti[j] = destiName[j]; //stores the entire path except the file name

	 }else
	 {
	    break;
	 }
	}
	temp_desti[j] = '\0';
	string temp = temp_desti;
	return temp;

}

void phase1::errorChecking1_1(string &name)
{
   char *temp = new char [length]; //dynamic array to store the rearranged name
   int count = 1;
   int x= 0;
   if(name[0] == '~' && name.length() > 1)
   {
      while(name[count] != '\0')
      {
         temp[x] = name[count]; //stores the rearranged name if the condition is met
         x++;
         count++;
      }
      temp[x] = '\0';
      string tempName = temp;
      name = home + tempName; // joins the two strings together and store it as a new string

      delete temp;
   }else if(name[0] == '~' && name.length() == 1)
   {
      name = home; 
   }

}

void phase1::errorChecking1_2(int Length, char array[], string name) //function does not belong to class
{
   int x = 0;
   for(int i=0;i<Length;i++)
   {

      array[i] = name[i]; // takes all the char in string and put in char array for the dir and 
      x++;                    // file validation function to execute
   }
   array[x] = '\0';
}

bool phase1::validating_source(string sourceName)
{
   if(fileChecking((sourceName).c_str()) == 0 && dirChecking((sourceName).c_str()) == 0)
   {
      return true;
   }else 
   {
      return false;
   }

}
bool phase1::check_desti_directory(string destiName,bool &dir_status)
{
   char in;
   cout<<"Do you want to create the missing destination directory(s), if any? Y/N"<<endl;
   cin>>in;       

   if(destiName[destiName.length()-1] != '/')
   {
      destiName = destiName + slash; //adds slash according to the condition
   }
   if(tolower(in) == 'y')
   {
      //create a new dir
      char dpath[destiName.length()+1];
      if(destiName[destiName.length()-1] != '/')
      {
         destiName = destiName + slash; //adds slash according to the condition
      }
      int x = 0;
      string temp_dpath = "/";
      for(int i=1;i<(int)destiName.length()+1;i++) //signed into unsigned int error so (int)
      {

         dpath[x] = destiName[i]; //storing all the characters including the slash
         if(destiName[i] == '/') //if slash  is found
         {

            dpath[x++] = '/';
            dpath[x++] = '\0'; //end the char array
            x=0;
            string td = dpath; //store the char array in a string
            temp_dpath = temp_dpath + td; //old path + new path
            if(dirChecking(temp_dpath.c_str()))
            {
               //if true, do nothing move on
               dir_status = false;
            }else
            {
               //if one of the folders in the destination path is not found create it 
               mkdir(temp_dpath.c_str(), (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IXOTH));
               dir_status = true;
            }
         }else
         {
            x++;
         }
      }
      return true;
   }else if (tolower(in) == 'n')
   {
      cout<<"Destination path checking has been cancelled, program cannot proceed"<<endl;
      cout<<"Terminating program"<<endl;
      return false;
   }else
   {
      cout<<"wrong input \nTerminating program"<<endl;
      return false;

   }

}
//get the list of contents from the dir
int phase1::getContents(string dirname, vector<string> &contentsList)
{

   DIR *dirPtr; // directory pointer
   dirPtr = opendir(dirname.c_str()); //open the dir and uses the pointer to point to it
   if (dirPtr == NULL) {
      printf("   Error %d when opening directory %s\n", errno, dirname.c_str());
      return errno;
   }
   struct dirent *dirContentPtr; //struct pointer to read the dir

   do {

      dirContentPtr = readdir(dirPtr); // reads the dir file by file
      if (dirContentPtr != NULL) {
         string fullname = addToPath(dirname, dirContentPtr->d_name);

         contentsList.push_back(string(dirContentPtr->d_name)); // adds te file name to the end of the vector
         s_file_count++;
         d_file_count++;
      }
   } while (dirContentPtr != NULL);

   closedir(dirPtr);// closes the dir which was opened earlier
   return 0;
}
//adds slash to the end of the directory
string phase1::addToPath(string dirname, const char *fname)
{
   string fullname = dirname;
   fullname += "/";
   fullname += string(fname);
   return fullname;
}


int phase1::fileChecking(const char *name) //why am i using char * instead of a string
{
   struct stat s;
   stat(name,&s);

   return S_ISREG(s.st_mode); //return 1 if found else 0 if not found

}

int phase1::dirChecking(const char *name)
{
   struct stat s ;
   stat(name, &s);
   return S_ISDIR(s.st_mode); //returns 1 if found else 0 if not found

}

int phase1::storeStatus()
{
   //if the operation can be performed return 1
   // if the operation cannot be performend return 2
   // if its an invalid operation return -1
   if((s_file == 1 && d_file ==1)) //|| (s_file == 1 && d_file == 0)
   {
      cout<<"Source and Destination are files, backup operation can be performed"<<endl;
      return 1;
   }else if((s_dir ==1 && d_dir ==1) || (s_dir ==1 && d_dir == 0)) // || (s_dir ==1 && d_dir == 0)
   {
      cout<<"Source and destination are directories, backup operation can be performed."<<endl;
      return 2; // copy recursively	
   }else if (s_file ==1 && d_dir == 1)
   {
      cout<<"Source is a file and destination is a directory, backup operation can be performed";
      cout<<endl;
      return 3;
   }else if(s_dir == 1 && d_file == 1)
   {
      cout<<"Source is a directory and destination is a file, backup operation cannot be ";
      cout<<"performed"<<endl;
      return -1;
   }else if((s_file == 1 && d_file ==0)) //|| (s_file == 1 && d_file == 0)
   {
      cout<<"Source and Destination are files, backup operation can be performed"<<endl;
      return 4;
   }else{
      cout<<"Invalid source"<<endl; 
      return -1;
   }
   //include if source is valid and destination is not present ask user permission to create destination
}

//stores the list of files in the source dir to array
void phase1::sourceListt(vector<string> &contentsList)
{
   sourceList = new string[s_file_count+1]; //creates a dynamic array to store the file names in dir
   for(int i=0;i<s_file_count;i++)
   {
      sourceList[i] = contentsList[i].c_str(); 

   }

   sourceList[s_file_count] = '\0'; // escape char to end the array

}
//stores the list of files in the destination dir to array
void phase1::destiListt(vector<string> &contentsList)
{

   destiList = new string[d_file_count+1];
   for(int i=0;i<d_file_count;i++)
   {

      destiList[i] = contentsList[i].c_str();

   }
   destiList[d_file_count] = '\0';

}

void phase1::clearVector(vector<string> &contentsList)
{

   contentsList.clear(); // deletes all the elememts in the vector array

}

void phase1::s_chfile_existance(char s_name[], int sourceLength) //isolates the filename and 
   // stores in a   variable                                                         
{
   char s_filenamee[length]; 
   int count = 0, temp =0, x=0;
   for(int i=0;i<sourceLength;i++)
   {
      if(s_name[i] == '/')
      {
         count++;  // counts the no.of slashes(/) in the source path
      }
   }
   for(int i=0;i<sourceLength;i++)
   {
      if(s_name[i] == '/')
      {
         temp++;
      }
      if(temp == count) // if the count is the same store the file name
      {
         if(s_name[i] == '/') // ignore if /
         {
         }else
         {
            s_filenamee[x] = s_name[i]; // storing file name
            x++;
         }
      }
   }
   s_filenamee[x] = '\0';
   s_filename = s_filenamee;
   //cout<<s_filenamee<<endl;

}

bool phase1::check_same_files(vector<string> contentsList)
{
   for (unsigned int entryNum = 0; entryNum < contentsList.size(); entryNum++) 
   {
      if(destiList[entryNum] == s_filename)
      {
         d_filename = destiList[entryNum];
         // a file with the same name exists in the destination directory
         // overwrite imminent
         return true;
      }

   }

   return false;
}

//function copies everything from source file to destination if the file is present in destinaton
void phase1::overwrite_file(string s_Name, string d_Name)
{
   //streampos begin,end; //positions the begin and end to read the file and get the size
   string slash = "/";
   int size_path = d_Name.length(); //gets teh size of the destination path
   if(d_Name[size_path-1] == '/')
   {
      d_Name = d_Name+d_filename; //concatinate the destination path with the file name
   }else if(d_Name[size_path-1] != '/')
   {
      d_Name = d_Name + slash + d_filename; // adds slash if not present
   }
   ifstream s_file;
   s_file.open(s_Name.c_str(),fstream::binary); // opens a file to be read in binary
   ofstream d_file;
   d_file.open(d_Name.c_str(),fstream::binary | fstream::trunc); //opens a file to write in binary

   char c;

   while (!s_file.eof()) //checks is the source file reached the end of file
   {
      s_file.get(c); //gets the input from the source file char by char
      if(!s_file.eof())
      {
         d_file<<c; //writes it to the destination file char by char if the file is present 
      }
   }

   s_file.close(); // closes the file when done
   d_file.close();   
}

void phase1::create_file(string s_Name, string d_Name)
{

   int size_path = d_Name.length(); //gets teh size of the destination path
  // cout<<size_path<<endl;
   if(d_Name[size_path]-1 == '/')
   {
      d_Name = d_Name+d_filename; //concatinate the destination path with the file name
   }else if(d_Name[size_path]-1 != '/')
   {
      d_Name = d_Name + slash + s_filename; // adds slash if not present
   }
   //cout<<d_Name<<endl;
   //cout<<s_filename<<endl;
   FILE *s_file = fopen(s_Name.c_str(),"r"); //creates or opens a file and in read mode

   FILE *d_file = fopen(d_Name.c_str(),"w"); //creates or opens a file in write mode
   char c;
   while(!feof(s_file))
   {
      c = fgetc(s_file); // reads file char by char
      if(!feof(s_file)) //why do you need another condition to check the eof condition????
      {  
         fputc(c, d_file); //writes file char by char
      }
   }
   fclose(s_file); //closes the file
   fclose(d_file); 

}

//function using the number of slashes finds the destination directory name and stores it
void phase1::store_dirName(string &temp_Name,string d_Name, int &slash_final)
{

   char *array = new char[length];
   int x= 0;
   int count = 0;
   int slash = 0;
   int l = d_Name.length();
   for(int i=0;i<l;i++)
   {

      if(d_Name[i] == '/') // counts the number of slash found in the desti path
      {
         count++;
      }
   }
   for(int j=0;j<l;j++)
   {
      if(d_Name[j] == '/')
      {
         slash++;
      }
      if(slash<count)
      {
         array[j] = d_Name[j]; //stores the entire desti path except file name
         x++; // increments everytime to make a note of end of array
      }

      if(slash == count) //if its the last slash in the desti path
      {
         slash_final = j; // store the location of the /
         slash++; // increament the slash so that if block does not execute next time
      } 
   }

   array[x] = '\0';
   temp_Name = array;
   delete array; //freeing memory
}

bool phase1::check_dir_exist(string d_Name)
{
   struct stat st;
   lstat(d_Name.c_str(), &st);
   if(S_ISDIR(st.st_mode))
   {
      //its a directory
      return true;
   }
   return false;

}

void phase1::usinp_yn(char &answer, string s_fname)
{
   cout<<"Do you want to overwrite this file: "<<s_fname<<" ? Y/N"<<endl;
   cin>>answer;

   while(true)
   {
      if(answer == 'y' || answer == 'n' || answer == 'N' || answer == 'Y')
      {
         break;
      }
      cout<<"Wrong input, please try again"<<endl;
      cout<<"Do you want to overwrite this file: "<<s_fname<<" ? Y/N"<<endl;
      cin>>answer;

      if(answer == 'y' || answer == 'n' || answer == 'N' || answer == 'Y')
      {
         break;
      }
   }   

}
char phase1::ask_overwrite_confirmation()
{
   char input;
   cout<<"The destination contains a folder with the same name, do you want to overwrite it?  Y/N"<<endl;
   cin>>input;
   return input;

}

void phase1::calc_file_size(string filename)
{
   streampos begin,end; //positions the begin and end to read the file and get the size
   ifstream file; // variabel to open a file
   file.open(filename.c_str(),fstream::binary); //opens the file in binary mode
   begin = file.tellg(); // starts calculating the file size
   file.seekg(0,ios::end); // reads the file till the end
   end = file.tellg(); //stops cauculating
   file_size = (end-begin); //stores the file size
   file.close(); // closes the file


}

void phase1::remove_dir(string destiName)
{

   DIR *pdir = NULL; // creating a pointer to a directory
   pdir   = opendir (destiName.c_str()); //using the pointer to open a dir using
   // the source path
   struct dirent *pent = NULL;
   if(pdir == NULL)
   {
      cout<<"Cannot open destination directory"<<endl;
      return;
   }
   while((pent = readdir(pdir)) != NULL)//pointing the pointer to read a dir and 
      // check if its NULL
   {
      if(pent == NULL)
      {
         cout<<"something is wrong"<<endl;
         return;
      }else
      {
         string temp = pent->d_name;
         if(fileChecking((destiName + pent->d_name).c_str())) //check if its a file
            //pent->d_name holds the file names
         {
            remove((destiName + pent->d_name).c_str());
           
         }else if(dirChecking((destiName + pent->d_name).c_str()) &&(!(temp == "." || temp == "..")))
         {
         //make a new directory
         //recursively call the smae function with different folder names
         remove_dir(destiName+pent->d_name+"/");
         remove((destiName + pent->d_name + "/").c_str());
         }
      }  
   }
   closedir(pdir); //close the source dir 
}

bool phase1::source_file_desti_dir(string sourceName, string destiName, char d_Name[], char s_Name[])
{
	 int sourceLength = sourceName.length();

	 vector<string> dirContents = vector<string>();
	 string s_fname;
     clearVector(dirContents); //delets the data in vector data
     getContents(destiName,dirContents); // gets the files stored in dir 
     destiListt(dirContents); // stores the file names in an array
     s_file_count = 0;
     s_chfile_existance(s_Name,sourceLength); //isolates the filename and stores in a variable
     // checks for same files in source and destination  directories
     bool over_write_status = check_same_files(dirContents);
     char answer; // stores Y/N from user
     s_fname = s_filename;
     if(over_write_status == true)
     {
        // ask for confirmation

        usinp_yn(answer,s_fname); //gets the user input y/n 

        if(answer == 'y' || answer == 'Y')
        {
           //overwrite
           overwrite_file(s_Name,d_Name);
           calc_file_size(sourceName);
           cout<<"Source: "<<s_fname<<"====== "<<file_size<<" Bytes"<<endl;
           calc_file_size(destiName + s_fname);
           cout<<"Destination: "<<s_fname<<"====== "<<file_size<<" Bytes"<<endl; 
           cout<<"Completed backing up your file(s)"<<endl;
           cout<<"Terminating Program"<<endl;
           return true;
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
        create_file(s_Name,d_Name); //creates a file in the destination and copies
        calc_file_size(sourceName);
        cout<<"Source: "<<s_fname<<"====== "<<file_size<<" Bytes"<<endl;
        calc_file_size(destiName + s_fname);
        cout<<"Destination: "<<s_fname<<"====== "<<file_size<<" Bytes"<<endl;
        cout<<"Completed backing up your file(s)"<<endl;
        cout<<"Terminating Program"<<endl;
        return true;
     }
}

bool phase1::source_file_desti_file(string sourceName, string destiName, char d_Name[], char s_Name[])
{

	  int sourceLength = sourceName.length();
     vector<string> dirContents = vector<string>();
     int slash_final = 0; //make a note of the array index of the last slash so that it can
     //be replaced by \0
     string temp_Name; // stores the entire desti path without file name

     store_dirName(temp_Name,d_Name,slash_final); // finds the desti dir name
     getContents(temp_Name,dirContents); // gets the files stored in dir 
     destiListt(dirContents); // stores the file names in an array
     s_file_count = 0;
     s_chfile_existance(s_Name,sourceLength); //isolates the filename and stores in a variable
     // checks for same files in source and destination  directories
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
           overwrite_file(s_Name,temp_Name);
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
        create_file(s_Name,temp_Name); //creates a file in the destination and copies
        calc_file_size(sourceName);
        cout<<"Source: "<<s_fname<<"====== "<<file_size<<" Bytes"<<endl;
        calc_file_size(destiName);
        cout<<"Destination: "<<s_fname<<"====== "<<file_size<<" Bytes"<<endl;
        cout<<"Completed backing up your file(s)"<<endl;
        cout<<"Terminating Program"<<endl;
     } 
     clearVector(dirContents); //(delets the data in vector data 
     return true;
}

void phase1::gui_source_dir_desti_dir(string sourceName,string destiName, float &percent)
{

     remove_dir(destiName); // goes through all the subfolders and removes id its a file
     rmdir(destiName.c_str()); // if the directory is empty delete it (it can contain empty subdirectories)
     mkdir(destiName.c_str(), (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IXOTH));//create dir
     overwrite_dir(sourceName,destiName,percent); //this copies dir to dir
     cout<<"Completed backing up your file(s)"<<endl;
     cout<<"Terminating Program"<<endl;
}

bool phase1::source_dir_desti_dir(string sourceName, string destiName, bool dir_status)
{
   float temp = 0.0;
	 if(dir_status == true)
     {
        overwrite_dir(sourceName,destiName,temp); //this copies dir to dir
        cout<<"Completed backing up your file(s)"<<endl;
        cout<<"Terminating Program"<<endl;
        return true;
     }else
     {
        char user_conf = ask_overwrite_confirmation();
        if(tolower(user_conf) == 'y')
        {
           remove_dir(destiName); // goes through all the subfolders and removes id its a file
           rmdir(destiName.c_str()); // if the directory is empty delete it (it can contain empty subdirectories)
           mkdir(destiName.c_str(), (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IXOTH));//create dir
           overwrite_dir(sourceName,destiName,temp); //this copies dir to dir
           cout<<"Completed backing up your file(s)"<<endl;
           cout<<"Terminating Program"<<endl;
           return true;            
        }else if(tolower(user_conf == 'n'))
        {
           cout<<"Terminating program"<<endl;
           return false;
        }else
        {
           cout<<"Invalid input"<<endl;
           cout<<"Terminating program"<<endl;
           return false;
        }
    }
}

void phase1::overwrite_dir(const string sourceName, const string destiName, float &percent)
{  
   
   DIR *pdir = NULL; // creating a pointer to a directory
   pdir   = opendir (sourceName.c_str()); //using the pointer to open a dir using
   // the source path
   struct dirent *pent = NULL;
   if(pdir == NULL)
   {
      cout<<"Cannot open source directory"<<endl;
      return;
   }
   while((pent = readdir(pdir)) != NULL)//pointing the pointer to read a dir and 
      // check if its NULL
   {

      if(pent == NULL)
      {
         cout<<"something is wrong"<<endl;
         return;
      }else
      {  
         string temp = pent->d_name;
         if(fileChecking((sourceName + pent->d_name).c_str())) //check if its a file
         {

            FILE *s_file = fopen((sourceName + pent->d_name).c_str(),"r"); //creates or opens a file and in read mode
            FILE *d_file = fopen((destiName + pent->d_name).c_str(),"w"); //creates or opens a file in write mode
            char c;
            while(!feof(s_file))
            {
               c = fgetc(s_file); // reads file char by char
               if(!feof(s_file)) //why do you need another condition to check the eof condition????
               {  
                  fputc(c, d_file); //writes file char by char
               }

            }

            fclose(s_file); // closes the file when done
            fclose(d_file); 
            calc_file_size(sourceName + pent->d_name); //calculates the file size and stores it in file_size
            cout<<"Source: "<<pent->d_name<<"====== "<<file_size<<" Bytes"<<endl;

            calc_file_size(destiName + pent->d_name);
            cout<<"Destination: "<<pent->d_name<<"====== "<<file_size<<" Bytes"<<endl;

         }else if(dirChecking((sourceName + pent->d_name).c_str()) && (!(temp == "." || temp == "..")))
         {
                  //cout<<"hello"<<endl;
      //cout<<sourceName<<endl;
            //make a new directory
            mkdir((destiName+pent->d_name).c_str(), (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IXOTH));
            //recursively call the smae function with different folder names
            overwrite_dir(sourceName+pent->d_name+"/", destiName+pent->d_name+"/",percent);
         }
      }  
   }
   closedir(pdir); //close the source dir 
}


//function to check if the file or folder has access permission
bool phase1::check_permission(const char *fname)
{
   struct stat st;
   int ret = stat(fname,&st);
   if (ret != 0) {
     cout<<"   bad entry "<<endl;
     return false;
   } else {
   	 if(!(((st.st_mode & S_IRUSR) == S_IRUSR)))
   	 {
   	 	cout<<"File or folder does not have access permission"<<endl;
   	 	return false;
   	 }else
   	 {
   	 	return true;
   	 }
   	 return true;
	}
}