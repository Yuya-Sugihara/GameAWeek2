
#ifndef WallManager_hpp
#define WallManager_hpp

#include "WallManager.hpp"

#include "cocos2d.h"
#include <list>
#include "Wall.hpp"
using namespace cocos2d;

class Wall;

class WallManager:public Ref
{
public:
    static WallManager* getInstance();
    static void destroy();
    void addWall(Wall* wall);
    std::list<Wall*> getWallList();
    int getSize();
    std::list<Wall*>::iterator getFirstWall()
    {
        return wallList.begin();
    }
private:
    static WallManager* instance;
    std::list<Wall*> wallList;
    
    WallManager();
    ~WallManager();
    
};


#endif /* WallManager_hpp */
