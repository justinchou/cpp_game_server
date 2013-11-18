#include "Tier.h"
#include "XTree.h"
#include <math.h>

Tier::Tier(){}

Tier::Tier(int score){
    this->maxId = 1;
    this->maxTier = 1;
    this->maxScore = 0;
    while(this->maxScore < score){
        this->maxTier++;
        this->maxId += pow(2,this->maxTier-1);
        this->maxScore = pow(2,this->maxTier-1) - 1;
    }

    this->head = new XTree();
    while(this->head->id <= this->maxId){
        
    }
}

Tier::~Tier(){
    
}
