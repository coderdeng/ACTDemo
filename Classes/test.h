#pragma once
#include <iostream>
#include <string>
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "tolua++.h"
}


class Foo
{
public:
	Foo();
	Foo(const std::string &name);
	~Foo();
	std::string Add(int a, int b);
private:
	std::string name;
};

int l_Foo_constructor(lua_State *l);
Foo *l_CheckFoo(lua_State *l, int n);
int l_Foo_add(lua_State *l);
int l_Foo_destructor(lua_State *l);
void RegisterFoo(lua_State *l);
