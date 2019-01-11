
#ifndef ResultLayer_hpp
#define ResultLayer_hpp

//#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class ResultLayer:public Layer
{
public:
    ResultLayer();
    ~ResultLayer();
    static ResultLayer* create();
    bool init() override;
    void onEnter() override;
    
    static Scene* createScene();
    virtual bool onTouchBegan(Touch* touch,Event* event) override;
    virtual void onTouchMoved(Touch* touch,Event* event) override;
    virtual void onTouchEnded(Touch* touch,Event* event) override;
    virtual void onTouchCancelled(Touch* touch,Event* event) override;
    
    void show();
    void changeToStartLayer();
};


#endif /* ResultLayer_hpp */
