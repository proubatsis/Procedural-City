--Vector Functions
function crossProduct(ax,ay,az,bx,by,bz)
	cx = ay*bz-az*by
	cy = az*bx-ax*bz
	cz = ax*by-ay*bx
	
	return cx,cy,cz
end

function normalize(x,y,z)
	m = math.sqrt((x*x)+(y*y)+(z*z))
	nx = x/m
	ny = y/m
	nz = z/m
	
	return nx,ny,nz
end

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

function createTriangle(x,y,z,upX,upY,upZ,rightX,rightY,rightZ)
	normalX,normalY,normalZ = normalize(crossProduct(upX,upY,upZ,rightX,rightY,rightZ))
	
	addVertex(x,y,z)
	addUV(0,0)
	addNormal(normalX,normalY,normalZ)
	
	addVertex(x+rightX,y+rightY,z+rightZ)
	addUV(1,0)
	addNormal(normalX,normalY,normalZ)
	
	addVertex(x+upX+rightX/2,y+upY+rightY/2,z+upZ+rightZ/2)
	addUV(0.5,1)
	addNormal(normalX,normalY,normalZ)
	
	addTriangle(baseIndex + 0, baseIndex + 1, baseIndex + 2)
	
	baseIndex = baseIndex + 3
end

--4 Walls
createNode()
setTexture("bricks.red.tex")

createQuad(-0.5,0,0.5, 0,1,0, 1,0,0)		--Front Wall
createQuad(0.5,0,-0.5, 0,1,0, -1,0,0)	--Back Wall

createQuad(-0.5,0,-0.5, 0,1,0, 0,0,1)	--Left Wall
createQuad(0.5,0,0.5, 0,1,0, 0,0,-1)		--Right Wall

--Two Windows
createNode()
baseIndex = 0
setTexture("windows.window.tex")

createQuad(-0.35,0.62,0.501, 0,0.2,0, 0.2,0,0)	--Left Window
createQuad(0.15,0.62,0.501, 0,0.2,0, 0.2,0,0)	--Right Window

--Roof
createNode()
baseIndex = 0
setTexture("roof.tex")

createTriangle(-0.55,0.982,0.55, 0,0.5,-0.55, 1.1,0,0)	--Roof Front
createTriangle(0.55,0.982,-0.55, 0,0.5,0.55, -1.1,0,0)	--Roof Back
createTriangle(-0.55,0.982,-0.55, 0.55,0.5,0, 0,0,1.1)	--Roof Left
createTriangle(0.55,0.982,0.55, -0.55,0.5,0, 0,0,-1.1)	--Roof Right

createQuad(0.55,0.982,0.55, 0,0,-1.1, -1.1,0,0)			--Base of the roof

--Door
createNode()
baseIndex = 0
setVertexColor(0,0,150)

createQuad(-0.1,0,0.501, 0,0.4,0, 0.2,0,0)