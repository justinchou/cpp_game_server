#include "CrashLogger.h"
#include <iostream>
#include <unistd.h>
#include <system.h>

using std::cout;
using std::endl;

int main()
{
    signal(SIGPIPE, _signal_handler);    // SIGPIPE，管道破裂。
    signal(SIGSEGV, _signal_handler);    // SIGSEGV，非法内存访问
    signal(SIGFPE, _signal_handler);       // SIGFPE，数学相关的异常，如被0除，浮点溢出，等等
    signal(SIGABRT, _signal_handler);     // SIGABRT，由调用abort函数产生，进程非正常退出
    signal(SIGKILL, _signal_handler);     // SIGABRT，由调用abort函数产生，进程非正常退出
    signal(SIGTERM, _signal_handler);     // SIGABRT，由调用abort函数产生，进程非正常退出

    while(1)
    {
        cout<<"aaa"<<endl;
        sleep(1);
        cout<<"bbb"<<endl;
        usleep(1000);
    }

    return 0;
}
