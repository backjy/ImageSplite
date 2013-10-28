//
//  BlockTec.cpp
//  HelloCpp
//
//  Created by MacMini-4 on 13-10-28.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//

#include "BlockTec.h"

#include "FileFind.h"

bool BlockTec::init()
{
    
    if (!CCNode::init())
    {
        return false;
    }

    
    FileUtilsEx::getInstance();
    
    m_iCurretnLoadIndex = 0;
    
    m_strLastSavepath = "";
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    m_pDisplay = CCSprite::create();
    
    m_pDisplay->setPosition(ccp(0, 0));
    
    m_pDisplay->setAnchorPoint(ccp(0, 0));
    
    addChild(m_pDisplay);
    
    m_iCurrentDisplay = 0;
    
    FileUtilsEx * fileEx = FileUtilsEx::getInstance();
    m_fullPath = fileEx->getProgramPath();
    fileEx->FindSubPath();
    
    m_pCurrentDo = CCLabelTTF::create("", "Arial", 40);
    m_pCurrentDo->setPosition(ccp(s.width/2, s.height - 100));
    m_pCurrentDo->setColor(ccc3(255, 0, 0));
    addChild(m_pCurrentDo);
    
    return true;
}

BlockTec::BlockTec()
{
    
}

BlockTec::~BlockTec()
{
}

void BlockTec::start()
{
    unscheduleUpdate();
    
    m_iCurretnLoadIndex = 0;
    
    m_iCurrentDisplay = 0;
    
    m_time = FileUtilsEx::getInstance()->getTime();
    
    FileUtilsEx::getInstance()->existFilePath((m_fullPath + "Documents/" + m_time));
    
    perLoadNextCache();
    
}

void BlockTec::update(float delta)
{
    
//    CCLOG("---:dsbr %d,%d",m_iCurrentDisplay, SpriteFrameCache::getInstance()->getAllKeys()->count());
    
//    if (m_iCurrentDisplay >= (CCSpriteFrameCache::sharedSpriteFrameCache()->getAllKeys()->count() - 1))
//    {
//        perLoadNextCache();
//        return;
//    }
    
    CCObject * obj = CCSpriteFrameCache::sharedSpriteFrameCache()->getAllKeys()->objectAtIndex(m_iCurrentDisplay);
    
    CCString * str = dynamic_cast<CCString*>(obj);
    if (str)
    {
        CCSpriteFrame * frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->getCString());
        m_pDisplay->setDisplayFrame(frame);
        
        float width = m_pDisplay->boundingBox().size.width;
        float height = m_pDisplay->boundingBox().size.height;
        
        CCRenderTexture * render = CCRenderTexture::create(width, height);
        render->setAnchorPoint(ccp(0, 0));
        render->setPosition(ccp(0, 0));
        
        render->begin();
        m_pDisplay->visit();
        render->end();
        
        string save = m_strLastSavepath + str->getCString();
        
        render->saveToFile(save.c_str());
        
        m_iCurrentDisplay ++;
        
        if (m_iCurrentDisplay >= (CCSpriteFrameCache::sharedSpriteFrameCache()->getAllKeys()->count() - 1))
        {
            perLoadNextCache();
            return;
        }
    }
}

void BlockTec::perLoadNextCache()
{
    unscheduleUpdate();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
    
    FileUtilsEx * fileEx = FileUtilsEx::getInstance();
    
    vector<string> * subFils = fileEx->getSubFils();

    for (int i=m_iCurretnLoadIndex; i<subFils->size(); i++)
    {
        
        string fileString = (*subFils)[i].c_str();
        
        CCLog("---:%s",fileString.c_str());
        
        if(fileString.find(".") == string::npos)
        {
            fileEx->existFilePath((m_fullPath + "Documents/" + m_time + "/"+ fileString));
            continue;
        }
        
        string plist = fileString.substr(fileString.size()-5,fileString.size());
        
        if (!plist.compare( "plist"))
        {
            string plistName = m_fullPath + "Resource/" + fileString;
            
            string pngName = m_fullPath + "Resource/" +  fileString.replace(fileString.size()-5, 5, "pvr.ccz");
            
//            log("--:%s",fileString.c_str());
//            log("--:%s",plistName.c_str());
//            log("--:%s",pngName.c_str());
            string fileNamePath = (m_fullPath + "Documents/" + m_time + "/" + fileString.substr(0,fileString.size()-6));
            fileEx->existFilePath(fileNamePath);
            
            CCLog("--- plist:%d",fileEx->existFile(plistName));
            CCLog("--- png  :%d",fileEx->existFile(pngName));
            
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistName.c_str(), pngName.c_str());
            
            m_iCurretnLoadIndex ++;
            
//            int index = fileString.find_last_of("/");
            
            string desktop = "/Users/macmini-4/Desktop/";
            
            m_strLastSavepath = fileNamePath + "/";
            
            fileEx->existFilePath(m_strLastSavepath);
            
            CCString * percentage = CCString::createWithFormat("%s, %.2fp",fileString.c_str(),(float)m_iCurretnLoadIndex / (float)subFils->size() * 100);
            m_pCurrentDo->setString(percentage->getCString());
            
            break;
        }
    }
    m_iCurrentDisplay = 0;
    scheduleUpdate();
}

void BlockTec::draw()
{
    ccDrawColor4B(0, 0, 0, 0);
    ccDrawRect(m_pDisplay->boundingBox().origin, m_pDisplay->boundingBox().size);
}