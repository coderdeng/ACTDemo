#include "beginScene.h"
#include "operatorLayer.h"
#include "gameScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* beginScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = beginScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool beginScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("beginScene.csb");
	auto layer = (Layer*)rootNode->getChildByName("beginLayer");

	auto begin_btn = (Button*)layer->getChildByName("beginButton");
	auto exit_btn = (Button*)layer->getChildByName("exitButton");

	begin_btn->addTouchEventListener(CC_CALLBACK_2(beginScene::startGame, this));
	exit_btn->addTouchEventListener(CC_CALLBACK_2(beginScene::exitGame, this));

	addChild(rootNode, 1, "root");

	return true;
}

void beginScene::startGame(Ref *pSender, Widget::TouchEventType type)
{
	log("replaceScene");
	auto nextScene = gameScene::createScene();
	auto scene = TransitionMoveInL::create(1.0f, nextScene);
	Director::getInstance()->replaceScene(scene);
}

void beginScene::exitGame(Ref *pSender, Widget::TouchEventType type)
{
	Director::getInstance()->end();
	exit(0);
}

void beginScene::onExit()
{
	Layer::onExit();
}