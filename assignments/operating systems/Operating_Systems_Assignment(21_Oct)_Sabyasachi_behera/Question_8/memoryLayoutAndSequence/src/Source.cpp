#include<iostream>
void fun2()
{
	int x;

	printf("\nmemory in stack(2nd function)\n%p\n", &x);
}

void fun()
{
	int x;

	printf("\nmemory in stack(1st function)\n%p\n", &x);
	fun2();
}


int main()
{
	char arr[6]="hello";
	char * chDynamic[10];
	printf("\naddress of \"hello\" (initialised read only area)\n%p", &"hello");
	printf("\nmemory allocated for array (initialised read write area)\n");
	for (int i = 0; i < 6; ++i) {
		printf("%p ", arr + i);
	}
	for (int i = 0; i < 10; ++i) {
		printf("%p ", chDynamic + i);
	}


	char ch1, ch2, ch3;
	int i1, i2, i3;

	printf("\nmemory allocated for individual declarations for char and int(uninitialised data segment - bss)\n");
	printf("\n%p  %p  %p  %p  %p  %p  ", &ch1, &ch2, &ch3, &i1, &i2, &i3);
	
	printf("\nmemory allocated dynamically (heap)\n");
	for (int i = 0; i < 10; ++i)
	{
		chDynamic[i] = (char*)malloc(1);
		printf("%p  ", chDynamic[i]);
	}
	fun();
	for (int i = 0; i < 10; ++i)
	{
		free(chDynamic[i]);
	}
	system("pause");
}