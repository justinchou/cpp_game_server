#include <iostream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "apposition.h"
#include "redis/redisclient.h"

#define MAX 1024

using namespace std;

void setRankMultiI(redis::client &c, string key);
void getRankListI(redis::client &c, string key);
void getRankTestI(redis::client &c, string key);

void setRankMultiII(redis::client &c, string key);
void getRankListII(redis::client &c, string key);
void getRankTestII(redis::client &c, string key);

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
            string key,uid,su_id;
            int score,rank;

//            key = "keyI";
//            setRankMultiI(c,key);
//            getRankListI(c,key);
//            getRankTestI(c,key);

            key = "keyII";
            setRankMultiII(c,key);
            getRankListII(c,key);
            getRankTestII(c,key);
        }

    }
    catch(redis::redis_error & e)
    {
        cerr << "got exception: " << e.what() << endl << "FAIL" << endl;
        return 1;
    }

    return 0;
}


void setRankMultiI(redis::client &c, string key)
{
    /**   set rank multi   **/
    int length;
    string su_id;
    
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
}

void getRankListI(redis::client &c, string key)
{
    string uid;
    int score;

    /**   get rank list   */
    uid = "u_key7374";
    score  = 109;
    int amount = 20;
    RankList *rlist = new RankList();
    getRankList(c,rlist,key,uid,score,amount);

    rlist->toplist->show();
    rlist->myrank->show();
    delete rlist;
}

void getRankTestI(redis::client &c,string key)
{
    string uid;
    int score, rank;

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


void setRankMultiII(redis::client &c, string key)
{
    /**   set rank multi   **/
    int length;
    string su_id;
    
    for(int i = 21; i < 40; i++)
    {
        su_id = "u_key";
        char cu_id[MAX];

        length = sprintf(cu_id,"%d",i*2+1);
        su_id += cu_id;
        setScore(c,key,su_id,(double)i*3+1);

        length = sprintf(cu_id,"%d",i*2+2);
        su_id += cu_id;
        setScore(c,key,su_id,(double)i*3+1);

        length = sprintf(cu_id,"%d",i*2+3);
        su_id += cu_id;
        setScore(c,key,su_id,(double)i*3+1);

        length = sprintf(cu_id,"%d",i*2+4);
        su_id += cu_id;
        setScore(c,key,su_id,(double)i*3+1);

        length = sprintf(cu_id,"%d",i*2+5);
        su_id += cu_id;
        setScore(c,key,su_id,(double)i*3+1);

    }
}

void getRankListII(redis::client &c, string key)
{
    string uid;
    double score;

    /**   get rank list   */
    uid = "u_key7374";
    score  = (double)109.0;
    int amount = 20;
    RankList *rlist = new RankList();
    getRankList(c,rlist,key,uid,score,amount);

    rlist->toplist->show();
    rlist->myrank->show();
    delete rlist;
}

void getRankTestII(redis::client &c,string key)
{
    string uid;
    int rank;

    /**   get person rank   */
    uid = "u_key73";
    rank = getRank(c,key,uid);
    cout<<uid<<" rank is: "<<rank<<endl;

    uid = "u_key7374";
    rank = getRank(c,key,uid);
    cout<<uid<<" rank is: "<<rank<<endl;

    uid = "u_key737475";
    rank = getRank(c,key,uid);
    cout<<uid<<" rank is: "<<rank<<endl;

    uid = "u_key73747576";
    rank = getRank(c,key,uid);
    cout<<uid<<" rank is: "<<rank<<endl;

    uid = "u_key7374757677";
    rank = getRank(c,key,uid);
    cout<<uid<<" rank is: "<<rank<<endl;


    uid = "u_key53";
    rank = getRank(c,key,uid);
    cout<<uid<<" rank is: "<<rank<<endl;

    uid = "u_key5354";
    rank = getRank(c,key,uid);
    cout<<uid<<" rank is: "<<rank<<endl;

    uid = "u_key535455";
    rank = getRank(c,key,uid);
    cout<<uid<<" rank is: "<<rank<<endl;

    uid = "u_key53545556";
    rank = getRank(c,key,uid);
    cout<<uid<<" rank is: "<<rank<<endl;

    uid = "u_key5354555657";
    rank = getRank(c,key,uid);
    cout<<uid<<" rank is: "<<rank<<endl;
}
