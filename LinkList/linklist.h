/**********************************************************************/
/*   Copyright (C) Muduo,2013-2014                                    */
/*   FileName              : linklist.h                               */
/*   Author                : Muduo                                    */
/*   Module Name           : linklist                                 */
/*   Language              : C                                        */
/*   Target Environment    : Any                                      */
/*   Date of First Release : 2013/09/16                               */
/*   Description           : A common linklist for all                */
/**********************************************************************/

/*
 *  Revision Log:
 *	
 *  Create by Muduo,2013/09/16
 *  Complete and Debug ,2013/09/17
 *
 */

#ifndef _LINKLIST_H
#define _LINKLIST_H

#include <Windows.h>

#define SUCCESS ((void*)0)
#define FAILURE ((void*)1)

/* members: data    -> any type
 *          next    -> point to next node
 */
typedef struct linkNode
{
	void *data;
	struct linkNode *next;
}tLinkNode;

/* members: count    -> the count of current list
 *          dataCmp  -> decide whether equal
 *          handle   -> when iterative the linklist ,it will be called
 *          head     -> the first node of the list
 */
typedef struct linkList
{
	int count;
	int (*dataCmp)(void *currData,void *find);
	void (*handle)(void *currData);
	tLinkNode *head;
	CRITICAL_SECTION lock;
}tLinkList;

/* params: self    -> current variable
 *         dataCmp -> you own compare function
 *         handle  -> when iterative the linklist will call it
 */
void  initLinkList(struct linkList *self , void *dataCmp,void *handle);

/* params: self    -> current variable
 *         data    -> data to be inserted
 *         size    -> the size of your data
 */
void *insertData(struct linkList *self,void *data , int size);

/* params: self    -> current variable
 *         find    -> the string you want to find and delete
 */
void *deleteData(struct linkList *self,void *find);

/* params: self    -> current variable
 *         find    -> the string you want to find to update
 *         newData -> data to be update
 *         size    -> the size of your data
 */
void *updateData(const struct linkList *self,void *find , void *newData ,int size);

/* params: self    -> current variable
 *         find    -> the string you want to find to query
 */
void *queryData(const struct linkList *self,void *find);

/* params: self    -> current variable ,you want to iterative
 */
void iterativeLinkList(const struct linkList *self);

#endif