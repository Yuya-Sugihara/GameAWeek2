#ifndef StateMachine_hpp
#define StateMachine_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class Enemy;
class Player;
class State;

enum EnemyState
{
    S_Patrol,
    S_Access,
    S_Attack,
    S_None
};

class StateMachine:public Ref
{
public:
    StateMachine(Enemy* enemy,Player* player);
    ~StateMachine();
    void update();
    void changeState();
    CC_SYNTHESIZE(EnemyState,mNextState,NextState);
private:
    Enemy* mEnemy;
    State* state;
    Player* mPlayer;
    
};

class State:public Ref
{
public:
    State(Enemy* enemy,Player* player);
    ~State();
    virtual void enter()=0;
    virtual void execute()=0;
    virtual void exit()=0;
protected:
    Enemy* mEnemy;
    Player* mPlayer;
};

class Patrol:public State
{
public:
    Patrol(Enemy* enemy,Player* player);
    virtual void enter() override;
    virtual void execute() override;
    virtual void exit() override;
};

class Access:public State
{
public:
    Access(Enemy* enemy,Player* player);
    virtual void enter() override;
    virtual void execute() override;
    virtual void exit() override;
};

class Attack:public State
{
public:
    Attack(Enemy* enemy,Player* player);
    virtual void enter() override;
    virtual void execute() override;
    virtual void exit() override;
};
#endif /* StateMachine_hpp */
