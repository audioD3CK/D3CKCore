#pragma once
#include "JuceHeader.h"
#include "CrossSSE.h"

template <int T=16>
class AlignedClass
{
public:
    AlignedClass()
    {
        size_t add = (size_t)this;
        jassert(add % T == 0) // class seems not to be aligned
    }
	void* operator new(size_t bytes) throw()
    {
        return _aligned_malloc(bytes,T);
    }
	void operator delete (void *p)
    {
        _aligned_free(p);
    }

};