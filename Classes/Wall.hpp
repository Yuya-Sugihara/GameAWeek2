
#ifndef Wall_hpp
#define Wall_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class Wall :public Sprite
{
private:
    Rect mRect;
    
public:
    
    static Wall* create(float width,float height);
    bool init(float width,float height);
    Wall();
    Wall(float width,float height);
    
    CC_SYNTHESIZE(float, mX, X);
    CC_SYNTHESIZE(float, mY, Y);
    CC_SYNTHESIZE(double, mWidth, Width);
    CC_SYNTHESIZE(double, mHeight, Height);
    
};
#endif /* Wall_hpp */
