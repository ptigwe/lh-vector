#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if(argc < 1)
		return 1;
	int n = atoi(argv[1]);
	printf("m= %d\n", n);
	printf("n= %d\n", n);
	printf("k= 1\n");
	printf("A=\n");
	int i, j;
	for(i = 0; i < n; ++i)
	{
		for(j = 0; j < n; ++j)
		{
			if(i == j)
				printf("1 ");
			else
				printf("0 ");
		}
		printf("\n");
	}
	
	printf("B=\n");
	for(i = 0; i < n; ++i)
	{
		for(j = 0; j < n; ++j)
		{
			if(i == j)
				printf("1 ");
			else
				printf("0 ");
		}
		printf("\n");
	}
	return 0;
}