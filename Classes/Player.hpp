
#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Character.hpp"
using namespace cocos2d;

class Character;

class Player:public Character
{
private:
    
public:
    static Player* create(float width,float height);
    bool init(float width,float height);
    Player();
    void update();
};
#endif /* Player_hpp */
