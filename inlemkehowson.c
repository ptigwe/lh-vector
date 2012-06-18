/* inlemke.c
 * Lemke direct
 * 16 Apr 2000
 * options:
 *      -i      run pivoting interactively, suggested with  '-v'
 *      -v      verbose: output tableau at every pivoting step
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
        /*  atoi        */
#include <string.h>
	/*  strlen	*/
#include <getopt.h>
        /* getopt(), optarg, optopt     */

#include "alloc.h"
#include "col.h"
#include "rat.h"

#include "lemke.h"
       /* for lemke.h  */ 

static int n; 	/* LCP dimension here */

int m, n1, k;

FILE* lcpout;

/* max no of characters + 1 (for terminating '\0') 
 * of a string  s  declared as  char s[MAXSTR] 
 * to be read from stdin by readstr
 */
#define MAXSTR 100  

/*------------------ error message ----------------*/
void notimpl (char *info)
{
    fflush(stdout);
    fprintf(stderr, "Program terminated with error. %s\n", info);
    exit(1);
}

/*------------------ read-in routines --------------------------*/
/* reads string  s  from stdin, to fit  char s[MAXSTR]
 * if length >= MAXSTR-1  a warning is sent to stderr
 * returns EOF if EOF encountered, then  s  undefined
 */
int readstr (char *s)        
{
    int tmp;
    char fs[10];    /* MAXSTR must not exceed 7 decimal digits      */
    sprintf (fs, "%%%ds",MAXSTR-1);        /* generate format str   */
    tmp = scanf (fs, s);
    if (strlen(s)==MAXSTR-1)
        {
        fprintf(stderr, "Warning: input string\n%s\n", s);
        fprintf(stderr, 
        "has max length %d, probably read incompletely\n", MAXSTR-1);
        }
    return tmp;     /* is EOF if scanf encounters EOF               */
}

/* s  is a string of nonblank chars, which have to
 * match in that order the next nonblank  stdin  chars
 * readconf  complains and terminates if not
 */
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

/* reads  n  rationals into the array  v  of rationals 
 * terminates with error if EOF encountered earlier
 * info  denotes name of array for error information
 * array indices in error info called  1...n
 */
void readnrats (Rat *v, const char *info)
{
    char srat[MAXSTR];
    int j ;
    /*int num,den;*/
    
    for (j=0; j<n; j++)
        {
        if(readstr(srat)==EOF)
            {
            fprintf(stderr, "Missing input of %s[%d]\n", info, j+1);
            notimpl("");
            }
        /*atoaa(srat, snum, sden);
        num = atoi(snum);
        if (sden[0]=='\0') 
            den = 1;
        else
            {
            den = atoi(sden);
            if (den<1)
                {
                fprintf(stderr, "Warning: Denominator "); 
                fprintf(stderr, "%d of %s[%d] set to 1 since not positive\n", 
                        den, info, j+1);
                den = 1;  
                }
            }*/
        /*v[j].num = num ;
        v[j].den = den ;*/
		v[j] = ratfroma(srat, info, j);
        } 
}   /* end of readnrats  */

Rat ** A;
Rat ** B;
void setmatrices(int m, int n)
{
	T2ALLOC(A, m, n, Rat);
	T2ALLOC(B, m, n, Rat);
}

void freematrices(int m)
{
	FREE2(A, m);
	FREE2(B, m);
}

void readMatrices()
{
	/* read in  M   */
	int i;
	char info[10];
	
	readconf("A=");
	
	for (i=0; i<m; ++i)
	{
		sprintf(info, "A[%d]", i+1);
		n = n1;
		readnrats(A[i], info);
	}
	
	readconf("B=");
	
	for (i=0; i<m; ++i)
	{
		sprintf(info, "B[%d]", i+1);
		n = n1;
		readnrats(B[i], info);
	}
}

void readGame (void)
        /* reads LCP data  n, M, q, d  from stdin       */
{
    /* get problem dimension */
    readconf("m=");
    scanf("%d", &m);
    readconf("n=");
    scanf("%d", &n1);
	readconf("k=");
	scanf("%d", &k);
    
    setmatrices(m, n1);
    readMatrices();
}       /* end of reading in LCP data   */

Rat maxrow(Rat* rat, int n)
{
	int i;
	Rat Mrow = ratfromi(0);
	for(i = 0; i < n; ++i)
	{
		Mrow = ratgreat(Mrow,rat[i]) ? Mrow : rat[i];
	}
	char str[MAXSTR];
	rattoa(Mrow, str);
	printf("Mrow=%s\n", str);
	return Mrow;
}

Rat maxMatrix(Rat** rat, int m, int n)
{
	int i;
	int tmpm = m;
	int tmpn = n;
	Rat M = ratfromi(0);
	for(i = 0; i < tmpm; ++i)
	{
		Rat r = maxrow(rat[i], tmpn);
		M = ratgreat(M, r) ? M : r;
	}
	return M;
}

