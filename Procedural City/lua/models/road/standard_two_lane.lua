dofile("lua/lib/vectors.lua")

--Building functions
baseIndex = 0
function createQuad(x,y,z,upX,upY,upZ,rightX,rightY,rightZ)
	normalX,normalY,normalZ = normalize(crossProduct(upX,upY,upZ,rightX,rightY,rightZ))
	
	addVertex(x,y,z)
	addUV(0,0)
	addNormal(normalX,normalY,normalZ)
	
	addVertex(x+rightX,y+rightY,z+rightZ)
	addUV(1,0)
	addNormal(normalX,normalY,normalZ)
	
	addVertex(x+rightX+upX,y+rightY+upY,z+rightZ+upZ)
	addUV(1,1)
	addNormal(normalX,normalY,normalZ)
	
	addVertex(x+upX,y+upY,z+upZ)
	addUV(0,1)
	addNormal(normalX,normalY,normalZ)
	
	addTriangle(baseIndex + 0, baseIndex + 1, baseIndex + 2)
	addTriangle(baseIndex + 2, baseIndex + 3, baseIndex + 0)
	
	baseIndex = baseIndex + 4
end

--Road
createNode()
setTexture("road.standard_two_lane.tex")
createQuad(-16,0,16, 0,0,-32, 32,0,0)

--Sidewalk
createNode()
baseIndex = 0
setTexture("road.sidewalk.tex")

createQuad(-6,0.15,16, 0,0,-32, 2,0,0)
createQuad(4,0.15,16, 0,0,-32, 2,0,0)

--Flat behind sidewalk
createNode()
baseIndex = 0

createQuad(-16,0.15,16, 0,0,-32, 10,0,0)
createQuad(6,0.15,16, 0,0,-32, 10,0,0)

--Curb
createNode()
baseIndex = 0

createQuad(-4,0,16, 0,0.15,0, 0,0,-32)	--Inner left
createQuad(4,0,-16, 0,0.15,0, 0,0,32)	--Inner right

createQuad(-16,0,-16, 0,0.15,0, 0,0,32)	--Outer left
createQuad(16,0,16, 0,0.15,0, 0,0,-32)	--Outer right

createQuad(-16,0,16, 0,0.15,0, 12,0,0)	--Front left
createQuad(4,0,16, 0,0.15,0, 12,0,0)	--Front right

createQuad(-4,0,-16, 0,0.15,0, -12,0,0)	--Back left
createQuad(16,0,-16, 0,0.15,0, -12,0,0)	--Back right