#ifndef LOGGER_HXX
#define LOGGER_HXX

#include <stdio.h>
#include <Windows.h>
#include <ctime>
#include "logger.hpp"
#pragma warning(disable : 4996)

Logger::Logger ()
{
    vWriteLogFile = CreateFileA ("logs.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

Logger::~Logger ()
{
    CloseHandle (vWriteLogFile);
}

int StrLen (const char * pString)
{
        int size {0};
    while (pString[size] != '\0') {
        size++;
    }
    return size;
}

void Logger::log (char * pString, eLogLevel pLevel)
{

	vLogLevel = pLevel;
        DWORD byte_written;
    if (vLogLevel == INFO) {

        WriteFile (vWriteLogFile, "INFO ", 5, &byte_written, NULL);
    } else if (vLogLevel == TRACE) {

        WriteFile (vWriteLogFile, "TRACE ", 6, &byte_written, NULL);
    } else if (vLogLevel == ERRORS) {

        WriteFile (vWriteLogFile, "ERROR ", 6, &byte_written, NULL);
    }
    char * buffer = pString;
    time_t t;
    time (&t);
    char * time_date = ctime (&t);
    WriteFile (vWriteLogFile, buffer, StrLen (buffer), &byte_written, NULL);

	WriteFile(vWriteLogFile, time_date, StrLen(time_date), &byte_written, NULL);
}


void Logger::SetLogLevel (eLogLevel pLevel)
{
	vLogLevel = pLevel;
}

eLogLevel Logger::GetLogLevel ()
{
    return vLogLevel;
}

#endif
