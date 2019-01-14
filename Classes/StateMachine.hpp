#ifndef StateMachine_hpp
#define StateMachine_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class Enemy;
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
    StateMachine(Enemy* enemy);
    ~StateMachine();
    void update();
    void changeState();
    CC_SYNTHESIZE(EnemyState,mNextState,NextState);
private:
    Enemy* mEnemy;
    State* state;
    EnemyState currentState;
    
};

class State:public Ref
{
public:
    State(Enemy* enemy);
    ~State();
    virtual void enter()=0;
    virtual void execute()=0;
    virtual void exit()=0;
protected:
    Enemy* mEnemy;
};

class Patrol:public State
{
public:
    Patrol(Enemy* enemy);
    virtual void enter() override;
    virtual void execute() override;
    virtual void exit() override;
};

class Access:public State
{
public:
    Access(Enemy* enemy);
    virtual void enter() override;
    virtual void execute() override;
    virtual void exit() override;
};

class Attack:public State
{
public:
    Attack(Enemy* enemy);
    virtual void enter() override;
    virtual void execute() override;
    virtual void exit() override;
};
#endif /* StateMachine_hpp */
