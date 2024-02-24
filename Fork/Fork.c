#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    //Reading the arguments
    char *N = argv[1]; 
    char *M = argv[2]; 
    char *S = argv[3];

    //Creating pid_t variables for all the children
    pid_t child1, child2, child11, child12;

    //Creating child 1 
    child1 = fork();

    if (child1 < 0)
    {
        printf("child 1 fork failed\n");
        return 1;
    }
    else if (child1 == 0)
    {
        //Creating child 1.1
        child11 = fork();

        if (child11 < 0)
        {

            printf("child 1.1 fork failed\n");
            return 1;
        }
        else if (child11 == 0)
        {
            //Executing external_program1.c in child 1.1, passing in the argument N
            execl("/home/aseif4/3305/external_program1.c", "/home/aseif4/3305/external_program1.c", N, NULL);
        } else {
            //Waiting for child 1.1
            wait(NULL);
        }

        //Creating child 1.2
        child12 = fork();

        if (child12 < 0)
        {
            printf("child 1.2 fork failed\n");
            return 1;
        }
        else if (child12 == 0)
        {
            //Executing external_program1.c in child 1.2, passing in the argument M
            execl("/home/aseif4/3305/external_program1.c", "/home/aseif4/3305/external_program1.c", M, NULL);
        } else {
            //Waiting for child 1.2
            wait(NULL);
        }
    }
    else
    {
        //Creating child 2
        child2 = fork();

        if (child2 < 0)
        {
            printf("Fork for child2 failed\n");
            return 1;
        }
        else if (child2 == 0)
        {
            //Executing external_program2.c in child 2, passing in the argument S
            execl("/home/aseif4/3305/external_program2.c", "/home/aseif4/3305/external_program2.c", S, NULL);
        }
        else
        {
            //Waiting for child 2
            wait(NULL);
        }
    }
    return 0;
}
