/* * * * * * * * * * * * * * * * * */
/* BTree.h * * * * * * * * * * * * */
/* Created by: Jordan Bonecutter * */
/* 13 November 2018  * * * * * * * */
/* * * * * * * * * * * * * * * * * */

#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include "StructHelper.h"

// Typedef Btree
typedef void BTree;

// BTree Functions
	// Alloc
BTree *newBTree(const StructHelper *helper);
	// Release
void releaseBTree(BTree *btree);
	// Accessors
void *getObjectWithCode(BTree *tree, long code);
void *getObjectWithComparator(BTree *tree, comparator compare);
unsigned long getSize(BTree *tree);
	// Mutors
void appendObject(BTree *tree, void *data, long value);
void appendTree(BTree *tree, long value);
	// Misc
unsigned long discretizeBTree(BTree *);
unsigned char compareBTrees(BTree *, BTree *);
	// File helpers
int saveTree(BTree *tree);
BTree *resurrectTree(FILE *fp);

// StructHelper Conforming
void releaseBTreeConforming(void *data);
void *newBTreeConforming(void);
unsigned long discretizeBTreeComforming(void *data);
unsigned char compareBTreesConforming(void *data1, void *data2);

static const StructHelper BTreeHelper = {
	&releaseBTreeConforming,
	&newBTreeConforming,
	&discretizeBTreeConforming,
	&compareBTreesConforming
};

#endif
