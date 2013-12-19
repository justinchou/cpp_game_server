#ifndef _INSERTION_SORT_H_
#define _INSERTION_SORT_H_

#include <iostream>
#include <map>
using std::multimap;

//namespace InsertionSort
//{
    #define INCREASE_SORT 1
    #define DECREASE_SORT 0
    #define DEFAULT_RANK -1
    #define FIRST_RANK    1
    
    template<typename T>
    void InsertionSortNumber(T *arr,int len, bool sort = INCREASE_SORT);
    
    template<typename T>
    void printNumber(T *arr, int len);
    
    template<typename T>
    class Node
    {
    public:
        T value;
        static int amount;
        int rank;
        Node *prev;
        Node *next;
    public:
        Node();
        Node(T value);
        ~Node();
    private:
    };

    template<typename T>
    class handleNode
    {
    public:
        handleNode();
        ~handleNode();
        int addNode(T value);
        int getRank(T value);
        int getTotalNum();
        int removeNode(T value, bool removeAll);
        void disp();
    private:
        void sort();
        Node<T> *head;
        Node<T> *tail;
        multimap<T,Node<T> *> list;
    };

//};

#endif
