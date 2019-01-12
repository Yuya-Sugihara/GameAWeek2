
#ifndef Muzzle_hpp
#define Muzzle_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class Muzzle:public Sprite{
private:
    Rect* muzzleRect;
public:
    static Muzzle* create(float width,float height);
    bool init(float width,float height);
    
    
};

#endif /* Muzzle_hpp */
