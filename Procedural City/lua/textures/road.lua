function step(a, x)
	if x >= a then
		return 1
	else
		return 0
	end
end

function pulse(a, b, x)
	return step(a, x) - step(b, x)
end

WIDTH = 512;
HEIGHT = 512;

createImage(WIDTH, HEIGHT);

THICKNESS = 0.15
SPLIT = 0.35

wMin = 0.5 - (THICKNESS / 2)
wMax = 0.5 + (THICKNESS / 2)
sMin = 0.5 - (SPLIT / 2)
sMax = 0.5 + (SPLIT / 2)

for x = 0, WIDTH, 1 do
	for y = 0, HEIGHT, 1 do
		fx = x / WIDTH
		fy = y / HEIGHT
		c = pulse(wMin, wMax, fx) - pulse(sMin, sMax, fy)
		setPixel(x, y, c, c, 0)
	end
end
