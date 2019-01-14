#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Character.hpp"
using namespace cocos2d;

class Muzzle;

class Enemy:public Character
{
private:
    
public:
    Enemy(float width,float height);
    
    void update();
};
#endif /* Enemy_hpp */
