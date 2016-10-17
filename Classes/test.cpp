#include "test.h"
#include <sstream>

Foo::Foo()
{
	std::cout << "Foo is borm" << std::endl;
}

Foo::Foo(const std::string &name) : name(name)
{
	std::cout << "Foo is borm by name" << std::endl;
}

std::string Foo::Add(int a, int b)
{
	std::stringstream ss;
	ss << name << ":" << a << "+" << b << " = " << (a + b);
	return ss.str();
}

Foo::~Foo()
{
	std::cout << "Foo is gone" << std::endl;
}

int l_Foo_constructor(lua_State* l)
{
	const char *name = luaL_checkstring(l, 1);
	Foo ** udatea = (Foo **)lua_newuserdata(l, sizeof(Foo*));
	*udatea = new Foo(name);
	return 1;
}

Foo* l_CheckFoo(lua_State* l, int n)
{
	return *(Foo **)luaL_checkudata(l, n, "luaL_Foo");
}

int l_Foo_add(lua_State* l)
{
	Foo *foo = l_CheckFoo(l, 1);
	int a = luaL_checknumber(l, 2);
	int b = luaL_checknumber(l, 3);
	std::string s = foo->Add(a, b);
	lua_pushstring(l, s.c_str());
	return 1;
}

int l_Foo_destructor(lua_State* l)
{
	Foo *foo = l_CheckFoo(l, 1);
	delete foo;
	return 0;
}

void RegisterFoo(lua_State* l)
{
	luaL_Reg sFooRegs[] =
	{
		{"new", l_Foo_constructor},
		{"new", l_Foo_add},
		{"__gs", l_Foo_destructor},
		{NULL, NULL}
	};
	luaL_newmetatable(l, "luaL_Foo");
	luaL_register(l, NULL, sFooRegs);
	lua_setfield(l, -1, "__index");
	lua_setglobal(l, "Foo");
}