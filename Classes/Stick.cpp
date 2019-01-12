#include "Stick.hpp"

Stick* Stick::create()
{
    Stick* stick=new Stick();
    if(!stick || !stick->init()) return nullptr;
    stick->autorelease();
    
    return stick;
}

bool Stick::init()
{
    if(!Sprite::init()) return false;
    bg=DrawNode::create();
    bg->drawDot(Vec2::ZERO,80,Color4F(0.3f,0.3f,0.3f,1.0f));
    addChild(bg);
    button=DrawNode::create();
    button->drawDot(Vec2::ZERO,40,Color4F(0.9f,0.9f,0.9f,1.0f));
    addChild(button);
    
    return true;
}

Stick::Stick():
mPos(Vec2::ZERO)
{
    
}

void Stick::moveStick(const Vec2 touchedPos)
{
    setPosition(touchedPos.x,touchedPos.y);
    mPos=touchedPos;
    //bg->setPosition(0,0);
    //button->setPosition(0,0);
}

void Stick::slideStick(const Vec2 touchedPos)
{
    button->setPosition(touchedPos-mPos);
}
