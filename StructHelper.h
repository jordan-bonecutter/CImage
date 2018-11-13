/* * * * * * * * * * * * * * * * * */
/* StructHelper.h  * * * * * * * * */
/* Created by: Jordan Bonecutter * */
/* 26 October 2018 * * * * * * * * */
/* * * * * * * * * * * * * * * * * */

#ifndef STRUCTHELPER_H
#define STRUCTHELPER_H

typedef void 			(*releaser)		(void *data);
typedef void *			(*allocator)	(void);
typedef unsigned long	(*discretizor)	(void *data);
typedef unsigned char 	(*comparator)	(void *data1, void *data2);

typedef struct
{
	releaser 	release;
	allocator 	alloc;
	discretizor dicrete;
	comparator 	compare;
};

#endif
