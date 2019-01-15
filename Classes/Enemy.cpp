#include "Enemy.hpp"
#include "Muzzle.hpp"
#include "WallManager.hpp"
#include "StateMachine.hpp"
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

void Enemy::access(Vec2 direction)
{
    //log("size: %d",WallManager::getInstance()->getWallList().size());
    Vec2 nowPos=getPosition();
    Vec2 toPlayerVector=direction-getPosition();
    Vec2 vector=toPlayerVector.getNormalized()*speed;
    Vec2 position=getPosition()+vector;
    if(!isContact(WallManager::getInstance()->getWallList(),vector))
    {
        log("in access");
        setPosition(position.x,position.y);
    }else{
        setPosition(nowPos.x,nowPos.y);
    }
    lookAt(toPlayerVector);
    
    if(toPlayerVector.length()<distanceToAttack)
    {
        mStateMachine->setNextState(S_Attack);
    }
}

void Enemy::patrol(Vec2 playerPos)
{
    float lengthToPlayer=(playerPos-getPosition()).length();
    if(lengthToPlayer<=Enemy::distanceToAccess)
    {
        mStateMachine->setNextState(S_Access);
    }
}
