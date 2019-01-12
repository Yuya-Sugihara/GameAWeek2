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
    mPos=touchedPos;
    setPosition(mPos.x,mPos.y);

    //bg->setPosition(0,0);
    //button->setPosition(0,0);
}
//
Vec2 Stick::slideStick(Touch* touch)
{
    Vec2 newButtonPos=Vec2::ZERO;
    
    if((touch->getLocation()-mPos).length() < mAvailableButtonLength)
    {
        newButtonPos=touch->getLocation()-mPos;
    }else{
        newButtonPos=(touch->getLocation()-mPos).getNormalized();
        newButtonPos=newButtonPos*mAvailableButtonLength;
        
    }
    button->setPosition(newButtonPos);
    return newButtonPos;
}
