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

function createCylinder(cx,cy,cz, sx,sy,sz)
	angle = 0
	count = 16
	addTriangles = 0
	for i = 1, count + 1 do
		x,z = math.cos(angle), math.sin(angle)
		
		addVertex(x*sx/2+cx,cy,z*sz/2+cz)
		addVertex(x*sx/2+cx,sy+cy,z*sz/2+cz)
		addNormal(x,z); addNormal(x,z);
		addUV((i-1)/count,0); addUV((i-1)/count,1);
		
		if i > 1 then
			addTriangle(baseIndex - 2, baseIndex - 1, baseIndex + 1)
			addTriangle(baseIndex + 1, baseIndex + 0, baseIndex - 2)
		end
		baseIndex = baseIndex + 2
		
		angle = angle + math.rad(360) / count
	end
end

--Road
createNode()
setTexture("plants.grass.tex")
createCylinder(0,0,0, 1,1,1)
