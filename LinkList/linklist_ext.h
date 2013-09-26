/**********************************************************************/
/*   Copyright (C) Muduo,2013-2014                                    */
/*   FileName              : linklist_ext.h                           */
/*   Author                : Muduo                                    */
/*   Module Name           : linklist_ext                             */
/*   Language              : C                                        */
/*   Target Environment    : Any                                      */
/*   Date of First Release : 2013/09/26                               */
/*   Description           : A ext linklist for all                   */
/**********************************************************************/

/*
 *  Revision Log:
 *	
 *  Create by Muduo,2013/09/26
 *  Complete and Debug 
 *
 */
#ifndef _LINKLIST_EXT_H
#define _LINKLIST_EXT_H
#define PROTIMES 100
#include "linklist.h"

typedef struct{
	int count;
	tLinkList headArr[PROTIMES];
}tLinkListExt;

/* params: self    -> current variable
 *         dataCmp -> you own compare function
 *         handle  -> when iterative the linklist_ext will call it
 */
void  initLinkListExt(tLinkListExt *self , void *dataCmp,void *handle);

/* params: self    -> current variable
 *         data    -> data to be inserted
 *         size    -> the size of your data
 */
void *insertDataExt(tLinkListExt *self,void *data , int size);

/* params: self    -> current variable
 *         find    -> the string you want to find and delete
 */
void *deleteDataExt(tLinkListExt *self,void *find);

/* params: self    -> current variable
 *         find    -> the string you want to find to update
 *         newData -> data to be update
 *         size    -> the size of your data
 */
void *updateDataExt(tLinkListExt *self,void *find , void *newData ,int size);

/* params: self    -> current variable
 *         find    -> the string you want to find to query
 */
void *queryDataExt(const tLinkListExt *self,void *find);

/* params: self    -> current variable ,you want to iterative
 */
void iterativeLinkListExt(const tLinkListExt *self);
#endif
