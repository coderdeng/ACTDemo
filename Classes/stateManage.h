#pragma once

class AIRole;

enum RoleActionStateID {
	AC_STAND = 0,
	AC_RUN,
	AC_DEAD,
	AC_DEFEND,
	AC_INJURED,
	AC_SKILL_A,
	AC_SKILL_B,
	AC_SKILL_C,
	AC_SKILL_D,
	AC_SKILL_E
};

namespace stateSpace {
	class stateManage;
	class state;
	class state_normal;
	class state_run;
	class state_leave;
	class state_skill_a;
	class state_skill_b;
	class state_skill_c;
	class state_skill_d;
	class state_skill_e;
	class state_defend;
	class state_injured;
	class state_death;
};
/*
 *class: mamage the state change
 */
class stateSpace::stateManage
{
	
};
/*
 *class: base of AIRole state
 */
class stateSpace::state
{
public:
	virtual void Execute(AIRole*) = 0;
	virtual void Exit() = 0;
	virtual RoleActionStateID getStateID() { return stateID; };
protected:
	RoleActionStateID stateID;
	enum {
		attackDistance = 150,
		skillDistance = 200
	};
};
/*
 *class: normal state of AIRole
 */
class stateSpace::state_normal : public state
{
public:
	state_normal();
	void Execute(AIRole*);
	void Exit();
};
/*
 * class: run state of AIRole
 */
class stateSpace::state_run : public state
{
public:
	state_run();
	void Execute(AIRole*);
	void Exit();
};

class stateSpace::state_leave : public state
{
public:
	state_leave();
	void Execute(AIRole*);
	void Exit();
};

/*
 *class: attack state of AIRole
 */
class stateSpace::state_skill_a : public state
{
public:
	state_skill_a();
	void Execute(AIRole*);
	void Exit();
};

class stateSpace::state_skill_b : public state
{
public:
	state_skill_b();
	void Execute(AIRole*);
	void Exit();
};

class stateSpace::state_skill_c :public state
{
public:
	state_skill_c();
	void Execute(AIRole*);
	void Exit();
};

class stateSpace::state_skill_d : public state
{
public:
	state_skill_d();
	void Execute(AIRole*);
	void Exit();
};

class stateSpace::state_skill_e : public state
{
public:
	state_skill_e();
	void Excute(AIRole*);
	void Exit();
};

/*
 *class: defend state of AIRole
 */
class stateSpace::state_defend : public state
{
public:
	state_defend();
	void Execute(AIRole*);
	void Exit();
};
/*
 *class: injured state of AIRole
 */
class stateSpace::state_injured : public state
{
public:
	state_injured();
	void Execute(AIRole*);
	void Exit();
};
/*
 *class: death state of AIRole
 */
class stateSpace::state_death : public state
{
public:
	state_death();
	void Execute(AIRole*);
	void Exit();
};