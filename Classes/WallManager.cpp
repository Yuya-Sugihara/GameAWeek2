#include "WallManager.hpp"
#include "Wall.hpp"

WallManager* WallManager::instance=nullptr;

//シングルトンクラスのインスタンスはnullptrで初期化する必要がある
WallManager* WallManager::getInstance()
{
    if(!instance) instance=new WallManager();
    return instance;
}

WallManager::WallManager()
{

}

WallManager::~WallManager()
{
    
}

void WallManager::addWall(Wall* wall)
{
    wallList.push_back(wall);
}
 

int WallManager::getSize()
{
    return (int)wallList.size();
}
 

