#define GPX(i,w) (i%w)
#define GPY(i,w) (i/w)
#define GI(x,y,w) (y*w+x)

__kernel void generate_texture(__global unsigned char *imgData, int width, int height) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
	
	int x = GPX(i,width);
	
	i = i * 4;
	
    // Do the operation
	imgData[i] = x/2;		//B
	imgData[i+1] = x/2;		//G
	imgData[i+2] = x/2;		//R
	imgData[i+3] = 255;		//Alpha
}