
#ifndef GameLayer_hpp
#define GameLayer_hpp

//#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

enum Tag
{
    T_Wall,
    T_Player,
    T_Stick
};

class GameLayer:public Layer
{
private:
    const float mPlayerMovementRate=0.03f;
    const float mAvailableButtonLength=100.0f;
    Vec2 toAddPlayerPos;
    float toAddPlayerRotation;
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
    
    void show();
    void createStage();
    void createWall(float x,float y,float width,float height);
    void changeToResultLayer();
};

#endif /* GameLayer_hpp */
