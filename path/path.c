#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define Z(i) (i)
#define W(i) (i + ndim)
#define MAXSTR 100

int ndim;
int m, n;

int* basic;
int count;

struct node
{
	int value;
	struct node* next;
}
node;

struct node* root;

void notimpl (char *info)
{
    fflush(stdout);
    fprintf(stderr, "Program terminated with error. %s\n", info);
    exit(1);
}

void readconf (const char *s)
{
    int i, len = strlen(s);
    char a[MAXSTR];
    for (i=0; i<len; i++)
        {
        if (scanf("%1s", &a[i])==EOF)
            /* make sure something is in  a  for error report       */
            a[i] = '\0';
        if (a[i] != s[i])
            /* the chars in  a  from stdin do not match those in s  */
            {
            fprintf(stderr, "\"%s\"  required from input, found \"%s\"\n",
                    s, a);
            notimpl("");
            }
        }
}

void printVariable(int var)
{
	if(var <= ndim)
	{
		printf("z%d ", var);
	}
	else
	{
		printf("w%d ", var-ndim);
	}
}

void dump()
{
	printf("Basic:\n");
	int i;
	for(i = 0; i < ndim; i++)
	{
		printVariable(basic[i]);
	}
	printf("\n");
}

void pivot(int i)
{	
	printVariable(basic[i+1]);
	printf("\n");
	if(basic[i+1] == W(i+2))
	{
		basic[i+1] = Z(i+2);
	}
	else
	{
		basic[i+1] = W(i+2);
	}
}

void init(int var)
{
	if((root->next->value) <= m)
	{
		printf("w2\n");
		pivot(var);
		printf("w1\n");
	}
	else
	{
		printf("w1\n");
		pivot(var);
		printf("w2\n");
	}
}

int main(int argc, char** argv)
{
	readconf("m=");
	scanf("%d", &m);
	readconf("n=");
	scanf("%d", &n);
	readconf("labels:");
	ndim = 2+m+n;
	
	basic = (int*)malloc(ndim * sizeof(int));
	
	/*Initialize the array of basic variables*/
	int i;
	for(i = 0; i < 2+m+n; i++)
	{
		basic[i] = W(i+1);
	}
	
	int var;
	count = 0;
	
	/*read the labels in and store them in a linked list*/
	root = malloc(sizeof(node));
	struct node* next = root;
	struct node* prev = root;
	while(scanf("%d", &var) != EOF)
	{
		next->value = var;
		next->next = malloc(sizeof(node));
		if(count == 1)
		{
			/*Let the second element be empty*/
			prev = next;
			next->next = malloc(sizeof(node));
			next = next->next;
			next->value = var;
			next->next = malloc(sizeof(node));
		}
		prev = next;
		next = next->next;
		count++;
	}
	free(prev->next);
	prev->next = NULL;
	
	/*Swap the last variable for the second*/
	struct node* sec = root->next;
	sec->value = prev->value;
	
	/*Delete the last element in the list*/
	prev = root;
	next = root;
	while(next->next != NULL)
	{
		prev = next;
		next = next->next;
	}
	free(prev->next);
	prev->next = NULL;
	
	/*Convert and print the new sequence*/
	next = root;
	count = 0;
	while(next != NULL)
	{
		if(count == 0)
			init(next->value);
		else
			pivot(next->value);
		count++;
		
		next = next->next;
	}
	printf("z0\n");
	
	free(basic);
	return 0;
}