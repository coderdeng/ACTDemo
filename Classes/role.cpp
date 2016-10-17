#include "role.h"

Role::Role() :
_sprite(nullptr),
_runAnimn(nullptr),
_standAnimn(nullptr),
_deadAnimn(nullptr),
_defendAnimn(nullptr),
_injuredAnimn(nullptr),
_skillA(nullptr),
_skillB(nullptr),
_skillC(nullptr),
_skillD(nullptr),
_skillE(nullptr),
_allowMove(true),
_bloodVolume(100),
_curHurtV(0)
{}

Role::~Role()
{
	CC_SAFE_RELEASE_NULL(_sprite);
	CC_SAFE_RELEASE_NULL(_runAnimn);
	CC_SAFE_RELEASE_NULL(_standAnimn);
	CC_SAFE_RELEASE_NULL(_deadAnimn);
	CC_SAFE_RELEASE_NULL(_defendAnimn);
	CC_SAFE_RELEASE_NULL(_injuredAnimn);
	CC_SAFE_RELEASE_NULL(_skillA);
	CC_SAFE_RELEASE_NULL(_skillB);
	CC_SAFE_RELEASE_NULL(_skillC);
	CC_SAFE_RELEASE_NULL(_skillD);
	CC_SAFE_RELEASE_NULL(_skillE);
}

bool Role::init()
{
	if (!Node::init()){
		return false;
	}
	return true;
}

bool Role::changeState(RoleActionStateID state)
{
	if (getCurStateID() == state){
		return false;
	}
	setCurStateID(state);
	return true;
}

void Role::runStandAnimation()
{
	if (changeState(AC_STAND)){
		getSprite()->stopAllActions();
		getSprite()->runAction(getStandAnimation());
		setNextStateID(AC_STAND);
		setAllowMove(true);
	}
}

void Role::runDeadAnimation()
{
	if (changeState(AC_DEAD)){
		getSprite()->stopAllActions();
		getSprite()->runAction(getDeadAnimation());
		setNextStateID(AC_STAND);
		setAllowMove(false);
	}
}

void Role::runRunAnimation()
{
	if (changeState(AC_RUN)){
		getSprite()->stopAllActions();
		getSprite()->runAction(getRunAnimation());
		setNextStateID(AC_STAND);
		setAllowMove(true);
	}
}

void Role::runDefendAnimation()
{
	if (changeState(AC_DEFEND)){
		getSprite()->stopAllActions();
		getSprite()->runAction(getDefendAnimation());
		setNextStateID(AC_STAND);
		setAllowMove(false);
	}
}

void Role::runInjuredAnimation()
{
	if (changeState(AC_INJURED)) {
		getSprite()->stopAllActions();
		getSprite()->runAction(getInjuredAnimation());
		setNextStateID(AC_STAND);
		setAllowMove(false);
	}
}

void Role::runSkillAAnimation()
{
	if (changeState(AC_SKILL_A)){
		getSprite()->stopAllActions();
		getSprite()->runAction(getSkillA());
		setAllowMove(false);
	}
}

void Role::runSkillBAnimation()
{
	if (changeState(AC_SKILL_B)){
		getSprite()->stopAllActions();
		getSprite()->runAction(getSkillB());
		setAllowMove(false);
	}
}

void Role::runSkillCAnimation()
{
	if (changeState(AC_SKILL_C)){
		getSprite()->stopAllActions();
		getSprite()->runAction(getSkillC());
		setAllowMove(false);
	}
}

void Role::runSkillDAnimation()
{
	if (changeState(AC_SKILL_D)){
		getSprite()->stopAllActions();
		getSprite()->runAction(getSkillD());
		setAllowMove(false);
	}
}

void Role::runSkillEAnimation()
{
	if (changeState(AC_SKILL_E)){
		getSprite()->stopAllActions();
		getSprite()->runAction(getSkillE());
		setAllowMove(false);
	}
}

void Role::createStandAnimCallback(Node *pSender)
{
	runNextAnimation();
}

void Role::injuredCallback()
{
	setBloodVolume(getBloodVolume() - getCurHurtV());
	CCLOG("Role: %f", _bloodVolume);
	setCurHurtV(0);
}

void Role::runNextAnimation()
{
	switch (getNextStateID())
	{
	case AC_DEAD:
		runDeadAnimation();
		break;
	case AC_INJURED:
		runInjuredAnimation();
		break;
	case AC_SKILL_A:
		runSkillAAnimation();
		break;
	case AC_SKILL_B:
		runSkillBAnimation();
		break;
	case AC_SKILL_C:
		runSkillCAnimation();
		break;
	case AC_SKILL_D:
		runSkillDAnimation();
		break;
	case AC_SKILL_E:
		runSkillEAnimation();
		break;
	case AC_RUN:
		runRunAnimation();
		break;
	case AC_DEFEND:
		runDefendAnimation();
		break;
	default:
		runStandAnimation();
		break;
	}
}