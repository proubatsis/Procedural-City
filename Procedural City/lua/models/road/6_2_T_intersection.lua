--[[
    Copyright (C) 2015 Panagiotis Roubatsis

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
--]]

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
setTexture("road.6_6_T_intersection.tex")	--6to6 shader also appropriate for 6to2
createQuad(-16,0,16, 0,0,-32, 32,0,0)

--Sidewalk
createNode()
baseIndex = 0
setTexture("road.sidewalk.tex")
createQuad(-16,0.15,16, 0,0,-32, 4,0,0)				--Left
createQuadUV(12,0.15,16, 0,0,-12, 4,0,0, 1,0.375)	--Right Top
createQuadUV(12,0.15,-4, 0,0,-12, 4,0,0, 1,0.375)	--Right Bottom

--Curb
createNode()
baseIndex = 0

createQuad(-12,0,16, 0,0.15,0, 0,0,-32)	--Inner left
createQuad(-16,0,-16, 0,0.15,0, 0,0,32)	--Outer left
createQuad(-16,0,16, 0,0.15,0, 4,0,0)	--Front left
createQuad(-12,0,-16, 0,0.15,0, -4,0,0)	--Back left

createQuad(12,0,-16, 0,0.15,0, 0,0,12)	--Inner right top
createQuad(16,0,-4, 0,0.15,0, 0,0,-12)	--Outer right top
createQuad(12,0,-4, 0,0.15,0, 4,0,0)	--Front right top
createQuad(16,0,-16, 0,0.15,0, -4,0,0)	--Back right top

createQuad(12,0,4, 0,0.15,0, 0,0,12)	--Inner right bottom
createQuad(16,0,16, 0,0.15,0, 0,0,-12)	--Outer right bottom
createQuad(12,0,16, 0,0.15,0, 4,0,0)	--Front right bottom
createQuad(16,0,4, 0,0.15,0, -4,0,0)	--Back right bottom