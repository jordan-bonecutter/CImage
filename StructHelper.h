/* * * * * * * * * * * * * * * * * */
/* StructHelper.h  * * * * * * * * */
/* Created by: Jordan Bonecutter * */
/* 26 October 2018 * * * * * * * * */
/* * * * * * * * * * * * * * * * * */

#ifndef STRUCTHELPER_H
#define STRUCTHELPER_H

// Return:
// 		void
typedef void 			(*releaser)			(void *data);

// Return:
// 		Pointer to newly allocated
// 		heap memory object
typedef void *			(*allocator)		(void);

// Return:
// 		A unique unsigned long value 
// 		corresponding to the specific
// 		instance of object passed (hash)
typedef unsigned long	(*discretizor)		(void *data);

// Return:
// 		0 if data1  > data2
// 		1 if data1 == data2
// 		2 if data1  < data2
typedef unsigned char 	(*objectComparator)	(void *data1, void *data2);

// Return:
// 		0 if discrete(data)  > value
// 		1 if discrete(data) == value
// 		2 if discrete(data)  < value
typedef unsigned char 	(*valueComparator)	(void *data, unsigned long value);

typedef struct
{
	releaser 			release;
	allocator 			alloc;
	discretizor 		dicrete;
	objectComparator 	objCompare;
	valueComparator		valCompare;
};

#endif
