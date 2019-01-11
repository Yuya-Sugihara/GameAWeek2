
#ifndef StartLayer_hpp
#define StartLayer_hpp

//#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class StartLayer:public Layer
{
public:
    StartLayer();
    ~StartLayer();
    static StartLayer* create();
    bool init() override;
    void onEnter() override;
    
    static Scene* createScene();
    virtual bool onTouchBegan(Touch* touch,Event* event) override;
    virtual void onTouchMoved(Touch* touch,Event* event) override;
    virtual void onTouchEnded(Touch* touch,Event* event) override;
    virtual void onTouchCancelled(Touch* touch,Event* event) override;
    
    void show();
    void changeToGameLayer();
};

#endif /* StartLayer_hpp */
