#include "StateMachine.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "WallManager.hpp"
#include <cmath>
StateMachine::StateMachine(Enemy* enemy,Player* player):
mEnemy(enemy),
mPlayer(player),
mNextState(S_None)
{
    state=new Patrol(mEnemy,mPlayer);
    state->enter();
}

StateMachine::~StateMachine()
{
    delete state;
    delete mEnemy;
    delete mPlayer;
}

void StateMachine::update()
{
    state->execute();
    if(mNextState!=S_None)
    {
        changeState();
    }
}

void StateMachine::changeState()
{
    state->exit();
    
    switch(mNextState)
    {
        case S_Patrol:
            delete state;
            state=0;
            state=new Patrol(mEnemy,mPlayer);
            break;
        case S_Access:
            delete state;
            state=0;
            state=new Access(mEnemy,mPlayer);
            break;
        case S_Attack:
            delete state;
            state=0;
            state=new Attack(mEnemy,mPlayer);
            break;
        default:
            log("changerState() ERROR");
            break;
    }
    
    state->enter();
    mNextState=S_None;
}

State::State(Enemy* enemy,Player* player):
mEnemy(enemy),
mPlayer(player)
{
    log("in State::State");
}

State::~State()
{
    log("in State::~State()");
    //delete mEnemy;
}

Patrol::Patrol(Enemy* enemy,Player* player):
State(enemy,player)
{
    log("in patrol::patrol");
}

void Patrol::enter()
{
    log("in Patrol::enter()");
    log("playerPosition.x: %f,playerPosition.y: %f",
        mPlayer->getPosition().x,mPlayer->getPosition().y);
}

void Patrol::execute()
{
    log("in Patrol::execute()");
    mEnemy->getStateMachine()->setNextState(S_Access);
}

void Patrol::exit()
{
    log("in Patrol::exit()");
}

Access::Access(Enemy* enemy,Player* player):
State(enemy,player)
{
    log("in Access::Access");
}

void Access::enter()
{
    log("in Access::enter()");
   
}

void Access::execute()
{
    log("in Access::execute()");
    Vec2 toPlayerVector=mPlayer->getPosition()-mEnemy->getPosition();
    mEnemy->lookAt(toPlayerVector);
    //mEnemy->getStateMachine()->setNextState(S_Attack);
}

void Access::exit()
{
    log("in Access::exit()");
}

Attack::Attack(Enemy* enemy,Player* player):
State(enemy,player)
{
    log("in Attack::Access");
}

void Attack::enter()
{
    log("in Attack::enter()");
    log("Enemy->getPosition().x: %f,Enemy->getPosition().y: %f",
        mEnemy->getPosition().x,mEnemy->getPosition().y);
    log("wall.x: %lf",(*( WallManager::getInstance()->getFirstWall() ))->getWidth() );
    
}

void Attack::execute()
{
    log("in Attack::execute()");
    
    if(mEnemy->getMuzzle()->getBulletList()->size()<Muzzle::maxBulletCount)
    {
        Vec2 toPlayerVector=mPlayer->getPosition()-mEnemy->getPosition();
        mEnemy->lookAt(toPlayerVector);
        auto gameLayer=mEnemy->getParent();
        mEnemy->fire();
    }
    //mEnemy->getStateMachine()->setNextState(S_Patrol);
}

void Attack::exit()
{
    log("in Attack::exit()");
}
