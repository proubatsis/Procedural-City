#define GPX(i,w) (i%w)
#define GPY(i,w) (i/w)
#define GI(x,y,w) (y*w+x)

#define CEMENT_WIDTH 0.28
#define METAL_THICKNESS 0.12
#define HCW CEMENT_WIDTH/2
#define HMT METAL_THICKNESS/2

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

int windowTile(float x, float y)
{
	float xp = pulse(HCW, 1-HCW, x);
	float yp = pulse(HMT, 1-HMT, y);
	
	if(xp == 1 && yp == 0)
	{
		return 1;	//Metal
	}else if(xp == 0)
	{
		return 2;	//Cement
	}
	return 3;		//Window
}

float skyscraper(float x, float y)
{
	float sx = x * 5;
	float sy = y * 25;
	int ix = (int)sx;
	int iy = (int)sy;
	float fx = sx - ix;
	float fy = sy - iy;
	
	int w = windowTile(fx, fy);
	if(w != 3)
		return w;
		
	w = 4;	//Normal
	if(iy%2 == 0)
		w = 5;	//Alternate colour
		
	return w;
}

__kernel void generate_texture(__global unsigned char *imgData, int width, int height) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
	
	unsigned char r, g, b;
	float c = skyscraper(GPX(i,width)/(float)width, GPY(i,width)/(float)height);
	
	if(c == 1)
	{
		r = 87;
		g = 97;
		b = 102;
	}else if(c == 2)
	{
		r = 153;
		g = r;
		b = r;
	}else if(c == 4)
	{
		r = 51;
		g = 77;
		b = 128;
	}else
	{
		r = 104;
		g = 128;
		b = 179;
	}
	
	i = i * 4;
	
    // Do the operation
	imgData[i] = b;			//B
	imgData[i+1] = g;		//G
	imgData[i+2] = r;		//R
	imgData[i+3] = 255;		//A
}
