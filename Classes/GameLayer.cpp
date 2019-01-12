#include "GameLayer.hpp"

#include "ResultLayer.hpp"
#include "Wall.hpp"
#include "WallManager.hpp"
#include "Player.hpp"
#include "Stick.hpp"

#include <math.h>

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
    scheduleUpdate();
}

void GameLayer::update(float dt)
{
    
    Player* player=(Player*) getChildByTag(T_Player);
    Vec2 playerPos=Vec2(player->getPosition().x,player->getPosition().y);
    Vec2 newPlayerPos=playerPos + toAddPlayerPos*mPlayerMovementRate;
    //float newPlayerRotation=player->getRotation()+toAddPlayerRotation;
    player->setPosition(newPlayerPos.x,newPlayerPos.y);
    //player->setRotation(newPlayerRotation);
     
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
    
    Player* player=Player::create(20,20);
    player->setPosition(400,200);
    player->setTag(T_Player);
    addChild(player);
    
    Stick* stick=Stick::create();
    stick->setTag(T_Stick);
    stick->moveStick(Vec2(125,125));
    addChild(stick);
    
}

void GameLayer::createWall(float x,float y,float width,float height)
{
    Wall* wall=Wall::create(width,height);
    wall->setColor(Color3B(200,100,100));
    wall->setPosition(x,y);
    wall->setTag(T_Wall);
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
    
    Stick* stick=(Stick*) getChildByTag(T_Stick);
    stick->moveStick(touch->getLocation());
    return true;
}

void GameLayer::onTouchMoved(Touch* touch,Event* event)
{
    Stick* stick=(Stick*) getChildByTag(T_Stick);
    Vec2 newButtonPos=Vec2::ZERO;
    if((touch->getLocation()-stick->getPos()).length() < mAvailableButtonLength)
    {
        newButtonPos=touch->getLocation();
        stick->slideStick(newButtonPos);
    }else{
        newButtonPos=(touch->getLocation()-stick->getPos()).getNormalized();
        newButtonPos=newButtonPos*mAvailableButtonLength+stick->getPos();
        stick->slideStick(newButtonPos);
    }
    
    toAddPlayerPos=newButtonPos-stick->getPos();
    toAddPlayerRotation=toAddPlayerPos.getAngle()*(180/M_PI);
   
    Player* player=(Player*) getChildByTag(T_Player);
    //float newPlayerRotation=player->getRotation()+toAddPlayerRotation;
    player->setRotation(-toAddPlayerRotation);
    
}

void GameLayer::onTouchEnded(Touch* touch,Event* event)
{
    toAddPlayerPos=Vec2::ZERO;
    toAddPlayerRotation=0.0f;
}

void GameLayer::onTouchCancelled(Touch* touch,Event* event)
{
    onTouchEnded(touch,event);
}