void complementMatrix(Rat** mat, Rat rat, int m, int n)
{
	int i;
	rat = ratneg(rat);
	for (i = 0; i < m; i++)
	{
		int j;
		for(j = 0; j < n; ++j)
		{
			mat[i][j] = ratneg(ratadd(mat[i][j], rat));
		}
	}
}

void convertlcpM()
{	
	n = m+n1+2;
    setlcp(n);
	int i;
	
	lcpM[0][0] = lcpM[0][1] = ratfromi(0);
	for(i = 0; i < m; ++i)
	{
		lcpM[0][i+2] = ratfromi(1);
	}
	for(i = 0; i < n1; ++i)
	{
		lcpM[0][i+2+m] = ratfromi(0);
	}
	
	lcpM[1][0] = lcpM[1][1] = ratfromi(0);
	for(i = 0; i < m; ++i)
	{
		lcpM[1][i+2] = ratfromi(0);
	}
	for(i = 0; i < n1; ++i)
	{
		lcpM[1][i+2+m] = ratfromi(1);
	}
	
	for(i = 0; i < m; ++i)
	{
		int j;
		for(j = 0; j < 2+m+n1; ++j)
		{
			if(j == 0)
			{
				lcpM[i+2][j] = ratfromi(-1);
			}
			else if (j > m+1)
			{
				lcpM[i+2][j] = A[i][j - (m+2)];
			}
			else
			{
				lcpM[i+2][j] = ratfromi(0);
			}
		}
	}
	
	for(i = 0; i < n1; ++i)
	{
		int j;
		for(j = 0; j < 2+m+n1; ++j)
		{
			if(j == 1)
			{
				lcpM[i+2+m][j] = ratfromi(-1);
			}
			else if (j > 1 && j < 2+m)
			{
				lcpM[i+2+m][j] = B[j - 2][i];
			}
			else
			{
				lcpM[i+2+m][j] = ratfromi(0);
			}
		}
	}
}

void convertq()
{
	rhsq[0] = rhsq[1] = ratfromi(-1);
	int i;
	for(i = 0; i < m+n1; i++)
	{
		rhsq[i+2] = ratfromi(0);
	}
}

void convertd()
{
	int i;
	for(i = 0; i < 2+m+n1; i++)
	{
		if(i == k+1)
		{
			vecd[i] = ratfromi(0);
		}
		else
		{
			vecd[i] = ratfromi(1);
		}
	}
}

void printlcpM()
{
	fprintf(lcpout, "n= %d\nM=\n", n);
	int i;
	for(i = 0; i < n; i++)
	{
		int j;
		for(j = 0; j < n; j++)
		{
			char str[MAXSTR];
			rattoa(lcpM[i][j], str);
			fprintf(lcpout, "%s ", str);
		}
		fprintf(lcpout, "\n");
	}
}

void printlcpq()
{
	fprintf(lcpout, "q= ");
	int i;
	for(i = 0; i < n; i++)
	{
		char str[MAXSTR];
		rattoa(rhsq[i], str);
		fprintf(lcpout, "%s ", str);
	}
}

void printlcpd()
{
	fprintf(lcpout, "\nd= ");
	int i;
	for(i = 0; i < n; i++)
	{
		char str[MAXSTR];
		rattoa(vecd[i], str);
		fprintf(lcpout, "%s ", str);
	}
}

void printLCP()
{
	printlcpM();
	printlcpq();
	printlcpd();
	fclose(lcpout);
}

void convert()
{	
	Rat o = ratfromi(1);
	
	Rat ma = maxMatrix(A, m, n);
	Rat a = ratfromi((int)ceil(rattodouble(ma)));
	a = (ratiseq(a, ma)) ? ratadd(a, o) : a;
	
	Rat mb = maxMatrix(B, m, n);
	Rat b = ratfromi((int)ceil(rattodouble(ma)));
	b = (ratiseq(b, mb)) ? ratadd(b, o) : b;
	
	complementMatrix(A, a, m, n);
	complementMatrix(B, b, m, n);
	convertlcpM();
	convertq();
	convertd();
	freematrices(m);
}

/* ---------------------- main ------------------------ */       
int main(int argc, char *argv[])
{
    int c;
    Flagsrunlemke flags;

    flags.maxcount   = 0;
    flags.bdocupivot = 1;
    flags.binitabl   = 1;
    flags.bouttabl   = 0;
    flags.boutsol    = 1;
    flags.binteract  = 0;
    flags.blexstats  = 1;

    /* parse options    */
    while ( (c = getopt (argc, argv, "if:v")) != -1)
        switch (c)
            {
            case 'i':
                flags.binteract  = 1;
                printf("Interactive flag set.\n");
                break;
			case 'f':
				lcpout = fopen(optarg, "w+");
				break;
            case 'v':
                flags.bouttabl   = 1;
                printf("Verbose tableau output.\n");
                break;
            case '?':
                if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Unknown option character `\\x%x'.\n",
                              optopt);
                return 1;
            default:
                abort ();
            }
    /* options are parsed and flags set */

	readGame();
	convert();
	if(lcpout != NULL)
	{
		printLCP();
	}
    runlemke(flags); 
    return 0;
}
