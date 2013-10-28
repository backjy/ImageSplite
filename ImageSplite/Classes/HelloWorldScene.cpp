#include "HelloWorldScene.h"

USING_NS_CC;

#include "FileFind.h"

#include "BlockTec.h"

CCScene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = CCScene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();

    CCLayerColor * background = CCLayerColor::create(ccc4(232, 233, 232, 255));
    addChild(background);
    
    CCMenuItem * closeItem = CCMenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",this,
                                           menu_selector(HelloWorld::menuCloseCallback));
    
	closeItem->setPosition(100,100);

    
    CCMenu * menu = CCMenu::create(closeItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu, 1);

    auto Path = CCLabelTTF::create(FileUtilsEx::getInstance()->getProgramPath().c_str(), "Arial", 20);
    Path->setColor(ccc3(0, 0, 0));
    Path->setPosition(ccp(visibleSize.width/2, visibleSize.height - 50));
    addChild(Path);
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    
    
    ((CCNode*)pSender)->setVisible(false);
    
    removeChildByTag(110);
    
    BlockTec * block = BlockTec::create();
    block->setTag(110);
    addChild(block);
    block->start();
}
