#include "CrashLogger.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>

void _signal_handler(int signo)
{
    _backtrace(signo);
    exit(0);
}

void _backtrace(const int eid)
{
    void *pTrace[256];
    char **ppszMsg = NULL;
    size_t uTraceSize = 0;
    static const char szSigMsg[][256] = {
        "Received SIGSEGV",
        "Received SIGPIPE",
        "Received SIGFPE",
        "Received SIGABRT"
    };

    do {
        if (0 == (uTraceSize = backtrace(pTrace, sizeof(pTrace) / sizeof(void *)))) {
            break;
        }
        if (NULL == (ppszMsg = backtrace_symbols(pTrace, uTraceSize))) {
            break;
        }

        printf("%s. call stack:\n", szSigMsg[eid]);
        for (size_t i = 0; i < uTraceSize; ++i) {
              printf("%s\n", ppszMsg[i]);
        }
    } while (0);

    if (NULL != ppszMsg) {
        free(ppszMsg);
        ppszMsg = NULL;
    }
}

