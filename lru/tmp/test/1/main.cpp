#include <iostream>
#include "hash_table.h"
using namespace std;

void dispAll(Hashtable* hashtable);
  
int main()
{
    char temp1[SIZE_KEY];
    Hashtable* hashtable = new Hashtable();
  
    Node N1("389","Mariam","8216734",22123.267);
  
    if(!hashtable->contains(N1.Key))
    {
        cout << "\nAdding node:  ";
        dispAll((Hashtable*)&N1);
        hashtable->put(&N1);
    }
  
    strcpy(N1.Key, "314");
    strcpy(N1.FullName, "Zeki");
    strcpy(N1.Tele_No, "8765623");
    N1.Salary = 98124.567;
    if(!hashtable->contains(N1.Key))
    {
        cout << "\nAdding node:  ";
        dispAll((Hashtable*)&N1);
        hashtable->put(&N1);
    }
  
    strcpy(N1.Key, "320");
    strcpy(N1.FullName, "Murad");
    strcpy(N1.Tele_No, "7231144");
    N1.Salary = 19834.575;
    if(!hashtable->contains(N1.Key))
    {
        cout << "\nAdding node:  ";
        dispAll((Hashtable*)&N1);
        hashtable->put(&N1);
    }
  
    strcpy(N1.Key, "768");
    strcpy(N1.FullName, "Hassan");
    strcpy(N1.Tele_No, "7689876");
    N1.Salary = 45124.755;
    if(!hashtable->contains(N1.Key))
    {
        cout << "\nAdding node:  ";
        dispAll((Hashtable*)&N1);
        hashtable->put(&N1);
    }
  
    strcpy(N1.Key, "756");
    strcpy(N1.FullName, "Ali");
    strcpy(N1.Tele_No, "9874545");
    N1.Salary = 43554.125;
    if(!hashtable->contains(N1.Key))
    {
        cout << "\nAdding node:  ";
        dispAll((Hashtable*)&N1);
        hashtable->put(&N1);
    }
  
    dispAll(hashtable);

    strcpy(temp1,"314");
    hashtable->remove(temp1);
    cout << "\n\nAfter removing 314:" << endl;

    dispAll(hashtable);
    cout << "\n\nDestroying hashtable:" << endl;

    delete hashtable;
    return 0;
}
  
void dispAll(Hashtable *hashtable)
{
    Node N1;
    cout << "\n\nCurrent nodes in hashtable:" << endl;
    hashtable->initIterator();
    while(hashtable->hasNext())
    {
        hashtable->getNextKey(N1.Key);
        hashtable->get(&N1);
        dispAll((Hashtable*)&N1);
    }
}

