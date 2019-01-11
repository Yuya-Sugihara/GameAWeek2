#include "Wall.hpp"


Wall* Wall::create(float x,float y,float width,float height)
{
    Wall* wall=new Wall();
    if(!wall || !wall->init(x,y,width,height)) return nullptr;
    
    wall->autorelease();
    
    return wall;
}

bool Wall::init(float x,float y,float width,float height)
{
    if(!Sprite::init()) return false;
    mRect=Rect(0,0,width,height);
    this->setTextureRect(mRect);
    this->setPosition(x,y);
    return true;
}

Wall::Wall()
{
    
}

Wall::Wall(float x,float y,float width,float height)
{
   
}
