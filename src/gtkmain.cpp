/* Name: Anand Sundar
Assignment: Phase 3
Date: 4 DEC, 2015
Purpose: This file contains the main (brain) of the program.
*/


#include "../hdr/gtkmain.h"
#include "../hdr/phase2.h"
#include "../hdr/comde.h"
/****************************************************************/

//global variables
string g_sfile,g_dfile,g_sfolder,g_dfolder, signall;


/****************************************************************/

static void toggled_func(GtkWidget* widget,gpointer data)
{
   string sourceName = g_sfile;
   string destiName = g_dfile;

   //radio button 1
   if(strcmp((char*) data,"1")==0) 
   {
      if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))){ //check if the first radio button is selected

         signall = "compress"; 
      }
   }
   //radio button 2
   if(strcmp((char*) data,"2")==0)
   {
      if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))){

         signall = "decompress";
      }
   }
   //radio button 3
   if(strcmp((char*) data,"3")==0)
   {
      if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))){

         signall = "backup";  
      }
   }
}

//stores the path of the source file
static void file_change1(GtkFileChooser *chooser2,char *file)
{

   file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser2)); //gets the address path of the selected file
   g_sfile = file;
}
//stores the path of the destination file 
static void file_change2(GtkFileChooser *chooser2,char *file)
{

   file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser2)); //gets the address path of the selected file
   g_dfile = file;
}
//sotores the path of the source folder
static void file_change_sf(GtkFileChooser *chooser2,char *file)
{

   file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser2)); //gets the address path of the selected file
   g_sfolder = (string) file;

}
//stores the path of the destination 
static void file_change_df(GtkFileChooser *chooser2,char *file)
{

   file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser2)); //gets the address path of the selected file
   g_dfolder = (string) file;

}
//backup,compress and decompress for file
static void gtk_file_backup()
{
   if(g_sfile == "" || g_dfile == "")
   {
      GtkWidget *error;
      //make a new dialog with a ok button
      error = gtk_message_dialog_new(NULL,GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,"No File Selected. Please select a source file and destination file");
      //prevent the dialog from resizing 
      gtk_window_set_resizable(GTK_WINDOW(error), FALSE);
      //when the user presses a button destry the widget
      g_signal_connect_swapped (error, "response",G_CALLBACK (gtk_widget_destroy),error);
      gtk_widget_show_all(error);
   }else
   {
      string sourceName = g_sfile;
      string destiName = g_dfile;
      if(signall == "backup"){
         phase1 tmp;   
         int sourceLength = sourceName.length(); // stores the length of the new path 
         char s_Name[sourceLength]; // creates a new character array with the new path length

         //stores the string sourceName in a character array so that character array can be used to find
         // whether the path is a file or directory
         tmp.errorChecking1_2(sourceLength,s_Name,sourceName);
         int destiLength = destiName.length(); 
         char d_Name[destiLength];
         tmp.errorChecking1_2(destiLength,d_Name,destiName);
         tmp.source_file_desti_file(sourceName, destiName, d_Name, s_Name);         
         gtk_main_quit();
      }else if(signall == "compress"){
         comde cd;
         sourceName = g_sfile;
         destiName = g_dfile;
         destiName = destiName + ".gz";

         char sName[cd.originalName.length()];
         cd.errorChecking1_2(cd.originalName.length(),sName,cd.originalName); //stores the source path in a char array
         char dName[cd.name_gz.length()];
         cd.errorChecking1_2(cd.name_gz.length(),dName,cd.name_gz); //stores the destination path in a char array
         cd.source_file_desti_file_compress(sourceName, destiName,sName,dName);
      }else if(signall == "decompress"){
         comde cd;
         sourceName = g_sfile;
         destiName = g_dfile;
         destiName = destiName + ".gz";

         if(!(sourceName[sourceName.length()-1] == 'z' && sourceName[sourceName.length()-2] == 'g' && sourceName[sourceName.length()-3 == '.']))
         {
            GtkWidget *error;
            //displays the error message dialog box
            error = gtk_message_dialog_new(NULL,GTK_DIALOG_DESTROY_WITH_PARENT,
                  GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,"Please select a source file that ends with \".gz\"");
            //prevent the dialog from resizing 
            gtk_window_set_resizable(GTK_WINDOW(error), FALSE);
            //when the user presses a button destry the widget
            g_signal_connect_swapped (error, "response",G_CALLBACK (gtk_widget_destroy),error);
            gtk_widget_show_all(error);   
            gtk_main_quit();
         }

         char sName[cd.name_gz.length()];
         cd.errorChecking1_2(cd.name_gz.length(),sName,cd.name_gz); //stores the source path in a char array
         char dName[cd.duplicateName.length()];
         cd.errorChecking1_2(cd.duplicateName.length(),dName,cd.duplicateName); //stores the destiantion path in a char array
         //calls the decompression function to get the actual file
         cd.source_file_compress_desti_file(sourceName, destiName,sName,dName);            
      }
   }
}
//interface to select the source and destination file
static void file_selection(GtkWidget *window) //here data is a struct passed in main
{

  
   gtk_widget_hide(window); //hides the main window

   GtkWidget *window2;
   window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL); //creates a new window
   gtk_window_set_position(GTK_WINDOW(window2), GTK_WIN_POS_CENTER_ALWAYS);
   g_signal_connect(window2, "delete-event", G_CALLBACK(gtk_main_quit), NULL); //when the user clicks the close button the program ends
   gtk_window_set_title(GTK_WINDOW (window2),"Source and Destination selection"); //casting the window(widget) into GTK_WINDOW
   gtk_container_set_border_width(GTK_CONTAINER (window2), 15); //adds the border of 15 inch
   gtk_window_set_resizable(GTK_WINDOW(window2), FALSE);
   GtkWidget *table, *source, *desti, *label1, *ok, *cancel, *s_browse_button, *d_browse_button, *radio1, *radio2, *radio3;

   table = gtk_table_new(4,5,0); //row,col, homogenous

   source = gtk_label_new("Select source file");
   desti = gtk_label_new("Select destination file");

   char *file1 = NULL;
   char *file2 = NULL;
   s_browse_button = gtk_file_chooser_button_new("Source", GTK_FILE_CHOOSER_ACTION_OPEN);
   gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(s_browse_button), g_get_home_dir()); //sets the default opening path to /home
   //calls file_change function to get the address path of the file
   g_signal_connect (G_OBJECT (s_browse_button), "selection_changed",G_CALLBACK (file_change1),(gpointer) file1);

   //g_print("%s",gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(s_browse_button)));
   d_browse_button = gtk_file_chooser_button_new("Destination", GTK_FILE_CHOOSER_ACTION_OPEN);
   gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(s_browse_button), g_get_home_dir()); //sets the default opening path to /home

   //calls file_change function to get the address path of the file
   g_signal_connect (G_OBJECT (d_browse_button), "selection_changed",G_CALLBACK (file_change2),(gpointer) file2);

   signall ="compress"; //default selection for file selection table
   //radio buttons for user to select from different options
   radio1 = gtk_radio_button_new_with_label(NULL,"Compress");
   g_signal_connect(radio1,"toggled",G_CALLBACK(toggled_func),(gpointer) "1");
   radio2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio1)),"Decompress");
   g_signal_connect(radio2,"toggled",G_CALLBACK(toggled_func),(gpointer) "2");
   radio3 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio1)),"Backup");
   g_signal_connect(radio3,"toggled",G_CALLBACK(toggled_func),(gpointer) "3");

   ok = gtk_button_new_with_mnemonic("   _Ok   ");
   g_signal_connect(ok,"clicked",G_CALLBACK(gtk_file_backup), NULL);
   cancel = gtk_button_new_with_mnemonic("_Cancel");

   g_signal_connect(G_OBJECT(cancel), "clicked", G_CALLBACK(gtk_main_quit), window);

   label1 = gtk_label_new("Choose Source and Destination"); //label displays some info
   //table to organize all the buttons properly
   gtk_table_attach(GTK_TABLE(table),label1,1,2,0,1,GTK_FILL,GTK_FILL,0,0);//left,right,top,down
   gtk_table_attach(GTK_TABLE(table),source,0,1,1,2,GTK_FILL,GTK_FILL,0,0);
   gtk_table_attach(GTK_TABLE(table),s_browse_button,1,3,1,2,GTK_FILL,GTK_FILL,0,0);
   gtk_table_attach(GTK_TABLE(table),desti,0,1,2,3,GTK_FILL,GTK_FILL,0,0);
   gtk_table_attach(GTK_TABLE(table),d_browse_button,1,3,2,3,GTK_FILL,GTK_FILL,0,0);
   gtk_table_attach(GTK_TABLE(table),radio1,0,1,3,4,GTK_FILL,GTK_FILL,0,0);
   gtk_table_attach(GTK_TABLE(table),radio2,1,2,3,4,GTK_FILL,GTK_FILL,0,0);
   gtk_table_attach(GTK_TABLE(table),radio3,2,3,3,4,GTK_FILL,GTK_FILL,0,0);
   gtk_table_attach(GTK_TABLE(table),ok,3,4,3,4,GTK_FILL,GTK_FILL,0,0);
   gtk_table_attach(GTK_TABLE(table),cancel,4,5,3,4,GTK_FILL,GTK_FILL,0,0);
   gtk_container_add(GTK_CONTAINER(window2), table);
   gtk_widget_show_all(window2);
}

