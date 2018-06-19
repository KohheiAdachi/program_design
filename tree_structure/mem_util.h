#ifndef __MEM_UTIL_H__
#define __MEM_UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int mem_util_count = 0;

void * malloc2(size_t s)
{
	size_t s2 = s + sizeof(size_t);
	size_t * m2 = (size_t*)malloc(s2);
	*m2 = s2;
	void * m = (void*)(m2+1);
	memset(m, 0xcc, s);
	printf("[malloc(%d):%p]\n", ++mem_util_count, m);
	return m;
}

void free2(void * m)
{
	printf("[free(%d):%p]\n", --mem_util_count, m);
	size_t * m2 = (size_t*)m - 1;
	size_t s2 = *m2;
	memset(m2, 0xcc, s2);
	free(m2);
}

#define malloc(s) malloc2(s)
#define free(m) free2(m)

#endif
