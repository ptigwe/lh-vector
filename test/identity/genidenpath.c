#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	if(argc < 2)
		return 1;
		
	int n = atoi(argv[1]);
	int k = atoi(argv[2]);
	
	printf("m= %d\nn= %d\n", n, n);
	printf("labels:\n");
	if(k <= n)
	{
		printf("%d\n%d\n", k+n, k);
	}
	else
	{
		printf("%d\n%d\n", k-n, k);
	}
	
	return 0;
}