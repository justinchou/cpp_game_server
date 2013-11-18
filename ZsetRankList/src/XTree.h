#ifndef _XTREE_H_
#define _XTREE_H_

class XTree
{
public:
    XTree();
    XTree(int,int,int);

    int getCount();
    void setCount(int);

    int getId();
    void setId(int);
    int getFrom();
    void setFrom(int);
    int getTo();
    void setTo(int);
    XTree *getLTree();
    void setLTree(XTree *);
    XTree *getRTree();
    void setRTree(XTree *);
private:
    int count = 0;

    int id;
    int from;
    int to;
    XTree *lp;
    XTree *rp;
};

#endif
