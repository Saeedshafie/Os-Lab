#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

int const num = 10; // number of childs
int id;
int root_pid; // father PID
int pid;

typedef struct
{
    int histData[25];
} Hist;

Hist *hist;

int main()
{
    int sample;  // count of samples
    printf("Number of Sample processes :");
    scanf("%d", &sample);

    clock_t start = clock();

    srand(time(0));

    if ((id = shmget(IPC_PRIVATE, sizeof(Hist), IPC_CREAT | 0666)) < 0)
    {
        printf("couldn't create the shared memory");
        exit(-1);
    }

    root_pid = getpid();

    for (int i = 0; i < num; i++)
    {
        if (getpid() == root_pid)
            pid = fork();
        else
            break;
    }

    hist = (Hist *)shmat(id, NULL, 0);


    if (getpid() == root_pid)
    {
        for (int i = 0; i < num; i++)
        {
            wait(NULL);
        }
    }
    else
    {
        // generating count 
        int count, random;
        for (int i = 0; i < sample / num; i++)
        {
            count = 0;
            for (int j = 0; j < 12; j++)
            {
                random = rand() % 101;
                if (random >= 49)
                {
                    count++;
                }
                else
                {
                    count--;
                }
            }
            hist->histData[count + 12]++;
        }

        exit(0);
    }

    clock_t end = clock();
    double time_spent = (double)(end - start)/CLOCKS_PER_SEC;
    printf("\nTime Spent %lf\n", time_spent);
    // print result
     for (int i = 0; i < 25; i++){
         printf("%d ", i - 12);
          for(int j = 0; j < (int)(hist->histData[i]/(sample/100)); j++) {
           printf("|");
        }
         printf("\n");
        }

    return 0;
}

