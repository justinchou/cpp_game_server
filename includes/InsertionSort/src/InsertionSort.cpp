#include "InsertionSort.h"
#include <iostream>
#include <map>
using namespace std;

template<typename T>
void InsertionSortNumber(T *arr,int len,bool sort = INCREASE_SORT)
{
    int i,j;
    for(i=0;i<len-1;i++)
    {
        j = i + 1;
        T temp = arr[j];
        if(sort){
            while( j>0 && temp < arr[j-1])
            {
                arr[j] = arr[j-1];
                j--;
            }
        } else {
            while( j>0 && temp > arr[j-1])
            {
                arr[j] = arr[j-1];
                j--;
            }
        }
        arr[j] = temp;
    }
}

template<typename T>
void printNumber(T *arr, int len)
{
    for (int i=0; i<len; i++)
    {
        cout<<i<<":\t"<<arr[i]<<endl;
    }
    cout<<"---------------"<<endl;
}


template<typename T>
int Node<T>::amount = 0;

template<typename T>
Node<T>::Node()
{
    this->prev = NULL;
    this->next = NULL;
    this->rank = DEFAULT_RANK;
    Node<T>::amount++;
}

template<typename T>
Node<T>::Node(T value):value(value)
{
    this->prev = NULL;
    this->next = NULL;
    this->rank = DEFAULT_RANK;
    Node<T>::amount++;
}

template<typename T>
Node<T>::~Node()
{
    this->prev = NULL;
    this->next = NULL;
    Node<T>::amount--;
}

template<typename T>
handleNode<T>::handleNode()
{
    this->head = NULL;
    this->tail = NULL;
}

template<typename T>
handleNode<T>::~handleNode()
{
    typename multimap<T,Node<T>*>::iterator it = (this->list).begin();
    while(it != this->list.end())
    {
        delete (*it).second;
        this->list.erase(it);
        it++;
    }
    this->head = NULL;
    this->tail = NULL;
}

template<typename T>
int handleNode<T>::addNode(T value)
{
    Node<T> *node = new Node<T>(value);
    if(this->head != NULL && this->tail != NULL)
    {
        this->tail->next = node;
        node->rank = this->tail->rank + 1;
        node->prev = this->tail;
        this->tail = node;
    }
    if(this->head == NULL && this->tail == NULL){
        this->head = node;
        this->tail = node;
        node->rank = FIRST_RANK;
    }

    while(node != this->head && node->rank < node->prev->rank)
    {
        Node<T> *prev = node->prev->prev;
        Node<T> *changeNode = node->prev;
        Node<T> *next = node->next;

        node->prev = prev;
        node->next = changeNode;

        changeNode->prev = node;
        changeNode->next = next;

        if(prev != NULL)
        {
            prev->next = node;
        }
        if(next != NULL)
        {
            next->prev = changeNode;
        }
        changeNode->rank ++;
        node->rank --;
    }
    return node->rank;
}

template<typename T>
int handleNode<T>::getRank(T value)
{
    typename multimap<T, Node<T>*>::iterator itfind = (this->list).find(value);
    if(itfind != (this->list).end())
    {
        Node<T> *node = (*itfind).second;
        return node->rank;
    } else {
        return DEFAULT_RANK;
    }
}

template<typename T>
int handleNode<T>::getTotalNum()
{
    return Node<T>::amount;
}

template<typename T>
int handleNode<T>::removeNode(T value, const bool removeAll = false)
{
    int count = 0;
    size_t amount = (this->list).erase(value);
    cout<<"delete: "<<amount<<endl;
    Node<T> *cursor = this->head;
    while(cursor != NULL)
    {
        if(cursor->value == value && (removeAll || 0 == count))
        {
            cursor->prev->next = cursor->next;
            cursor->next->prev = cursor->prev;
            count ++;
        }
        cursor->next->rank -= count;
        cursor = cursor->next;
    }
    return count;
}

template<typename T>
void handleNode<T>::disp()
{
    typename multimap<T,Node<T>*>::iterator it = (this->list).begin();
    while(it != (this->list).end())
    {
        cout<<(*it).first<<":\t"<<(*it).second->rank<<endl;
    }
}
