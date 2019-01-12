
#ifndef StickButton_hpp
#define StickButton_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class Stick:public Sprite
{
private:
    DrawNode* bg;
    DrawNode* button;
    const float mAvailableButtonLength=100.0f;
    
public:
    static Stick* create();
    bool init();
    Stick();
    void moveStick(const Vec2 touchedPos);
    Vec2 slideStick(Touch* touch);
    CC_SYNTHESIZE(Vec2,mPos,Pos);
};
#endif /* StickButton_hpp */
