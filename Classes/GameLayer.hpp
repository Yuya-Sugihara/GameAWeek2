
#ifndef GameLayer_hpp
#define GameLayer_hpp

//#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class GameLayer:public Layer
{
public:
    GameLayer();
    ~GameLayer();
    static GameLayer* create();
    bool init() override;
    void onEnter() override;
    
    static Scene* createScene();
    virtual bool onTouchBegan(Touch* touch,Event* event) override;
    virtual void onTouchMoved(Touch* touch,Event* event) override;
    virtual void onTouchEnded(Touch* touch,Event* event) override;
    virtual void onTouchCancelled(Touch* touch,Event* event) override;
    
    void show();
    void changeToResultLayer();
};

#endif /* GameLayer_hpp */
