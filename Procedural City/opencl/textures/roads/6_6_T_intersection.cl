#define GPX(i,w) (i%w)
#define GPY(i,w) (i/w)
#define GI(x,y,w) (y*w+x)

#define LINE_THICKNESS 0.25
#define SPLIT 0.5
#define HLT (LINE_THICKNESS/2)
#define HSP (SPLIT/2)

typedef struct Color
{
	int r, g, b;
}color;

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
	
	if(ix == 30 || ix == 32)
	{
		float c = pulse(0.5-HLT,0.5+HLT,fx);
		return (int)c * 255;
	}
	
	return 0;
}

color solidYellow(float x, float y)
{
	float c = pulse(0.5-HLT, 0.5+HLT, x);
	color clr;
	clr.r = c * 255;
	clr.g = c * 255;
	clr.b = 0;
	
	return clr;
}

color brokenWhite(float x, float y)
{
	float c = pulse(0.5-HLT, 0.5+HLT, x) - pulse(0.5-HSP, 0.5+HSP, y);
	
	color clr;
	clr.r = 0;
	clr.g = 0;
	clr.b = 0;
	
	if(c > 0.0)
	{
		clr.r = c * 255;
		clr.g = c * 255;
		clr.b = c * 255;
	}
	
	return clr;
}

color road(float x, float y)
{
	float sx = x * 31 + 1;
	float sy = y * 31 + 1;
	int ix = (int)sx;
	int iy = (int)sy;
	float fx = sx - ix;
	float fy = sy - iy;
	
	if(crossWalk(x,y) == 255)
	{
		color clr;
		clr.r = 255;
		clr.g = 255;
		clr.b = 255;
		return clr;
	}
	
	if(ix == 16)
	{
		return solidYellow(fx, fy);
	}
	if(ix == 8 || ix == 12 || ix == 20 || ix == 24)
	{
		return brokenWhite(fx, fy);
	}
	
	color c;
	c.r = 0;
	c.g = 0;
	c.b = 0;
	
	return c;
}

__kernel void generate_texture(__global unsigned char *imgData, int width, int height) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
	
	unsigned char r, g, b;
	color c = road(GPX(i,width)/(float)width, GPY(i,width)/(float)height);
	
	r = c.r;
	g = c.g;
	b = c.b;
	
	i = i * 4;
	
    // Do the operation
	imgData[i] = b;			//B
	imgData[i+1] = g;		//G
	imgData[i+2] = r;		//R
	imgData[i+3] = 255;		//A
}