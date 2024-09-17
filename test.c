#include "philosophers.h"

int main ()
{
    pthread_mutex_t *test;

    int i = pthread_mutex_init (test, NULL);
    printf("mutex initialased is : %d\n", i);
    i = pthread_mutex_lock(test);
    printf("mutex locked is : %d\n", i);
    i = pthread_mutex_unlock(test);
    printf("mutex unlocked is : %d\n", i);
}