/* rat.h
 * typedef Bool
 * computing with rationals
 * 22 Apr 2000
 */
#ifdef GLEMKE

#include "gmp.h"
#include "gmpwrap.h"

#endif
#include "mp.h"


#define MAXSTR 100

#ifndef TRUE
#define TRUE 1L
#endif
#ifndef FALSE
#define FALSE 0L
#endif

typedef int Bool;        /* Boolean value 0/1                   */

typedef struct 
{
	#ifdef GLEMKE
    gmpt        num;    /* numerator    */
    gmpt        den;    /* denominator  */
	#else
    mp        num;    /* numerator    */
    mp        den;    /* denominator  */
	#endif
}
Rat;

#ifdef GLEMKE

Rat ratinit();

void ratclear(Rat rat);

#endif

Rat itorat(int num, int den);

Rat ratfroma(char* str, const char* info, int j);

Rat atorat(char* str);

/* returns sum  a+b, normalized                         */
Rat ratadd (Rat a, Rat b);

/* returns quotient  a/b, normalized                    */
Rat ratdiv (Rat a, Rat b);

/* converts integer i to rational                       */
Rat ratfromi(int i);

/* computes gcd of integers  a  and  b,  0 if both 0 and stores the value in c  
int ratgcd(int a, int b);*/
#ifdef GLEMKE
void ratgcd(gmpt a, gmpt b, gmpt c);
#else
void ratgcd(mp a, mp b, mp c);
#endif

/* returns Boolean condition that a > b                 */
Bool ratgreat (Rat a, Rat b);

/* returns quotient  1/a, normalized only if  a  is     */
Rat ratinv (Rat a);

/* returns Boolean condition that a==b
 * a, b are assumed to be normalized
 */
Bool ratiseq (Rat a, Rat b);

/* returns product  a*b, normalized                     */
Rat ratmult (Rat a, Rat b);

/* returns -a, normalized only if a normalized          */
Rat ratneg (Rat a);

/* normalizes (make den>0, =1 if num==0)
 * and reduces by  gcd(num,den)
 */
Rat ratreduce (Rat a);

Rat maxrow(Rat* rat, int n);

Rat maxMatrix(Rat** rat, int m, int n);

/* converts rational  r  to string  s, omit den 1
 * s  must be sufficiently long to contain result
 * returns length of string
 */
int rattoa (Rat r, char *s);

/* converts rational  a  to  double                     */
double rattodouble (Rat a);
