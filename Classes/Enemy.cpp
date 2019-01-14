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

//このクラスにstateMachineを持たせて、メンバ変数を変更、そのメンバ変数を参照して実行
void Enemy::update()
{
    //stateMachine->execute();
}

/*
 class StateMachine
 {
 Enemy*enemy;
 };
*/
