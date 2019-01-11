#include "GameLayer.hpp"

#include "ResultLayer.hpp"
#include "Wall.hpp"
#include "WallManager.hpp"

GameLayer::GameLayer()
{
    
}

GameLayer::~GameLayer()
{
    
}

GameLayer* GameLayer::create()
{
    GameLayer* layer=new GameLayer();
    layer->init();
    layer->autorelease();
    
    return layer;
}

bool GameLayer::init()
{
    if(!Layer::init()) return false;
    
    return true;
}

void GameLayer::onEnter()
{
    Layer::onEnter();
    
    EventListenerTouchOneByOne* gameListener=EventListenerTouchOneByOne::create();
    gameListener->setSwallowTouches(true);
    gameListener->onTouchBegan=CC_CALLBACK_2(GameLayer::onTouchBegan,this);
    gameListener->onTouchMoved=CC_CALLBACK_2(GameLayer::onTouchMoved,this);
    gameListener->onTouchEnded=CC_CALLBACK_2(GameLayer::onTouchEnded,this);
    gameListener->onTouchCancelled=CC_CALLBACK_2(GameLayer::onTouchCancelled,this);
    Director::getInstance()->getEventDispatcher()
    ->addEventListenerWithSceneGraphPriority(gameListener,this);
    
    createStage();
}

Scene* GameLayer::createScene()
{
    Scene* scene=Scene::create();
    scene->autorelease();
    scene->retain();
    
    GameLayer* layer=GameLayer::create();
    scene->addChild(layer);
    
    return scene;
}

void GameLayer::createStage()
{
    auto size=Director::getInstance()->getWinSize();
    Rect bg=Rect(0,0,size.height,size.height);
    Sprite* sprite=Sprite::create();
    sprite->setTextureRect(bg);
    sprite->setPosition(size.width/2,size.height/2);
    addChild(sprite);
    
    createWall(400,450,20,450);
    createWall(650,400,300,10);
}

void GameLayer::createWall(float x,float y,float width,float height)
{
    log("in GameLayer::createWall");

    Wall* wall=Wall::create(width,height);
    wall->setColor(Color3B(200,100,100));
    wall->setPosition(x,y);
    addChild(wall);

    WallManager::getInstance()->addWall(wall);
    log("size: %d",WallManager::getInstance()->getSize());
    
 
}

void GameLayer::show()
{
    Label* label=Label::createWithSystemFont("GameLayer","arial",56);
    auto size=Director::getInstance()->getWinSize();
    label->setPosition(size.width/2,size.height/2);
    addChild(label);
}

void GameLayer::changeToResultLayer()
{
    Scene* scene=ResultLayer::createScene();
    Director::getInstance()->replaceScene(scene);
}

bool GameLayer::onTouchBegan(Touch* touch,Event* event)
{
    //changeToResultLayer();
    return true;
}

void GameLayer::onTouchMoved(Touch* touch,Event* event)
{
    log("x: %f",touch->getLocation().y);
}

void GameLayer::onTouchEnded(Touch* touch,Event* event)
{
    
}

void GameLayer::onTouchCancelled(Touch* touch,Event* event)
{
    
}
