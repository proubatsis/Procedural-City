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
