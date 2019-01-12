
#ifndef WallManager_hpp
#define WallManager_hpp

#include "WallManager.hpp"

#include "cocos2d.h"
#include <list>

using namespace cocos2d;

class Wall;

class WallManager:public Ref
{
public:
    static WallManager* getInstance();
    void addWall(Wall* wall);
    std::list<Wall*> getWallList();
    int getSize();
private:
    static WallManager* instance;
    std::list<Wall*> wallList;
    
    WallManager();
    ~WallManager();
    
};


#endif /* WallManager_hpp */
