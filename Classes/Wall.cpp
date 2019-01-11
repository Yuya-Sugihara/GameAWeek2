#include "Wall.hpp"


Wall* Wall::create(float width,float height)
{
    Wall* wall=new Wall();
    if(!wall || !wall->init(width,height)) return nullptr;
    
    wall->autorelease();
    
    return wall;
}

bool Wall::init(float width,float height)
{
    log("in Wall::init");
    if(!Sprite::init()) return false;
    mRect=Rect(0,0,width,height);
    this->setTextureRect(mRect);
    return true;
}

Wall::Wall()
{
    
}

Wall::Wall(float width,float height)
{
   
}