/*========================*/  
/* |      BTree.c       | */
/*========================*/  
#include "BTree.h"  
#include <stdio.h>  
#include <stdlib.h>  
#include <assert.h>  
  
Result SearchBTree(BTree T,KeyType k)  
{  
    Result result;  
    BTree p,pre;  
    Status found = false;  
    int i = 1;  
      
    p = T;  
    pre = NULL;  
    while (p && !found)  
    {  
        for(i=1;i<p->keynum;i++)  
        {  
            if (k <= p->key[i])  
                break;  
        }  
        if (k == p->key[i])  
            found = true;  
        else  
        {  
            pre = p;  
            p = p->ptr[i-1];  
        }  
    }  
  
    result.i = i-1;  
      
    if(found)  
        result.pt = p;  
    else  
        result.pt = pre;  
  
    result.tag = found;  
    return result;  
}  

Status InsertBTree(BTree &T,KeyType K, BTree q,int i)  
{  
    int j, s;  
    KeyType x;  
    BTree ap, temp;  
    bool finished = false;  
      
    x = K;  
    ap = NULL;  
    while (q && !finished)  
    {  
        for (j = q->keynum; j > i; j --)  
        {  
            q->key[j + 1] = q->key[j];  
            q->ptr[j + 1] = q->ptr[j];  
        }  
        q->key[i + 1] = x;  
        q->ptr[i + 1] = ap;  
        q->keynum ++;  
          
        if (q->keynum < NUM)  
            finished = true;  
        else  
        {  
            s = NUM / 2 + 1;  
            x = q->key[s];  
            q->keynum = s - 1;  
            ap = (BTree)malloc(sizeof(BTNode));  
            assert(ap != NULL);  
            ap->keynum = NUM - s;  
            for ( j = 1; j <= NUM - s; j ++)  
            {  
                ap->key[j] = q->key[s + j];  
                ap->ptr[j - 1] = q->ptr[s + j - 1];  
                if (ap->ptr[j - 1]!= NULL)  
                    ap->ptr[j - 1]->parent = ap;  
            }  
            ap->ptr[NUM - s] = q->ptr[NUM];  
            if (ap->ptr[NUM - s] != NULL)  
                ap->ptr[j - 1]->parent = ap;  
              
            q = q->parent;                           //向上分裂  
              
            if (q)                                   //求出i的值  
            {  
                for (j = 1; j <= q->keynum && x > q->key[j]; j ++)  
                    NULL;  
                ap->parent = q;  
                i = j - 1;  
            }  
        }//else  
    }//while  
    if (!finished) //q = NULL;  
    {  
        temp = (BTree)malloc(sizeof(BTNode));  
        assert(temp != NULL);  
        temp->parent = NULL;  
        temp->keynum = 1;  
        temp->key[1] = x;  
        temp->ptr[0] = T;  
        temp->ptr[1] = ap;  
        if (ap != NULL)  
            ap->parent = temp;  
        if (T != NULL)  
            T->parent = temp;  
        T = temp;  
    }  
    return true;  
}  
Status CreateBTree(BTree &T, int size, int *key)  
{  
    Result result;  
    int i;  
      
    for (i = 0; i < size; i ++)  
    {  
        result = SearchBTree(T, key[i]);  
        if (!result.tag)    //需要插入  
            if (!InsertBTree(T, key[i],result.pt, result.i))  
                return false;  
    }  
    return true;  
}  
  
void PrintBTree(BTree T)  
{  
    int front,rear, i, count;  
    BTree Queue[1000], temp;  
      
    front = rear = 0;  
    Queue[rear ++] = T;  
    while (front < rear)    
    {  
        temp = Queue[front++];  
        if (temp != NULL)  
        {  
            count = 0;  
            for (i = 0; i <= temp->keynum; i ++)  
                if (temp->ptr[i] != NULL)  
                    count ++;  
                printf("[%d]", count);  
                for ( i = 1; i <= temp->keynum; i ++)  
                    printf("%d ", temp->key[i]);  
                printf("\n");  
                for (i = 0; i <= temp->keynum; i ++)  
                    Queue[rear ++] = temp->ptr[i];  
        }  
    }  
}  
