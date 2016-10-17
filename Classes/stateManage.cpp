#include "stateManage.h"
#include "AIRole.h"

using namespace stateSpace;
///the execute of normal state
state_normal::state_normal()
{
	stateID = AC_STAND;
}
void state_normal::Execute(AIRole *AIr)
{
	AIr->runStandAnimation();
	AIr->changeRunState(AIr->myNextAction());
}
void state_normal::Exit()
{
	delete this;
}

/// run state
state_run::state_run()
{
	stateID = AC_RUN;
}
void state_run::Execute(AIRole *AIr)
{
	AIr->runRunAnimation();
	AIr->changeRunState(AIr->myNextAction());
}
void state_run::Exit()
{
	delete this;
}
/// leave state
state_leave::state_leave()
{
	stateID = AC_RUN;
}
void state_leave::Execute(AIRole *AIr)
{
	if (AIr->getDistance() > 0) {
		AIr->getSprite()->setFlippedX(false);
	}
	else AIr->getSprite()->setFlippedX(true);
	AIr->runRunAnimation();
	AIr->changeRunState(AIr->myNextAction());
}
void state_leave::Exit()
{
	delete this;
}

///the execute of attack state
state_skill_a::state_skill_a()
{
	stateID = AC_SKILL_A;
}
void state_skill_a::Execute(AIRole *AIr)
{
	AIr->runSkillAAnimation();
	AIr->changeRunState(AIr->myNextAction());
}
void state_skill_a::Exit()
{
	delete this;
}

/// state_skill_b
state_skill_b::state_skill_b()
{
	stateID = AC_SKILL_B;
}
void state_skill_b::Execute(AIRole* AIr)
{
	AIr->runSkillBAnimation();
	AIr->changeRunState(AIr->myNextAction());
}
void state_skill_b::Exit() {
	delete this;
}

/// state_skill_c
state_skill_c::state_skill_c()
{
	stateID = AC_SKILL_C;
}
void state_skill_c::Execute(AIRole* AIr)
{
	AIr->runSkillCAnimation();
	AIr->changeRunState(AIr->myNextAction());
}
void state_skill_c::Exit()
{
	delete this;
}

/// state_skill_d
state_skill_d::state_skill_d()
{
	stateID = AC_SKILL_D;
}
void state_skill_d::Execute(AIRole* AIr)
{
	AIr->runSkillDAnimation();
	AIr->changeRunState(AIr->myNextAction());
}
void state_skill_d::Exit()
{
	delete this;
}

/// state_skill_e
state_skill_e::state_skill_e()
{
	stateID = AC_SKILL_E;
}
void state_skill_e::Excute(AIRole* AIr)
{
	AIr->runSkillEAnimation();
	AIr->changeRunState(AIr->myNextAction());
}
void state_skill_e::Exit()
{
	delete this;
}

///the execute of defend state
state_defend::state_defend()
{
	stateID = AC_DEFEND;
}
void state_defend::Execute(AIRole *AIr)
{
	AIr->runDefendAnimation();
	AIr->changeRunState(AIr->myNextAction());
}
void state_defend::Exit()
{
	delete this;
}

///the execute of dinjured state
state_injured::state_injured()
{
	stateID = AC_INJURED;
}
void state_injured::Execute(AIRole *AIr)
{
	AIr->runInjuredAnimation();
	AIr->changeRunState(AIr->myNextAction());
}
void state_injured::Exit()
{
	delete this;
}

///the execute of death state
state_death::state_death()
{
	stateID = AC_DEAD;
}
void state_death::Execute(AIRole *AIr)
{
	AIr->runDeadAnimation();
	AIr->changeRunState(AIr->myNextAction());
}
void state_death::Exit()
{
	delete this;
}
