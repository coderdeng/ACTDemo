#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class beginScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	virtual void onExit();

	// implement the "static create()" method manually
	CREATE_FUNC(beginScene);
private:
	void startGame(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void exitGame(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
};

