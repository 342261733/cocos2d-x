//
//  FlowWord.h
//  text
//
//  Created by xunianqiang on 14-10-10.
//
//

#ifndef __text__FlowWord__
#define __text__FlowWord__
//工具类，加载文字的？？
#include <iostream>

#include "cocos2d.h"

USING_NS_CC;//啥意思？

class FlowWord:public CCNode
{
public:
    FlowWord();
    ~FlowWord();
    CREATE_FUNC(FlowWord);
    virtual bool init();
    
public:
    void showWord(const char *text,CCPoint pos);
    void flowEnd();
    
private:
    CCLabelTTF *m_textLab;
    
};

#endif /* defined(__text__FlowWord__) */
