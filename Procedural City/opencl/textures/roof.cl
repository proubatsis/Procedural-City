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

float pulseWave(float x, float length)
{
	float h = -0.5*cospi(2*x)+0.5;
	if(h > (1.0-length))
	{
		return 1.0;
	}else
	{
		return 0.0;
	}
}

float roof(float x, float y)
{
	float cx = 5.0 * x;
	float cx2 = 5.0 * (x-0.5);
	float cy = 5.0 * (y - 10.0);
	
	bool shift = ((int)cy)%2==0;
	float c = 0.0;
	if(shift)
	{
		c = pulseWave(cx, 0.99);
	}else
	{
		c = pulseWave(cx2,0.99);
	}
	c = c + pulseWave(cy, 0.99);
	
	return c;
}

__kernel void generate_texture(__global unsigned char *imgData, int width, int height) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
	
	unsigned char r, g, b;
	float c = roof(GPX(i,width)/(float)width, GPY(i,width)/(float)height);
	
	if(c > 1.0)
	{
		r = 51;
		g = r;
		b = r;
	}else
	{
		r = 26;
		g = r;
		b = r;
	}
	
	i = i * 4;
	
    // Do the operation
	imgData[i] = b;			//B
	imgData[i+1] = g;		//G
	imgData[i+2] = r;		//R
	imgData[i+3] = 255;		//A
}