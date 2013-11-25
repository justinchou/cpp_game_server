#include <iostream>
#include <map>
#include "lru-k.h"
using namespace std;

LRUCache::LRUCache(int i)
{
    this->CurrentSize = 0;
    this->CacheSize = i;
}

LRUCache::~LRUCache()
{
    map<string,CacheNode*> &m = this->nodes;
    map<string,CacheNode*>::iterator it = m.begin();
    while( it != m.end() )
    {
        delete (*it).second;
        it++;
    }    
    this->clear();
    cout<<"LRU over"<<endl;
}

string LRUCache::getValue(string key)
{
    CacheNode *node = (CacheNode *) this->nodes[key];
    if (node != NULL)
    {
        this->moveToHead(node);
        return node->value;
    } else {
        return "";
    }
}

void LRUCache::setValue(string key, string value)
{
    CacheNode *node = (CacheNode *) this->nodes[key];

    if(node == NULL)
    {
        if(this->CurrentSize >= this->CacheSize)
        {
            if(this->last != NULL)
            {
                this->nodes.erase(this->last->key);
                this->removeLast();
            }
        } else {
            CurrentSize++;
        }
        node = new CacheNode();
        node->prev = NULL;
        node->next = NULL;
    }
    node->key = key;
    node->value = value;

    this->moveToHead(node);
//    pair<string,CacheNode*> tmp(key,node);
//    this->nodes.insert(tmp);
    this->nodes[key] = node;
}

CacheNode *LRUCache::removeNode(string key)
{
    CacheNode *node = (CacheNode *) this->nodes[key];

    if(node != NULL)
    {
        if(node->prev != NULL)
        {
            node->prev->next = node->next;
        }
        if(node->next != NULL)
        {
            node->next->prev = node->prev;
        }

        if(this->last == node)
        {
            this->last = node->prev;
        }
        if(this->first == node)
        {
            this->first = node->next;
        }
    }
    return node;
}

void LRUCache::clear()
{
    this->first = NULL;
    this->last = NULL;
}

void LRUCache::removeLast()
{
    if(this->last != NULL)
    {
        if(this->last->prev != NULL)
        {
            this->last->prev->next = NULL;
        } else {
            this->first = NULL;
        }
        this->last = this->last->prev;
    }
}

void LRUCache::moveToHead(CacheNode* node)
{
    if(node == this->first)
    {
        return;
    }
    if(node->prev != NULL)
    {
        node->prev->next = node->next;
    }
    if(node->next != NULL)
    {
        node->next->prev = node->prev;
    }
    if(node == this->last)
    {
        this->last = node->prev;
    }
    
    if(this->first != NULL)
    {
        node->next = this->first;
        this->first->prev = node;
    } else {
        node->next = NULL;
    }
    node->prev = NULL;
    
    this->first = node;
    
    if(this->last == NULL)
    {
        this->last = this->first;
    }

}

void LRUCache::disp()
{
    cout<<"-----------------------------------------"<<"disp start:"<<endl;

    cout<<"max sortage:"<<this->CacheSize<<endl;
    cout<<"now sortage:"<<this->CurrentSize<<endl<<endl;

    map<string,CacheNode*> &m = this->nodes;
    map<string,CacheNode*>::iterator it = m.begin();
    while( it != m.end() )
    {
        if((*it).second != NULL){
            cout<<(*it).first<<":"<<(*it).second<<"\t"<<((*it).second)->key<<":"<<((*it).second)->value<<endl;
        } else {
            cout<<(*it).first<<":"<<(*it).second<<endl;
        }
        it++;
    }

    cout<<"-----------------------------------------"<<"disp second:"<<endl;

    CacheNode *p;
    p = this->first;
    while(p != NULL)
    {
        cout<<p->key<<":"<<p->value<<endl;
        p = p->next;
    }

    cout<<"-----------------------------------------"<<"disp third:"<<endl;

    p = this->last;
    while(p != NULL)
    {
        cout<<p->key<<":"<<p->value<<endl;
        p = p->prev;
    }

    cout<<"-----------------------------------------"<<"disp over;"<<endl;
}
