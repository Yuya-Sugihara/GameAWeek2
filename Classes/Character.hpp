#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class Wall;
class Muzzle;
class Bullet;

enum CharacterTag
{
    T_Muzzle
};

class Character:public Sprite
{
private:
   
protected:
    Rect* characterRect;
    Color3B characterColor;
    Muzzle* muzzle;
public:
    //static Character* create();
    virtual bool init(float width,float height);
    Character();
    ~Character();
    
    virtual void update()=0;
    void lookAt(Vec2 direction);
    void fire();
    bool isContact(std::list<Wall*> walllist,Vec2 addVector);
    bool isContact(std::list<Bullet*> bulletlist);
    Muzzle* getMuzzle(){ return muzzle;}
    
    CC_SYNTHESIZE(Vec2,mToAddVector,ToAddVector);
    CC_SYNTHESIZE(float,mToAddRotation,ToAddRotation);
    
};
#endif /* Character_hpp */
