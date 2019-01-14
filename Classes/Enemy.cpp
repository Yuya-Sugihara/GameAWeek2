#include "Enemy.hpp"
#include "Muzzle.hpp"

Enemy::Enemy(float width,float height)
{
    Character::init(width,height);
    autorelease();
    characterColor=Color3B(30,100,30);
    setColor(characterColor);
    log("Enemy position.x: %f,Enemy position.y: %f",getPosition().x,getPosition().y);
    
}


void Enemy::update()
{
    //muzzle->fire(Vec2(0,-1));
}
