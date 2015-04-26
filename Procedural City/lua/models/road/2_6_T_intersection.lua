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

function createQuadUV(x,y,z,upX,upY,upZ,rightX,rightY,rightZ,uvX,uvY)
	normalX,normalY,normalZ = normalize(crossProduct(upX,upY,upZ,rightX,rightY,rightZ))
	
	addVertex(x,y,z)
	addUV(0,0)
	addNormal(normalX,normalY,normalZ)
	
	addVertex(x+rightX,y+rightY,z+rightZ)
	addUV(uvX,0)
	addNormal(normalX,normalY,normalZ)
	
	addVertex(x+rightX+upX,y+rightY+upY,z+rightZ+upZ)
	addUV(uvX,uvY)
	addNormal(normalX,normalY,normalZ)
	
	addVertex(x+upX,y+upY,z+upZ)
	addUV(0,uvY)
	addNormal(normalX,normalY,normalZ)
	
	addTriangle(baseIndex + 0, baseIndex + 1, baseIndex + 2)
	addTriangle(baseIndex + 2, baseIndex + 3, baseIndex + 0)
	
	baseIndex = baseIndex + 4
end

--Intersection
createNode()
setTexture("road.T_intersection.tex")
createQuad(-16,0,16, 0,0,-32, 32,0,0)

--Sidewalk
createNode()
baseIndex = 0
setTexture("road.sidewalk.tex")

createQuad(-6,0.15,16, 0,0,-32, 2,0,0)	--Top of T

createQuadUV(16,0.15,-12, -12,0,0, 0,0,-4, 1,0.375)	--Left of T
createQuadUV(16,0.15,16, -12,0,0, 0,0,-4, 1,0.375)	--Right of T

--Flat behind sidewalk
createNode()
baseIndex = 0
createQuad(-16,0.15,16, 0,0,-32, 10,0,0)	--Left

--Curb
createNode()
baseIndex = 0

createQuad(-4,0,16, 0,0.15,0, 0,0,-32)	--Inner left
createQuad(-16,0,-16, 0,0.15,0, 0,0,32)	--Outer left
createQuad(-16,0,16, 0,0.15,0, 12,0,0)	--Front left
createQuad(-4,0,-16, 0,0.15,0, -12,0,0)	--Back left

--Top Right
createQuad(4,0,16, 0,0.15,0, 12,0,0)	--Front
createQuad(16,0,12, 0,0.15,0, -12,0,0)	--Back
createQuad(4,0,12, 0,0.15,0, 0,0,4)		--Left
createQuad(16,0,16, 0,0.15,0, 0,0,-4)	--Right

--Bottom Right
createQuad(4,0,-12, 0,0.15,0, 12,0,0)	--Front
createQuad(16,0,-16, 0,0.15,0, -12,0,0)	--Back
createQuad(4,0,-16, 0,0.15,0, 0,0,4)	--Left
createQuad(16,0,-12, 0,0.15,0, 0,0,-4)	--Right