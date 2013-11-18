#ifndef _TIER_H_
#define _TIER_H_

class Tier
{
public:
    Tier();
    Tier(int);
    int getIdFrom(int);
    int getIdTo(int);
    
private:
    static int maxScore;
    static int maxTier;
    static int maxId;
    XTree *head;
};

#endif
