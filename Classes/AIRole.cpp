#include "AIRole.h"
#include <ctime>
#include <random>

AIRole::AIRole() : 
	Role()
{

}

AIRole::~AIRole() 
{

}
/*
 *	Function		:	getDistance
 *	Description		:	get the distance between the rival and role
 *	Return			:	the distance
 *	Others			:	// 其它说明 
 */
float AIRole::getDistance()
{
	return getPositionX() - getRival()->getPositionX();
}

/*
 *	Function		:	changeRunState 
 *	Description		:	change the role's state and execute 
 *	Others			:	 
 */
void AIRole::changeRunState(stateSpace::state *newState)
{
	if (!newState)
		return;
	_currentState->Exit();
	_currentState = newState;
	newState = nullptr;
	//_currentState->Execute(this);
}

/*
 *	Function		:	myNextAction
 *	Description		:	get the next state of roleSelf
 *	Calls			:	normalThinking, attackThinking, injuredThinking 
 *	Return			:	the role's next state
 *	Others			:	
 */
stateSpace::state* AIRole::myNextAction()
{
	stateSpace::state *nextState = nullptr;
	switch (_currentState->getStateID())
	{
	case AC_STAND:
	case AC_RUN:
		nextState = normalThinking();
		break;
	}
	return nextState;
}

/*
 *	Function		:	// 函数名称 
 *	Description		:	// 函数功能、性能等的描述 
 *	Return			:	// 函数返回值的说明 
 *	Others			:	// 其它说明 
 */
stateSpace::state* AIRole::normalThinking()
{
	std::uniform_int_distribution<int> u(0, 100);
	std::default_random_engine e(time(0));
	stateSpace::state* s = nullptr;

	switch (_rival->getCurStateID())
	{
	case AC_STAND:
	case AC_RUN:
		if (abs(getDistance()) > 100) {
			if (u(e) < 30) {
				s = new stateSpace::state_run;
			}
			else if (u(e) < 50) {
				s = new stateSpace::state_leave;
			}
			else
				s = new stateSpace::state_normal;
		}
		else {
			if (u(e) < 90) {
				s = new stateSpace::state_skill_a;
			}
			else {
				s = new stateSpace::state_leave;
			}
		}
		break;
	case AC_SKILL_A:
	case AC_SKILL_B:
	case AC_SKILL_C:
	case AC_SKILL_D:
	case AC_SKILL_E:
		if (abs(getDistance()) < 100) {
			if (u(e) < 50) {
				s = new stateSpace::state_defend;
			}
			else
				s = new stateSpace::state_leave;
		}
		else
			s = new stateSpace::state_normal;
		break;
	default:
		break;
	}
	return s;
}

stateSpace::state* AIRole::attackThinking()
{
	return new stateSpace::state_normal;
}

stateSpace::state* AIRole::injuredThinking()
{
	return new stateSpace::state_normal;
}