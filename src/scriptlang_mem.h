#ifndef __SCRIPTLANG_MEM_H__
#define __SCRIPTLANG_MEM_H__

#define MEM_S_NAME 50
#define MEM_S_VALUE 100

struct sl_mem
{
	int n;
	int m_id;
	int m_state;
	int m_value_int;
	char m_name[MEM_S_NAME];
	char m_value_str[MEM_S_VALUE];
	struct sl_mem* next;
};

void mem_free_ll (struct sl_mem**);
int mem_insert (struct sl_mem**, int, int, int, char*, char*);
int mem_remove (struct sl_mem**, int);

int mem_set_int (struct sl_mem**, int, char*);
int mem_set_str (struct sl_mem**, char*, char*);
int mem_get_int (struct sl_mem**, int*, char*);
int mem_get_str (struct sl_mem**, char*, size_t, char*);

#endif /* __SCRIPTLANG_MEM_H__ */
