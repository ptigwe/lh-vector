/*
  * list.h
  * A list of equilibrium
  * Author: Tobenna Peter, Igwe  ptigwe@gmail.com
  */

#ifndef LIST_H
#define LIST_H

typedef struct node_t
{
	Equilibrium eq;
	int* link;
	struct node_t* next;
}node;

/* Creates a new node */
node* newnode(int n);

/*Finds and returns the location of an equilibrium in the list 
 Returns -1 if the equilibrium is not in the list*/
int contains(node* list, Equilibrium eq);

/* Adds the equilibrium to the list, and returns its index position
 * in the list. If the equilibrium already exists, it returns the 
 * index where it is stoeed, and doesn't add it. */
int addEquilibrium(node* list, Equilibrium eq);

/* Get node at index */
node* getNodeat(node* list, int n);

/* Computes the number of elements in the list */
int listlength(node* list);

/* Prints all the elements in the list */
void printlist(node* list);

#endif