/******************************************************************
* kopy.c
* An example Unix-like shell copy command/utility.
* Copies the first file to the second. Options to be defined.
* D.Heffernan1/April/2007  last update: 27/Sep/11ver 0.1.1
* HT update 2018
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFSIZE 1024 //or BUFFSIZE 4096
// Main function
int main (int argc, char *argv[])   {
  int i;
  int fileArg = 0;// Count for files on command line
  int infd, outfd;// File descriptor for input and output file
  int num_read, num_write;// Numbers of characters returned by a file access
  char buff [BUFFSIZE];// Buffer for use in file access
  char* fileName[2] = {};   // Point to file names

  // Parse the command line arguments
  for(i = 1; i < argc; i++) {
    if (argv[i][0] == '-')  {// Check for a command option
      // Simple message display, a real system would process options
      printf ("You have selected an option\n");
    }else {
    	fileName[fileArg++] = argv[i];
    } // record the filename in argv[]
  }
   // Open the first file for reading 
   infd = open (fileName[0], O_RDONLY); 
    if (infd == -1) {  // error check followed by error messages 
    printf ("Failed to open first file %s!!!\n", fileName[0]); 
    printf ("Please check CMD arguments.\n"); 
    return 1; 
   }
  // Open/create the second file for writing
  outfd = open (fileName[1], O_CREAT | O_WRONLY, 0600 );
  if (outfd == -1) { // error check followed by error messages
    printf ("Failed to open second file %s!!!\n", fileName[1]);
    printf ("Missing output filename.\n");
    close (infd);
    return 1;
  }
  // Now copy the contents of the first file to the second file
  while (( num_read = read (infd, buff, sizeof (buff))) > 0)  {
    num_write = write(outfd, buff, num_read);
    // Check for basic failure
    if (num_write != num_read) {
    	printf ("Problem -mismatch between write size and read size!\n");
    }
  }
  // remember to close all open files before exit
  close (outfd);
  close (infd);
  return 0; //program exits
}    
