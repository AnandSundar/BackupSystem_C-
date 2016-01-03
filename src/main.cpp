/* Name: Anand Sundar
Assignment: Phase 3
Date: 4 DEC, 2015
Purpose: This file contains the main (brain) of the program.
*/

#include "../hdr/gtkmain.h"
#include "../hdr/phase2.h"
#include "../hdr/comde.h"

// stand alone function not related to class
int backup_compress(); // gets the user input when the program starts

int main(int argc, char *argv[]) //command line arguments  
{
   bool perflag; // permission flag
   if(argc == 1) //no arguments supplied
   {
      cout<<"Do you want to use GTK(GUI)? Y/N"<<endl;
      char inp;
      cin>>inp;
      inp = tolower(inp);
      if(inp == 'y')
      {
         gtkmain(argc,argv);
         return 0;
      }
      phase1 ph; // creating an object of class phase1
      comde cd; //creting an object of class comde (compress_decompress)

      int u_i = backup_compress(); //stores the appropriate returned value in u_i (user input)
      if(u_i == 1)
      {
         //start compressing
         cd.comde_userinput_1(); // gets the input for orginal duplicate and commpress file names
         cd.errorChecking1(cd.originalName); //checks to see if the given string is <256
         cd.name_gz = cd.name_gz + ".gz"; //adds .gz to the end of the filename
         cd.errorChecking1(cd.name_gz); //checks to see if the given string is <256
         cd.errorChecking1_1(cd.originalName); //replaces ~ with /home
         cd.errorChecking1_1(cd.name_gz); //replaces ~ with /home
         bool val_originalName = cd.validating_source(cd.originalName); // checks if the source path
         // is valid
         if(val_originalName == true) //if the given path is invalid display an error message and end the program
         {
            cout<<"Source directory path is invalid"<<endl;
            cout<<"Terminating Program"<<endl;
            return 0;
         }

         perflag = cd.check_permission(cd.originalName.c_str());
         if(perflag == false)
         {
            cout<<"Terminating program"<<endl;
            return 0;
         }

         char temp_desti[cd.name_gz.length()];
         // calcs the total no.of slashes and stores the entire path without file name
         string temp_dpath = cd.nofile_path(cd.name_gz,temp_desti,cd.name_gz.length());
         bool dir_status;
         bool check = cd.check_desti_directory(temp_dpath,dir_status); //checks if the entire path is valid
         //if not creates the folders

         if(check == false) //if the checking has been cancelled
         {
            return 0; //end the program
         }

         cd.s_file = cd.fileChecking((cd.originalName).c_str()); //checks if its a file
         cd.d_file = cd.fileChecking((cd.name_gz).c_str());  //check to see if its a file
         cd.d_dir = cd.dirChecking((cd.name_gz).c_str()); //check if its a directory
         char sName[cd.originalName.length()];
         cd.errorChecking1_2(cd.originalName.length(),sName,cd.originalName); //stores the source path in a char array
         char dName[cd.name_gz.length()];
         cd.errorChecking1_2(cd.name_gz.length(),dName,cd.name_gz); //stores the destination path in a char array
         int status = cd.storeStatus(); 
         if(status == 1) //source is a file and destination file
         {
            //calls the compress function to compress the given file
            bool stat = cd.source_file_desti_file_compress(cd.originalName, cd.name_gz,sName,dName);

            if(stat == false)
            {
               cout<<"Terminating Program"<<endl;
               return 0;
            }
         }else
         {
            cout<<"Invalid destination path"<<endl;
            return 0;
         }

      }else if(u_i == 2)
      {
         //start decompress
         cd.comde_userinput_2(); //stores the user input for the decompress phase

         cd.errorChecking1(cd.name_gz); //checks to see if the given string is <256
         cd.errorChecking1(cd.duplicateName); //checks to see if the given string is <256
         cd.errorChecking1_1(cd.name_gz); //replaces ~ with /home
         cd.errorChecking1_1(cd.duplicateName); //replaces ~ with /home
         bool val_originalName = cd.validating_source(cd.name_gz); // checks if the source path
         // is valid
         if(val_originalName == true)
         {
            cout<<"Source directory path is invalid"<<endl;
            cout<<"Terminating Program"<<endl;
            return 0;
         }

         perflag = cd.check_permission(cd.name_gz.c_str());
         if(perflag == false)
         {
            cout<<"Terminating program"<<endl;
            return 0;
         }

         char temp_desti[cd.duplicateName.length()];
         // calcs the total no.of slashes and stores the entire path without file name
         string temp_dpath = cd.nofile_path(cd.duplicateName,temp_desti,cd.duplicateName.length());
         bool dir_status;
         bool check = cd.check_desti_directory(temp_dpath,dir_status); //checks if the entire path is valid
         //if not creates the folders
         if(check == false) //if the checking has been cancelled
         {
            return 0; //end the program
         }

         cd.s_file = cd.fileChecking((cd.name_gz).c_str()); //checks if its a file
         cd.d_file = cd.fileChecking((cd.duplicateName).c_str()); 
         cd.d_dir = cd.dirChecking((cd.duplicateName).c_str()); //checks if its a directory
         char sName[cd.name_gz.length()];
         cd.errorChecking1_2(cd.name_gz.length(),sName,cd.name_gz); //stores the source path in a char array
         char dName[cd.duplicateName.length()];
         cd.errorChecking1_2(cd.duplicateName.length(),dName,cd.duplicateName); //stores the destiantion path in a char array

         int status = cd.storeStatus(); //returns the status code 
         if(status == 1) //source is a file and destination file
         {
            //calls the decompression function to get the actual file
            bool stat = cd.source_file_compress_desti_file(cd.name_gz, cd.duplicateName,sName,dName);

            if(stat == false)
            {
               return 0;
            }
         }else
         {
            cout<<"Invalid destination path"<<endl;
            return 0;
         }
      }else if(u_i == 4) //navigate into the file system
      {

         cout<<endl;
         cout<<"Initiating navigation protocol....."<<endl;
         bool flag = cd.navigation_protocol(); //calls the navigation function
         if(flag == false)
         {
            cout<<"Terminating Program"<<endl;
            return 0;
         }


      }else if(u_i == 3) //start the back up (phase 1)
      {		
         // variables to store the source and destination names
         string sourceName = "";
         string destiName = "";

         ph.sourceInput(sourceName); // gets user input for source
         ph.errorChecking1(sourceName); //errorChecking1 checks only syntax of the user input

         //checks the source name for ~ and replace it with /home and stores the address path in a right 
         //format
         ph.errorChecking1_1(sourceName);
         int sourceLength = sourceName.length(); // stores the length of the new path 
         char s_Name[sourceLength]; // creates a new character array with the new path length

         //stores the string sourceName in a character array so that character array can be used to find
         // whether the path is a file or directory
         ph.errorChecking1_2(sourceLength,s_Name,sourceName);
         ph.destiInput(destiName); //gets user input for destinational path
         ph.errorChecking1(destiName); //same as above
         ph.errorChecking1_1(destiName); //same as above
         int destiLength = destiName.length();
         char d_Name[destiLength];
         ph.errorChecking1_2(destiLength,d_Name,destiName); //same as above 
         bool val_source = ph.validating_source(sourceName); //checks the validity (syntax) of the source path
         if(val_source == true)
         {
            cout<<"Source path is invalid"<<endl;
            cout<<"Terminating Program"<<endl;
            return 0;
         } 

         perflag = cd.check_permission(sourceName.c_str());
         if(perflag == false)
         {
            cout<<"Terminating program"<<endl;
            return 0;
         }

         char temp_desti[destiName.length()];
         // calcs the total no.of slashes and stores the entire path without file name
         string temp_dpath = ph.nofile_path(destiName,temp_desti,destiName.length());

         bool dir_status;
         bool check = ph.check_desti_directory(temp_dpath,dir_status); //checks if the entire path is valid 
         //if not creates the folders
         if(check == false)
         {
            return 0;
         }
         ph.s_file = ph.fileChecking(s_Name); // if 1 then it is a file, if 0 not a file
         ph.s_dir = ph.dirChecking(s_Name); // same as above for directory
         ph.d_file = ph.fileChecking(d_Name);// check to see if the destination is a file
         ph.d_dir = ph.dirChecking(d_Name); //check to see if the destination is a directory
         int status = ph.storeStatus();
         //string s_fname;
         if(status == 3) // source is a file and destination is a directory
         {
            //start backup operation
            ph.source_file_desti_dir(sourceName,destiName,d_Name,s_Name); //carryouts the back operation

            //deleting the dynamic string array to clear the memory space
            delete [] ph.destiList;
            ph.destiList = NULL;
            return 0;

         }else if(status == -1)
         {
            cout<<"Terminating program"<<endl;
            return 0;
         }else if(status == 1) // copy source file to destination file
         {
            //function call to copy source file to destination file
            ph.source_file_desti_file(sourceName, destiName, d_Name, s_Name); 

            delete [] ph.destiList; //delete the dynamic array
            ph.destiList = NULL; // point the pointer to NULL
            return 0;
         }else if(status == 2) //copy source directory to destination directory(recursive copy)
         {
            //function call to copy dire to dire
            ph.source_dir_desti_dir(sourceName, destiName, dir_status);
            return 0;
         }
      }


   }else if(argc == 5 && (argv[1] == wzip && argv[3] == wdesti)) //if the source and destination is given as cla
   {
      comde cd; //creting an object of class comde (compress_decompress)
      string sourceName=argv[2];//store the source name given in the cla
      string destiName=argv[4];// stores the destination name given in cla
      cd.errorChecking1(sourceName); //checks to see if the given string is <256
      cd.errorChecking1(destiName); //checks to see if the given string is <256
      cd.errorChecking1_1(sourceName); //replaces ~ with /home
      cd.errorChecking1_1(destiName); //replaces ~ with /home
      bool val_originalName = cd.validating_source(sourceName); // checks if the source path
      // is valid
      if(val_originalName == true) //terminate the program if the path is invalid
      {
         cout<<"Source directory path is invalid"<<endl;
         cout<<"Terminating Program"<<endl;
         return 0;
      }

      perflag = cd.check_permission(sourceName.c_str());
      if(perflag == false)
      {
         cout<<"Terminating program"<<endl;
         return 0;
      }

      if((sourceName[sourceName.length()-2] != 'g' && sourceName[sourceName.length()-1] != 'z') && sourceName[sourceName.length()-3]!='.')
      {
         //compressing file
         destiName = destiName + ".gz";
         //cout<<destiName<<endl;
         char temp_desti[destiName.length()];
         // calcs the total no.of slashes and stores the entire path without file name
         string temp_dpath = cd.nofile_path(destiName,temp_desti,destiName.length());
         bool dir_status;
         bool check = cd.check_desti_directory(temp_dpath,dir_status); //checks if the entire path is valid
         //if not creates the folders

         if(check == false) //if the checking has been cancelled
         {
            return 0; //end the program
         }

         cd.s_file = cd.fileChecking((sourceName).c_str());//check to see if the source is a file
         cd.d_file = cd.fileChecking((destiName).c_str()); //check to see if the desti is a file
         cd.d_dir = cd.dirChecking((destiName).c_str()); //check to see if the desti is a dir
         char sName[sourceName.length()];
         cd.errorChecking1_2(sourceName.length(),sName,sourceName); //stores the source path in a char array
         char dName[destiName.length()];
         cd.errorChecking1_2(destiName.length(),dName,destiName);// stores the destination path in a char array

         int status = cd.storeStatus();
         if(status == 1) //source is a file and destination file
         {
            // function call to compress the source file to desti file
            bool stat = cd.source_file_desti_file_compress(sourceName, destiName,sName,dName);

            if(stat == false)
            {
               cout<<"Terminating Program"<<endl;
               return 0;
            }
         }else
         {
            cout<<"Invalid destination path"<<endl;
            return 0;
         }
      }else if(sourceName[sourceName.length()-2] =='g' &&sourceName[sourceName.length()-1] == 'z' &&sourceName[sourceName.length()-3] =='.')
      {
         //decompressing file
         char temp_desti[destiName.length()];
         // calcs the total no.of slashes and stores the entire path without file name
         string temp_dpath = cd.nofile_path(destiName,temp_desti,destiName.length());
         bool dir_status;
         bool check = cd.check_desti_directory(temp_dpath,dir_status); //checks if the entire path is valid
         //if not creates the folders
         if(check == false) //if the checking has been cancelled
         {
            return 0; //end the program
         }

         cd.s_file = cd.fileChecking((sourceName).c_str());//check to see if the source is a file
         cd.d_file = cd.fileChecking((destiName).c_str()); //check to see if the destination is a file
         cd.d_dir = cd.dirChecking((destiName).c_str()); // check to see if the destination is a dir
         char sName[sourceName.length()];
         cd.errorChecking1_2(sourceName.length(),sName,cd.name_gz); //stores the path in a char array
         char dName[destiName.length()];
         cd.errorChecking1_2(destiName.length(),dName,destiName); //stores the path in a char array

         int status = cd.storeStatus();
         if(status == 1) //source is a file and destination file
         {
            // function call to decompress the compressed file
            bool stat = cd.source_file_compress_desti_file(sourceName, destiName,sName,dName);

            if(stat == false)
            {
               cout<<"Terminating Program"<<endl;
               return 0;
            }
         }
      }
   /*}else if(argc == 3)
   {
      if(argv[1] == wzip){
         
      }*/

   }else if((argc == 5)&&(argv[1] == wsource) &&(argv[3] == wdesti)) //cla to backup (phase1)
   { //both source and destination are given
      phase1 ph; // creating an object of class phase1
      string sourceName = argv[2];
      string destiName = argv[4];

      ph.errorChecking1(sourceName); //errorChecking1 checks only syntax of the user input

      //checks the source name for ~ and replace it with /home and stores the address path in a right 
      //format
      int sourceLength = sourceName.length(); // stores the length of the new path 
      char s_Name[sourceLength]; // creates a new character array with the new path length

      //stores the string sourceName in a character array so that character array can be used to find
      // whether the path is a file or directory
      ph.errorChecking1_2(sourceLength,s_Name,sourceName);
      ph.errorChecking1(destiName); //same as above
      int destiLength = destiName.length();
      char d_Name[destiLength];
      ph.errorChecking1_2(destiLength,d_Name,destiName); //same as above 
      bool val_source = ph.validating_source(sourceName); //checks the validity of the source path
      if(val_source == true)// end the program if the path is invalid
      {
         cout<<"Source path is invalid"<<endl;
         cout<<"Terminating Program"<<endl;
         return 0;
      }

      perflag = ph.check_permission(sourceName.c_str());
      if(perflag == false)
      {
         cout<<"Terminating program"<<endl;
         return 0;
      }

      char temp_desti[destiName.length()];
      // calcs the total no.of slashes and stores the entire path without file name
      string temp_dpath = ph.nofile_path(destiName,temp_desti,destiName.length());

      bool dir_status;
      bool check = ph.check_desti_directory(temp_dpath,dir_status); // returns a true or false value depending on the user input
      if(check == false)
      {
         return 0;
      }
      ph.s_file = ph.fileChecking(s_Name); // if 1 then it is a file, if 0 not a file
      ph.s_dir = ph.dirChecking(s_Name); // check to see if the source is dir
      ph.d_file = ph.fileChecking(d_Name);// check to see if the destination is a file
      ph.d_dir = ph.dirChecking(d_Name);// check to see if the destination is a dir
      int status = 0;
      status = ph.storeStatus();

      if(status == 3) // source is a file and destination is a directory
      {
         //start backup operation
         //function call to copy source file to desti dir
         ph.source_file_desti_dir(sourceName, destiName, d_Name, s_Name);

         delete [] ph.destiList;// delete the dynamic array
         ph.destiList = NULL;
         return 0;
      }else if(status == -1) // invalid input end the program
      {
         cout<<"Terminating program"<<endl;
         return 0;
      }else if(status == 1) // copy source file to destination file
      {
         // function call to copy source file to destination file
         ph.source_file_desti_file(sourceName, destiName, d_Name, s_Name);

         delete [] ph.destiList;//free the memory
         ph.destiList = NULL;
         return 0;
      }else if(status == 2) //copy source directory to destination directory(recursive copy)
      {
         // function call to copy dir to dir
         ph.source_dir_desti_dir(sourceName, destiName, dir_status);

      }
   }else if((argc == 3)) // only source or destination is given in command line 
   {
      if(argv[1] == wsource){ // check source for validity and request destination path    
         phase1 ph; // creating an object of class phase1
         string sourceName = argv[2]; //assigns the source path from the command line
         string destiName="";
         ph.errorChecking1(sourceName); //errorChecking1 checks only syntax of the user input

         //checks the source name for ~ and replace it with /home and stores the address path in a right 
         //format
         int sourceLength = sourceName.length(); // stores the length of the new path 
         char s_Name[sourceLength]; // creates a new character array with the new path length

         //stores the string sourceName in a character array so that character array can be used to find
         // whether the path is a file or directory
         ph.errorChecking1_2(sourceLength,s_Name,sourceName);
         ph.destiInput(destiName); //gets user input for destinational path
         ph.errorChecking1(destiName); //same as above
         ph.errorChecking1_1(destiName); //same as above
         int destiLength = destiName.length();
         char d_Name[destiLength];
         ph.errorChecking1_2(destiLength,d_Name,destiName); //same as above 
         bool val_source = ph.validating_source(sourceName); //checks the validity of the source path

         if(val_source == true)// end the program if the source is invalid
         {
            cout<<"Source path is invalid"<<endl;
            cout<<"Terminating Program"<<endl;
            return 0;
         }

         perflag = ph.check_permission(sourceName.c_str());
         if(perflag == false)
         {
            cout<<"Terminating program"<<endl;
            return 0;
         }

         char temp_desti[destiName.length()];
         // calcs the total no.of slashes and stores the entire path without file name
         string temp_dpath = ph.nofile_path(destiName,temp_desti,destiName.length());

         bool dir_status;
         bool check = ph.check_desti_directory(temp_dpath,dir_status);

         if(check == false)//if the checking is cancelled end the program
         {
            return 0;
         }
         ph.s_file = ph.fileChecking(s_Name); // if 1 then it is a file, if 0 not a file
         ph.s_dir = ph.dirChecking(s_Name); // same as above for directory
         ph.d_file = ph.fileChecking(d_Name); //check if destination is a file
         ph.d_dir = ph.dirChecking(d_Name);// check if the destiantion is dir
         int status = ph.storeStatus();
         string s_fname;
         if(status == 3) // source is a file and destination is a directory
         {
            //start backup operation
            ph.source_file_desti_dir(sourceName, destiName, d_Name,s_Name);

            delete [] ph.destiList; //free dynamic memory
            ph.destiList = NULL;
            return 0;
         }else if(status == -1)
         {
            cout<<"Terminating program"<<endl;
            return 0;
         }else if(status == 1) // copy source file to destination file
         {
            //function call to source file to destination file
            ph.source_file_desti_file(sourceName, destiName, d_Name, s_Name);

            delete [] ph.destiList;//freeing memory
            ph.destiList = NULL;
            return 0;
         }else if(status == 2) //copy source directory to destination directory(recursive copy)
         {
            ph.source_dir_desti_dir(sourceName, destiName, dir_status);
            return 0;
         }
      }else if(argv[1] == wdesti){ // check destination for validity and request source path
         phase1 ph;
         string destiName = argv[2];
         string sourceName = ""; 
         ph.sourceInput(sourceName); // gets user input for source
         ph.errorChecking1(sourceName); //errorChecking1 checks only syntax of the user input

         //checks the source name for ~ and replace it with /home and stores the address path in a right 
         //format
         ph.errorChecking1_1(sourceName);
         int sourceLength = sourceName.length(); // stores the length of the new path 
         char s_Name[sourceLength]; // creates a new character array with the new path length

         //stores the string sourceName in a character array so that character array can be used to find
         // whether the path is a file or directory
         ph.errorChecking1_2(sourceLength,s_Name,sourceName);
         ph.errorChecking1(destiName); //same as above
         ph.errorChecking1_1(destiName); //same as above
         int destiLength = destiName.length();
         char d_Name[destiLength];
         ph.errorChecking1_2(destiLength,d_Name,destiName); //same as above 
         bool val_source = ph.validating_source(sourceName); //checks the validity of the source path
         if(val_source == true)
         {
            cout<<"Source path is invalid"<<endl;
            cout<<"Terminating Program"<<endl;
            return 0;
         }

         perflag = ph.check_permission(sourceName.c_str());
         if(perflag == false)
         {
            cout<<"Terminating program"<<endl;
            return 0;
         }

         char temp_desti[destiName.length()];
         // calcs the total no.of slashes and stores the entire path without file name
         string temp_dpath = ph.nofile_path(destiName,temp_desti,destiName.length());

         bool dir_status;
         bool check = ph.check_desti_directory(temp_dpath,dir_status);
         if(check == false)
         {
            return 0;
         }
         ph.s_file = ph.fileChecking(s_Name); // if 1 then it is a file, if 0 not a file
         ph.s_dir = ph.dirChecking(s_Name); // same as above for directory
         ph.d_file = ph.fileChecking(d_Name);
         ph.d_dir = ph.dirChecking(d_Name);
         int status = ph.storeStatus();
         string s_fname;
         if(status == 3) // source is a file and destination is a directory
         {
            //start backup operation
            ph.source_file_desti_dir(sourceName, destiName, d_Name,s_Name);

            delete [] ph.destiList;
            ph.destiList = NULL;
            return 0;
         }else if(status == -1)
         {
            cout<<"Terminating program"<<endl;
            return 0;
         }else if(status == 1) // copy source file to destination file
         {
            ph.source_file_desti_file(sourceName, destiName, d_Name, s_Name);
            delete [] ph.destiList;
            ph.destiList = NULL;
            return 0;
         }else if(status == 2) //copy source directory to destination directory(recursive copy)
         {
            ph.source_dir_desti_dir(sourceName, destiName, dir_status);
            return 0;
         }       
      }else
      {
         cout<<"Invalid command line input"<<endl;
         cout<<"Terminating Program"<<endl;
      }
   }else
   {
      cout<<"Invalid command line input"<<endl;
      cout<<"Terminating Program"<<endl;    
   }

   return 0;
}
