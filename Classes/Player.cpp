
#include "Player.hpp"
#include "Character.hpp"
#include "Muzzle.hpp"

Player* Player::create(float width,float height)
{
    Player* player=new Player();
    if(!player || !player->init(width,height)) return nullptr;
    player->autorelease();
    
    return player;
}

bool Player::init(float width,float height)
{
    if(!Character::init(width,height)) return false;
    setColor(characterColor);
    
    muzzle=Muzzle::create(width/2,height/2);
    muzzle->setPosition(width*(5/4),height/2);
    this->addChild(muzzle);

    return true;
}

Player::Player()
{
    characterColor=Color3B(100,200,200);
}
void Player::update()
{
    
}

