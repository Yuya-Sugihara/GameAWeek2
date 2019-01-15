#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Character.hpp"
using namespace cocos2d;

class Muzzle;
class StateMachine;

class Enemy:public Character
{
private:
    static constexpr float speed=1.0f;
    static constexpr float distanceToAccess=500.0f;
    static constexpr float distanceToAttack=300.0f;
public:
    Enemy(float width,float height);
    
    void update();
    void access(Vec2 direction);
    void patrol(Vec2 playerPos);
    CC_SYNTHESIZE(StateMachine*, mStateMachine, StateMachine);
};
#endif /* Enemy_hpp */
