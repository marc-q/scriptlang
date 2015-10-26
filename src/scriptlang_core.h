#ifndef __SCRIPTLANG_CORE_H__
#define __SCRIPTLANG_CORE_H__

#define P_CMD "scriptlang"
#define P_VERSION "0.0.1 A"
#define P_LICENCE "GNU GPL v.3"

#define SL_LINEMAX 200
#define SL_SEP ":\n"
#define SL_SEP_SUB ";\n"

#define SL_SYM_VAR '$'
#define SL_SYM_TKN ":"
#define SL_SYM_SUBTKN ";"

/* VARS */
#define SL_WRD_INT "int"
#define SL_WRD_INTN "intn"
#define SL_WRD_FLOAT "float"
#define SL_WRD_FLOATN "floatn"
#define SL_WRD_STR "str"
#define SL_WRD_STRN "strn"
#define SL_WRD_SET "set"

/* STDLIB */
#define SL_WRD_DEF "def"
#define SL_WRD_FED "fed\n"

/* STDIO */
#define SL_WRD_PRINT "print"
#define SL_WRD_READ "read"
#define SL_WRD_PRINTM "printm"

/* ALU */
#define SL_WRD_ADD "add"
#define SL_WRD_SUB "sub"
#define SL_WRD_MPL "mpl"
#define SL_WRD_DIV "div"
#define SL_WRD_MOD "mod"
#define SL_WRD_IF "if"
#define SL_WRD_FI "fi\n"
#define SL_WRD_ELSE "else\n"

/* MATH */
#define SL_WRD_RAND "rand"

#define SL_ALU_ADD 0
#define SL_ALU_SUB 1
#define SL_ALU_MPL 2
#define SL_ALU_DIV 3
#define SL_ALU_MOD 4

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
