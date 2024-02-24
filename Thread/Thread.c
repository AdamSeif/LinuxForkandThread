#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int input_array[4];

// Sum function
void *sum(void *thread_id)
 {
    int X = input_array[0];
    int Y = input_array[1];
    int S = X + Y;
    input_array[2] = S;
    printf("3. thread_1 (TID %lu) reads X = %d and Y = %d from input_array[]\n", pthread_self(), X, Y);
    printf("4. thread_1 (TID %lu) writes X + Y = %d to input_array[2]\n", pthread_self(), S);
    pthread_exit(NULL);
}

// Even/Odd function
void *even_odd(void *thread_id)
 {
    int S = input_array[2];

    printf("5. thread_2 (TID %lu) reads %d from input_array[2]\n", pthread_self(), S);

    if (S % 2 == 0) {
        printf("6. thread_2 (TID %lu) identifies that %d is an even number\n", pthread_self(), S);
    } else {
        printf("6. thread_2 (TID %lu) identifies that %d is an odd number\n", pthread_self(), S);
    }

}

// Multiplication function
void *multiplication(void *thread_id)
 {
    int X = input_array[0];
    int Y = input_array[1];
    int M = X * Y;

    input_array[3] = M;

    printf("7. thread_2 (TID %lu) reads X = %d and Y = %d from input_array[]\n", pthread_self(), X, Y);
    printf("8. thread_2 (TID %lu) writes X * Y = %d to input_array[3]\n", pthread_self(), M);

    pthread_exit(NULL);
}

// Reverse function
void *reverse_num(void *thread_id) 
{
    int M = input_array[3];
    printf("9.thread_3 (TID %lu) reads %d from input_array[3]\n", pthread_self(), M);

    int reversed = 0;

    while (M > 0) 
    {
        reversed = reversed * 10 + M % 10;
        M /= 10;
    }

    printf("10.thread_3 (TID %lu) reverses the number %d -> %d\n", pthread_self(), input_array[3], reversed);

    pthread_exit(NULL);
}

// Thread2 helper function
void *thread2functions(void *thread_id)
{
    even_odd(thread_id);
    multiplication(thread_id);
}

int main(int argc, char *argv[]) 
{
    // Reading the arguments
    int X = atoi(argv[1]);
    int Y = atoi(argv[2]);

    printf("1. parent (PID %d) receives X = %d and Y = %d from the user\n", getpid(), X, Y);

    input_array[0] = X;
    input_array[1] = Y;

    printf("2. parent (PID %d) writes X = %d and Y = %d to input_array[]\n", getpid(), X, Y);

    pthread_t thread_1, thread_2, thread_3;

    //  Creating first thread
    pthread_create(&thread_1, NULL, sum, NULL);
    pthread_join(thread_1, NULL);

    // Creating second thread
    pthread_create(&thread_2, NULL, thread2functions, NULL);
    pthread_join(thread_2, NULL);

    // Creating third thread
    pthread_create(&thread_3, NULL, reverse_num, NULL);
    pthread_join(thread_3, NULL);

    return 0;
}
