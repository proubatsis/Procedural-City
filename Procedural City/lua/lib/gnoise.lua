gradients = {}
size = 256	--Size of gradients array
function initialize()
	for i = 0, size-1, 1 do
		gradients[i] = math.random() * 2 - 1
	end
end

function lattice(x,y,fx,fy)
	i = math.floor(x*5323 + y*5287) % (size - 2)
	return gradients[i] * fx + gradients[i+1]*fy
end

--Smooth interpolation (3x^2 - 2x^3)
function interpolate(a,b,t)
	return (t*t*(3-2*t)) * (b - a) + a
end

function gnoise(x,y)
	ix = math.floor(x)
	iy = math.floor(y)
	fx = x - ix
	fy = y - iy
	
	top = interpolate(lattice(ix,iy,fx,fy), lattice(ix+1,iy,fx-1,fy), fx)
	bottom = interpolate(lattice(ix,iy+1,fx,fy-1), lattice(ix+1,iy+1,fx-1,fy-1), fx)
	
	return interpolate(top, bottom, fy)
end
