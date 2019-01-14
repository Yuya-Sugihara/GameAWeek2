#include "Bullet.hpp"
#include "Wall.hpp"

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

Bullet::Bullet():
mReflectedCount(0)
{
    //log("in Bullet::Bullet");
    characterColor=Color3B(100,100,100);
}

void Bullet::update()
{
    Vec2 addVector=mDirection.getNormalized()*speed;
    setPosition(getPosition()+addVector);
}

void Bullet::update(std::list<Wall*> list)
{
    std::list<Wall*>::iterator it;
    Rect bulletRect=getBoundingBox();
    for(it=list.begin();it!=list.end();it++)
    {
        Rect wallRect=(*it)->getBoundingBox();
        if(wallRect.intersectsRect(bulletRect))
        {
            if((*it)->getWidth()==10 ) mDirection.x*=-1;
            else if((*it)->getHeight()==10 ) mDirection.y*=-1;
            mReflectedCount++;
        }
    }
    update();
}
