#include "Bullet.hpp"

Bullet* Bullet::create(float width,float height,Vec2 direction)
{
    Bullet* bullet=new Bullet();
    if(!bullet || !bullet->init(width,height,direction)) return nullptr;
    bullet->autorelease();
    
    return bullet;
}

bool Bullet::init(float width,float height,Vec2 direction)
{
    if(!Character::init(width,height)) return false;
    setColor(characterColor);
    mDirection=direction;
    
    
    return true;
}

Bullet::Bullet()
{
    //log("in Bullet::Bullet");
    characterColor=Color3B(100,100,100);
}

void Bullet::update()
{
    Vec2 addVector=mDirection.getNormalized()*speed;
    setPosition(getPosition()+addVector);
}
