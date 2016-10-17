#pragma once
#include "AIRole.h"

class monster : public AIRole
{
public:
	monster();
	virtual ~monster();
	virtual bool init();
	CREATE_FUNC(monster);
	
	void onMove();
	void onStop();
	virtual void runSkillAAnimation();
	virtual void runSkillBAnimation();
	virtual void runSkillCAnimation();
	virtual void runSkillDAnimation();
	virtual void runSkillEAnimation();
	float getDistance();

private:
	void updateBox();
	virtual void update(float dalta);
	void attackCallbackFunc(Node *pSender);
	void continuSkill();

};