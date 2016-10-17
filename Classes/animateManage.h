#pragma once

#include <string>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

class animateManage
{
public:
	static Animate* createAnimate(const char *fileName, int frame, int fps);
};
