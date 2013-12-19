#include <unistd.h>
#include <iostream>
#include <string>
#include <pthread.h>

using namespace std;

void *echo1(void *);
void *echo2(void *);

class Args
{
public:
    struct timespec t;
    pthread_t id;
    string msg;
public:
    Args(struct timespec t,pthread_t id,string msg):t(t),id(id),msg(msg){}
};

int main()
{
    struct timespec t1;
    t1.tv_sec = 2;
    t1.tv_nsec = 0;
    struct timespec t2;
    t2.tv_sec = 1;
    t2.tv_nsec = 0;

    pthread_t id1,id2;

    string msg1 = "pthread NO1:";
    string msg2 = "pthread NO2:";

    Args *args1 = new Args(t1,id1,msg1);
    Args *args2 = new Args(t2,id2,msg2);

    pthread_create(&id1,NULL,echo1,(void*)args1);
    pthread_create(&id2,NULL,echo2,(void*)args2);

    pthread_join(id1,NULL);
    pthread_join(id2,NULL);

    return 0;
}

void *echo1(void *args)
{
    Args *params = (Args *)args;
    for(int i = 0; i<100; i++)
    {
        cout<<"i is:"<<i<<endl;
        nanosleep(&params->t,NULL);
    }
    pthread_exit(&params->id);
}

void *echo2(void *args)
{
    Args *params = (Args *)args;
    for(int i = 0; i<100; i++)
    {
        cout<<params->msg<<" i is:"<<i<<endl;
        nanosleep(&params->t,NULL);
    }
    pthread_exit(&params->id);
}
