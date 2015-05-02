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