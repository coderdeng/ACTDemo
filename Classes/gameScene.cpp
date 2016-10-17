#include "gameScene.h"
#include "operatorLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* gameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// 'layer' is an autorelease object
	auto layer = gameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool gameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("gameScene.csb");
	auto operatorlayer = operatorLayer::create();
	auto pt = ProgressTimer::create(Sprite::create("ui/progressTimer.png"));
	pt->setPercentage(100);
	pt->setPosition(250, 600);
	pt->setType(ProgressTimer::Type::BAR);
	pt->setMidpoint(Vec2(0, 0.5));
	pt->setBarChangeRate(Vec2(1, 0));

	rootNode->addChild(pt, 1, "progressTimer");
	shana = shana::create();
	monster = monster::create();
	monster->setRival(shana);
	operatorlayer->setTheRole(shana);
	operatorlayer->setTheEnemy(monster);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	visibleSize.height -= 200;

	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 2.0f);
	body->setPositionOffset(Vec2(0, 40));
	rootNode->setPhysicsBody(body);

	rootNode->addChild(shana, 0, "shana");
	rootNode->addChild(monster, 0, "monster");
	rootNode->addChild(operatorlayer);
	shana->setAnchorPoint(Vec2(0.5, 0));
	monster->setAnchorPoint(Vec2(0.5, 0));
	shana->setName("shana");
	monster->setName("monster");
	shana->setScale(2);
	monster->setScale(2);

	PhysicsMaterial material(1.0f, 0.0f, 0.1f);
	auto body1 = PhysicsBody::createBox(shana->getSprite()->getContentSize(), material);
	shana->setPhysicsBody(body1);
	auto body2 = PhysicsBody::createBox(monster->getSprite()->getContentSize(), material);
	monster->setPhysicsBody(body2);

	shana->setPosition(Vec2(200, 200));
	monster->setPosition(Vec2(1000, 200));
	addChild(rootNode, 1, "rootNode");

	//scheduleUpdate();
	return true;
}


bool gameScene::checkCrash()
{
	//CCLOG("distance: %f", abs(shana->getPositionX() - monster->getPositionX()));
	if (true){
		
	}
	return true;
}

void gameScene::hurtCompute()
{
	if (shana->getCurStateID() == AC_SKILL_A) {
		monster->setCurHurtV(10);
		CCLOG("%f", monster->getBloodVolume());
	}
}

//层进入时执行
void gameScene::onEnter()
{
	Layer::onEnter();
	//加入物理碰撞监听
	addPhysicsListener();

	//加入背景音乐
	addBackgroundMusic();

}

void gameScene::addBackgroundMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("backMusic.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("backMusic.mp3", true);
}

void gameScene::addPhysicsListener()
{
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [this](PhysicsContact& contact) {
		Role *role1 = (Role*)contact.getShapeA()->getBody()->getNode();
		Role *role2 = (Role*)contact.getShapeB()->getBody()->getNode();

		Role *shana = (role1->getName() == "shana") ? role1 : role2;
		Role *monster = (role2->getName() == "monster") ? role2 : role1;

		//检查角色 shana 是否处在攻击状态
		if (shana->getCurStateID() == AC_SKILL_A || shana->getCurStateID() == AC_SKILL_B ||
			shana->getCurStateID() == AC_SKILL_C || shana->getCurStateID() == AC_SKILL_D ||
			shana->getCurStateID() == AC_SKILL_E) {
			monster->setNextStateID(AC_INJURED);
			log("shana act");
		}

		//检查角色 monster 是否处在攻击状态
		if (monster->getCurStateID() == AC_SKILL_A || monster->getCurStateID() == AC_SKILL_B ||
			monster->getCurStateID() == AC_SKILL_C || monster->getCurStateID() == AC_SKILL_D ||
			monster->getCurStateID() == AC_SKILL_E) {
			shana->setNextStateID(AC_INJURED);
			log("monster act");
			auto pt = static_cast<ProgressTimer*>(
				this->getChildByName("rootNode")->getChildByName("progressTimer"));
			pt->setPercentage(pt->getPercentage() - 1.0f);
		}
		log("onContactBegin");
		return true;
	};
	listener->onContactPreSolve = [](PhysicsContact& contact, PhysicsContactPreSolve& solve) {
		CCLOG("onContactPostSolve");
		return true;
	};
	listener->onContactPostSolve = [](PhysicsContact& contact, const PhysicsContactPostSolve& solve) {
		CCLOG("onContactPostSolve");
	};
	listener->onContactSeparate = [](PhysicsContact& contact) {
		CCLOG("onContactSeperate");
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

}