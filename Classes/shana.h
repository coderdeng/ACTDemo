#pragma once

#include "cocos2d.h"
#include "role.h"

USING_NS_CC;

class shana : public Role
{
public:
	shana();
	~shana();
	virtual bool init();
	CREATE_FUNC(shana);
	//移动，按方向键时，判断角色所在的状态，如果正在进行其他动作不执行
	void onMove();
	//停止，一般在绑定在其他动作之后
	void onStop();
	//角色技能动画
	virtual void runSkillAAnimation();
	virtual void runSkillBAnimation();
	virtual void runSkillCAnimation();
	virtual void runSkillDAnimation();
	virtual void runSkillEAnimation();

	CC_SYNTHESIZE(bool, _canMutiAtk, CanMutilAttack);

private:
	void updateBox();
	virtual void update(float delta);
	void updateSelf();
	void centerViewOfPoint(Vec2 pos);
	void attackCallbackFunc(Node *pSender);
	void continuSkill();
};
