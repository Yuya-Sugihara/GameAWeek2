#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Character.hpp"
using namespace cocos2d;

class Bullet:public Character
{
private:
    //Rect bulletRect;
    Vec2 mDirection;
    const float speed=30.0f;
public:
    static Bullet* create(float width,float height,Vec2 direction);
    bool init(float width,float height,Vec2 direction);
    Bullet();
    
    void update();
};
#endif /* Bullet_hpp */
