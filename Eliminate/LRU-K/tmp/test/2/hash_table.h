#ifndef _HASH_TABLE_
#define _HAHS_TABLE_

#include <map>
using namespace std;

class CacheNode
{
public:
    CacheNode *prev;
    CacheNode *next;
    string key;
    string value;
public:
    CacheNode(){}
private:
};

class LRUCache
{
public:
    LRUCache(int);
    string getValue(string);
    void setValue(string,string);
    CacheNode *removeNode(string);
    void clear();
    void removeLast();
    void moveToHead(CacheNode*);
    void disp();
private:
    int CacheSize;
    int CurrentSize;
    CacheNode *first;
    CacheNode *last;
    map<string,CacheNode*> nodes;
};

#endif
