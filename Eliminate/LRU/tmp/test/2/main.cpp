#include <iostream>
#include "hash_table.h"
#include <string>
using namespace std;

int main()
{
    LRUCache *lru = new LRUCache(10);

    string key1 = "12";
    string value1 = "aa";

    lru->setValue(key1,value1);
    cout<<"value:"<<lru->getValue(key1)<<endl;
    return 0;
}
