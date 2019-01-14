
#include "Player.hpp"


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
    
    return true;
}

Player::Player()
{
    characterColor=Color3B(100,200,200);
}
void Player::update()
{
    
}

