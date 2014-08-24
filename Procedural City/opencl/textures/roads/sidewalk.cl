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

color sideWalk(float x, float y)
{
	float sx = 15 * x + 1;
	float sy = 15 * y + 1;
	int ix = (int)sx;
	int iy = (int)sy;
	float fx = sx - ix;
	float fy = sy - iy;
	
	float p = pulse(0.4,0.6,fy) + pulse(0.49,0.51,fy);
	color clr;
	if(p == 2.0)
	{
		clr.r = 26;
		clr.g = 26;
		clr.b = 26;
	}else if(p == 1.0)
	{
		clr.r = 77;
		clr.g = 77;
		clr.b = 77;
	}else
	{
		clr.r = 102;
		clr.g = 102;
		clr.b = 102;
	}
	return clr;
}

__kernel void generate_texture(__global unsigned char *imgData, int width, int height) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
	
	unsigned char r, g, b;
	color c = sideWalk(GPX(i,width)/(float)width, GPY(i,width)/(float)height);
	
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