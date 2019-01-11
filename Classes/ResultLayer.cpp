#include "ResultLayer.hpp"

#include "StartLayer.hpp"

ResultLayer::ResultLayer()
{
    
}

ResultLayer::~ResultLayer()
{
    
}

ResultLayer* ResultLayer::create()
{
    ResultLayer* layer=new ResultLayer();
    layer->init();
    layer->autorelease();
    
    return layer;
}

bool ResultLayer::init()
{
    if(!Layer::init()) return false;
    
    return true;
}

void ResultLayer::onEnter()
{
    Layer::onEnter();
    
    EventListenerTouchOneByOne* resultListener=EventListenerTouchOneByOne::create();
    resultListener->setSwallowTouches(true);
    resultListener->onTouchBegan=CC_CALLBACK_2(ResultLayer::onTouchBegan,this);
    resultListener->onTouchMoved=CC_CALLBACK_2(ResultLayer::onTouchMoved,this);
    resultListener->onTouchEnded=CC_CALLBACK_2(ResultLayer::onTouchEnded,this);
    resultListener->onTouchCancelled=CC_CALLBACK_2(ResultLayer::onTouchCancelled,this);
    Director::getInstance()->getEventDispatcher()
    ->addEventListenerWithSceneGraphPriority(resultListener,this);
    
    show();
}

Scene* ResultLayer::createScene()
{
    Scene* scene=Scene::create();
    scene->autorelease();
    scene->retain();
    
    ResultLayer* layer=ResultLayer::create();
    scene->addChild(layer);
    
    return scene;
}

void ResultLayer::show()
{
    Label* label=Label::createWithSystemFont("ResultLayer","arial",56);
    auto size=Director::getInstance()->getWinSize();
    label->setPosition(size.width/2,size.height/2);
    addChild(label);
}

void ResultLayer::changeToStartLayer()
{
    Scene* scene=StartLayer::createScene();
    Director::getInstance()->replaceScene(scene);
}
 
bool ResultLayer::onTouchBegan(Touch* touch,Event* event)
{
    changeToStartLayer();
    return true;
}

void ResultLayer::onTouchMoved(Touch* touch,Event* event)
{
    
}

void ResultLayer::onTouchEnded(Touch* touch,Event* event)
{
    
}

void ResultLayer::onTouchCancelled(Touch* touch,Event* event)
{
    
}

