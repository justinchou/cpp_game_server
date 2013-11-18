#include "XTree.h"

XTree::XTree(){
    this->id = 1;
    this->from = 0;
    this->to = 1;

    this->lp = NULL;
    this->rp = NULL;
}

XTree::XTree(int id, int from, int to){
    this->id = id;
    this->from = from;
    this->to = to;

    this->lp = NULL;
    this->rp = NULL;
}

int XTree::getCount()
{
    return this->count;
}
void XTree::setCount(int i)
{
    this->count = i;
}

int XTree::getId()
{
    return this->id;
}
void XTree::setId(int i)
{
    this->id = i;
}
int XTree::getFrom()
{
    return this->from;
}
void XTree::setFrom(int i)
{
    this->from = i;
}
int XTree::getTo()
{
    return this->to;
}
void XTree::setTo(int i)
{
    this->to = int i;
}
XTree *getLTree()
{
    return this->lp;
}
void XTree::setLTree(XTree *p)
{
    this->lp = p;
}
XTree *getRTree()
{
    return this->rp;
}
void XTree::setRTree(XTree *p)
{
    this->rp = p;
}

