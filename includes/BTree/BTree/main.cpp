
#include "BTree.h"
int main(void)  
{  
    BTree T = NULL;  
    int key[15] = { 45, 24, 53, 90, 3, 12, 37, 50, 61, 70, 100, 30, 26, 85, 7};  
      
    CreateBTree(T, 15, key);  
    PrintBTree(T);  
    return 1;  
}  
