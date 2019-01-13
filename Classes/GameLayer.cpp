#include "GameLayer.hpp"

#include "ResultLayer.hpp"
#include "Wall.hpp"
#include "WallManager.hpp"
#include "Player.hpp"

#include "Stick.hpp"
#include <cmath>

using namespace ui;
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
    Vec2 newPlayerPos=Vec2::ZERO;
    Vec2 nextMovingVector=toAddPlayerPos*mPlayerMovementRate;
    Vec2 playerPos=Vec2(player->getPosition().x,player->getPosition().y);
    
    if(!player->isContact(WallManager::getInstance()->getWallList(),nextMovingVector))
    {
        newPlayerPos=playerPos + nextMovingVector;
    }else{
        newPlayerPos=playerPos;
    }
    player->setPosition(newPlayerPos.x,newPlayerPos.y);
    player->update();
    
    Muzzle* muzzle=player->getMuzzle();
    std::list<Bullet*>* list=muzzle->getBulletList();
    if(list->size()) removeBullet(list);
    
    judgeGameClear();
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
    addChild(sprite,Z_Bg);
    
    createWall(400,450,20,450);
    createWall(650,400,300,10);
    
    Player* player=Player::create(20,20);
    player->setPosition(mPlayerInitPos);
    player->setTag(T_Player);
    addChild(player,Z_Player);
    
    Stick* stick=Stick::create();
    stick->setTag(T_Stick);
    stick->moveStick(Vec2(125,125));
    addChild(stick,Z_Stick);
    
    goal=DrawNode::create();
    goal->drawDot(Vec2::ZERO,mGoalRadius,Color4F(0.1f,0.1f,0.1f,1.0f));
    goal->setPosition(mGoalPos);
    addChild(goal,Z_Bg);
    
    createFireButton();
}

void GameLayer::createWall(float x,float y,float width,float height)
{
    Wall* wall=Wall::create(width,height);
    wall->setColor(Color3B(200,100,100));
    wall->setPosition(x,y);
    wall->setTag(T_Wall);
    addChild(wall,Z_Wall);

    WallManager::getInstance()->addWall(wall);
    log("size: %d",WallManager::getInstance()->getSize());
}

void GameLayer::createFireButton()
{
    ui::Button* fireButton=ui::Button::create();
    fireButton->setTouchEnabled(true);
    fireButton->setPosition(Vec2(1000,200));
    fireButton->setTitleText("FIRE");
    fireButton->setTitleFontSize(56);
    fireButton->setTitleColor(Color3B::RED);
    fireButton->
    addTouchEventListener(this,toucheventselector(GameLayer::touchEvent));
    this->addChild(fireButton);
}

void GameLayer::touchEvent(Ref* sender,ui::TouchEventType type)
{
    switch(type)
    {
  
        case TOUCH_EVENT_BEGAN:
        {
            log("fire");
            Player* player=(Player*) getChildByTag(T_Player);
            Muzzle* muzzle=player->getMuzzle();
            Vec2 forwardVector=Vec2(1,1);
            forwardVector=Vec2(forwardVector.x*std::cos( (player->getRotation()*(M_PI/180)) ),
                               forwardVector.y*std::sin( -(player->getRotation()*(M_PI/180)) ) );
            
            Bullet* bullet=muzzle->fire(forwardVector);
            bullet->setPosition(player->getPosition());
            bullet->setRotation( -forwardVector.getAngle()*(180/M_PI) );
            log("TOUCH_EVENT_BEGAN");
            
            addChild(bullet,Z_Bullet);
            break;
        }
        default:
            
            break;
    }
   
    
}
void GameLayer::show()
{
    Label* label=Label::createWithSystemFont("GameLayer","arial",56);
    auto size=Director::getInstance()->getWinSize();
    label->setPosition(size.width/2,size.height/2);
    addChild(label);
}

void GameLayer::judgeGameClear()
{
    Player* player=(Player*) getChildByTag(T_Player);
    Rect playerRect=player->getBoundingBox();
    //playerがゴールに到達したか
    if(playerRect.containsPoint(mGoalPos)) gameClear(100);
    
}

void GameLayer::removeBullet(std::list<Bullet*>* list)
{

    std::list<Bullet*>::iterator it;
    std::list<Bullet*>::iterator removingIt;
    Size winSize=Director::getInstance()->getWinSize();
    
  
    for(it=list->begin();it!=list->end();)
    {
        Vec2 pos=(*it)->getPosition();
        if(pos.x<0 || pos.x>winSize.width || pos.y<0 || pos.y>winSize.height)
        {
            (*it)->removeFromParentAndCleanup(true);
            it=list->erase(it);
            if(!list->size() )
            {
                return;
            }
        }else{
            (*it)->update();
            it++;
        }
    }
}
void GameLayer::gameClear(int score)
{
    changeToResultLayer();
}
void GameLayer::changeToResultLayer()
{
    Scene* scene=ResultLayer::createScene();
    Director::getInstance()->replaceScene(scene);
}

bool GameLayer::onTouchBegan(Touch* touch,Event* event)
{
    
    Stick* stick=(Stick*) getChildByTag(T_Stick);
    stick->moveStick(touch->getLocation());
    
    
    return true;
}

void GameLayer::onTouchMoved(Touch* touch,Event* event)
{
    
    Stick* stick=(Stick*) getChildByTag(T_Stick);

    toAddPlayerPos=stick->slideStick(touch);
    toAddPlayerRotation=toAddPlayerPos.getAngle()*(180/M_PI);
   
    Player* player=(Player*) getChildByTag(T_Player);
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
