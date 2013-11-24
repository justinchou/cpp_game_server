#include <iostream>
#include <time.h>
using namespace std;

int main()
{
    time_t timestamp;
    time(&timestamp);
    char *time = ctime(&timestamp);
    cout<<timestamp<<endl;
    cout<<time<<endl;
    return 0;
}
