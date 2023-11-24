#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t childPID;
    int childSTAT;
    char *args[] = {"ls", "-l", "-h", NULL};

    childPID = fork();
  //error handling 
    if (childPID < 0) {
        perror("fork");
        exit(1);
    } 
  //parent process
    if (childPID > 0) {
      wait(&childSTAT);
      printf("Child exited with return code %d\n", WEXITSTATUS(childSTAT));
        
    }
    //child process
    else {
        execvp("ls", args);
        perror("execvp");
        exit(1);
    }

    return 0;
}
