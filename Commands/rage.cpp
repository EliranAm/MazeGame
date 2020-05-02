#include "rage.h"

#include "../Objects/hero.h"
#include "../Objects/room.h"
#include <tr1/memory>
#include <string>

namespace advcpp
{

const std::string Rage::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	Room::SPHero hero =  room->GetHero(_heroID);
	hero->SetStatus(Hero::RAGE);
	std::string retVal = "This is a very dangerous actionn you can hurt yourself\nare you sure?? (y/n)\n";
	return retVal;
}


}	//namespace advcpp
