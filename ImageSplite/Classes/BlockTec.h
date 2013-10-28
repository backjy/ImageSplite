#ifndef __BlockTec__
#define __BlockTec__

#include "cocos2d.h"

using namespace cocos2d;

using namespace std;


class BlockTec : public CCNode {
    
    string m_strLastSavepath;
    
    int m_iCurretnLoadIndex;
    
    CCSprite * m_pDisplay;
    
    int m_iCurrentDisplay;
    
    string m_fullPath;
    
    string m_time;
    
    void update(float delta);
    void perLoadNextCache();
    
    CCLabelTTF * m_pCurrentDo;
public:
    BlockTec();
    virtual ~BlockTec();
    virtual bool init();
    CREATE_FUNC(BlockTec);
    
    virtual void draw();
    
    void start();
};


#endif // __HELLOWORLD_SCENE_H__
