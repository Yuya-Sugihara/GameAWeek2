
#ifndef GameLayer_hpp
#define GameLayer_hpp

//#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class Bullet;

enum Tag
{
    T_Wall,
    T_Player,
    T_Stick,
    T_Bullet
};

enum ZOrder
{
    Z_Bg,
    Z_Wall,
    Z_Player,
    Z_Stick,
    Z_Bullet
};

class GameLayer:public Layer
{
private:
    const float mPlayerMovementRate=0.03f;
    const float mGoalRadius=10;
    const Vec2 mGoalPos=Vec2(750,100);
    const Vec2 mPlayerInitPos=Vec2(300,600);
    Vec2 toAddPlayerPos;
    float toAddPlayerRotation;
    
    DrawNode* goal;
public:
    GameLayer();
    ~GameLayer();
    static GameLayer* create();
    bool init() override;
    void onEnter() override;
    virtual void update(float dt) override;
    
    static Scene* createScene();
    virtual bool onTouchBegan(Touch* touch,Event* event) override;
    virtual void onTouchMoved(Touch* touch,Event* event) override;
    virtual void onTouchEnded(Touch* touch,Event* event) override;
    virtual void onTouchCancelled(Touch* touch,Event* event) override;
    void touchEvent(Ref* sender,ui::TouchEventType type);
    
    void show();
    void createStage();
    void createWall(float x,float y,float width,float height);
    void createFireButton();
    void judgeGameClear();
    void gameClear(int score);
    void changeToResultLayer();
    void removeBullet(std::list<Bullet*>* list);
    
};

#endif /* GameLayer_hpp */
