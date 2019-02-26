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


     int bkg;
     pid_t  pid;
     int    status;
     
     /*we first have to check if the command wants to be executed in the background*/
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
              waitpid(pid,NULL,0);
          bkg = 0;
     }
    return 0;
}
