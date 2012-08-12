/* rat.h
 * typedef Bool
 * computing with rationals
 * 22 Apr 2000
 * Author: Bernhard von Stengel  stengel@maths.lse.ac.uk
 */
#ifndef RAT_H
#define RAT_H

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

typedef struct /* GSoC12: Tobenna Peter, Igwe (Edited) */
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

/* Initialise a rational number and returns it */
/* GSoC12: Tobenna Peter, Igwe */
Rat ratinit();

/* Frees the memory occupied by a rational number */
/* GSoC12: Tobenna Peter, Igwe */
void ratclear(Rat rat);

#endif

/* Creates a rational number from two integers */
Rat itorat(int num, int den);

/* converts integer i to rational                       */
Rat ratfromi(int i);

#ifdef GLEMKE
/* Create a rational number from two gmp numbers *//* GSoC12: Tobenna Peter, Igwe */
Rat gmptorat(gmpt num, gmpt den);
/* Create a rational number from one gmp number *//* GSoC12: Tobenna Peter, Igwe */
Rat ratfromgmp(gmpt a);
#else
/* Create a rational number from two mp numbers *//* GSoC12: Tobenna Peter, Igwe */
Rat mptorat(mp num, mp den);
/* Create a rational number from one mp number *//* GSoC12: Tobenna Peter, Igwe */
Rat ratfrommp(mp a);
#endif

/* Parses a string that of the format "x", "x/y" and "x.y"
 * and returns the equivalent rational numbers */
/* GSoC12: Tobenna Peter, Igwe */
Rat ratfroma(char* str, const char* info, int j);

/* returns sum  a+b, normalized                         */
Rat ratadd (Rat a, Rat b);

/* returns quotient  a/b, normalized                    */
Rat ratdiv (Rat a, Rat b);

/* returns product  a*b, normalized                     */
Rat ratmult (Rat a, Rat b);

/* returns -a, normalized only if a normalized          */
Rat ratneg (Rat a);

/* normalizes (make den>0, =1 if num==0)
 * and reduces by  gcd(num,den)
 */
Rat ratreduce (Rat a);

/* computes gcd of integers  a  and  b,  0 if both 0 and stores the value in c*/
/* GSoC12: Tobenna Peter, Igwe */
#ifdef GLEMKE
void ratgcd(gmpt a, gmpt b, gmpt c);
#else
void ratgcd(mp a, mp b, mp c);
#endif

/* returns quotient  1/a, normalized only if  a  is     */
Rat ratinv (Rat a);

/* returns Boolean condition that a > b                 */
Bool ratgreat (Rat a, Rat b);

/* returns Boolean condition that a==b
 * a, b are assumed to be normalized
 */
Bool ratiseq (Rat a, Rat b);

/* Returns the maximum element in an array of n Rat elements */
/* GSoC12: Tobenna Peter, Igwe */
Rat maxrow(Rat* rat, int n);

/* Returns the maximum element in an mxn matrix of Rat elements */
/* GSoC12: Tobenna Peter, Igwe */
Rat maxMatrix(Rat** rat, int m, int n);

/* converts rational  r  to string  s, omit den 1
 * s  must be sufficiently long to contain result
 * returns length of string
 */
int rattoa (Rat r, char *s);

/* converts rational  a  to  double                     */
double rattodouble (Rat a);

#endif