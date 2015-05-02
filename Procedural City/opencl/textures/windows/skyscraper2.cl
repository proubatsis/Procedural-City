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

#define WINDOW_HEIGHT 0.35
#define HWH WINDOW_HEIGHT/2

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

float3 windowTile(int ix)
{
	ix = ix%5;
	
	if(ix == 1) return (float3)(0.2, 0.2, 0.2);
	if(ix == 2) return (float3)(0, 0, 0.2);
	if(ix == 3) return (float3)(0.2, 0.2, 0);
	if(ix == 4) return (float3)(0, 0.1, 0.2);
	return (float3)(0, 0, 0.2);
}

float3 skyscraper(float x, float y)
{
	float sx = x * 5;
	float sy = y * 25;
	int ix = (int)sx;
	int iy = (int)sy;
	float fx = sx - ix;
	float fy = sy - iy;
	
	float p = pulse(0.5-HWH, 0.5+HWH, fy);
	if(p > 0)
	{
		if(iy%2 == 0) return windowTile(ix+1);
		return windowTile(ix);
	}
		
	return (float3)(0.9,0.9,0.84);
}

__kernel void generate_texture(__global unsigned char *imgData, int width, int height) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
	
	float3 c = skyscraper(GPX(i,width)/(float)width, GPY(i,width)/(float)height);
	
	i = i * 4;
	
    // Do the operation
	imgData[i] = 255*c.z;		//B
	imgData[i+1] = 255*c.y;		//G
	imgData[i+2] = 255*c.x;		//R
	imgData[i+3] = 255;			//A
}
