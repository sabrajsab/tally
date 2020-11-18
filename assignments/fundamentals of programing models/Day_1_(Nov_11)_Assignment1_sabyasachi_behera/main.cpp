#include <stdio.h>
#include <pthread.h>
#include "customio.hpp"

void * Sum(void * pParam) 
{
	int num = * (int *) pParam;
	printf ("\n%c%d\n", num < 0 ? '-' : '\0' ,(num * (num + (num < 0 ? -1 : 1))) / 2);
}


int main()
{

		 pthread_t t1;
		 int number;
		 int n;
		

	printf("Enter number: ");
    n = scan<int> ();
	printf("%d\n", n);

	if (n < -10000 || n > 10000) {

		printf("\nEnter a number between -10000 and 10000.\n");
		return 1;
	}


	if (pthread_create(&t1, NULL, Sum, (void *) &n)) {

		printf("\nError in thread creation.\n");
		return 2;
	}

    if (pthread_join(t1, NULL)) {
		
		printf("\npthread_join failed.\n");
		return 3;
	}
    return 0;
}



