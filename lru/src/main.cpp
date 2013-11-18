#include <iostream>
#include <stdio.h>
#include "lru.h"
#include <string>
#include <cstdlib>
using namespace std;

#define MAX_RETRIES 20

void retPrint(LRUCache*);

int main()
{
    LRUCache *lru = new LRUCache(10);
    int i = 0;
    while( i < MAX_RETRIES ){
        string key, value;
    
        cout<<"input key:";
        cin>>key;
        if(key.length() == 0){
            retPrint(lru);
            return 1;
        }
        cout<<"input value:";
        cin>>value;
        if(value.length() == 0){
            retPrint(lru);
            return 2;
        }

        lru->setValue(key,value);
        i++;
    }
    retPrint(lru);
    return 0;
}

void retPrint(LRUCache *lru)
{
    lru->disp();
    delete lru;
}
