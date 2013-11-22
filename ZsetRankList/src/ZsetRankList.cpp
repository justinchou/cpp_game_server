#include <iostream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "apposition.h"
#include "redis/redisclient.h"

#define MAX 1024

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
    
        redis::client &c = *shared_c;

        {
            string key = "keyI";
            string uid,su_id;
            int score,rank;

            /**   set rank multi   **/
            int length;
            for(int i = 21; i < 40; i++)
            {
                su_id = "u_key";
                char cu_id[MAX];

                length = sprintf(cu_id,"%d",i*2+1);
                su_id += cu_id;
                setScore(c,key,su_id,i*3+1);

                length = sprintf(cu_id,"%d",i*2+2);
                su_id += cu_id;
                setScore(c,key,su_id,i*3+1);

                length = sprintf(cu_id,"%d",i*2+3);
                su_id += cu_id;
                setScore(c,key,su_id,i*3+1);

                length = sprintf(cu_id,"%d",i*2+4);
                su_id += cu_id;
                setScore(c,key,su_id,i*3+1);

                length = sprintf(cu_id,"%d",i*2+5);
                su_id += cu_id;
                setScore(c,key,su_id,i*3+1);

            }


            /**   get rank list   */
            uid = "u_key7374";
            score  = 109;
            int amount = 20;
            RankList *rlist = new RankList();
            getRankList(c,rlist,key,uid,score,amount);

            rlist->toplist->show();
            rlist->myrank->show();
            delete rlist;

            /**   get person rank   */
            uid = "u_key73";
            score  = 109;
            rank = getRank(c,key,uid,score);
            cout<<uid<<" rank is: "<<rank<<endl;

            uid = "u_key7374";
            score  = 109;
            rank = getRank(c,key,uid,score);
            cout<<uid<<" rank is: "<<rank<<endl;

            uid = "u_key737475";
            score  = 109;
            rank = getRank(c,key,uid,score);
            cout<<uid<<" rank is: "<<rank<<endl;

            uid = "u_key73747576";
            score  = 109;
            rank = getRank(c,key,uid,score);
            cout<<uid<<" rank is: "<<rank<<endl;

            uid = "u_key7374757677";
            score  = 109;
            rank = getRank(c,key,uid,score);
            cout<<uid<<" rank is: "<<rank<<endl;


            uid = "u_key53";
            score  = 79;
            rank = getRank(c,key,uid,score);
            cout<<uid<<" rank is: "<<rank<<endl;

            uid = "u_key5354";
            score  = 79;
            rank = getRank(c,key,uid,score);
            cout<<uid<<" rank is: "<<rank<<endl;

            uid = "u_key535455";
            score  = 79;
            rank = getRank(c,key,uid,score);
            cout<<uid<<" rank is: "<<rank<<endl;

            uid = "u_key53545556";
            score  = 79;
            rank = getRank(c,key,uid,score);
            cout<<uid<<" rank is: "<<rank<<endl;

            uid = "u_key5354555657";
            score  = 79;
            rank = getRank(c,key,uid,score);
            cout<<uid<<" rank is: "<<rank<<endl;


        }    
    }
    catch(redis::redis_error & e)
    {
        cerr << "got exception: " << e.what() << endl << "FAIL" << endl;
        return 1;
    }

    return 0;
}
