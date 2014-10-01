#pragma once
#include "JuceHeader.h"
#include <xmmintrin.h>
#include <emmintrin.h>
#include <math.h>

#ifdef __MINGW_H
#define _aligned_free __mingw_aligned_free
#define _aligned_malloc __mingw_aligned_malloc
#endif

#if !defined (_aligned_malloc) && defined(JUCE_MAC)
static void* _aligned_malloc (size_t bytes, size_t alignment) throw()
{
	void *p1 ,*p2; // basic pointer needed for computation.
	
	if((p1 =(void *) malloc(bytes + alignment + sizeof(size_t)))==NULL)
		return NULL;
	
	size_t addr=(size_t)p1+alignment+sizeof(size_t);
	
	p2=(void *)(addr - (addr%alignment));
	
	*((size_t *)p2-1)=(size_t)p1;
	
	return p2;
}
#endif

#if !defined (_aligned_free) && defined(JUCE_MAC)
static void _aligned_free (void *p)
{
	/* Find the address stored by aligned_malloc ,"size_t" bytes above the
	 current pointer then free it using normal free routine provided by C. */
	if(p)
		free((void *)(*((size_t *) p-1)));
}
#endif