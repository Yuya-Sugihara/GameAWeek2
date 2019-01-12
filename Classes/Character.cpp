#include "Character.hpp"
#include "Wall.hpp"

/*
Character* Character::create()
{
    Character* character=new Character();
    if(!Character || character->init()) return nullptr;
    character->autorelease();
    
    return character;
}
*/

bool Character::init(float width,float height)
{
    if(!Sprite::init()) return false;
    characterRect=new Rect(0,0,width,height);
    setTextureRect(*characterRect);
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
    /*
    characterRect.size.width*=0.7f;
    characterRect.size.height*=0.7f;
     */
    characterRect.origin+=addVector;
    std::list<Wall*>::iterator it;
    for(it=wallList.begin();it!=wallList.end();it++)
    {
        Rect wallRect=(*it)->getBoundingBox();
        if(characterRect.intersectsRect(wallRect)) return true;
    }

    return false;
}
