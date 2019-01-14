#include "StateMachine.hpp"
#include "Enemy.hpp"


StateMachine::StateMachine(Enemy* enemy):
mEnemy(enemy),
mNextState(S_None)
{
    state=new Patrol(enemy);
}

StateMachine::~StateMachine()
{
    delete state;
    delete mEnemy;
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
            state=new Patrol(mEnemy);
            break;
        case S_Access:
            delete state;
            state=0;
            state=new Access(mEnemy);
            break;
        case S_Attack:
            delete state;
            state=0;
            state=new Attack(mEnemy);
            break;
        default:
            log("changerState() ERROR");
            break;
    }
    state->enter();
    mNextState=S_None;
}

State::State(Enemy* enemy):
mEnemy(enemy)
{
    log("in State::State");
}

State::~State()
{
    log("in State::~State()");
    //delete mEnemy;
}

Patrol::Patrol(Enemy* enemy):
State(enemy)
{
    log("in patrol::patrol");
}

void Patrol::enter()
{
    log("in Patrol::enter()");
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

Access::Access(Enemy*enemy):
State(enemy)
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
    mEnemy->getStateMachine()->setNextState(S_Attack);
}

void Access::exit()
{
    log("in Access::exit()");
}

Attack::Attack(Enemy*enemy):
State(enemy)
{
    log("in Attack::Access");
}

void Attack::enter()
{
    log("in Attack::enter()");
    log("Enemy->getPosition().x: %f,Enemy->getPosition().y: %f",
        mEnemy->getPosition().x,mEnemy->getPosition().y);
}

void Attack::execute()
{
    log("in Attack::execute()");
    mEnemy->getStateMachine()->setNextState(S_Patrol);
}

void Attack::exit()
{
    log("in Attack::exit()");
}
