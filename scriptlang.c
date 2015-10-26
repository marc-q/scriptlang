/* Copyright 2015 Marc Volker Dickmann */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

static void sl_define_float (sl_core* mcore, struct sl_mem** first, char* mname, float mvalue)
{
	if (mname[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
	}
	
	mem_insert (first, mcore->memcount, MEM_TYPE_FLOAT, mvalue, "", mname);
	
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
	
	mem_set_uni2 (first, mvalue, mname);
}

static void sl_cpy_uni (struct sl_mem** first, char* mname_to, char* mname_from)
{
	if (mname_to[0] != SL_SYM_VAR || mname_from[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
	}
	
	mem_cpy_uni (first, mname_to, mname_from);
}

static void sl_arithmetic (struct sl_mem** first, char* mname, sl_mem_var* mvar_two, int state)
{
	int mtype;
	sl_mem_var mvar;
	
	if (mname[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
	}
	
	mem_get_uni (first, &mvar, &mtype, mname);
	
	switch (mtype)
	{
		case MEM_TYPE_INT:
			switch (state)
			{
				case SL_ALU_ADD:
					mvar.v_int += mvar_two->v_int;
					break;
				case SL_ALU_SUB:
					mvar.v_int -= mvar_two->v_int;
					break;
				case SL_ALU_MPL:
					mvar.v_int *= mvar_two->v_int;
					break;
				case SL_ALU_DIV:
					mvar.v_int /= mvar_two->v_int;
					break;
				case SL_ALU_MOD:
					mvar.v_int %= mvar_two->v_int;
					break;
				default:
					break;
			}
			break;
		case MEM_TYPE_FLOAT:
			switch (state)
			{
				case SL_ALU_ADD:
					mvar.v_float += mvar_two->v_float;
					break;
				case SL_ALU_SUB:
					mvar.v_float -= mvar_two->v_float;
					break;
				case SL_ALU_MPL:
					mvar.v_float *= mvar_two->v_float;
					break;
				case SL_ALU_DIV:
					mvar.v_float /= mvar_two->v_float;
					break;
				case SL_ALU_MOD:
					/* Casts to int for now, thinking about limiting modulo to int vars. */
					mvar.v_float = (int)mvar.v_float % (int)mvar_two->v_float;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
	
	mem_set_uni (first, &mvar, mname);
}

static void sl_arithmetic_var (struct sl_mem** first, char* mname, char* mvalue, int state)
{
	int mtype;
	sl_mem_var mvar;
	
	mem_get_uni (first, &mvar, &mtype, mvalue);
	
	sl_arithmetic (first, mname, &mvar, state);
}

static void sl_randm (struct sl_mem** first, char* mname)
{
	sl_mem_var mvar;
	
	mvar.v_int = rand ();
	
	mem_set_uni (first, &mvar, mname);
}

static void sl_readm (struct sl_mem** first, char* mname)
{
	char sl_str[100];
	
	scanf ("%s", sl_str);
	
	sl_set_uni (first, mname, sl_str);
}

static int sl_if (struct sl_mem** first, char* mname, int mmode, char* mvalue)
{
	int mtype, mtype_two;
	struct sl_mem* ptr = NULL;
	sl_mem_var mvar, mvar_two;
	
	if (mname[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
	}
	
	mem_get_uni (first, &mvar, &mtype, mname);
	
	switch (mtype)
	{
		case MEM_TYPE_INT:
			if (mvalue[0] == SL_SYM_VAR)
			{
				mem_get_uni (first, &mvar_two, &mtype_two, mvalue);
			}
			else if (isdigit (mvalue[0]) != 0)
			{
				mvar_two.v_int = atoi (mvalue);
				mtype_two = MEM_TYPE_INT;
			}
			
			if (mtype != mtype_two)
			{
				printf ("ERROR: Variables have different types!\n");
				return 0;
			}
		
			switch (mmode)
			{
				case '<':
					if (mvar.v_int < mvar_two.v_int)
					{
						return 0;
					}
					break;
				case '=':
					if (mvar.v_int == mvar_two.v_int)
					{
						return 0;
					}
					break;
				case '>':
					if (mvar.v_int > mvar_two.v_int)
					{
						return 0;
					}
					break;
				default:
					break;
			}
			break;
		case MEM_TYPE_FLOAT:
			if (mvalue[0] == SL_SYM_VAR)
			{
				mem_get_uni (first, &mvar_two, &mtype_two, mvalue);
			}
			else if (isdigit (mvalue[0]) != 0)
			{
				mvar_two.v_float = atof (mvalue);
				mtype_two = MEM_TYPE_FLOAT;
			}
			
			if (mtype != mtype_two)
			{
				printf ("ERROR: Variables have different types!\n");
				return 0;
			}
		
			switch (mmode)
			{
				case '<':
					if (mvar.v_float < mvar_two.v_float)
					{
						return 0;
					}
					break;
				case '=':
					if (mvar.v_float == mvar_two.v_float)
					{
						return 0;
					}
					break;
				case '>':
					if (mvar.v_float > mvar_two.v_float)
					{
						return 0;
					}
					break;
				default:
					break;
			}
			break;
		case MEM_TYPE_STR:
			if (mvalue[0] == SL_SYM_VAR)
			{
				mem_get_uni (first, &mvar_two, &mtype_two, mvalue);
			}
			else if (isalnum (mvalue[0]) != 0)
			{
				strcpy (mvar_two.v_str, mvalue);
				mtype_two = MEM_TYPE_STR;
			}
			
			if (mtype != mtype_two)
			{
				printf ("ERROR: Variables have different types!\n");
				return 0;
			}
		
			if (utils_streq (mvar.v_str, mvar_two.v_str) == 0)
			{
				return 0;
			}
			break;
		default:
			break;
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

static int sl_printm (struct sl_mem** first, char* mname, char* mformat)
{
	int mtype;
	sl_mem_var mvar;
	
	mtype = 0;
	
	if (mname[0] != SL_SYM_VAR)
	{
		printf ("ERROR: Names of variables starts with an %c !\n", SL_SYM_VAR);
		return -1;
	}

	mem_get_uni (first, &mvar, &mtype, mname);

	if (utils_streq (mformat, SL_WRD_INT) == 0)
	{
		printf ("%i", mvar.v_int);
	}
	else if (utils_streq (mformat, SL_WRD_INTN) == 0)
	{
		printf ("%i\n", mvar.v_int);
	}
	else if (utils_streq (mformat, SL_WRD_FLOAT) == 0)
	{
		printf ("%f", mvar.v_float);
	}
	else if (utils_streq (mformat, SL_WRD_FLOATN) == 0)
	{
		printf ("%f\n", mvar.v_float);
	}
	else if (utils_streq (mformat, SL_WRD_STR) == 0)
	{		
		sl_printf (mvar.v_str);
	}
	else if (utils_streq (mformat, SL_WRD_STRN) == 0)
	{	
		printf ("%s\n", mvar.v_str);
	}
	
	return 0;
}

static int read_file (char* filename)
{
	int i, sl_argc, sl_ifstate, sl_funcstate, sl_seekpos, sl_preseekpos;
	char line[SL_LINEMAX], sl_cache[100], sl_function[50], sl_args[4][100];
	char *token, *subtoken, *saveptr, *saveptrsub;
	FILE *sl_file;
	sl_core mcore;
	sl_mem_var mvar;
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
			if (sl_funcstate == 1 || utils_streq (line, SL_WRD_FED) == 0)
			{
				if (sl_funcstate == 2)
				{
					fseek (sl_file, sl_preseekpos, SEEK_SET);
					sl_funcstate = 0;
				}
				else if (utils_streq (line, SL_WRD_FED) == 0)
				{
					sl_funcstate = 0;
				}
			}
			else if (sl_ifstate == 1 || utils_streq (line, SL_WRD_ELSE) == 0)
			{
				if (sl_ifstate == 0)
				{
					sl_ifstate = 1;
				}
				else if (utils_streq (line, SL_WRD_FI) == 0 || utils_streq (line, SL_WRD_ELSE) == 0)
				{
					sl_ifstate = 0;
				}
			}
			else if (strstr (line, SL_SYM_TKN) != NULL && strstr (line, SL_SYM_SUBTKN) == NULL)
			{
				token = strtok_r (line, SL_SEP, &saveptr);
				
				if (parser_get_str (token, SL_WRD_DEF, sl_args[0], sizeof (sl_args[0]), SL_SEP, saveptr) == 0)
				{
					/* Until we intodruce args, we dont need more than one arg for this. */
					sl_define_function (&mcore, &first, sl_args[0], ftell (sl_file));
					sl_funcstate = 1;
				}
				else if (parser_get_str (token, SL_WRD_PRINT, sl_args[0], sizeof (sl_args[0]), SL_SEP, saveptr) == 0)
				{
					sl_printf (sl_args[0]);
				}
				else if (parser_get_str (token, SL_WRD_READ, sl_args[0], sizeof (sl_args[0]), SL_SEP, saveptr) == 0)
				{
					sl_readm (&first, sl_args[0]);
				}
				else if (parser_get_str (token, SL_WRD_RAND, sl_args[0], sizeof (sl_args[0]), SL_SEP, saveptr) == 0)
				{
					sl_randm (&first, sl_args[0]);
				}
			}
			else if (strstr (line, SL_SYM_TKN) != NULL && strstr (line, SL_SYM_SUBTKN) != NULL)
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
				else if (utils_streq (sl_function, SL_WRD_FLOAT) == 0)
				{
					sl_define_float (&mcore, &first, sl_args[0], atof (sl_args[1]));
				}
				else if (utils_streq (sl_function, SL_WRD_STR) == 0)
				{
					sl_define_str (&mcore, &first, sl_args[0], sl_args[1]);
				}
				else if (utils_streq (sl_function, SL_WRD_SET) == 0)
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
				else if (utils_streq (sl_function, SL_WRD_PRINTM) == 0)
				{
					sl_printm (&first, sl_args[0], sl_args[1]);
				}
				else if (utils_streq (sl_function, SL_WRD_ADD) == 0)
				{
					if (sl_args[1][0] == SL_SYM_VAR)
					{
						sl_arithmetic_var (&first, sl_args[0], sl_args[1], SL_ALU_ADD);
					}
					else if (isdigit (sl_args[1][0]) != 0)
					{
						if (strstr (sl_args[1], ".") == NULL)
						{
							mvar.v_int = atoi (sl_args[1]);
						}
						else
						{
							mvar.v_float = atol (sl_args[1]);
						}
						
						sl_arithmetic (&first, sl_args[0], &mvar, SL_ALU_ADD);
					}
					else
					{
						printf ("ERROR: Not an integer!\n");
					}
				}
				else if (utils_streq (sl_function, SL_WRD_SUB) == 0)
				{
					if (sl_args[1][0] == SL_SYM_VAR)
					{
						sl_arithmetic_var (&first, sl_args[0], sl_args[1], SL_ALU_SUB);
					}
					else if (isdigit (sl_args[1][0]) != 0)
					{
						if (strstr (sl_args[1], ".") == NULL)
						{
							mvar.v_int = atoi (sl_args[1]);
						}
						else
						{
							mvar.v_float = atol (sl_args[1]);
						}
						
						sl_arithmetic (&first, sl_args[0], &mvar, SL_ALU_SUB);
					}
					else
					{
						printf ("ERROR: Not an integer!\n");
					}
				}
				else if (utils_streq (sl_function, SL_WRD_MPL) == 0)
				{
					if (sl_args[1][0] == SL_SYM_VAR)
					{
						sl_arithmetic_var (&first, sl_args[0], sl_args[1], SL_ALU_MPL);
					}
					else if (isdigit (sl_args[1][0]) != 0)
					{
						if (strstr (sl_args[1], ".") == NULL)
						{
							mvar.v_int = atoi (sl_args[1]);
						}
						else
						{
							mvar.v_float = atol (sl_args[1]);
						}
						
						sl_arithmetic (&first, sl_args[0], &mvar, SL_ALU_MPL);
					}
					else
					{
						printf ("ERROR: Not an integer!\n");
					}
				}
				else if (utils_streq (sl_function, SL_WRD_DIV) == 0)
				{
					if (sl_args[1][0] == SL_SYM_VAR)
					{
						sl_arithmetic_var (&first, sl_args[0], sl_args[1], SL_ALU_DIV);
					}
					else if (isdigit (sl_args[1][0]) != 0)
					{
						if (strstr (sl_args[1], ".") == NULL)
						{
							mvar.v_int = atoi (sl_args[1]);
						}
						else
						{
							mvar.v_float = atol (sl_args[1]);
						}
						
						sl_arithmetic (&first, sl_args[0], &mvar, SL_ALU_DIV);
					}
					else
					{
						printf ("ERROR: Not an integer!\n");
					}
				}
				else if (utils_streq (sl_function, SL_WRD_MOD) == 0)
				{
					if (sl_args[1][0] == SL_SYM_VAR)
					{
						sl_arithmetic_var (&first, sl_args[0], sl_args[1], SL_ALU_MOD);
					}
					else if (isdigit (sl_args[1][0]) != 0)
					{
						if (strstr (sl_args[1], ".") == NULL)
						{
							mvar.v_int = atoi (sl_args[1]);
						}
						else
						{
							mvar.v_float = atol (sl_args[1]);
						}
						
						sl_arithmetic (&first, sl_args[0], &mvar, SL_ALU_MOD);
					}
					else
					{
						printf ("ERROR: Not an integer!\n");
					}
				}
				else if (utils_streq (sl_function, SL_WRD_IF) == 0)
				{
					if (sl_if (&first, sl_args[0], sl_args[1][0], sl_args[2]) != 0)
					{
						sl_ifstate = 1;
					}		
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
	
	srand (time (NULL));
	
	if (argc == 2)
	{
		read_file (argv[1]);
	}
	
	return 0;
}
