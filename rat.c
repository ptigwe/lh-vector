/* rat.c 
 * computing with rationals
 * 27 Apr 2000
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
	/* sprintf	*/
#include "rat.h"

	/* for improved precision in  ratadd(a, b)	*/

Rat itorat(int num, int den)
{
	Rat r;
	itomp(num, r.num);
	itomp(den, r.den);
	ratreduce(r);
	return r;
}

Rat parseRat(char* srat, const char* info, int j)
{
	char snum[MAXSTR], sden[MAXSTR];
	int num, den;
	
	atoaa(srat, snum, sden);
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
    }
	Rat r = itorat(num, den);
	return r;
}

Rat parseDecimal(char* srat, const char* info, int j)
{
	double x;
	int count;
	char* sub;
	
	sscanf(srat, "%lf", &x);
	
	sub = strchr(srat, '.');
	if(strchr(sub+1, '.') != NULL)
	{
		fprintf(stderr, "Error: Decimal ");
		fprintf(stderr, "%s of %s[%d] has more than one decimal point\n", srat, info, j);
		exit(1);
	}
	count = strlen(sub+1);
	
	int num = floor(x * pow(10, count));
	int den = pow(10, count);
	
	Rat rat = itorat(num, den);
	return rat;
}

Rat ratfroma(char* srat, const char* info, int j)
{
	char* pos;
	Rat rat;
	
	if((pos = strchr(srat, '.')) != NULL)
	{
		rat = parseDecimal(srat, info, j);
	}
	else
	{
		rat = parseRat(srat, info, j);
	}
	return rat;
}

Rat ratadd (Rat a, Rat b)
{
    /*
    a.num = a.num * b.den + a.den * b.num;
    a.den *= b.den;
    return ratreduce(a);
    */

    mp num, den, x, y, t;

    /*itomp (a.num, num) ;*/
	copy(num, a.num);
    /*itomp (a.den, den) ;*/
	copy(den, a.den);
    /*itomp (b.num, x) ;*/
	copy(x, b.num);
    /*itomp (b.den, y) ;*/
	copy(y, b.den);
    mulint (y, num, t);
	copy(num, t);
    mulint (den, x, x);
    linint (num, 1, x, 1);
    mulint (y, den, den);
    reduce(num, den) ;
    /*mptoi( num, &a.num, 1 );
    mptoi( den, &a.den, 1 );*/
	copy(a.num, num);
	copy(a.den, den);
    return a ; 
}

Rat ratdiv (Rat a, Rat b)
{
    return ratmult(a, ratinv(b) );
}

Rat ratfromi(int i)
{
    Rat tmp;
    /*tmp.num = i; */
	itomp(i, tmp.num);
    /*tmp.den = 1; */
	itomp(1, tmp.den);
    return tmp;
}

/*
int ratgcd(int a, int b)
{
    int c;
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (a < b) { c=a; a=b; b=c; }
    while (b != 0)
        {
        c = a % b;
        a = b ;
        b = c ;
        }
    return a;
}*/

void ratgcd(mp a, mp b, mp c)
{
	mp d;
	copy(c, a);
	copy(d, b);
	gcd(c, d);
}

Rat ratinv (Rat a)
{
    mp x;

    /*x = a.num ;*/
	copy(x, a.num);
    /*a.num = a.den ;*/
	copy(a.num, a.den);
    /*a.den = x ;*/
	copy(a.den, x);
    return a;
}
Bool ratiseq (Rat a, Rat b)
{
	/*return (a.num == b.num && a.den == b.den);*/
	mp c;
	itomp(1, c);
	int x = comprod(a.num, c, b.num, c);
	int y = comprod(a.den, c, b.den, c);
    return ((x == 0) && (y == 0));
}

Bool ratgreat (Rat a, Rat b)
{
    Rat c = ratadd(a, ratneg(b));
    return (positive(c.num));
}

Rat ratmult (Rat a, Rat b)
{
    mp x;

    /* avoid overflow in intermediate product by cross-cancelling first
     */
    /*x = a.num ; */
	copy(x, a.num);
    /*a.num = b.num ;*/
	copy(a.num, b.num);
    /*b.num = x ;*/
	copy(b.num, x);
    a = ratreduce(a);
    b = ratreduce(b);
    /*a.num *= b.num;*/
	mulint(a.num, b.num, x);
	copy(a.num, x);
    /*a.den *= b.den;*/
	mulint(a.den, b.den, x);
	copy(a.den, x);
    return ratreduce(a);        /* a  or  b  might be non-normalized    s*/
}

Rat ratneg (Rat a)
        /* returns -a                                           */
{
    /*a.num = - a.num;*/
	changesign(a.num);
    return  a;
}

Rat ratreduce (Rat a)
{
    if (zero(a.num))
	{
		/*a.den = 1;*/
		itomp(1, a.den);
	}
    else
	{
		mp div;
		mp c;
		if (negative(a.den))
		{
			/*a.den = -a.den;*/
			changesign(a.den);
			/*a.num = -a.num;*/
			changesign(a.num);
		}
		/*div = ratgcd(a.den, a.num);*/
		ratgcd(a.den, a.num, div);
		/*a.num = a.num/div;*/
		divint(a.num, div, c);
		copy(a.num, c);
		/*a.den = a.den/div;*/
		divint(a.den, div, c);
		copy(a.den, c);
	}
    return a;
}

int rattoa (Rat r, char *s)
{
	char str[MAXSTR];
    int l, a;
    /*l = sprintf(s, "%d", r.num);*/
	mptoa(r.num, str);
    l = sprintf(s, "%s", str);
    /*if (r.den != 1)*/
	if(!one(r.den))
    {
        /*a = sprintf(s+l, "/%d", r.den);*/
		mptoa(r.den, str);
        a = sprintf(s+l, "/%s", str);
        l += a + 1;
    }
    return l;
}

double rattodouble(Rat a)
{
	int num, den;
	mptoi(a.num, &num, 1);
	mptoi(a.den, &den, 1);
    /*return (double) a.num / (double) a.den ;*/
	return (double)num / (double)den;
}
