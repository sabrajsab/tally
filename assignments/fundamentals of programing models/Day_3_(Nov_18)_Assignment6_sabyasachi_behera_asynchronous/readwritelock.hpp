#ifndef READWRITELOCK_HPP
#define READWRITELOCK_HPP

#include <stdio.h>
#include <windows.h>

#define threadcount 100

struct tLocks
{
           tLocks ();
	int    uReaders;
	HANDLE uCounterMutex;
	HANDLE uReadWriteMutex;
};

class ReadLock {
    
public:

    void Wait   ();
    void Signal ();

private:

    bool flag;
};

class WriteLock {

public:

    void Wait   ();
    void Signal ();
};

#include "readwritelock.hxx"
#endif
