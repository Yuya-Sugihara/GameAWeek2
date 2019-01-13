#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class Wall;
class Character:public Sprite
{
private:
   
protected:
    Rect* characterRect;
    Color3B characterColor;
    
public:
    //static Character* create();
    virtual bool init(float width,float height);
    Character();
    ~Character();
    
    virtual void update()=0;
    bool isContact(std::list<Wall*> walllist,Vec2 addVector);
    //bool isContact(Wall* wall,Vec2 addVector);
};
#endif /* Character_hpp */
