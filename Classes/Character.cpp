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

void Character::lookAt(Vec2 direction)
{
    float rotation=direction.getAngle()*(180/M_PI);
    setRotation(-rotation);
}

void Character::fire()
{
    if(muzzle->getBulletList()->size()< Muzzle::maxBulletCount)
    {
        Vec2 forwardVector=Vec2(1,1);
        forwardVector=Vec2(forwardVector.x*std::cos( (getRotation()*(M_PI/180)) ),
                       forwardVector.y*std::sin( -(getRotation()*(M_PI/180)) ) );
    
        Bullet* bullet=muzzle->fire(forwardVector);
        bullet->setPosition(getPosition());
        bullet->setRotation( -forwardVector.getAngle()*(180/M_PI) );
        
        Layer* gameLayer=(Layer*)getParent();
        gameLayer->addChild(bullet);
        
    }
    
}
bool Character::isContact(std::list<Wall*> wallList,Vec2 addVector)
{
    Rect characterRect=getBoundingBox();
    log("character.x: %f,character.y: %f",
        getPosition().x,getPosition().y);
    log("origin.x: %f,origin.y: %f",
        characterRect.origin.x,characterRect.origin.y);
    //characterRect.origin=getPosition();
    characterRect.origin+=addVector*3;
    /*
    characterRect.size.width*=0.8f;
    characterRect.size.height*=0.8f;
     */
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
