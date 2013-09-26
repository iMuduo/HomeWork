/*****************************************************************************/
/*   Copyright (C) Muduo,2013-2014                                           */
/*   FileName              : studentList.c                                   */
/*   Author                : Muduo                                           */
/*   Module Name           : studentList                                     */
/*   Language              : C                                               */
/*   Target Environment    : Any                                             */
/*   Date of First Release : 2013/09/16                                      */
/*   Description           : A simple info manager use common linklist.h     */
/*****************************************************************************/

/*
 *  Revision Log:
 *	
 *  Create by Muduo,2013/09/17
 *  Complete and Debug ,2013/09/17
 *
 */

#include "linklist.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "linklist_ext.h"
#include <MMSystem.h>

#define TRUE 1
#define FALSE 0
#define StudentList tLinkListExt

/* members: id    -> identify of student
 *          name  -> name to student
 */
typedef struct {
	int id;
	char name[20];
}tStudent;

/*my own cmp function */
int dataCmp(void *currData,void *find)
{
	tStudent *curr = (tStudent *)currData;
	int *id = find;
	if(curr->id== *id) return TRUE;
	return FALSE;
}

/*my own iterative hanle function ,print curr data */
void handle(void *currData)
{
	if(currData == NULL)
		printf("data not exists!\n");
	else
	{
		tStudent *curr = (tStudent *)currData;
		printf("id : %d  name : %s\n",curr->id,curr->name);
	}
}


/*print the UI of curr program*/
void printUI()
{
	printf("              Welcome to use student info manager V2.0              \n");
	printf("                                                                    \n");
	printf("   MenuList:                                                        \n");
	printf("              1.insert command I ,like I(100,username)              \n");
	printf("              2.delete command D ,like D(100)                       \n");
	printf("              3.update command U ,like U(100,username)              \n");
	printf("              3.query  command Q ,like Q(100)                       \n");
	printf("              4.print  command P                                    \n");
	printf("              5.combin above with  space                            \n");
	printf("              6.clear command C                                     \n");
	printf("              7.goto version 1.0  command E                         \n");
	printf("                                                                    \n");
	printf("       if you hava any question,you may connact QQ:49668929         \n");
}

/*print the UI of curr program*/
void printUI1()
{
	printf("              Welcome to use student info manager V1.0              \n");
	printf("                                                                    \n");
	printf("   MenuList:                                                        \n");
	printf("              1.insert command I ,like I(100,username)              \n");
	printf("              2.delete command D ,like D(100)                       \n");
	printf("              3.update command U ,like U(100,username)              \n");
	printf("              3.query  command Q ,like Q(100)                       \n");
	printf("              4.print  command P                                    \n");
	printf("              5.combin above with  space                            \n");
	printf("              6.clear command C                                     \n");
	printf("              7.end command E                                       \n");
	printf("                                                                    \n");
	printf("       if you hava any question,you may connact QQ:49668929         \n");
}

