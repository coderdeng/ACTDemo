#pragma once

#include "role.h"
#include "stateManage.h"

class AIRole : public Role
{
public:
	AIRole();
	virtual ~AIRole();
	CREATE_FUNC(AIRole);

	virtual float getDistance();
	virtual void changeRunState(stateSpace::state *newState);
	virtual stateSpace::state* myNextAction();

	CC_SYNTHESIZE(Role*, _rival, Rival);

protected:
	CC_SYNTHESIZE(stateSpace::state*, _currentState, CurrentState);

protected:
	virtual stateSpace::state* normalThinking();
	virtual stateSpace::state* attackThinking();
	virtual stateSpace::state* injuredThinking();
	
private:

};