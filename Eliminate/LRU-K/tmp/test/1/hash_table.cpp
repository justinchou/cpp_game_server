#include "hash_table.h"

Hashtable::Hashtable(int T)
{
    size = 0;
    table_size = T;
    table = new Node*[table_size];
    for(int i=0; i<table_size; i++)
    {
        table[i] = NULL;
    }
}
  
Hashtable::~Hashtable()
{
    removeAll();
    delete[] table;
}
  
void dispAll(Node *N1)
{
    cout << "\nKey:        " << N1->Key << "\nFullName: "
        << N1->FullName <<"\nTele.:     " << N1->Tele_No << "\nSalary:    "
        << setprecision(12) << N1->Salary<< "\nTax:        " << N1->Tax << endl;
}
  
bool Hashtable::put(Node *N)
{
    if(find(N->Key) != NULL)
    {
        return false;
    }
    Node* entry = new Node(N->Key, N->FullName,N->Tele_No, N->Salary);
    int bucket = hashString(N->Key);
    entry->next = table[bucket];
    table[bucket] = entry;
    size++;
    return true;
} 
  
bool Hashtable::get(Node* N)
{
    Node* temp = find(N->Key);
    if(temp == NULL)
    {
        N->FullName[0] = '\0';
        return false;
    }
    else
    {
        strcpy(N->FullName, temp->FullName);
        strcpy(N->Tele_No, temp->Tele_No);
        N->Salary = temp->Salary;
        N->Tax = temp->Tax;
        return true;
    }
}
  
bool Hashtable::contains(char* Key)
{
    if(find(Key) == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}
  
  
bool Hashtable::remove(char* Key)
{
    int bucket = hashString(Key);
    Node* temp = table[bucket];
    if(temp == NULL)
    {
        return false;
    }
    else if(strcmp(Key, temp->Key) == 0)
    {
        table[bucket] = temp->next;
        delete temp;
        size--;
        return true;
    }
    else
    {
        Node* temp_next = temp->next;
        while(temp_next != NULL)
        {
            if(strcmp(Key, temp_next->Key) == 0)
            {
                temp->next = temp_next->next;
                delete temp_next;
                size--;
                return true;
            }
            temp = temp->next;
            temp_next = temp_next->next;
        }
    }
    return false;
}
  
void Hashtable::removeAll()
{
    for(int i=0; i<table_size; i++)
    {
        Node* temp = table[i];
        while(temp != NULL)
        {
            Node* next = temp->next;
            dispAll(temp);
            delete temp;
            temp = next;
        }
    }
    size = 0;
}
  
int Hashtable::getSize()
{
    return size;
}
  
Node* Hashtable::find(char* Key)
{
    int bucket = hashString(Key);
    Node* temp = table[bucket];
    while(temp != NULL)
    {
        if(strcmp(Key, temp->Key) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
  
long Hashtable::hashString(char* Key)
{
    int n = strlen(Key);
    long h = 0;
    for(int i=0; i<n; i++)
    {
        h = (h << 3) ^ Key[i];
    }
     return abs(h % table_size );
}
  
void Hashtable::initIterator()
{
    current_entry = NULL;
    current_index = table_size;
    for(int i=0; i<table_size; i++)
    {
        if(table[i] == NULL)
        {
             continue;
        }
        else
        {
            current_entry = table[i];
            current_index = i;
            break;
        }
    }
}
  
bool Hashtable::hasNext()
{
    if(current_entry == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Hashtable::getNextKey(char* Key)
{
    if(current_entry == NULL)
    {
        Key[0] = '\0';
        return;
    }
    strcpy(Key, current_entry->Key);
    if(current_entry->next != NULL)
    {
        current_entry = current_entry->next;
    }
    else
    {
      for(int i=current_index+1; i<table_size; i++)
      {
          if(table[i] == NULL)
          {
              continue;
          }
          current_entry = table[i];
          current_index = i;
          return;
      }
      current_entry = NULL;
      current_index = table_size;
    }
}
