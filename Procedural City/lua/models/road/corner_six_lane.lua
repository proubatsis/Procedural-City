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

--Road
createNode()
setTexture("road.T_intersection.tex")
createQuad(-16,0,16, 0,0,-32, 32,0,0)

--Sidewalk
createNode()
baseIndex = 0
setTexture("road.sidewalk.tex")
createQuad(-16,0.15,16, 0,0,-32, 4,0,0)				--Left
createQuadUV(16,0.15,16, -28,0,0, 0,0,-4, 1,0.875)	--Top
createQuadUV(12,0.15,-12, 0,0,-4, 4,0,0, 0.01,0.01)	--Bottom right corner

--Curb
createNode()
baseIndex = 0

createQuad(-12,0,12, 0,0.15,0, 0,0,-28)	--Inner left
createQuad(-16,0,-16, 0,0.15,0, 0,0,32)	--Outer left
createQuad(-12,0,-16, 0,0.15,0, -4,0,0)	--Front left

--Top
createQuad(-16,0,16, 0,0.15,0, 32,0,0)	--Front
createQuad(16,0,12, 0,0.15,0, -28,0,0)	--Back
createQuad(16,0,16, 0,0.15,0, 0,0,-4)	--Right

--Bottom right corner
createQuad(12,0,-12, 0,0.15,0, 4,0,0)	--Front
createQuad(16,0,-16, 0,0.15,0, -4,0,0)	--Back
createQuad(12,0,-16, 0,0.15,0, 0,0,4)	--Left
createQuad(16,0,-12, 0,0.15,0, 0,0,-4)	--Right