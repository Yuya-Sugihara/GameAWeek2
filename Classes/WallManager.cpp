#include "WallManager.hpp"
#include "Wall.hpp"

WallManager* WallManager::instance=nullptr;

//シングルトンクラスのインスタンスはnullptrで初期化する必要がある

//todo::２週目のlistに関するクラッシュを治す
WallManager* WallManager::getInstance()
{
    if(!instance)
    {
        instance=new WallManager();
        instance->autorelease();
        instance->retain();
    }
    return instance;
}

void WallManager::destroy()
{
    if(instance)
    {
        delete instance;
        instance=0;
    }
}

WallManager::WallManager()
{

}

WallManager::~WallManager()
{
    log("in WallManager::~WallManager()");
    wallList.clear();
}

void WallManager::addWall(Wall* wall)
{
    wallList.push_back(wall);
}

std::list<Wall*> WallManager::getWallList()
{
    return wallList;
}
 

int WallManager::getSize()
{
    return (int)wallList.size();
}
 

