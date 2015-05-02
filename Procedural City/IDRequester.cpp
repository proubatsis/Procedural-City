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

#include "IDRequester.h"

irr::s32 IDRequester::currentMinId = 1;

irr::s32 IDRequester::request()
{
	irr::s32 id = currentMinId;
	currentMinId++;
	return id;
}

IDPool IDRequester::requestPool(irr::s32 idCount)
{
	irr::s32 min = currentMinId;
	irr::s32 max = currentMinId + idCount - 1;
	currentMinId += max + 1;
	return IDPool(min, max);
}
