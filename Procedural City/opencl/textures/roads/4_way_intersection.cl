/*
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
*/

#define GPX(i,w) (i%w)
#define GPY(i,w) (i/w)
#define GI(x,y,w) (y*w+x)

#define LINE_THICKNESS 0.25
#define HLT (LINE_THICKNESS/2)

float sstep(float a, float x)
{
	if(x >= a)
	{
		return 1;
	}
	return 0;
}

float pulse(float a, float b, float x)
{
	return sstep(a, x) - sstep(b, x);
}

int crossWalk(float x, float y)
{
	float sx = x * 32 + 1;
	float sy = y * 32 + 1;
	int ix = (int)sx;
	int iy = (int)sy;
	float fx = sx - ix;
	float fy = sy - iy;
	
	if(iy == 1 || iy == 3 || iy == 30 || iy == 32)
	{
		float c = pulse(0.5-HLT,0.5+HLT,fy);
		return (int)c * 255;
	}else if(ix == 1 || ix == 3 || ix == 30 || ix == 32)
	{
		float c = pulse(0.5-HLT,0.5+HLT,fx);
		return (int)c * 255;
	}
	
	return 0;
}

__kernel void generate_texture(__global unsigned char *imgData, int width, int height) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
	
	unsigned char r, g, b;
	int c = crossWalk(GPX(i,width)/(float)width, GPY(i,width)/(float)height);
	
	r = c;
	g = r;
	b = r;
	
	i = i * 4;
	
    // Do the operation
	imgData[i] = b;			//B
	imgData[i+1] = g;		//G
	imgData[i+2] = r;		//R
	imgData[i+3] = 255;		//A
}

