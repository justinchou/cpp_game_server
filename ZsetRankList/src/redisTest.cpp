#include "redis/redisclient.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        bool CLUSTER_MODE = false;
        boost::shared_ptr<redis::client> shared_c;
    
        if(CLUSTER_MODE)
          shared_c = init_cluster_client();
        else
          shared_c = init_non_cluster_client();
    
        redis::client & c = *shared_c;

        {
            c.set("justin","chou");
            string v = c.get("justin");
            cout<<"value:"<<v<<endl;
        }    
    }
    catch(redis::redis_error & e)
    {
        cerr << "got exception: " << e.what() << endl << "FAIL" << endl;
        return 1;
    }

    return 0;
}
