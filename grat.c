/* rat.c 
 * computing with rationals
 * 27 Apr 2000
 */

#define GLEMKE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
	/* sprintf	*/
#include "rat.h"

Rat ratinit()
{
	Rat rat;
	ginit(rat.num);
	ginit(rat.den);
	return rat;
}

Rat ratclone(Rat rat)
{
	Rat r = ratinit();
	gset(r.num, rat.num);
	gset(r.den, rat.den);
	return r;
}

void ratclear(Rat rat)
{
	gclear(rat.num);
	gclear(rat.den);
}

Rat itorat(int num, int den)
{
	Rat r = ratinit();
	gitomp(num, r.num);
	gitomp(den, r.den);
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
	/* for improved precision in  ratadd(a, b)	*/
Rat ratadd (Rat a, Rat b)
{
    /*
    a.num = a.num * b.den + a.den * b.num;
    a.den *= b.den;
    return ratreduce(a);
    */

    gmpt num, den, x, y, t;
	Rat c = ratinit();
	
	ginit(num);
	ginit(den);
	ginit(x);
	ginit(y);
	ginit(t);

    /*itomp (a.num, num) ;*/
	gset(num, a.num);
    /*itomp (a.den, den) ;*/
	gset(den, a.den);
    /*itomp (b.num, x) ;*/
	gset(x, b.num);
    /*itomp (b.den, y) ;*/
	gset(y, b.den);
    gmulint (y, num, t);
	gset(num, t);
    gmulint (den, x, x);

    /*linint (num, 1, x, 1);*/
	gadd(t, num, x);
	gset(num, t);

    gmulint (y, den, den);
    greduce(num, den) ;
    /*mptoi( num, &a.num, 1 );
    mptoi( den, &a.den, 1 );*/
	gset(c.num, num);
	gset(c.den, den);
	
	gclear(num);
	gclear(den);
	gclear(x);
	gclear(y);
	gclear(t);
	
    return c ; 
}

Rat ratdiv (Rat a, Rat b)
{
    return ratmult(a, ratinv(b) );
}

Rat ratfromi(int i)
{
    Rat tmp = ratinit();
    /*tmp.num = i; */
	gitomp(i, tmp.num);
    /*tmp.den = 1; */
	gitomp(1, tmp.den);
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

void ratgcd(gmpt a, gmpt b, gmpt c)
{
	gmpt d, e;
	ginit(d);
	ginit(e);
	
	gset(d, a);
	gset(e, b);
	mpz_gcd(c, d, e);
	
	gclear(d);
	gclear(e);
}

Rat ratinv (Rat a)
{
	Rat a1 = ratclone(a);
	
    /*a.num = a.den ;*/
	gset(a1.num, a.den);
    /*a.den = x ;*/
	gset(a1.den, a.num);
	
    return a1;
}
Bool ratiseq (Rat a, Rat b)
{
	/*return (a.num == b.num && a.den == b.den);*/
	Rat a1 = ratclone(a);
	Rat b1 = ratclone(b);
	Rat c = ratadd(a1, ratneg(b1));
	
	int i = gzero(c.num);
	
	ratclear(a1);
	ratclear(b1);
	ratclear(c);
    return i;
}

Bool ratgreat (Rat a, Rat b)
{
	Rat a1 = ratclone(a);
	Rat b1 = ratclone(b);
    Rat c = ratadd(a1, ratneg(b1));

	int i = gpositive(c.num);
	
	ratclear(a1);
	ratclear(b1);
	ratclear(c);
    return i;
}

Rat ratmult (Rat a, Rat b)
{
	Rat a1 = ratclone(a);
	Rat b1 = ratclone(b);
    gmpt x;
	ginit(x);

    /* avoid overflow in intermediate product by cross-cancelling first
     */
    /*x = a.num ; */
	gset(x, a.num);
    /*a.num = b.num ;*/
	gset(a1.num, b.num);
    /*b.num = x ;*/
	gset(b1.num, x);
    a1 = ratreduce(a1);
    b1 = ratreduce(b1);
    /*a.num *= b.num;*/
	gmulint(a1.num, b1.num, x);
	gset(a1.num, x);
    /*a.den *= b.den;*/
	gmulint(a1.den, b1.den, x);
	gset(a1.den, x);
	
	gclear(x);
    return ratreduce(a1);        /* a  or  b  might be non-normalized    s*/
}

Rat ratneg (Rat a)
        /* returns -a                                           */
{
    /*a.num = - a.num;*/
	gchangesign(a.num);
    return  a;
}

Rat ratreduce (Rat a)
{
    if (gzero(a.num))
	{
		/*a.den = 1;*/
		gitomp(1, a.den);
	}
    else
	{
		gmpt div;
		gmpt c;
		ginit(div);
		ginit(c);
		if (gnegative(a.den))
		{
			/*a.den = -a.den;*/
			gchangesign(a.den);
			/*a.num = -a.num;*/
			gchangesign(a.num);
		}
		/*div = ratgcd(a.den, a.num);*/
		ratgcd(a.den, a.num, div);
		/*a.num = a.num/div;*/
		gexactdivint(a.num, div, c);
		gset(a.num, c);
		/*a.den = a.den/div;*/
		gexactdivint(a.den, div, c);
		gset(a.den, c);
		gclear(div);
		gclear(c);
	}
    return a;
}

int rattoa (Rat r, char *s)
{
	char str[MAXSTR];
    int l, a;
    /*l = sprintf(s, "%d", r.num);*/
	gmptoa(r.num, str);
    l = sprintf(s, "%s", str);
    /*if (r.den != 1)*/
	if(!gone(r.den))
    {
        /*a = sprintf(s+l, "/%d", r.den);*/
		gmptoa(r.den, str);
        a = sprintf(s+l, "/%s", str);
        l += a + 1;
    }
    return l;
}

double rattodouble(Rat a)
{
	int num, den;
	gmptoi(a.num, &num, 1);
	gmptoi(a.den, &den, 1);
    /*return (double) a.num / (double) a.den ;*/
	return (double)num / (double)den;
}
