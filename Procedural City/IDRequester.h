/*
	Created by Panagiotis Roubatsis
	Description: Assigns IDs for objects to be
	rendered by irrlicht.
*/

#ifndef ID_REQUESTER_H
#define ID_REQUESTER_H

#include <irrlicht.h>

//Manage a pool of IDs
class IDPool
{
private:
	irr::s32 _min, _max;
	irr::s32 _current;

public:
	IDPool() : _min(1), _max(100) {_current = 1;}

	IDPool(irr::s32 min, irr::s32 max)
		: _min(min), _max(max)
	{
		_current = min;
	}

	irr::s32 request()
	{
		irr::s32 id = _current;
		if(_current < _max) _current++;
		return id;
	}
};

//Request IDs
class IDRequester
{
private:
	static irr::s32 currentMinId;

public:
	static irr::s32 request();
	static IDPool requestPool(irr::s32 idCount);
};



#endif