#ifndef _ZSETRANKLIST_APPOSITION_H_
#define _ZSETRANKLIST_APPOSITION_H_
#include "redis/redisclient.h"
#include <string>

using std::string;

class HashObject{
public:
    string uid;
    int score;
    HashObject *prev;
    HashObject *next;
public:
    HashObject(){}
    HashObject(string uid, int score):uid(uid),score(score)
    {
        this->prev = NULL;
        this->next = NULL;
    }
    void show();
    void show(int rank);
};

class HashList{
public:
    int length;
    HashObject *head;
    HashObject *tail;
public:
    HashList(){}
    HashList(int length):length(length)
    {
        this->head = NULL;
        this->tail = NULL;
    }
    ~HashList()
    {
        HashObject *p = this->head;
        while(p!=NULL)
        {
            this->head = this->head->next;
            delete p;
            p = this->head;
        }
    }
    void show();
};

class RankList{
public:
    HashList *toplist;
    HashObject *myrank;
public:
    RankList()
    {
        this->toplist = NULL;
        this->myrank = NULL;
    }
    ~RankList()
    {
        delete toplist;
        delete myrank;
    }
};

void setScore(redis::client &c,string key, string uid, int score);
int getRank(redis::client &c,string key, string uid, int score);
HashList *reHashObject(redis::client &c,string arr[],string uid,int score);
void getRankList(redis::client &c,RankList *rlist, string key, string uid, int score, int amount);

#endif
