/*========================*/  
/* |      BTree.h       | */
/*========================*/  
 
#ifndef _BTREE_H_  
#define _BTREE_H_  
#define NUM 3  
#define KeyType int  
#define Status  int  
  
typedef struct BTNode {  
    int keynum;  
    struct BTNode * parent;  
    KeyType key[NUM+1];  
    struct BTNode * ptr[NUM+1];  
}BTNode,*BTree;  
  
typedef struct  {  
    BTNode * pt;  
    int i;  
    int tag;  
}Result;  
  
  
Result SearchBTree(BTree T, KeyType K);  
Status InsertBTree(BTree &T, KeyType K, BTree q, int i);  
Status CreateBTree(BTree &T, int size, int *key);  
void PrintBTree(BTree T);  
 
 
#endif  
