--Building functions
function createTreeBranchNode(px,py,pz, sx,sy,sz, rx,ry,rz)
	createNode()
	baseIndex = 0
	setTexture("plants.tree.wood.tex")
	
	faces = 16
	for i = 1, faces + 1 do
		angle = (math.rad(360)/faces) * (i-1)
		x,z = math.cos(angle), math.sin(angle)
		
		addVertex(x*sx, 0, z*sz)
		addVertex(x*sx/2, sy, z*sz/2)
		addNormal(x, 0, z); addNormal(x, 0, z);
		addUV((i-1)/faces,0); addUV((i-1)/faces,1);
		
		if i > 1 then
			addTriangle(baseIndex - 2, baseIndex - 1, baseIndex + 1)
			addTriangle(baseIndex + 1, baseIndex + 0, baseIndex - 2)
		end
		baseIndex = baseIndex + 2
	end
	
	setRotation(rx, ry, rz)
	setPosition(px, py, pz)
	switchToNode(0)	--This is so that all co-ordinates will be relative to the origin
end

function createLeafNode(px,py,pz, sx,sy,sz, rx,ry,rz)
	createNode()
	baseIndex = 1	--Accounts for the center vertex
	setTexture("plants.grass.tex")
	
	addVertex(0,0,0)	--Center vertex (Index 0)
	addNormal(0,1,0)
	addUV(0.5,0.5)
	
	sides = 8	--Create an octagon
	for i = 1, sides do
		angle = (math.rad(360) / (sides-1)) * (i-1)
		x,z = math.cos(angle),math.sin(angle)
		
		addVertex(x*sx, 0, z*sz)
		addNormal(0,1,0)
		addUV(0.5*x+0.5,0.5*z+0.5)
		
		if i > 1 then
			--addTriangle(baseIndex - 1, baseIndex + 0, 0)
			addTriangle(baseIndex - 1, 0, baseIndex + 0)
		end
		baseIndex = baseIndex + 1
	end
	
	setRotation(rx, ry, rz)
	setPosition(px, py, pz)
	switchToNode(0)
end

--Standard stack data type with push and pop functions
Stack = {}
Stack.__index = Stack
function Stack.create()
	local s = {}
	setmetatable(s, Stack)
	s.stackValues = {}	--Where the elements in the stack will be held
	return s
end
function Stack:push(element)
	table.insert(self.stackValues, 1, element)
end
function Stack:pop()
	element = self.stackValues[1]
	table.remove(self.stackValues, 1)
	return element
end

--Defines a tree branch size, rotation and position
TreeBranch = {}
TreeBranch.__index = TreeBranch
function TreeBranch.create(x,y,z, sx,sy,sz, rx,ry,rz)
	local tb = {}
	setmetatable(tb, TreeBranch)
	tb.x=x; tb.y=y; tb.z=z;
	tb.sx=sx; tb.sy=sy; tb.sz=sz;
	tb.rx=rx; tb.ry=ry; tb.rz=rz;
	tb.upX=0; tb.upY=1; tb.upZ=0;
	return tb;
end
function TreeBranch:rotateX(angle)
	self.upX,self.upY,self.upZ = rotateAroundX(self.upX,self.upY,self.upZ, angle)
	self.rx = self.rx + angle
end
function TreeBranch:rotateZ(angle)
	self.upX,self.upY,self.upZ = rotateAroundZ(self.upX,self.upY,self.upZ, angle)
	self.rz = self.rz + angle
end
function TreeBranch:move()
	self.x = self.x + self.upX * self.sy
	self.y = self.y + self.upY * self.sy
	self.z = self.z + self.upZ * self.sy
	
	self.sx = self.sx/2
	self.sy = self.sy/1.2
	self.sz = self.sz/2
end
function TreeBranch:createCopy()
	local tb = {}
	setmetatable(tb, TreeBranch)
	tb.x=self.x; tb.y=self.y; tb.z=self.z;
	tb.sx=self.sx; tb.sy=self.sy; tb.sz=self.sz;
	tb.rx=self.rx; tb.ry=self.ry; tb.rz=self.rz;
	tb.upX=self.upX; tb.upY=self.upY; tb.upZ=self.upZ;
	return tb
end
function TreeBranch:draw()
	createTreeBranchNode(self.x,self.y,self.z, self.sx,self.sy,self.sz, self.rx,self.ry,self.rz)
	if self.sy < 2.45 then
		lX = self.x + self.upX * self.sy
		lY = self.y + self.upY * self.sy
		lZ = self.z + self.upZ * self.sy
		createLeafNode(lX,lY,lZ, 1.2,1,1.2, self.rx,self.ry,self.rz)
	end
end

function randAngle()
	--[[r=math.random()
	if r > 0.8 then
		return 50
	elseif r > 0.6 then
		return 40
	else
		return 45
	end]]--
	return 45
end

--L-System
axiom = "D"
rules = "D[<D][>D][+D][-D]"
lSystem = axiom
repetitions = 4	--How many times the tree should branch off

--Create the L-System
for i = 1, repetitions do
	lSystem = string.gsub(lSystem, axiom, rules)
end

curr = TreeBranch.create(0,0,0, 0.5,5,0.5, 0,0,0)	--Trunk
s = Stack.create()
--Draw the L-System
for i = 1, #lSystem do
	action = string.sub(lSystem,i,i)
	
	if action == "D" then
		curr:draw()
		curr:move()
	elseif action == "[" then
		s:push(curr:createCopy())
	elseif action == "]" then
		curr = s:pop()
	elseif action == "<" then
		curr:rotateZ(-randAngle())
	elseif action == ">" then
		curr:rotateZ(randAngle())
	elseif action == "+" then
		curr:rotateX(randAngle())
	elseif action == "-" then
		curr:rotateX(-randAngle())
	end
end