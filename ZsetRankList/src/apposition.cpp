#include "apposition.h"
#include <string>
#include <iostream>

using namespace std;

void HashList::show()
{
    HashObject *cursor = this->head;
    int rank = 1;
    while(cursor != NULL)
    {
        cursor->show(rank);
        cursor = cursor->next;
        rank++;
    }
}

void HashObject::show()
{
    cout<<"uid:"<<this->uid<<"\tscore:"<<this->score<<endl;
}

void HashObject::show(int rank)
{
    cout<<"rank"<<rank<<"\tuid:"<<this->uid<<"\tscore:"<<this->score<<endl;
}

void setScore(redis::client &c,string key, string uid, int score)
{
    c.zadd(key,score,uid);
}

int getRank(redis::client &c,string key, string uid, int score)
{
    int rank  = c.zrevrank(key,uid);
    int count = c.zcount(key,score,score);
    if(count > 1)
    {
        redis::client::string_vector list;
        c.zrangebyscore(key,score,score,list);
        int vSize = list.size();
        for(int i=0; i<vSize; i++)
        {
            if(uid == list[i]){
                return rank - ( vSize - (i + 1) ) + 1;
            }
        }
    }
    return rank + 1;
}

void reHashObject(HashList *hlist, redis::client::string_score_vector &list,string uid,int score)
{
    int length = list.size();
//    HashList *hlist = new HashList(length);
    bool exchange = true;
    bool exclude = false;
    string key;
    int value;
    for(int i = 0; i<length; i++)
    {
        redis::client::string_score_pair kv = list[i];
        key = kv.first;
        value = kv.second;
        if(exchange && score == value){
            exchange = false;
            exclude  = true;
            HashObject *p = new HashObject(uid,score);
    
            if (hlist->head != NULL && hlist->tail != NULL)
            {
                p->prev = hlist->tail;
                hlist->tail->next = p;
                hlist->tail = p;
            }
            if (hlist->head == NULL) {
                hlist->head = p;
            }
            if (hlist->tail == NULL) {
                hlist->tail = p;
            }
        }
        if(exclude && uid == key){
            continue;
        }
    
        HashObject *p = new HashObject(key,value);
    
        if (hlist->head != NULL && hlist->tail != NULL)
        {
            p->prev = hlist->tail;
            hlist->tail->next = p;
            hlist->tail = p;
        }
        if (hlist->head == NULL) {
            hlist->head = p;
        }
        if (hlist->tail == NULL) {
            hlist->tail = p;
        }
    
    }

}

void getRankList(redis::client &c,RankList *rlist, string key, string uid, int score, int amount)
{
    int start = 0;
    redis::client::string_score_vector list;
    c.zrevrange(key,start,amount,list);

    int length = list.size();
    HashList *toplist = new HashList(length);
    reHashObject(toplist,list,uid,score);

    HashObject *myrank = new HashObject(uid,score);
    rlist->toplist = toplist;
    rlist->myrank = myrank;
}
