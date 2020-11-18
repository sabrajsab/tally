#ifndef GENPURPOSEALLOCATOR_HPP
#define GENPURPOSEALLOCATOR_HPP

union Header {
    struct {
        Header * uPtr;
        unsigned uSize;
    } uBuff;
    long long x;
};

void * Calloc (unsigned, unsigned);

void * Malloc (unsigned);

void Init ();

static Header * GetMemoryFromOS (unsigned);

void Free (void *);

#endif
