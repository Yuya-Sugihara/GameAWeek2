
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
    static Wall* create(float x,float y,float width,float height);
    bool init(float x,float y,float width,float height);
    Wall();
    Wall(float x,float y,float width,float height);
    
};
#endif /* Wall_hpp */
