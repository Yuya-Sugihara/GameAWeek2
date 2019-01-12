#include "Muzzle.hpp"

Muzzle* Muzzle::create(float width,float height)
{
    Muzzle* muzzle=new Muzzle();
    if(!muzzle || !muzzle->init(width,height)) return nullptr;
    muzzle->autorelease();
    
    return muzzle;
}

bool Muzzle::init(float width,float height)
{
    if(!Sprite::init()) return false;
    
    muzzleRect=new Rect(0,0,width,height);
    setTextureRect(*muzzleRect);
    setColor(Color3B(75,75,200));
    
    return true;
}
