
#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Character.hpp"
#include "Muzzle.hpp"
using namespace cocos2d;

class Muzzle;

enum PlayerTag
{
    T_Muzzle
};

class Player:public Character
{
private:
    Muzzle* muzzle;
    
public:
    static Player* create(float width,float height);
    bool init(float width,float height);
    Player();
    void update();
    
    void moveByStick(Vec2* vector);
    Muzzle* getMuzzle(){ return muzzle;}
};
#endif /* Player_hpp */
