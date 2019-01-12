
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
    
public:
    static Stick* create();
    bool init();
    Stick();
    void moveStick(const Vec2 touchedPos);
    void slideStick(const Vec2 touchedPos);
    
    CC_SYNTHESIZE(Vec2,mPos,Pos);
};
#endif /* StickButton_hpp */
