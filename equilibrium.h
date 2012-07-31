/* Include rat.h before this file */
#ifndef EQUILIBRIUM_H
#define EQUILIBRIUM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "alloc.h"
#include "col.h"
#include "rat.h"

#ifdef GLEMKE
#include "gmp.h"
#include "gmpwrap.h"
#else
#include "mp.h"
#endif

typedef struct equilibrium
{
	#ifndef GLEMKE
	mp** A;
	mp *scfa;
	mp det;
	#else
	gmpt** A;
	gmpt* scfa;
	gmpt det;
	#endif
	
	int* bascobas;
	int* whichvar;
	int lcpdim;
}Equilibrium;

#ifndef GLEMKE
Equilibrium createEquilibrium(mp** A, mp* scfa, mp det, int* bascobas, int* whichvar, int dim);
#else
Equilibrium createEquilibrium(gmpt** A, gmpt* scfa, gmpt det, int* bascobas, int* whichvar, int dim);
#endif

void freeEquilibrium(Equilibrium eq);

void printEquilibrium(Equilibrium eq);

Rat* getStrategies(Equilibrium eq);

int equilibriumisEqual(Equilibrium e1, Equilibrium e2);

#endif