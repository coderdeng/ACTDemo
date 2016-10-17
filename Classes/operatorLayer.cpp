#include "operatorLayer.h"

USING_NS_CC;

using namespace cocostudio::timeline;

// on "init" you need to initialize your instance
bool operatorLayer::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("operatorLayer.csb");
	Button *atcButton = (Button*)rootNode->getChildByName("attack");
	atcButton->addTouchEventListener(CC_CALLBACK_2(operatorLayer::attackEnermy, this));

	//方向按钮
	Layout *dirpanel = (Layout*)rootNode->getChildByName("dirPanel");
	((Button*)dirpanel->getChildByName("backButton"))
		->addTouchEventListener(CC_CALLBACK_2(operatorLayer::backFunc, this));;
	((Button*)dirpanel->getChildByName("forwardButton"))
		->addTouchEventListener(CC_CALLBACK_2(operatorLayer::forwardFunc, this));
	((Button*)dirpanel->getChildByName("downButton"))
		->addTouchEventListener(CC_CALLBACK_2(operatorLayer::downFunc, this));

	//菜单按钮
	Layout *menuPanel = (Layout*)rootNode->getChildByName("menuPanel");
	((Button*)menuPanel->getChildByName("exitButton"))
		->addTouchEventListener(CC_CALLBACK_2(operatorLayer::exitFunc, this));

	//注册按键事件
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(operatorLayer::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(operatorLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	
	addChild(rootNode);

	return true;
}

//touch事件
void operatorLayer::attackEnermy(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//连招一
		if (getTheRole()->getCurStateID() == AC_SKILL_A && getTheRole()->SkillQue.empty())
			getTheRole()->SkillQue.push_back(AC_SKILL_B);
		//连招二
		else if (getTheRole()->getCurStateID() == AC_SKILL_B && getTheRole()->SkillQue.empty())
			getTheRole()->SkillQue.push_back(AC_SKILL_C);
		//技能
		else if (getTheRole()->getCurStateID() == AC_DEFEND)
			getTheRole()->runSkillDAnimation();
		if (!getTheRole()->getAllowMove())break;

		getTheRole()->runSkillAAnimation();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void operatorLayer::backFunc(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
	case Widget::TouchEventType::MOVED:
		if (!getTheRole()->getAllowMove())break;
		if (!getTheRole()->getSprite()->isFlippedX()){
			getTheRole()->getSprite()->setFlippedX(true);
		}
		getTheRole()->runRunAnimation();
		break;
	default:
		if (getTheRole()->getCurStateID() != AC_RUN &&
			getTheRole()->getCurStateID() != AC_STAND)break;
		getTheRole()->runStandAnimation();
		break;
	}
}

void operatorLayer::forwardFunc(Ref *sPender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
	case Widget::TouchEventType::MOVED:
		if (!getTheRole()->getAllowMove())break;
		if (getTheRole()->getSprite()->isFlippedX()){
			getTheRole()->getSprite()->setFlippedX(false);
		}
		getTheRole()->runRunAnimation();
		break;
	default:
		if (!getTheRole()->getAllowMove())break;
		getTheRole()->runStandAnimation();
		break;
	}
}

void operatorLayer::downFunc(Ref *sPender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		if (!getTheRole()->getAllowMove())break;
		getTheRole()->runDefendAnimation();
		break;
	default:
		if (!getTheRole()->getAllowMove() &&
			getTheRole()->getCurStateID() != AC_DEFEND)break;
		getTheRole()->runStandAnimation();
		break;
	}
}

//按键
void operatorLayer::onKeyPressed(EventKeyboard::KeyCode keycode, Event *e)
{
	switch (keycode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		if (!getTheRole()->getAllowMove())break;
		if (!getTheRole()->getSprite()->isFlippedX()){
			getTheRole()->getSprite()->setFlippedX(true);
		}
		getTheRole()->runRunAnimation();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:		
		if (!getTheRole()->getAllowMove())break;
		if (getTheRole()->getSprite()->isFlippedX()){
			getTheRole()->getSprite()->setFlippedX(false);
		}
		getTheRole()->runRunAnimation();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		if (!getTheRole()->getAllowMove())break;
		getTheRole()->runDefendAnimation();
	default:
		break;
	}
}

void operatorLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event *e)
{
	switch (keycode)
	{
	default:		
		if (!getTheRole()->getAllowMove() &&
			getTheRole()->getCurStateID() != AC_DEFEND)break;
		getTheRole()->runStandAnimation();
		break;
	}
}



void operatorLayer::exitFunc(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	default:
		exit(0);
		break;
	}
}