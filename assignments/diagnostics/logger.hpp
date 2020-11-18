#ifndef LOGGER_HPP
#define LOGGER_HPP
#include "Windows.h"

enum eLogLevel
{
    ERRORS,
    TRACE,
    INFO
};

class Logger {
  private:
    HANDLE      vWriteLogFile;
    eLogLevel   vLogLevel;
  public:
                Logger      ();
                ~Logger     ();
    void        log         (char *, eLogLevel = TRACE);
    void        SetLogLevel (eLogLevel);
    eLogLevel   GetLogLevel ();
};

int StrLen(const char * pString);
#endif