#pragma once

#include "cocos2d.h"
#include <deque>
#include "stateManage.h"

USING_NS_CC;

class Role : public Node{
public:
	Role();
	virtual ~Role();
	virtual bool init();
	CREATE_FUNC(Role);

	//角色精灵
	CC_SYNTHESIZE_RETAIN(Sprite*, _sprite, Sprite);
	CC_SYNTHESIZE(bool, _allowMove, AllowMove);
	//角色拥有的动画
	CC_SYNTHESIZE_RETAIN(Action*, _runAnimn, RunAnimation);
	CC_SYNTHESIZE_RETAIN(Action*, _standAnimn, StandAnimation);
	CC_SYNTHESIZE_RETAIN(Action*, _deadAnimn, DeadAnimation);
	CC_SYNTHESIZE_RETAIN(Action*, _defendAnimn, DefendAnimation);
	CC_SYNTHESIZE_RETAIN(Action*, _injuredAnimn, InjuredAnimation);
	CC_SYNTHESIZE_RETAIN(Action*, _skillA, SkillA);
	CC_SYNTHESIZE_RETAIN(Action*, _skillB, SkillB);
	CC_SYNTHESIZE_RETAIN(Action*, _skillC, SkillC);
	CC_SYNTHESIZE_RETAIN(Action*, _skillD, SkillD);
	CC_SYNTHESIZE_RETAIN(Action*, _skillE, SkillE);

	//角色当前状态 ID
	CC_SYNTHESIZE(RoleActionStateID, _curStateID, CurStateID);
	//角色下一帧状态 ID
	CC_SYNTHESIZE(RoleActionStateID, _nextStateID, NextStateID);
	//角色当前受到的伤害
	CC_SYNTHESIZE(float, _curHurtV, CurHurtV);

	//角色连招状态
	std::deque<RoleActionStateID> SkillQue;

	//攻击碰撞矩形
	CC_SYNTHESIZE(Rect, _hitBox, HitBox);
	//血量
	CC_SYNTHESIZE(float, _bloodVolume, BloodVolume);

public:
	void runStandAnimation();
	void runDeadAnimation();
	void runRunAnimation();
	void runDefendAnimation();
	void runInjuredAnimation();

	virtual void runSkillAAnimation();
	virtual void runSkillBAnimation();
	virtual void runSkillCAnimation();
	virtual void runSkillDAnimation();
	virtual void runSkillEAnimation();

protected:
	Size bodySize;
	bool changeState(RoleActionStateID state);
	void createStandAnimCallback(Node* pSender);
	void runNextAnimation();
	void injuredCallback();

};
