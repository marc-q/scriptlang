/* Copyright 2015 Marc Volker Dickmann */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "src/scriptlang_core.h"
#include "src/scriptlang_mem.h"

static void sl_define_int (sl_core* mcore, struct sl_mem** first, char* mname, int mvalue)
{
	if (mname[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
	}
	
	mem_insert (first, mcore->memcount, MEM_TYPE_INT, mvalue, "", mname);
	
	mcore->memcount++;
}

static void sl_define_str (sl_core* mcore, struct sl_mem** first, char* mname, char* mvalue)
{
	if (mname[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
	}
	
	mem_insert (first, mcore->memcount, MEM_TYPE_STR, 0, mvalue, mname);
	
	mcore->memcount++;
}

static void sl_define_function (sl_core* mcore, struct sl_mem** first, char* mname, int mseekpos)
{
	if (mname[0] == SL_SYM_VAR)
	{
		printf ("ERROR: Names of functions dont starts with an %c !\n", SL_SYM_VAR);
	}
	
	mem_insert (first, mcore->memcount, MEM_TYPE_INT, mseekpos, "", mname);
	
	mcore->memcount++;
}

static void sl_set_uni (struct sl_mem** first, char* mname, char* mvalue)
{
	if (mname[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
	}
	
	mem_set_uni (first, mvalue, mname);
}

static void sl_set_int (struct sl_mem** first, char* mname, int mvalue)
{
	if (mname[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
	}
	
	mem_set_int (first, mvalue, mname);
}

static void sl_set_str (struct sl_mem** first, char* mname, char* mvalue)
{
	if (mname[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
	}
	
	mem_set_str (first, mvalue, mname);
}

static void sl_cpy_uni (struct sl_mem** first, char* mname_to, char* mname_from)
{
	if (mname_to[0] != SL_SYM_VAR || mname_from[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
	}
	
	mem_cpy_uni (first, mname_to, mname_from);
}

static void sl_arithmetic_int (struct sl_mem** first, char* mname, int mvalue, int state)
{
	int sl_cache;
	
	if (mname[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
	}
	
	mem_get_int (first, &sl_cache, mname);
	
	switch (state)
	{
		case 0:
			sl_cache += mvalue;
			break;
		case 1:
			sl_cache -= mvalue;
			break;
		case 2:
			sl_cache *= mvalue;
			break;
		case 3:
			sl_cache /= mvalue;
			break;
		default:
			break;
	}
	
	sl_set_int (first, mname, sl_cache);
}

static void sl_arithmetic_int_var (struct sl_mem** first, char* mname, char* mvalue, int state)
{
	int sl_cache;
	
	mem_get_int (first, &sl_cache, mvalue);
	
	sl_arithmetic_int (first, mname, sl_cache, state);
}

static void sl_readm (struct sl_mem** first, char* mname, char* mformat)
{
	int sl_int;
	char sl_str[100];
	
	sl_int = 0;
	
	if (mname[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
	}
	else if (utils_streq (mformat, SL_WRD_INT) == 0)
	{
		scanf ("%i", &sl_int);
		
		mem_set_int (first, sl_int, mname);			
	}
	else if (utils_streq (mformat, SL_WRD_STR) == 0)
	{
		scanf ("%s", sl_str);
		
		mem_set_str (first, sl_str, mname);
	}
}

static int sl_if (struct sl_mem** first, char* mname, int mmode, char* mvalue, char* mformat)
{
	int sl_int, sl_int_cache;
	char sl_str[100], sl_str_cache[100];
	struct sl_mem* ptr = NULL;
	
	sl_int = sl_int_cache = 0;
	
	if (mname[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
	}
	else if (utils_streq (mformat, SL_WRD_INT) == 0)
	{	
		mem_get_int (first, &sl_int, mname);
		
		if (mvalue[0] == SL_SYM_VAR)
		{
			mem_get_int (first, &sl_int_cache, mvalue);
		}
		else if (isdigit (mvalue[0]) != 0)
		{
			sl_int_cache = atoi (mvalue);
		}
		
		switch (mmode)
		{
			case '<':
				if (sl_int < sl_int_cache)
				{
					return 0;
				}
				break;
			case '=':
				if (sl_int == sl_int_cache)
				{
					return 0;
				}
				break;
			case '>':
				if (sl_int > sl_int_cache)
				{
					return 0;
				}
				break;
			default:
				break;
		}
	}
	else if (utils_streq (mformat, SL_WRD_STR) == 0)
	{
		mem_get_str (first, sl_str, sizeof (sl_str), mname);
		
		if (mvalue[0] == SL_SYM_VAR)
		{
			mem_get_str (first, sl_str_cache, sizeof (sl_str_cache), mvalue);
		}
		else if (isalnum (mvalue[0]) != 0)
		{
			strcpy (sl_str_cache, mvalue);
		}
		
		if (utils_streq (sl_str, sl_str_cache) == 0)
		{
			return 0;
		}
	}
	
	return 1;
}

static void sl_printf (char* message)
{
	int len;
	
	len = strlen (message);
	
	if (strlen (message) > 1 && message[len-2] == '\\' && message[len-1] == 'n')
	{
		message[len-2] = ' ';
		message[len-1] = '\n';
	}
	
	printf ("%s", message);
}

static void sl_printm (struct sl_mem** first, char* mname, char* mformat)
{
	int sl_int;
	char sl_str[100];
	
	sl_int = 0;
	
	if (mname[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
	}
	else if (utils_streq (mformat, SL_WRD_INT) == 0)
	{
		mem_get_int (first, &sl_int, mname);
		
		printf ("%i", sl_int);
	}
	else if (utils_streq (mformat, SL_WRD_INTN) == 0)
	{
		mem_get_int (first, &sl_int, mname);
		
		printf ("%i\n", sl_int);
	}
	else if (utils_streq (mformat, SL_WRD_STR) == 0)
	{
		mem_get_str (first, sl_str, sizeof (sl_str), mname);
				
		sl_printf (sl_str);
	}
	else if (utils_streq (mformat, SL_WRD_STRN) == 0)
	{
		mem_get_str (first, sl_str, sizeof (sl_str), mname);
				
		printf ("%s\n", sl_str);
	}
}

static int read_file (char* filename)
{
	int i, sl_argc, sl_ifstate, sl_funcstate, sl_seekpos, sl_preseekpos;
	char line[SL_LINEMAX], sl_cache[100], sl_function[50], sl_args[4][100];
	char *token, *subtoken, *saveptr, *saveptrsub;
	FILE *sl_file;
	sl_core mcore;
	struct sl_mem *first = NULL;
	
	mcore.memcount = sl_ifstate = sl_funcstate = sl_seekpos = sl_preseekpos = 0;
	
	sl_file = fopen (filename, "r");
	
	if (sl_file == NULL)
	{
		return -1;
	}
	
	while (fgets (line, sizeof (line), sl_file) != NULL)
	{
		strcpy (sl_cache, "");
		
		for (i = 0; i < 4; i++)
		{
			strcpy (sl_args[i], "");
		}
				
		if (line[0] != '#' && utils_streq (line, "") != 0)
		{
			if (sl_funcstate == 1 || utils_streq (line, "fed\n") == 0)
			{
				if (sl_funcstate == 2)
				{
					fseek (sl_file, sl_preseekpos, SEEK_SET);
					sl_funcstate = 0;
				}
				else if (utils_streq (line, "fed\n") == 0)
				{
					sl_funcstate = 0;
				}
			}
			else if (sl_ifstate == 1 || utils_streq (line, "else\n") == 0)
			{
				if (sl_ifstate == 0)
				{
					sl_ifstate = 1;
				}
				else if (utils_streq (line, "fi\n") == 0 || utils_streq (line, "else\n") == 0)
				{
					sl_ifstate = 0;
				}
			}
			else if (strstr (line, ":") != NULL && strstr (line, ";") == NULL)
			{
				token = strtok_r (line, SL_SEP, &saveptr);
				
				if (parser_get_str (token, "print", sl_args[0], sizeof (sl_args[0]), SL_SEP, saveptr) == 0)
				{
					sl_printf (sl_args[0]);
				}
			}
			else if (strstr (line, ":") != NULL && strstr (line, ";") != NULL)
			{
				token = strtok_r (line, SL_SEP, &saveptr);
				
				if (strlen (token) < sizeof (sl_function))
				{
					strcpy (sl_function, token);
				}
				
				token = strtok_r (NULL, SL_SEP, &saveptr);
				
				if (strlen (token) < sizeof (sl_cache))
				{
					strcpy (sl_cache, token);
				}
				
				subtoken = strtok_r (sl_cache, SL_SEP_SUB, &saveptrsub);
				
				sl_argc = 0;
				while (subtoken != NULL)
				{
					if (strlen (subtoken) < sizeof (sl_args[0]))
					{
						strcpy (sl_args[sl_argc], subtoken);
					}
					
					subtoken = strtok_r (NULL, SL_SEP_SUB, &saveptrsub);
					sl_argc++;
				}
			
				if (utils_streq (sl_function, SL_WRD_INT) == 0)
				{
					sl_define_int (&mcore, &first, sl_args[0], atoi (sl_args[1]));
				}
				else if (utils_streq (sl_function, SL_WRD_STR) == 0)
				{
					sl_define_str (&mcore, &first, sl_args[0], sl_args[1]);
				}
				else if (utils_streq (sl_function, "set") == 0)
				{
					if (sl_args[1][0] == SL_SYM_VAR)
					{
						sl_cpy_uni (&first, sl_args[0], sl_args[1]);
					}
					else
					{
						sl_set_uni (&first, sl_args[0], sl_args[1]);
					}
				}
				else if (utils_streq (sl_function, "printm") == 0)
				{
					sl_printm (&first, sl_args[0], sl_args[1]);
				}
				else if (utils_streq (sl_function, "add") == 0)
				{
					if (sl_args[1][0] == SL_SYM_VAR)
					{
						sl_arithmetic_int_var (&first, sl_args[0], sl_args[1], 0);
					}
					else if (isdigit (sl_args[1][0]) != 0)
					{
						sl_arithmetic_int (&first, sl_args[0], atoi (sl_args[1]), 0);
					}
					else
					{
						printf ("ERROR: Not an integer!\n");
					}
				}
				else if (utils_streq (sl_function, "sub") == 0)
				{
					if (sl_args[1][0] == SL_SYM_VAR)
					{
						sl_arithmetic_int_var (&first, sl_args[0], sl_args[1], 1);
					}
					else if (isdigit (sl_args[1][0]) != 0)
					{
						sl_arithmetic_int (&first, sl_args[0], atoi (sl_args[1]), 1);
					}
					else
					{
						printf ("ERROR: Not an integer!\n");
					}
				}
				else if (utils_streq (sl_function, "mpl") == 0)
				{
					if (sl_args[1][0] == SL_SYM_VAR)
					{
						sl_arithmetic_int_var (&first, sl_args[0], sl_args[1], 2);
					}
					else if (isdigit (sl_args[1][0]) != 0)
					{
						sl_arithmetic_int (&first, sl_args[0], atoi (sl_args[1]), 2);
					}
					else
					{
						printf ("ERROR: Not an integer!\n");
					}
				}
				else if (utils_streq (sl_function, "div") == 0)
				{
					if (sl_args[1][0] == SL_SYM_VAR)
					{
						sl_arithmetic_int_var (&first, sl_args[0], sl_args[1], 3);
					}
					else if (isdigit (sl_args[1][0]) != 0)
					{
						sl_arithmetic_int (&first, sl_args[0], atoi (sl_args[1]), 3);
					}
					else
					{
						printf ("ERROR: Not an integer!\n");
					}
				}
				else if (utils_streq (sl_function, "read") == 0)
				{
					sl_readm (&first, sl_args[0], sl_args[1]);
				}
				else if (utils_streq (sl_function, "if") == 0)
				{
					if (sl_if (&first, sl_args[0], sl_args[1][0], sl_args[2], sl_args[3]) != 0)
					{
						sl_ifstate = 1;
					}		
				}
				else if (utils_streq (sl_function, "def") == 0)
				{
					sl_define_function (&mcore, &first, sl_args[0], ftell (sl_file));
					sl_funcstate = 1;	
				}
				else if (mem_get_int (&first, &sl_seekpos, sl_function) == 0)
				{
					sl_preseekpos = ftell (sl_file);
					fseek (sl_file, sl_seekpos, SEEK_SET);
					sl_funcstate = 2;
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
	printf ("Scriptlang v. %s (C) 2015 Marc Volker Dickmann\n\n", P_VERSION);
	
	if (argc == 2)
	{
		read_file (argv[1]);
	}
	
	return 0;
}
