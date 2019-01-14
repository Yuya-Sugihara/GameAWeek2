#include "Character.hpp"
#include "Wall.hpp"
#include "Muzzle.hpp"

bool Character::init(float width,float height)
{
    if(!Sprite::init()) return false;
    characterRect=new Rect(0,0,width,height);
    setTextureRect(*characterRect);
    
    muzzle=Muzzle::create(width/2,height/2);
    muzzle->setPosition(width*(5/4),height/2);
    this->addChild(muzzle,T_Muzzle);

    return true;
}

Character::Character()
{
    
}

Character::~Character()
{
    
}

bool Character::isContact(std::list<Wall*> wallList,Vec2 addVector)
{
    Rect characterRect=this->getBoundingBox();
 
    characterRect.origin+=addVector;
    std::list<Wall*>::iterator it;
    for(it=wallList.begin();it!=wallList.end();it++)
    {
        Rect wallRect=(*it)->getBoundingBox();
        if(characterRect.intersectsRect(wallRect)) return true;
    }
    return false;
}

bool Character::isContact(std::list<Bullet*> bulletList)
{
    std::list<Bullet*>::iterator it;
    //log("position.x: %f,position.y: %f",this->getPosition().x,this->getPosition().y);
    for(it=bulletList.begin();it!=bulletList.end();it++)
    {
        Rect characterRect=getBoundingBox();
        Vec2 bulletPosition=(*it)->getPosition();
        if(characterRect.containsPoint(bulletPosition)) return true;
    }
    
    return false;
}

/*
bool Character::isContact(Wall* wall,Vec2 addVector)
{
    Rect characterRect=this->getBoundingBox();
    
    characterRect.origin+=addVector;
    
    Rect wallRect=wall->getBoundingBox();
    if(characterRect.intersectsRect(wallRect)) return true;
    
    
    return false;
}
 */
