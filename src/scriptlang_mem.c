/* Copyright 2015 Marc Volker Dickmann */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scriptlang_core.h"
#include "scriptlang_mem.h"

/*
	Function: mem_free_ll (struct sl_mem** first);
	Description: Free's all elements from a sl_mem linked list.
	InitVersion: 0.0.1
*/
void mem_free_ll (struct sl_mem** first)
{
	struct sl_mem* ptr = *first, *preptr;
	
	while (ptr != NULL)
	{
		preptr = ptr;
		ptr = ptr->next;
		free (preptr);
	}
}

/*
	Function: mem_insert (struct sl_mem** first, int n, int mid, int mvalue_int, char* mvalue_str, char* mname);
	Description: Inserts a new mem object with data.
	InitVersion: 0.0.1
*/
int mem_insert (struct sl_mem** first, int n, int mid, int mvalue_int, char* mvalue_str, char* mname)
{
	struct sl_mem *newobj = malloc (sizeof (struct sl_mem)), *preobj;
	
	if (newobj == NULL)
	{
		return -1;
	}
	
	newobj->n = n;
	newobj->m_id = mid;
	newobj->m_value_int = mvalue_int;
	newobj->next = NULL;
	
	if (strlen (mname) >= MEM_S_NAME || strlen (mvalue_str) >= MEM_S_VALUE)
	{
		return -2;
	}

	strcpy (newobj->m_name, mname);
	strcpy (newobj->m_value_str, mvalue_str);
	
	if (*first == NULL)
	{
		*first = newobj;
	}
	else
	{
		preobj = *first;
		
		while (1)
		{
			if (preobj->n == newobj->n)
			{
				free (newobj);
				break;
			}
			else if (preobj->next == NULL)
			{
				preobj->next = newobj;
				break;
			}
			else if (preobj->next->n > newobj->n)
			{
				newobj->next = preobj->next;
				preobj->next = newobj;
				break;
			}
			
			preobj = preobj->next;
		}
	}
	
	return 0;
}

/*
	Function: mem_remove (struct sl_mem** first, int id);
	Description: Removes a mem object!
	InitVersion: 0.0.1
*/
int mem_remove (struct sl_mem** first, int mid)
{
	struct sl_mem* ptr = *first, *pre = NULL;
	
	if (ptr == NULL)
	{
		return -1;
	}
	
	while (ptr != NULL)
	{
		if (ptr->m_id == mid)
		{
			if (ptr == *first)
			{
				*first = ptr->next;
				free (ptr);
			}
			else
			{
				pre->next = ptr->next;
				free (ptr);
			}
			
			break;
		}
		else
		{
			pre = ptr;
			ptr = ptr->next;
		}
	}
	
	return 0;
}

int mem_set_int (struct sl_mem** first, int mvalue, char* mname)
{
	int state;
	struct sl_mem* ptr = *first;
	
	state = 0;
	
	if (ptr == NULL)
	{
		return -1;
	}
	
	while (ptr != NULL)
	{
		if (utils_streq (ptr->m_name, mname) == 0)
		{
			ptr->m_value_int = mvalue;
			
			state = 1;
			
			break;
		}
		
		ptr = ptr->next;
	}
	
	if (state == 0)
	{
		printf ("Variable not found!\n");
	}
	
	return 0;
}

int mem_set_str (struct sl_mem** first, char* mvalue, char* mname)
{
	int state;
	struct sl_mem* ptr = *first;
	
	state = 0;
	
	if (ptr == NULL)
	{
		return -1;
	}
	
	while (ptr != NULL)
	{
		if (utils_streq (ptr->m_name, mname) == 0)
		{
			if (strlen (mvalue) < MEM_S_VALUE)
			{
				strcpy (ptr->m_value_str, mvalue);
				
				state = 1;
			}
			
			break;
		}
		
		ptr = ptr->next;
	}
	
	if (state == 0)
	{
		printf ("Variable not found!\n");
	}
	
	return 0;
}

int mem_get_int (struct sl_mem** first, int* out, char* mname)
{
	int state;
	struct sl_mem* ptr = *first;
	
	state = 0;
	
	if (ptr == NULL)
	{
		return -1;
	}
	
	while (ptr != NULL)
	{
		if (utils_streq (ptr->m_name, mname) == 0)
		{
			*out = ptr->m_value_int;
			
			state = 1;
			
			break;
		}
		
		ptr = ptr->next;
	}
	
	if (state == 0)
	{
		printf ("Variable not found!");
	}
	
	return 0;
}

int mem_get_str (struct sl_mem** first, char* out, size_t outsize, char* mname)
{
	struct sl_mem* ptr = *first;
	
	if (ptr == NULL)
	{
		return -1;
	}
	
	while (ptr != NULL)
	{
		if (utils_streq (ptr->m_name, mname) == 0)
		{
			if (strlen (ptr->m_value_str) < outsize)
			{
				strcpy (out, ptr->m_value_str);
			}
			
			break;
		}
		
		ptr = ptr->next;
	}
	
	if (strcmp (out, "") == 0)
	{
		strcpy (out, "Variable not found!");
	}
	
	return 0;
}