static float percent = 0.0;
//progress bar to check how much copy is done
static gboolean inc_progress(gpointer data)
{
   percent+= 0.15;
   if(percent >=1.0)
   {
      percent = 0.0;
      gtk_main_quit();
   }
   gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(data), percent); //creates a progress bar
   char c[3];
   sprintf(c,"%d%%",static_cast<int>(percent*100)); //includes the percentage
   gtk_progress_bar_set_text(GTK_PROGRESS_BAR(data),c); //initializes the progress bar
   return true;
}
//backups the folder recursively
static void backup_folder(GtkWidget *data)
{
   gtk_widget_hide(data);
   GtkWidget *error, *progress;
   if(g_sfolder == "" || g_dfolder == "")
   {

      //make a new dialog with a ok button
      error = gtk_message_dialog_new(NULL,GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,"No File Selected. Please select a source folder and destination folder");
      //prevent the dialog from resizing 
      gtk_window_set_resizable(GTK_WINDOW(error), FALSE);
      //when the user presses a button destry the widget
      g_signal_connect_swapped (error, "response",G_CALLBACK (gtk_widget_destroy),error);
      gtk_widget_show_all(error);
   }else
   {
      phase1 tmp;

      //add progress bar
      GtkWidget *window3;
      window3 = gtk_window_new (GTK_WINDOW_TOPLEVEL); //creates a new window
      gtk_window_set_position(GTK_WINDOW(window3), GTK_WIN_POS_CENTER_ALWAYS);
      g_signal_connect(window3, "delete-event", G_CALLBACK(gtk_main_quit), NULL); //when the user clicks the close button the program ends
      gtk_window_set_title(GTK_WINDOW (window3),"See progress"); //casting the window(widget) into GTK_WINDOW
      gtk_container_set_border_width(GTK_CONTAINER (window3), 15); //adds the border of 15 inch
      gtk_window_set_resizable(GTK_WINDOW(window3), FALSE);
      gtk_window_activate_focus(GTK_WINDOW(window3)); //make the window active
      progress = gtk_progress_bar_new();

      g_timeout_add(300,inc_progress,progress);
      gtk_container_add(GTK_CONTAINER(window3),progress);
      gtk_widget_show_all(window3);
      //gtk_widget_grab_focus(progress);
      tmp.gui_source_dir_desti_dir(g_sfolder + "/",g_dfolder + "/",percent); //backup the source folder to destination folder
   }
   //gtk_main_quit();
}
//window to select a source and destination folder
static void folder_selection(GtkWidget *window)
{
   gtk_widget_hide(window);
   GtkWidget *window2;
   window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL); //creates a new window
   gtk_window_set_position(GTK_WINDOW(window2), GTK_WIN_POS_CENTER_ALWAYS);
   g_signal_connect(window2, "delete-event", G_CALLBACK(gtk_main_quit), NULL); //when the user clicks the close button the program ends
   gtk_window_set_title(GTK_WINDOW (window2),"Source and Destination selection"); //casting the window(widget) into GTK_WINDOW
   gtk_container_set_border_width(GTK_CONTAINER (window2), 15); //adds the border of 15 inch
   gtk_window_set_resizable(GTK_WINDOW(window2), FALSE);
   GtkWidget *table, *source, *desti, *label1, *ok, *cancel, *s_browse_button, *d_browse_button;

   table = gtk_table_new(4,5,0); //row,col, homogenous

   source = gtk_label_new("Select source folder");
   desti = gtk_label_new("Select destination folder");

   gchar *file1 = NULL;
   s_browse_button = gtk_file_chooser_button_new("Source", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);

   //calls file_change function to get the address path of the folder
   g_signal_connect (G_OBJECT (s_browse_button), "selection_changed",G_CALLBACK (file_change_sf),(gpointer) file1);
   gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(s_browse_button), g_get_home_dir()); //sets the default opening path to /home

   d_browse_button = gtk_file_chooser_button_new("Destination", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);

   //calls file_change function to get the address path of the folder
   g_signal_connect (G_OBJECT (d_browse_button), "selection_changed",G_CALLBACK (file_change_df),(gpointer) file1);   
   gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(d_browse_button), g_get_home_dir()); //sets the default opening path to /home
   ok = gtk_button_new_with_mnemonic("   _Ok   ");
   g_signal_connect(G_OBJECT(ok), "clicked", G_CALLBACK(backup_folder), window2);

   cancel = gtk_button_new_with_mnemonic("_Cancel");
   g_signal_connect(G_OBJECT(cancel), "clicked", G_CALLBACK(gtk_main_quit), window);

   label1 = gtk_label_new("Choose Source and Destination"); //label displays some info
   gtk_table_attach(GTK_TABLE(table),label1,1,2,0,1,GTK_FILL,GTK_FILL,0,0);//left,right,top,down
   gtk_table_attach(GTK_TABLE(table),source,0,1,1,2,GTK_FILL,GTK_FILL,0,0);
   gtk_table_attach(GTK_TABLE(table),s_browse_button,1,3,1,2,GTK_FILL,GTK_FILL,0,0);
   gtk_table_attach(GTK_TABLE(table),desti,0,1,2,3,GTK_FILL,GTK_FILL,0,0);
   gtk_table_attach(GTK_TABLE(table),d_browse_button,1,3,2,3,GTK_FILL,GTK_FILL,0,0);
   gtk_table_attach(GTK_TABLE(table),ok,3,4,3,4,GTK_FILL,GTK_FILL,0,0);
   gtk_table_attach(GTK_TABLE(table),cancel,4,5,3,4,GTK_FILL,GTK_FILL,0,0);
   gtk_container_add(GTK_CONTAINER(window2), table);

   gtk_widget_show_all(window2);

}
//creates a middle window to select between file and folder
static void middle_window(GtkWidget *window)
{
   gtk_widget_hide(window); //hides the main window
   GtkWidget *window2;
   window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL); //creates a new window
   gtk_window_set_default_size(GTK_WINDOW(window2), 250, 50); //sets the default size of the window to 300*300
   gtk_window_set_position(GTK_WINDOW(window2), GTK_WIN_POS_CENTER_ALWAYS); //positions the window in the center of the screen
   g_signal_connect(window2, "delete-event", G_CALLBACK(gtk_main_quit), NULL); //when the user clicks the close button the program ends
   gtk_window_set_title(GTK_WINDOW (window2),"Select file or folder"); //casting the window(widget) into GTK_WINDOW
   gtk_container_set_border_width(GTK_CONTAINER (window2), 15); //adds the border of 15 inch   
   //gtk_window_set_resizable(GTK_WINDOW(window2), FALSE);
   GtkWidget *file, *folder, *lab, *vbox;
   vbox = gtk_vbox_new(false,0);
   gtk_container_add(GTK_CONTAINER(window2),vbox);
   lab = gtk_label_new("Select file or folder");
   file = gtk_button_new_with_mnemonic("_Select a File");
   g_signal_connect(G_OBJECT(file),"clicked",G_CALLBACK(file_selection),window2);
   folder = gtk_button_new_with_mnemonic("S_elect a Folder");
   g_signal_connect(G_OBJECT(folder),"clicked",G_CALLBACK(folder_selection),window2);
   gtk_container_add(GTK_CONTAINER(vbox),lab);
   gtk_container_add(GTK_CONTAINER(vbox),file);
   gtk_container_add(GTK_CONTAINER(vbox),folder);

   gtk_widget_show_all(window2);
}
//function brain of gtk interface
void gtkmain(int argc, char *argv[])
{
	/***************************************************************************************************************************/
      gtk_init(&argc, &argv);

      GtkWidget *button_backup, *quit;
      GtkWidget *box;
      GtkWidget *window;

      window = gtk_window_new (GTK_WINDOW_TOPLEVEL); //creates a new window
      g_signal_connect (window, "delete-event", G_CALLBACK(gtk_main_quit), NULL); //when the user clicks the close button the program ends
      gtk_window_set_title(GTK_WINDOW (window),"MainWindow"); //casting the window(widget) into GTK_WINDOW
      gtk_container_set_border_width(GTK_CONTAINER (window), 15); //adds the border of 15 inch

      box = gtk_vbox_new(FALSE,0); //creates a box to arrange the buttons vertically
      gtk_container_add (GTK_CONTAINER (window), box); //add the box to the main window

      gtk_window_set_resizable (GTK_WINDOW (window), FALSE); //allows the user to resize the window
      gtk_window_activate_focus(GTK_WINDOW(window)); //make the window active
      gtk_window_set_default_size(GTK_WINDOW(window), 100, 120); //sets the default size of the window to 300*300
      gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS); //positions the window in the center of the screen
      gtk_window_set_destroy_with_parent(GTK_WINDOW (window), TRUE); //true - make the main will kill itself if the tramsient will dies
      //gtk_window_set_default (GTK_WINDOW(window), button_exit); //this button will activate when the user presses enter
      //gtk_window_iconify(GTK_WINDOW(window)); //minimise the window
      //gtk_window_deiconify(GTK_WINDOW(window)); //unminimise the window
      gtk_window_set_decorated(GTK_WINDOW(window),TRUE); //decorates the title bar of the window;
      button_backup = gtk_button_new_with_mnemonic("_Backup files and folders"); //adds a button the main window
      gtk_container_add(GTK_CONTAINER(box), button_backup); //box is added on top of the container and button is added on top the box
      //g_signal_connect(G_OBJECT(button_backup), "clicked", G_CALLBACK(backup_function), window); //calls the backup_function when the button is clicked
      g_signal_connect(G_OBJECT(button_backup), "clicked", G_CALLBACK(middle_window), window);
      quit = gtk_button_new_with_mnemonic("_Quit"); //label of a button
      gtk_container_add(GTK_CONTAINER(box), quit); //button is added to the container
      g_signal_connect(quit, "clicked", G_CALLBACK(gtk_main_quit), NULL); //program quits when the button is clicked   


      gtk_widget_show(quit);
      gtk_widget_show(button_backup);
      gtk_widget_show(box);
      gtk_widget_show(window); //displays the new window

      gtk_main();
      
      /*************************************************************************************************************************/

}
