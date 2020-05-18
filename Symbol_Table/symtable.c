#include<stdio.h>

typedef struct symtable_ele
{
	char name[50];
	char class[15];
	int scope;
	int declared;
	int latest_occurence;
	//int isdeclared;
	char id_value[10];
}symtable_ele;

typedef struct symtable
{
	symtable_ele table[500];
}symtable;

symtable symt;
int top=-1;
char currid[50];
//char ids_array[100][50];
//int ids_top=-1;
//char ids_value[100][10];


/*void insert_ids(char* id)
{
	strcpy(ids_array[ids_top++],id);
}

int find_ids_index(char* id)
{
	for(int i=0;i<=ids_top;i++)
	{
		if(strcmp(ids_array[i],id)==0)
		{
			return i;
		}
	}
	return -1;
}*/

int find_index(char* name,int isparam,int isfunc)
{
	for(int i=0;i<=top;i++)
	{
		if(isfunc==1)
		{
			if(strcmp(symt.table[i].name,name)==0 && strcmp(symt.table[i].class,"Function")==0)
				return i;
		}
		if(isparam==1)
		{
			if(strcmp(symt.table[i].name,name)==0 && strcmp(symt.table[i].class,"Parameter")==0)
				return i;
		}
		if(isparam==0 && isfunc==0)
		{
			if(strcmp(symt.table[i].name,name)==0 && strcmp(symt.table[i].class,"Variable")==0)
				return i;
		}
	}
	return -1;
}

void print_table()
{
	printf("%-20s\t%-20s\t%-20s\t%-20s\t%-20s\t%-50s\n","Name","Class","Scope","Declared Line Number","Latest Occurence Line Number","Value");
	for(int i=0;i<=top;i++)
	{
		printf("%-20s\t%-20s\t%-20d\t%-20d\t%-20d\t%-50s\n",symt.table[i].name,symt.table[i].class,symt.table[i].scope,symt.table[i].declared,symt.table[i].latest_occurence,symt.table[i].id_value);
	}
}

int isfunc=0;
int isparam=0;