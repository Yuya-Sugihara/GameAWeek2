#include "GameLayer.hpp"

#include "ResultLayer.hpp"
#include "Wall.hpp"
#include "WallManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

#include "Stick.hpp"
#include <cmath>

using namespace ui;
GameLayer::GameLayer()
{
    
}

GameLayer::~GameLayer()
{
    WallManager::destroy();
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
    
    Vec2 newPlayerPos=Vec2::ZERO;
    Vec2 nextMovingVector=mPlayer->getToAddVector()*mPlayerMovementRate;
    Vec2 playerPos=Vec2(mPlayer->getPosition().x,mPlayer->getPosition().y);
    
    if(!mPlayer->isContact(WallManager::getInstance()->getWallList(),nextMovingVector))
    {
        newPlayerPos=playerPos + nextMovingVector;
    }else{
        newPlayerPos=playerPos;
    }
    mPlayer->setPosition(newPlayerPos.x,newPlayerPos.y);
    mPlayer->update();
    
    Muzzle* playerBulletMuzzle=mPlayer->getMuzzle();
    std::list<Bullet*>* playerBulletList=playerBulletMuzzle->getBulletList();
    if(playerBulletList->size()) updateBullet(playerBulletList);
    
    Enemy* enemy=(Enemy*) getChildByTag(T_Enemy);
    fire(enemy);
    
    Muzzle* enemyMuzzle=enemy->getMuzzle();
    //log("enemyMuzzle->getBulletList: %d",enemyMuzzle->getBulletList()->size());
    std::list<Bullet*>* enemyBulletList=enemyMuzzle->getBulletList();
    if(enemyBulletList->size()) updateBullet(enemyBulletList);
   
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
    
    mPlayer=Player::create(20,20);
    mPlayer->setPosition(mPlayerInitPos);
    mPlayer->setTag(T_Player);
    addChild(mPlayer,Z_Player);
    
    Enemy* enemy=new Enemy(50,50);
    enemy->setPosition(mEnemyInitPos);
    enemy->setRotation(90);
    enemy->setTag(T_Enemy);
    addChild(enemy,Z_Enemy);
    
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
            fire(mPlayer);
            break;
        }
        default:
            
            break;
    }
}
void GameLayer::fire(Character* character)
{
    //log("fired");
    Muzzle* muzzle=character->getMuzzle();
    Vec2 forwardVector=Vec2(1,1);
    forwardVector=Vec2(forwardVector.x*std::cos( (character->getRotation()*(M_PI/180)) ),
                       forwardVector.y*std::sin( -(character->getRotation()*(M_PI/180)) ) );
    
    Bullet* bullet=muzzle->fire(forwardVector);
    bullet->setPosition(character->getPosition());
    bullet->setRotation( -forwardVector.getAngle()*(180/M_PI) );
    
    addChild(bullet,Z_Bullet);
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
    Rect playerRect=mPlayer->getBoundingBox();
    //playerがゴールに到達したか
    if(playerRect.containsPoint(mGoalPos)) gameClear(100);
    Enemy* enemy=(Enemy*) getChildByTag(T_Enemy);
    std::list<Bullet*>* enemyBulletList=enemy->getMuzzle()->getBulletList();
    std::list<Bullet*>* playerBulletList=mPlayer->getMuzzle()->getBulletList();
    if( mPlayer->isContact(*enemyBulletList) ) changeToResultLayer();
    if( enemy->isContact(*playerBulletList) ) changeToResultLayer();
}

void GameLayer::updateBullet(std::list<Bullet*>* list)
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

    mPlayer->setToAddVector( stick->slideStick(touch) );
    mPlayer->setToAddRotation( mPlayer->getToAddVector().getAngle()*(180/M_PI) );
   
    mPlayer->setRotation(-mPlayer->getToAddRotation());
    
}

void GameLayer::onTouchEnded(Touch* touch,Event* event)
{
    mPlayer->setToAddVector(Vec2::ZERO);
    toAddPlayerRotation=0.0f;
}

void GameLayer::onTouchCancelled(Touch* touch,Event* event)
{
    onTouchEnded(touch,event);
}
