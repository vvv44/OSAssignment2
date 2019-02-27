//
//	EE 4374 Assignment # 2 Command Executer
//	Author: ???
//
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

/*Function to duplicate a string*/
char* str_duplicate(char* string){
  short i = 0;
  while(string[i] != '\0'){
    i++;
  }
  i++;
  char* copy = (char*) malloc(i*sizeof(char));
  i =0;
  while(*string){
    copy[i] = *string;
    i++;
    string++;
  }
  return copy;
}

/*We will make a variable to hold filename, which will be modified by writeToFile*/
char* filename;

//This function will determine if output of a program has to be written to a file
//will return 1 if so, and 0 if not.
int writeToFile(char **args){
     int i;
     i = 0;
     while(args[i] != 0){ //reach the end of tokens
          i++;
     }
     if(args[i-2][0] == '>'){//technically i-1 points to the filename, filename must be one word, and nothing should be after it
          /*We have to eliminate the '>' while keeping the filename saved somewhere.*/
          filename = str_duplicate(args[i-1]); //make a copy of the potential filename
          free(args[i-1]);//remove filename and > symbol
          free(args[i-2]);
          args[i-2] = NULL; //set last element to null
          return 1;
     }else{
          return 0;
     }
}

int execBackground(char **args)
{
    int i;
    // check for the ampersand at the end of the set of tokens
    i = 0;
    while(args[i] != 0)
    {
         i++;
    }                       // traverse to the end of the tokens
    if(args[i-1][0] == '&') // check the last token
    {
        free(args[i-1]);
        args[i-1] = NULL;  // remove the ampersand
        return 1;
    }
    else
    {
        return 0;
    }
}

int executeCmd(char **args)
{
    /*We will execute the command given, with the arguments given*/
    /*We have to take the first token since that is the command, and the rest of the tokens (if any) 
    pass them as arguments*/

      /*We  check if command's output has to be directed to a file*/
     if(writeToFile(args) == 1){
          int fd;
          if((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_CREAT, 
          S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1){ 
               perror (filename);
               exit( EXIT_FAILURE);
          }
          dup2(fd, 1);
          close(fd);
     }

     int bkg; //will say if command wants to run program on background
     pid_t  pid;
     int    status;

     /*we have to check if the command wants to be executed in the background*/
     if(execBackground(args) == 1){
          //execute in background
          bkg = 1;
     }
    

     //else we execute normally

     if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          /* for the child process:         */
          if (execvp(*args, args) < 0) {     /* execute the command  */
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else { 
          if(!bkg)                       /* for the parent:      */
              waitpid(pid,NULL,0); //seems to work as background only for first command
              //further children creation does not keep the shell working
          bkg = 0;
     }
    return 0;
}
//FIXME: add output writing to file