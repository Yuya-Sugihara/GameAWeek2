#include "StartLayer.hpp"

#include "GameLayer.hpp"

StartLayer::StartLayer()
{
    
}

StartLayer::~StartLayer()
{
    
}

StartLayer* StartLayer::create()
{
    StartLayer* layer=new StartLayer();
    layer->init();
    layer->autorelease();
    
    return layer;
}

bool StartLayer::init()
{
    if(!Layer::init()) return false;
    
    return true;
}

void StartLayer::onEnter()
{
    Layer::onEnter();
    
    EventListenerTouchOneByOne* startListener=EventListenerTouchOneByOne::create();
    startListener->setSwallowTouches(true);
    startListener->onTouchBegan=CC_CALLBACK_2(StartLayer::onTouchBegan,this);
    startListener->onTouchMoved=CC_CALLBACK_2(StartLayer::onTouchMoved,this);
    startListener->onTouchEnded=CC_CALLBACK_2(StartLayer::onTouchEnded,this);
    startListener->onTouchCancelled=CC_CALLBACK_2(StartLayer::onTouchCancelled,this);
    Director::getInstance()->getEventDispatcher()
    ->addEventListenerWithSceneGraphPriority(startListener,this);
    
    show();
}

Scene* StartLayer::createScene()
{
    Scene* scene=Scene::create();
    scene->autorelease();
    scene->retain();
    
    StartLayer* layer=StartLayer::create();
    scene->addChild(layer);
    
    return scene;
}

void StartLayer::show()
{
    Label* label=Label::createWithSystemFont("StartLayer","arial",56);
    auto size=Director::getInstance()->getWinSize();
    label->setPosition(size.width/2,size.height/2);
    addChild(label);
}


void StartLayer::changeToGameLayer()
{
    Scene* scene=GameLayer::createScene();
    Director::getInstance()->replaceScene(scene);
}

bool StartLayer::onTouchBegan(Touch* touch,Event* event)
{
    changeToGameLayer();
    return true;
}

void StartLayer::onTouchMoved(Touch* touch,Event* event)
{
    
}

void StartLayer::onTouchEnded(Touch* touch,Event* event)
{
    
}

void StartLayer::onTouchCancelled(Touch* touch,Event* event)
{
    
}
