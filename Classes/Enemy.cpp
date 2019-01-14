#include "Enemy.hpp"
#include "Muzzle.hpp"

Enemy::Enemy(float width,float height)
{
    Character::init(width,height);
    autorelease();
    characterColor=Color3B(30,100,30);
    setColor(characterColor);
    
    muzzle=Muzzle::create(width/2,height/2);
    muzzle->setPosition(width*(5/4),height/2);
    this->addChild(muzzle,T_Muzzle);
}


void Enemy::update()
{
    muzzle->fire(Vec2(0,-1));
}
