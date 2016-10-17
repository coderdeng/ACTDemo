function Foo:speak()
	print("hello, I am a Foo")
end

local foo = Foo.new("fred")
local m = foo:add(3, 4)

print(m)

foo:speak()

Foo.add_ = Foo.add

function Foo:add(a, b)
	return "here comes the magic: "..self:add_(a, b)
end

m = foo:add(9, 8)

print(m)
