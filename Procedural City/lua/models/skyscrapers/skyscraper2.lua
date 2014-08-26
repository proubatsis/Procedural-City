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

--Ground
createNode()
createQuad(-16,0,16, 0,0,-32, 32,0,0)

--4 Walls
createNode()
baseIndex = 0
setTexture("windows.skyscraper2.tex")

createQuad(-15,0,15, 0,100,0, 30,0,0)	--Front
createQuad(15,0,-15, 0,100,0, -30,0,0)	--Back

createQuad(-15,0,-15, 0,100,0, 0,0,30)	--Left
createQuad(15,0,15, 0,100,0, 0,0,-30)	--Right

--Roof (Generally Won't be seen)
createQuad(-15, 100, 15, 0,0,-30, 30,0,0)