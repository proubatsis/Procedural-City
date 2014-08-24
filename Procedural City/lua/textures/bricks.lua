--Periodic function of pulses
function pulseWave(x, length)
	h = -0.5*math.cos(6.28*x)+0.5
	if h > (1 - length) then
		return 1
	else
		return 0;
	end
end

function brickTexture(x, y)
	c = 0
	
	xx = 5*x
	yy = 12.5*(y-10)	--Translate to avoid bad bricks
	
	if (math.floor(yy)%2) == 0 then
		c = pulseWave(xx, 0.99)
	else
		c = pulseWave(5*(x-0.5), 0.99)
	end
	c = c + pulseWave(yy, 0.99)
	
	if c > 1 then
		return 0.5,0,0		--Red
	else
		return 0.3,0.3,0.3	--Gray
	end
end

--Create Image
WIDTH = 512
HEIGHT = 512

createImage(WIDTH, HEIGHT)
for x = 0, WIDTH, 1 do
	for y = 0, HEIGHT, 1 do
	
		fx = x / WIDTH
		fy = y / HEIGHT
		
		r,g,b = brickTexture(fx, fy)
		setPixel(x, y, r, g, b)
	end
end
