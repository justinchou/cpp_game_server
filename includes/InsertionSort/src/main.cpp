#include <iostream>
#include "InsertionSort.h"

using std::cout;
using std::endl;

void sortIncrease();
void sortDecrease();
void sortNodeIncrease();
void sortNodeDecrease();

int main()
{
    sortIncrease();
    sortDecrease();
    sortNodeIncrease();
    sortNodeDecrease();

    return 0;
}

/**
 * sort example I: sort number with increase
 */
void sortIncrease()
{
    int len;
    cout<<"This is Increase:"<<endl;
    int iarr[] = {4,7,10,11,10,12,9,15,10};
    len = sizeof(iarr) / sizeof(*iarr);
    printNumber(iarr,len);
    InsertionSortNumber(iarr,len);
    printNumber(iarr,len);

    float farr[] = {4.5,7.2,10.1,11.2,10.3,12.4,9.5,15.6,10.1};
    len = sizeof(farr) / sizeof(*farr);
    printNumber(farr,len);
    InsertionSortNumber(farr,len);
    printNumber(farr,len);

}

/**
 * sort example II: sort number with decrease
 */
void sortDecrease()
{
    int len;
    cout<<"This is Decrease:"<<endl;
    int iarr[] = {4,7,10,11,10,12,9,15,10};
    len = sizeof(iarr) / sizeof(*iarr);
    printNumber(iarr,len);
    InsertionSortNumber(iarr,len,DECREASE_SORT);
    printNumber(iarr,len);

    int farr[] = {4.5,7.2,10.1,11.2,10.3,12.4,9.5,15.6,10.1};
    len = sizeof(farr) / sizeof(*farr);
    printNumber(farr,len);
    InsertionSortNumber(farr,len,DECREASE_SORT);
    printNumber(farr,len);
}

/**
 * sort example III: sort node with increase
 */
void sortNodeIncrease()
{
    int i,rank;
    int iarr[] = {1,7,3,9,9,5,4,2,6,9,7,8,0,9,2,7};
    int len = sizeof(iarr) / sizeof(*iarr);

    handleNode<int> *hl = new handleNode<int>();
    for(i=0; i<len; i++)
    {
        rank = hl->addNode(iarr[i]);
        cout<<rank<<endl;
    }

    int amount = hl->getTotalNum();
    cout<<"arr len: "<<len<<" node len: "<<amount<<endl;

    for(i=0; i<amount; i++)
    {
        rank = hl->getRank(iarr[i]);
        cout<<i<<": "<<rank<<endl;
    }

    int node = 9;
    hl->disp();
    hl->removeNode(node);
    hl->disp();
    hl->removeNode(node,true);
    hl->disp();
}

/**
 * sort example IV: sort node with decrease
 */
void sortNodeDecrease()
{

}
