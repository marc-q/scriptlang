#ifndef __SCRIPTLANG_MEM_H__
#define __SCRIPTLANG_MEM_H__

#define MEM_S_NAME 50
#define MEM_S_VALUE 100

#define MEM_TYPE_INT 0
#define MEM_TYPE_STR 1

union _sl_mem_var
{
	int v_int;
	char v_str[MEM_S_VALUE];
};

typedef union _sl_mem_var sl_mem_var; 

struct sl_mem
{
	int n;
	int m_type;
	char m_name[MEM_S_NAME];
	sl_mem_var m_value;
	struct sl_mem* next;
};

void mem_free_ll (struct sl_mem**);
int mem_insert (struct sl_mem**, int, int, int, char*, char*);
int mem_remove (struct sl_mem**, char*);

int mem_set_uni (struct sl_mem**, char*, char*);
int mem_cpy_uni (struct sl_mem**, char*, char*);
int mem_set_int (struct sl_mem**, int, char*);
int mem_set_str (struct sl_mem**, char*, char*);
int mem_get_int (struct sl_mem**, int*, char*);
int mem_get_str (struct sl_mem**, char*, size_t, char*);

#endif /* __SCRIPTLANG_MEM_H__ */