void version1()
{
	
	/* variable: studentList    -> curr list
	 *           student        -> as a tmp variable to save curr info
	 *           commands       -> combine command you want to exe
	 *           id             -> analyze id of student in cmd
	 *           name           -> analyze name of student in cmd
	 *           cmd            -> analyze sub command in commande,split with  
	 *           flags          -> analyze command
	 */
	tLinkList *studentList=(tLinkList *)malloc(sizeof(tLinkList));
	tStudent student;
	char commands[1000],id[10],name[20], *cmd,flag;
	int pos,i;
	LARGE_INTEGER start,stop,frequency;

	QueryPerformanceFrequency(&frequency);/* get frequency of cpu each 1s*/
	/* init list with my self define function then print program UI*/
	initLinkList(studentList,dataCmp,handle);
	printUI1();

	/* */
	for (i=0;i<100000;i++)
	{
		student.id=i;
		sprintf(student.name,"student %d",i);
		insertData(studentList,&student,sizeof(student));
	}
	/* loop to deal with commands*/
	while(TRUE)
	{
		scanf("%s",commands);
		cmd=strtok(commands," ");
		/* loop to deal with command, split with  */
		do
		{
			/*analyze curr command to get id and name*/
			flag=cmd[0];
			if(strchr(cmd,',') !=NULL)
			{
					pos=strchr(cmd,',')-cmd;
					strncpy(id,cmd+2,pos-1);
					id[pos-2]='\0';
					strcpy(name,cmd+pos+1);
					name[strlen(name)-1]='\0';
					student.id = atoi(id);
					strcpy(student.name,name);
			}
			else
			{
					strcpy(id,cmd+2);
					id[strlen(id)-1]='\0';
					student.id = atoi(id);				
			}

			/* both upper and lower can be executed*/
			switch(toupper(flag))
			{
				case 'I' :
					insertData(studentList,&student,sizeof(tStudent));
					break;
				case 'D' :
					if(deleteData(studentList,&student)==SUCCESS)
						printf("%s deletes successfully!\n",id);
					else
						printf("%s not exists in the list!\n",id);
					break;				
				case 'U' :
					updateData(studentList,&student,&student.id,sizeof(tStudent));
					break;				
				case 'Q' :
					/* query and print the data*/
					QueryPerformanceCounter(&start);
					handle(queryData(studentList,&student.id));
					QueryPerformanceCounter(&stop);
					printf("cost ticks :%d ns\n",(stop.QuadPart-start.QuadPart)*1000000/frequency.QuadPart);
					break;				
				case 'P' :
					iterativeLinkList(studentList);
					break;
				case 'C' :
					system("cls");
					printUI1();
					break;
				case 'E' :
					exit(0);
					break;
				default:
					printf("command error ,please try again !\n");
			}
			cmd=strtok(NULL," ");
		}while(cmd != NULL);
	}
	system("pause");
}

main()
{
	
	/* variable: studentList    -> curr list
	 *           student        -> as a tmp variable to save curr info
	 *           commands       -> combine command you want to exe
	 *           id             -> analyze id of student in cmd
	 *           name           -> analyze name of student in cmd
	 *           cmd            -> analyze sub command in commande,split with  
	 *           flags          -> analyze command
	 */
	StudentList *studentList=(StudentList *)malloc(sizeof(StudentList));
	tStudent student;
	char commands[1000],id[10],name[20], *cmd,flag;
	int pos,i;
	LARGE_INTEGER start,stop,frequency;

	QueryPerformanceFrequency(&frequency);/* get frequency of cpu each 1s*/
	/* init list with my self define function then print program UI*/
	initLinkListExt(studentList,dataCmp,handle);
	printUI();

	/* */
	for (i=0;i<100000;i++)
	{
		student.id=i;
		sprintf(student.name,"student %d",i);
		insertDataExt(studentList,&student,sizeof(student));
	}
	/* loop to deal with commands*/
	while(TRUE)
	{
		scanf("%s",commands);
		cmd=strtok(commands," ");
		/* loop to deal with command, split with  */
		do
		{
			/*analyze curr command to get id and name*/
			flag=cmd[0];
			if(strchr(cmd,',') !=NULL)
			{
					pos=strchr(cmd,',')-cmd;
					strncpy(id,cmd+2,pos-1);
					id[pos-2]='\0';
					strcpy(name,cmd+pos+1);
					name[strlen(name)-1]='\0';
					student.id = atoi(id);
					strcpy(student.name,name);
			}
			else
			{
					strcpy(id,cmd+2);
					id[strlen(id)-1]='\0';
					student.id = atoi(id);				
			}

			/* both upper and lower can be executed*/
			switch(toupper(flag))
			{
				case 'I' :
					insertDataExt(studentList,&student,sizeof(tStudent));
					break;
				case 'D' :
					if(deleteDataExt(studentList,&student)==SUCCESS)
						printf("%s deletes successfully!\n",id);
					else
						printf("%s not exists in the list!\n",id);
					break;				
				case 'U' :
					updateDataExt(studentList,&student,&student.id,sizeof(tStudent));
					break;				
				case 'Q' :
					/* query and print the data*/
					QueryPerformanceCounter(&start);
					handle(queryDataExt(studentList,&student.id));
					QueryPerformanceCounter(&stop);
					printf("cost ticks :%d ns\n",(stop.QuadPart-start.QuadPart)*1000000/frequency.QuadPart);
					break;				
				case 'P' :
					iterativeLinkListExt(studentList);
					break;
				case 'C' :
					system("cls");
					printUI();
					break;
				case 'E' :
					version1();
					break;
				default:
					printf("command error ,please try again !\n");
			}
			cmd=strtok(NULL," ");
		}while(cmd != NULL);
	}
	system("pause");
}