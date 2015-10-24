/* Copyright 2015 Marc Volker Dickmann */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "src/scriptlang_core.h"
#include "src/scriptlang_mem.h"

static void sl_define_int (sl_core* mcore, struct sl_mem** first, char* mname, int mvalue)
{
	mem_insert (first, mcore->memcount, mcore->memcount, mvalue, "", mname);
	
	mcore->memcount++;
}

static void sl_define_str (sl_core* mcore, struct sl_mem** first, char* mname, char* mvalue)
{
	mem_insert (first, mcore->memcount, mcore->memcount, 0, mvalue, mname);
	
	mcore->memcount++;
}

static void sl_set_int (struct sl_mem** first, char* mname, int mvalue)
{
	mem_set_int (first, mvalue, mname);
}

static void sl_set_int_var (struct sl_mem** first, char* mname, char* mvalue)
{
	int sl_cache;
	
	mem_get_int (first, &sl_cache, mvalue);
	
	sl_set_int (first, mname, sl_cache);
}

static void sl_set_str (struct sl_mem** first, char* mname, char* mvalue)
{
	mem_set_str (first, mvalue, mname);
}

static void sl_set_str_var (struct sl_mem** first, char* mname, char* mvalue)
{
	char sl_cache[50];
	
	mem_get_str (first, sl_cache, sizeof (sl_cache), mvalue);
	
	sl_set_str (first, mname, sl_cache);
}

static void sl_printf (char* message)
{
	printf ("%s\n", message);
}

static void sl_printm (struct sl_mem** first, char* mname, char* mformat)
{
	int sl_int;
	char sl_str[100];
	
	sl_int = 0;
	
	if (utils_streq (mformat, "int") == 0)
	{
		mem_get_int (first, &sl_int, mname);
		
		printf ("%i\n", sl_int);
					
	}
	else if (utils_streq (mformat, "str") == 0)
	{
		mem_get_str (first, sl_str, sizeof (sl_str), mname);
				
		sl_printf (sl_str);
	}
}

static int read_file (char* filename)
{
	int sl_int;
	char line[SL_LINEMAX], sl_str[100], sl_name[50], sl_cache[100];
	char *token, *subtoken, *saveptr;
	FILE *sl_file;
	sl_core mcore;
	struct sl_mem *first = NULL;
	
	mcore.memcount = 0;
	
	sl_file = fopen (filename, "r");
	
	if (sl_file == NULL)
	{
		return -1;
	}
	
	while (fgets (line, sizeof (line), sl_file) != NULL)
	{
		strcpy (sl_str, "");
		strcpy (sl_name, "");
		strcpy (sl_cache, "");
		
		if (line[0] != '#')
		{
			token = strtok_r (line, SL_SEP, &saveptr);
		
			if (parser_get_str (token, "print", sl_str, sizeof (sl_str), SL_SEP, saveptr) == 0)
			{
				sl_printf (sl_str);
			}
			else if (parser_get_str (token, "printm", sl_cache, sizeof (sl_cache), SL_SEP, saveptr) == 0)
			{
				subtoken = strtok_r (sl_cache, SL_SEP_SUB, &saveptr);
			
				if (strlen (subtoken) < sizeof (sl_name))
				{
					strcpy (sl_name, subtoken);
				}
			
				subtoken = strtok_r (NULL, SL_SEP_SUB, &saveptr);
			
				if (strlen (subtoken) < sizeof (sl_str))
				{
					strcpy (sl_str, subtoken);
				}
			
				subtoken = strtok_r (NULL, SL_SEP_SUB, &saveptr);
				
				if (sl_name[0] != '$')
				{
					printf ("Names of variables starts with an $ !\n");
				}
				else
				{
					sl_printm (&first, sl_name, sl_str);
				}
			}
			else if (parser_get_str (token, "int", sl_cache, sizeof (sl_cache), SL_SEP, saveptr) == 0)
			{
				subtoken = strtok_r (sl_cache, SL_SEP_SUB, &saveptr);
			
				if (strlen (subtoken) < sizeof (sl_name))
				{
					strcpy (sl_name, subtoken);
				}
			
				subtoken = strtok_r (NULL, SL_SEP_SUB, &saveptr);
			
				if (isdigit (subtoken[0]) != 0)
				{
					sl_int = atoi (subtoken);
				}
			
				subtoken = strtok_r (NULL, SL_SEP_SUB, &saveptr);
			
				if (sl_name[0] != '$')
				{
					printf ("Names of variables starts with an $ !\n");
				}
				else
				{
					sl_define_int (&mcore, &first, sl_name, sl_int);
				}
			}
			else if (parser_get_str (token, "str", sl_cache, sizeof (sl_cache), SL_SEP, saveptr) == 0)
			{
				subtoken = strtok_r (sl_cache, SL_SEP_SUB, &saveptr);
			
				if (strlen (subtoken) < sizeof (sl_name))
				{
					strcpy (sl_name, subtoken);
				}
			
				subtoken = strtok_r (NULL, SL_SEP_SUB, &saveptr);
			
				if (strlen (subtoken) < sizeof (sl_str))
				{
					strcpy (sl_str, subtoken);
				}
			
				subtoken = strtok_r (NULL, SL_SEP_SUB, &saveptr);
			
				if (sl_name[0] != '$')
				{
					printf ("Names of variables starts with an $ !\n");
				}
				else
				{
					sl_define_str (&mcore, &first, sl_name, sl_str);
				}
			}
			else if (parser_get_str (token, "set", sl_cache, sizeof (sl_cache), SL_SEP, saveptr) == 0)
			{
				subtoken = strtok_r (sl_cache, SL_SEP_SUB, &saveptr);
			
				if (strlen (subtoken) < sizeof (sl_name))
				{
					strcpy (sl_name, subtoken);
				}
			
				subtoken = strtok_r (NULL, SL_SEP_SUB, &saveptr);
			
				if (strlen (subtoken) < sizeof (sl_str))
				{
					strcpy (sl_str, subtoken);
				}
			
				subtoken = strtok_r (NULL, SL_SEP_SUB, &saveptr);
			
				if (sl_name[0] != '$')
				{
					printf ("Names of variables starts with an $ !\n");
				}
				else if (sl_str[0] == '$')
				{
					sl_set_int_var (&first, sl_name, sl_str);
					sl_set_str_var (&first, sl_name, sl_str);
				}
				else
				{
					if (isdigit (sl_str[0]) != 0)
					{
						sl_set_int (&first, sl_name, atoi (sl_str));
					}
					
					sl_set_str (&first, sl_name, sl_str);
				}
			}	
		}
	}
	
	fclose (sl_file);
	
	mem_free_ll (&first);
	
	return 0;
}

int main (int argc, char* argv[])
{
	printf ("Scriptlang v. %s (C) 2015 Marc Volker Dickmann\n", P_VERSION);
	
	if (argc == 2)
	{
		read_file (argv[1]);
	}
	
	return 0;
}
