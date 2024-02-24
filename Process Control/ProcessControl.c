#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int summation(int start, int end)
{
    int sum = 0;
    if (start < end)
    {
        sum = ((end * (end + 1)) - (start * (start - 1))) / 2;
    }
    return sum;
}

int ith_part_start(int i, int N, int M)
{
    int part_size = N / M;
    int start = i * part_size;
    return start;
}

int ith_part_end(int i, int N, int M)
{
    int part_size = N / M;
    int end = (i < M - 1) ? ((i + 1) * part_size - 1) : N;
    return end;
}

int main(int argc, char **argv)
{
    // Reading the arguments
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);

    // Creating a variable to hold the total sum
    int totalSum = 0;

    // Creating a pipe
    int status;
    int port[2];
    status = pipe(port);

    // Creating pid_t variables for child1 and children 1.1 to 1.M
    pid_t child1, children1toM;

    if (status < 0)
    {
        printf("pipe failed\n");
        exit(0);
    }

    printf("parent(PID %d): process started\n\n", getpid());

    // Creating child1
    child1 = fork();
    if (child1 < 0)
    {
        printf("child 1 fork failed\n");
        exit(0);
    }
    else if (child1 == 0)
    {
        printf("child_1(PID %d): process started from parent(PID %d)\n", getpid(), getppid());

        // Creating 1 to M children
        for (int i = 1; i <= M; i++)
        {
            children1toM = fork();

            if (children1toM < 0)
            {
                printf("children1toM fork failed\n");
                return 1;
            }
            else if (children1toM == 0)
            {
                int partialSum = summation(ith_part_start(i, N, M), ith_part_end(i, N, M));

                // Writing partial sum to port
                write(port[1], &partialSum, sizeof(int));
                printf("child_1.%d(PID %d): fork() successful\n", i, getpid());
                printf("child_1.%d(PID %d): partial sum: [%d - %d] = %d\n", i, getpid(), ith_part_start(i, N, M), ith_part_end(i, N, M), partialSum);

                exit(0);
            }
	}  
            // Reading M partial sums from the pipe
            for (int i = 0; i < M; i++)
            {
                int partialSum;
                read(port[0], &partialSum, sizeof(int));
                totalSum += partialSum;
            }

            for(int i=0;i<M;i++)
            {
                wait(NULL);
            }
            // This is the end of child1
            printf("\n\nchild_1(PID %d): total sum = %d\n", getpid(), totalSum);
            printf("child_1(PID %d): child_1 completed\n", getpid());
        
    }
    else
    {
        printf("parent(PID %d): forking child_1\n", getpid());
        printf("parent(PID %d): fork successful for child_1(PID %d): \n", getpid(), child1);
        printf("parent(PID %d): waiting for child_1(PID %d) to complete\n\n", getpid(), getpid());

        wait(NULL);
        
        printf("\n\nparent(PID %d): parent completed\n", getpid());
    }

    return 0;
}
