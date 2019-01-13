
#ifndef Muzzle_hpp
#define Muzzle_hpp

#include <stdio.h>
#include "cocos2d.h"

#include "Bullet.hpp"

using namespace cocos2d;

class Muzzle:public Sprite{
private:
    Rect* muzzleRect;
    std::list<Bullet*> bulletList;
public:
    static Muzzle* create(float width,float height);
    bool init(float width,float height);
    
    Bullet* fire(Vec2 direction);
    void update();
    std::list<Bullet*>* getBulletList() {return &bulletList;}
};

#endif /* Muzzle_hpp */
