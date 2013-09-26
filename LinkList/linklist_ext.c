#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "linklist_ext.h"

/* Init list  */
void  initLinkListExt(tLinkListExt *self , void *dataCmp,void *handle)
{
	int i;
	self->count = 0;
	for (i=0;i<PROTIMES;i++)
	{
		initLinkList(&(self->headArr[i]),dataCmp,handle);
	}
}

/* may alter head, use critical section resolve */
void *insertDataExt(tLinkListExt *self,void *data, int size)
{
	int pos=(*(int *)data) % PROTIMES;
	void *result=insertData(&(self->headArr[pos]),data,size);
	self->count++;
	return result;
}

/* may alter head, use critical section resolve */
void *deleteDataExt(tLinkListExt *self,void *find)
{
	int pos=(*(int *)find) % PROTIMES;
	void *result=deleteData(&(self->headArr[pos]),find);
	if (result == SUCCESS)
		self->count--;
	return result;
}

/* alter nothing  */
void *updateDataExt(const tLinkListExt *self,void *find ,void *newData ,int size)
{
	int pos=(*(int *)find) % PROTIMES;
	return updateData(&(self->headArr[pos]),find,newData,size);
}

/* alter nothing  */
void *queryDataExt(const tLinkListExt *self,void *find)
{
	int pos=(*(int *)find) % PROTIMES;
	return queryData(&(self->headArr[pos]),find);
}

/* alter nothing  */
void iterativeLinkListExt(const tLinkListExt *self)
{
	int i;
	for (i=0;i<PROTIMES;i++)
	{
		iterativeLinkList(&(self->headArr[i]));
	}
}