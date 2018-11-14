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
	bele *cL;
	bele *cR;
	bele *parent;
	void *data;
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
	ret->top->cL = NULL;
	ret->top->cR = NULL;
	ret->top->parent = NULL;
	ret->top->data = NULL;
	ret->itemHelper = helper;

	// Return 
	return ret;
}

void releaseBTree(BTree *btree)
{
	struct bele *curr = unravel(btree)->top->pL, *temp = NULL;

	// Traverse to the bottom of the
	// tree and release elements upwards
	while(unravel(btree)->size > 0)
	{
		// If the current branch 
		// is not at the bottom
		if(curr->pL || curr->pR)
		{
			// Prefer the left branch
			if(curr->pL)
			{
				curr = curr->pL;
			}
			else
			{
				curr = curr->pL;
			}
		}

		// If the current branch is a
		// bottom branch, delete it
		else
		{
			// Release the data
			unravel(btree)->itemHelper->release(curr->data);

			// Release the leaf data
			temp = curr->parent;
			if(temp->pL == curr)
			{
				free(temp->pL);
				temp->pL = NULL;
			}

			else
			{
				free(temp->pR);
				temp->pR = NULL;
			}

			unravel(btree)->size--;
			curr = temp;
		}
	}

	// Finally, free the whole tree
	free(btree);
}

void *getObjectWithCode(BTree *tree, unsigned long code, unsigned char codeLen)
{
	// Start at the top 
	// of the tree
	struct bele *ret = unravel(tree)->top;
	for(unsigned char n = 0; n < codeLen; n++)
	{
		// Go left or right depending 
		// on the provided code 
		if(code & 0x1)
		{
			if(!ret->pL)
			{
				return NULL;
			}
			ret = ret->pL;
		}
		
		else
		{
			if(!ret->pR)
			{
				return NULL;
			}
			ret = ret->pR;
		}

		// Shift the code down by one
		code >>= 1;
	}

	// Return the object
	return ret->data;
}

void *getObjectOfValue(BTree *btree, unsigned long code, valueComparator compare)
{

}
