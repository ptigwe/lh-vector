/* lemke.h
 * 16 Apr 2000
 * declarations for lcp solver
 * Author: Bernhard von Stengel  stengel@maths.lse.ac.uk
 */

/* #include before:  rat.h       */
#ifndef LEMKE_H
#define LEMKE_H

#define MAXLCPDIM 2000       /* max LCP dimension                       */
#define INFOSTRINGLENGTH 8   /* string naming vars, e.g. "z0", "w187"   */
#define LCPSTRL  60          /* length of string containing LCP entry   */

extern int nrows;
extern int ncols;
extern int k;
extern int k2;
extern Rat** payoffA;
extern Rat** payoffB;

/* LCP input data                                               */
extern  Rat **lcpM;             /* LCP Matrix                   */
extern  Rat *rhsq;              /* right hand side  q           */
extern  Rat *vecd;              /* LCP covering vector  d       */
extern  int lcpdim;             /* LCP dimension                */

/* LCP result data                                              */
extern  Rat  *solz;             /* LCP solution  z  vector      */
/* no. of Lemke pivot iterations, including the first to pivot z0 in    */
extern  int  pivotcount;

int vartoa(int v, char s[]);

/* allocate and initialize with zero entries an LCP of dimension  n
 * this is the only method changing  lcpdim  
 * exit with error if fails, e.g. if  n  not sensible
 */
void setlcp(int n);

/* output the LCP as given      */
void outlcp (void);

/* flags for  runlemke  */
typedef struct
{
    int   maxcount  ;   /* max no. of iterations, infinity if 0         */
    int   bdocupivot;   /* Y/N  document pivot step                     */
    int   binitabl ;    /* Y/N  output entire tableau at beginning/end  */
    int   bouttabl  ;   /* Y/N  output entire tableau at each step      */
    int   boutsol   ;   /* Y/N  output solution                         */
    int   binteract ;   /* Y/N  interactive pivoting                    */
    int   blexstats ;   /* Y/N  statistics on lexminratio tests         */
    int   interactcount;/* Number of interactive entries                *//* GSoC12: Tobenna Peter, Igwe */
	int   binitmethod;  /* Used to select the initialisation method     *//* GSoC12: Tobenna Peter, Igwe */
    int   boutinvAB;	/* Y/N  output inverse of A_B                   *//* GSoC12: Tobenna Peter, Igwe */
	int   bisArtificial;/* If the current equilibrium is artificial     *//* GSoC12: Tobenna Peter, Igwe */
}Flagsrunlemke;

/* solve LCP via Lemke's algorithm,
 * solution in  solz [0..lcpdim-1]
 * exit with error if ray termination
 */
void runlemke(Flagsrunlemke flags);

/* Compute all equilibria */
/* GSoC12: Tobenna Peter, Igwe */
void computeEquilibria(Flagsrunlemke flags);

#endif