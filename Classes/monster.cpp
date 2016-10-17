#include "monster.h"
#include "animateManage.h"

monster::monster() :
	AIRole()
{
}

monster::~monster()
{
}

bool monster::init()
{
	if (!AIRole::init()) {
		return false;
	}
	setSprite(Sprite::create("role/shana/shana_1.png", Rect(0, 0, 55, 62)));

	bodySize = getSprite()->getContentSize();

	addChild(getSprite());
	setBloodVolume(100);

	//初始化动作
	setStandAnimation(RepeatForever::create(animateManage::createAnimate("role/shana/shana_1.png", 4, 6)));
	setRunAnimation(RepeatForever::create(animateManage::createAnimate("role/shana/shana_forward.png", 8, 8)));
	setDeadAnimation(RepeatForever::create(animateManage::createAnimate("role/shana/shana_dead.png", 3, 3)));
	setDefendAnimation(RepeatForever::create(animateManage::createAnimate("role/shana/shana_defend.png", 2, 4)));
	setInjuredAnimation(Sequence::create(
		animateManage::createAnimate("role/shana/shana_4.png", 2, 4),
		CallFuncN::create(CC_CALLBACK_0(monster::injuredCallback, this)),
		CallFuncN::create(CC_CALLBACK_1(monster::createStandAnimCallback, this)),
		NULL
	));
	setSkillA(Sequence::create(
		animateManage::createAnimate("role/shana/shana_2.png", 7, 14),
		CallFuncN::create(CC_CALLBACK_1(monster::attackCallbackFunc, this)),
		CallFuncN::create(CC_CALLBACK_1(monster::createStandAnimCallback, this)),
		CallFuncN::create(CC_CALLBACK_0(monster::continuSkill, this)),
		NULL
	));
	setSkillB(Sequence::create(
		animateManage::createAnimate("role/shana/shana_2extra1.png", 9, 18),
		CallFuncN::create(CC_CALLBACK_1(monster::attackCallbackFunc, this)),
		CallFuncN::create(CC_CALLBACK_1(monster::createStandAnimCallback, this)),
		CallFuncN::create(CC_CALLBACK_0(monster::continuSkill, this)),
		NULL
	));
	setSkillC(Sequence::create(
		animateManage::createAnimate("role/shana/shana_2extra2.png", 8, 16),
		CallFuncN::create(CC_CALLBACK_1(monster::attackCallbackFunc, this)),
		CallFuncN::create(CC_CALLBACK_1(monster::createStandAnimCallback, this)),
		NULL
	));
	setSkillD(Sequence::create(
		animateManage::createAnimate("role/shana/shana_2extra3.png", 13, 20),
		CallFuncN::create(CC_CALLBACK_1(monster::attackCallbackFunc, this)),
		CallFuncN::create(CC_CALLBACK_1(monster::createStandAnimCallback, this)),
		NULL
	));
	setSkillE(Sequence::create(
		animateManage::createAnimate("role/shana/shana_2extra4.png", 8, 20),
		CallFuncN::create(CC_CALLBACK_1(monster::attackCallbackFunc, this)),
		CallFuncN::create(CC_CALLBACK_1(monster::createStandAnimCallback, this)),
		NULL
	));

	getSprite()->setFlippedX(true); 
	setCurrentState(new stateSpace::state_normal);
	scheduleUpdate();
	return true;
}

void monster::onMove()
{
	if (getDistance() > 0) {
		getSprite()->setFlippedX(true);
	}
	else {
		getSprite()->setFlippedX(false);
	}
	if (getCurStateID() == AC_RUN) {
		if ((getPositionX() <= 0 && getSprite()->isFlippedX()) ||
			(getPositionX() >= 1280 && !getSprite()->isFlippedX())) {
			runStandAnimation();
			return;
		}
		if (getSprite()->isFlippedX()) {
			runAction(MoveBy::create(1 / 60, Vec2(-4, 0)));
		}
		else {
			runAction(MoveBy::create(1 / 60, Vec2(4, 0)));
		}
	}
}

void monster::onStop()
{

}

void monster::runSkillAAnimation()
{
	Role::runSkillAAnimation();
	setCurStateID(AC_SKILL_A);
}

void monster::runSkillBAnimation()
{
	Role::runSkillBAnimation();
	setCurStateID(AC_SKILL_B);
}

void monster::runSkillCAnimation()
{
	Role::runSkillCAnimation();
	setCurStateID(AC_SKILL_C);
}

void monster::runSkillDAnimation()
{
	Role::runSkillDAnimation();
	setCurStateID(AC_SKILL_D);
}

void monster::runSkillEAnimation()
{
	Role::runSkillEAnimation();
	setCurStateID(AC_SKILL_E);
}

void monster::attackCallbackFunc(Node *pSender)
{

}

void monster::update(float delta)
{
	if (getCurrentState()) {
		_currentState->Execute(this);
	}
	onMove();
	updateBox();
}

void monster::updateBox()
{
	auto body = getPhysicsBody();
	PhysicsMaterial material(1.0f, 0.0f, 0.1f);
	log("Moster: updateBodyBox");
	if (getCurStateID() == AC_SKILL_A || getCurStateID() == AC_SKILL_B
		|| getCurStateID() == AC_SKILL_C || getCurStateID() == AC_SKILL_D
		|| getCurStateID() == AC_SKILL_E) {

		log("on updateBox: if act");
		body->removeAllShapes();
		body->addShape(PhysicsShapeBox::create(Size(bodySize.width + 30, bodySize.height) * 2, material));
		if (getSprite()->isFlippedX()) {
			body->setPositionOffset(Vec2(-30, 0));
		}
		else {
			body->setPositionOffset(Vec2(30, 0));
		}
		body->setContactTestBitmask(0xFFFFFFFF);
	}
	else {
		log("Moster: on updateBox: if not act");
		body->setPositionOffset(Vec2(0, 0));
		body->removeAllShapes();
		body->addShape(PhysicsShapeBox::create(bodySize * 2, material));
		body->setContactTestBitmask(0xFFFFFFFF);
	}
}

float monster::getDistance()
{
	return getPositionX() - getRival()->getPositionX();
}

void monster::continuSkill()
{
	if (SkillQue.empty())return;
	int skill = SkillQue.front();
	SkillQue.pop_front();
	switch (skill)
	{
	case AC_SKILL_B:
		runSkillBAnimation();
		break;
	case AC_SKILL_C:
		runSkillCAnimation();
		break;
	default:
		break;
	}
}