#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#define SIZE_KEY       16
#define SIZE_VALUE1    64
#define SIZE_VALUE2    16
#define DEFAULT_TABLESIZE    101
using namespace std;

typedef struct Node
{
    Node(const char* Key1 = "\0", const char* fName = "\0",
            const char *tele ="\0", const double sal = 0.0 )
    {
        strcpy(Key, Key1);
        strcpy(FullName, fName);
        strcpy(Tele_No, tele);
        Salary = sal;
        Tax = 0.005 * Salary;
        next = NULL;
    }
    char Key[SIZE_KEY];
    char FullName[SIZE_VALUE1];
    char Tele_No[SIZE_VALUE2];
    double Salary;
    double Tax;
    Node *next;
} Node;
  
class Hashtable
{
private:
    int table_size;
    Node** table;
    int size;
    long hashString(char* Key);
    Node* find(char* Key);
    Node* current_entry;
    int current_index;
public:
    Hashtable(int T = DEFAULT_TABLESIZE);//constructor
    virtual ~Hashtable();//destructor
    bool put(Node *);
    bool get(Node *);
    bool contains(char* Key);
    bool remove(char* Key);
    void removeAll();
    int getSize();
    void initIterator();
    bool hasNext();
    void getNextKey(char* Key);
    friend void dispAll(Node *);
};
