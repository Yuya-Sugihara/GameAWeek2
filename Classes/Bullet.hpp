#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Character.hpp"
using namespace cocos2d;

class Wall;
class Bullet:public Character
{
private:
    Vec2 mDirection;
    const float speed=5.0f;
public:
    static const int reflectCount=5;
    
    static Bullet* create(float width,float height,Vec2 direction);
    bool init(float width,float height,Vec2 direction);
    Bullet();
    
    void update();
    void update(std::list<Wall*> list);
    
    CC_SYNTHESIZE(int , mReflectedCount, ReflectedCount);
};
#endif /* Bullet_hpp */
