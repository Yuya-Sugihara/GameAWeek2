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

bool Character::isContact(Wall* wall)
{
    Rect characterRect=this->boundingBox();
    Rect wallRect=wall->boundingBox();
    if(characterRect.intersectsRect(wallRect)) return true;
    return false;
}
