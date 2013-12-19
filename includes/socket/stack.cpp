/** XXX g++ -g -rdynamic -o mytest main.cpp */
/** man backtrace_symbols */
/** man addr2line */


#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <cstring>

#include <unistd.h>
#include <execinfo.h>


void dump_stack(FILE *);
void segv_handle(int);

static int foo(int);
int foo_1(int);

int main()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = segv_handle;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGSEGV, &sa, 0) < 0) {
        perror("sigaction");
        exit(1);
    }
    foo(7);
    return 0;
}

static int foo(int a)
{
    return foo_1(a - 1);
}

int foo_1(int a)
{
    if(a > 0) return foo(a - 1);

    char *p = 0;
    /** crash here */
    memcpy(p, "hello", 5);
    return 0;
}

void dump_stack(FILE *log)
{
    void *bufs[100];
    int n = backtrace(bufs, 100);
    char **infos = backtrace_symbols(bufs, n);

    if(!infos) exit(1);

    fprintf(log, "==================\n");
    fprintf(log, "Frame info:\n");

    char cmd[512];
    int len = snprintf(cmd, sizeof(cmd),
        "addr2line -ifC -e ./stack");
    char *p = cmd + len;
    size_t s = sizeof(cmd) - len;
    for(int i = 0; i < n; ++i) {
        fprintf(log, "%s\n", infos[i]);
        if(s > 0) {
            len = snprintf(p, s, " %p", bufs[i]);
            p += len;
            s -= len;
        }
    }
    fprintf(log, "src info:\n");

    FILE *fp;
    char buf[128];
    if((fp = popen(cmd, "r"))) {
        while(fgets(buf, sizeof(buf), fp))
            fprintf(log, "%s", buf);
        pclose(fp);
    }
    free(infos);
    fprintf(log, "==================\n");

    /** same as: */
    backtrace_symbols_fd(bufs, n, STDOUT_FILENO);
    fprintf(log, "==================\n");
}

void segv_handle(int s)
{
    dump_stack(stdout);

    exit(127 + s);
}
