#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "role.h"
#include "monster.h"

USING_NS_CC;
using namespace cocos2d::ui;

class operatorLayer : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(operatorLayer);

	CC_SYNTHESIZE(Role*, _role, TheRole);
	CC_SYNTHESIZE(Role*, _enemy, TheEnemy);

	void attackEnermy(Ref* pSender, Widget::TouchEventType type);
	void backFunc(Ref* pSender, Widget::TouchEventType type);
	void forwardFunc(Ref *pSender, Widget::TouchEventType type);
	void upFunc(Ref *pSender, Widget::TouchEventType type);
	void downFunc(Ref *pSender, Widget::TouchEventType type);
	void exitFunc(Ref *pSender, Widget::TouchEventType type);

	void onKeyPressed(EventKeyboard::KeyCode keycode, Event *e);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event *e);
};
