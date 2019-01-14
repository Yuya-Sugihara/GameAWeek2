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

Bullet* Muzzle::fire(Vec2 direction)
{
    Bullet* bullet=Bullet::create(10,10,direction);
    bulletList.push_back(bullet);
    return bullet;
}

void Muzzle::update()
{

}
