/* * * * * * * * * * * * * * * * * */
/* BTree.h * * * * * * * * * * * * */
/* Created by: Jordan Bonecutter * */
/* 13 November 2018  * * * * * * * */
/* * * * * * * * * * * * * * * * * */

#include "BTree.h"
#include <stdlib.h>

#define unravel(x) ((struct btree *)x)

// Define tree element
struct bele
{
	void *pL;
	void *pR;
};

// Define tree
struct btree
{
	unsigned long size;
	bele *top;
	const StructHelper *itemHelper;
};

BTree *newBTree(const StructHelper *helper)
{
	// Helper must not be NULL!
	if(!helper)
	{
		return NULL;
	}
	
	// Alloc
	struct btree *ret = malloc(sizeof(struct btree));

	// Init
	ret->size = 0;
	ret->top = malloc(sizeof(struct bele));
	ret->top->pL = NULL;
	ret->top->pR = NULL;
	ret->itemHelper = helper;

	// Return 
	return ret;
}

void releaseBTree(BTree *btree)
{
	struct bele *lastBranch = NULL;

	while(1)
	{
		
	}
}
