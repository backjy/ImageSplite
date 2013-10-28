#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace std;

class HelloWorld : public cocos2d::CCLayer
{
    string m_strCurrentSavePath;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
};

#endif // __HELLOWORLD_SCENE_H__
