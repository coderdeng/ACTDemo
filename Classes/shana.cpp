#include "shana.h"
#include "animateManage.h"

shana::shana()
{

}

shana::~shana(){}

//初始化角色shana，动作等
bool shana::init()
{
	if (!Role::init()){
		return false;
	}

	setSprite(Sprite::create("role/shana/shana_1.png", Rect(0, 0, 55, 62)));
	addChild(getSprite());
	bodySize = Size(55, 62);	

	//初始化动作
	setStandAnimation(RepeatForever::create(animateManage::createAnimate("role/shana/shana_1.png", 4, 6)));
	setRunAnimation(RepeatForever::create(animateManage::createAnimate("role/shana/shana_forward.png", 8, 8)));
	setDeadAnimation(RepeatForever::create(animateManage::createAnimate("role/shana/shana_dead.png", 3, 3)));
	setDefendAnimation(RepeatForever::create(animateManage::createAnimate("role/shana/shana_defend.png", 2, 4)));
	setInjuredAnimation(Sequence::create(
		animateManage::createAnimate("role/shana/shana_4.png", 2, 4),
		CallFuncN::create(CC_CALLBACK_0(shana::injuredCallback, this)),
		CallFuncN::create(CC_CALLBACK_1(shana::createStandAnimCallback, this)),
		NULL
	));
	setSkillA(Sequence::create(
		animateManage::createAnimate("role/shana/shana_2.png", 7, 14),
		CallFuncN::create(CC_CALLBACK_1(shana::attackCallbackFunc, this)),
		CallFuncN::create(CC_CALLBACK_1(shana::createStandAnimCallback, this)),
		CallFuncN::create(CC_CALLBACK_0(shana::continuSkill, this)),
		NULL
		));
	setSkillB(Sequence::create(
		animateManage::createAnimate("role/shana/shana_2extra1.png", 9, 18),
		CallFuncN::create(CC_CALLBACK_1(shana::attackCallbackFunc, this)),
		CallFuncN::create(CC_CALLBACK_1(shana::createStandAnimCallback, this)),
		CallFuncN::create(CC_CALLBACK_0(shana::continuSkill, this)),
		NULL
		));
	setSkillC(Sequence::create(
		animateManage::createAnimate("role/shana/shana_2extra2.png", 8, 16),
		CallFuncN::create(CC_CALLBACK_1(shana::attackCallbackFunc, this)),
		CallFuncN::create(CC_CALLBACK_1(shana::createStandAnimCallback, this)),
		NULL
		));
	setSkillD(Sequence::create(
		animateManage::createAnimate("role/shana/shana_2extra3.png", 13, 20),
		CallFuncN::create(CC_CALLBACK_1(shana::attackCallbackFunc, this)),
		CallFuncN::create(CC_CALLBACK_1(shana::createStandAnimCallback, this)),
		NULL
		));
	setSkillE(Sequence::create(
		animateManage::createAnimate("role/shana/shana_2extra4.png", 8, 20),
		CallFuncN::create(CC_CALLBACK_1(shana::attackCallbackFunc, this)),
		CallFuncN::create(CC_CALLBACK_1(shana::createStandAnimCallback, this)),
		NULL
		));
	
	runStandAnimation();
	scheduleUpdate();
	return true;
}

void shana::onMove()
{
	if (getCurStateID() == AC_RUN){
		if ((getPositionX() <= 0 && getSprite()->isFlippedX()) ||
			(getPositionX() >= 1280 && !getSprite()->isFlippedX())) {
			return;
		}
		if (getSprite()->isFlippedX()){
			runAction(MoveBy::create(1 / 60, Vec2(-4, 0)));
		}
		else {
			runAction(MoveBy::create(1 / 60, Vec2(4, 0)));
		}
	}
}

void shana::onStop()
{

}

void shana::runSkillAAnimation()
{
	Role::runSkillAAnimation();
	setCurStateID(AC_SKILL_A);
	setCanMutilAttack(true);
}

void shana::runSkillBAnimation()
{
	Role::runSkillBAnimation();
	setCurStateID(AC_SKILL_B);
	setCanMutilAttack(true);
}

void shana::runSkillCAnimation()
{
	Role::runSkillCAnimation();
	setCurStateID(AC_SKILL_C);
	setCanMutilAttack(true);
}

void shana::runSkillDAnimation()
{
	Role::runSkillDAnimation();
	if (getSprite()->isFlippedX()){
		runAction(Sequence::create(
			MoveBy::create(7 / 20, Vec2(-50, 0)),
			MoveBy::create(6 / 20, Vec2(-30, 0)),
			NULL
			));
	}
	else {
		runAction(Sequence::create(
			MoveBy::create(7 / 20, Vec2(50, 0)),
			MoveBy::create(6 / 20, Vec2(30, 0)),
			NULL
			));
	}
	setCurStateID(AC_SKILL_D);
	setCanMutilAttack(true);
}

void shana::runSkillEAnimation()
{
	Role::runSkillEAnimation();
	if (getSprite()->isFlippedX()){
		runAction(MoveBy::create(0.5f, Vec2(-200, 0)));
	}
	else {
		runAction(MoveBy::create(0.5f, Vec2(200, 0)));
	}
	setCurStateID(AC_SKILL_E);
	setCanMutilAttack(true);
}

void shana::updateBox()
{
	auto body = getPhysicsBody();
	PhysicsMaterial material(1.0f, 0.0f, 0.1f);
	log("Shana: updateBodyBox");
	if (getCurStateID() == AC_SKILL_A || getCurStateID() == AC_SKILL_B 
			|| getCurStateID() == AC_SKILL_C || getCurStateID() == AC_SKILL_D 
			|| getCurStateID() ==AC_SKILL_E) {

		log("Shana: on updateBox: if act");
		body->removeAllShapes();
		body->addShape(PhysicsShapeBox::create(Size(bodySize.width + 30, bodySize.height)*2, material));
		if (getSprite()->isFlippedX()) {
			body->setPositionOffset(Vec2(-30, 0));
		}
		else {
			body->setPositionOffset(Vec2(30, 0));
		}
		body->setContactTestBitmask(0xFFFFFFFF);
	}
	else {
		log("Shana: on updateBox: if not act");
		body->setPositionOffset(Vec2(0, 0));
		body->removeAllShapes();
		body->addShape(PhysicsShapeBox::create(bodySize*2, material));
		body->setContactTestBitmask(0xFFFFFFFF);
	}
}

void shana::update(float delta)
{
	onMove();
	updateBox();
}

void shana::updateSelf()
{

}

void shana::centerViewOfPoint(Vec2 pos)
{
	
}

void shana::attackCallbackFunc(Node *pSender)
{

}

void shana::continuSkill()
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