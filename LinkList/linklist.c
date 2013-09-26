#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "linklist.h"

/* Init list  */
void  initLinkList(struct linkList *self , void *dataCmp,void *handle)
{
	self->count = 0;
	self->dataCmp = dataCmp;
	self->handle = handle;
	self->head = NULL;

	/*Init Critical Section*/
	InitializeCriticalSection(&self->lock);
}

/* may alter head, use critical section resolve */
void *insertData(struct linkList *self,void *data, int size)
{
	tLinkNode *node = (tLinkNode *)malloc(sizeof(tLinkNode));
	node->data = malloc(size);
	memcpy(node->data,data,size);

	/*Critical Section Begin*/
	EnterCriticalSection(&self->lock);

	node->next = self->head;
	self->head = node;
	self->count++;

	/*Critical Section End*/
	LeaveCriticalSection(&self->lock);

	return data;
}

/* may alter head, use critical section resolve */
void *deleteData(struct linkList *self,void *find)
{
	tLinkNode *curr , *pre;
	curr = pre = self->head;
	while(curr != NULL)
	{
		if(self->dataCmp(curr->data,find))
		{
			/*Critical Section Begin*/
			EnterCriticalSection(&self->lock);

			if(curr == pre)
				self->head = curr->next;
			else
				pre->next = curr->next;
			free(curr);
			self->count--;

			/*Critical Section End*/
			LeaveCriticalSection(&self->lock);

			return SUCCESS;
		}
		pre = curr;
		curr = curr->next;
	}
	return FAILURE;
}

/* alter nothing  */
void *updateData(const struct linkList *self,void *find , void *newData ,int size)
{
	tLinkNode *curr;
	curr =  self->head;
	while(curr != NULL)
	{
		if(self->dataCmp(curr->data,find))
		{
			free(curr->data);
			curr->data = malloc(size);
			memcpy(curr->data,newData,size);
			return SUCCESS;
		}
		curr = curr->next;
	}
	return FAILURE;
}

/* alter nothing  */
void *queryData(const struct linkList *self,void *find)
{
	tLinkNode *curr;
	curr =  self->head;
	while(curr != NULL)
	{
		if(self->dataCmp(curr->data,find))
			return curr->data;
		curr = curr->next;
	}
	return NULL;
}

/* alter nothing  */
void iterativeLinkList(const struct linkList *self)
{
	tLinkNode *curr;
	curr =  self->head;
	while(curr != NULL)
	{
		self->handle(curr->data);
		curr = curr->next;
	}
}