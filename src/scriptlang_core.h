#ifndef __SCRIPTLANG_CORE_H__
#define __SCRIPTLANG_CORE_H__

#define P_CMD "scriptlang"
#define P_VERSION "0.0.1 A"
#define P_LICENCE "GNU GPL v.3"

#define SL_LINEMAX 200
#define SL_SEP ":\n"
#define SL_SEP_SUB ";\n"

#define SL_SYM_VAR '$'

#define BIGGEST(a,b) ((a>b) ? (a) : (b))

struct _sl_core
{
	int id;
	int memcount;
};

typedef struct _sl_core sl_core;

int parser_get_str (char*, char*, char*, size_t, char*, char*);
int parser_get_int (char*, char*, int*, char*, char*);
int utils_streq (char*, char*);

#endif /* __SCRIPTLANG_CORE_H__ */
