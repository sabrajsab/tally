#ifndef GENPURPOSEALLOCATOR_HPP
#define GENPURPOSEALLOCATOR_HPP

union Header {
    struct {
        Header * uNextPtr;
        Header * uPrevPtr;
        bool uFlag;
        unsigned uSize;
    } uBuff;
    long long x;
};

void * Malloc (unsigned);

static Header * GetMemoryFromOS (unsigned);

void Free (void *);

#endif
