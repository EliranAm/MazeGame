#include "talk.h"

#include "../Objects/hero.h"
#include "../Objects/room.h"
#include <tr1/memory>
#include <string>

namespace advcpp
{

const std::string Talk::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	Room::SPHero hero =  room->GetHero(_heroID);
	hero->SetStatus(Hero::TALKING);
	std::string retVal = "What do yo want to say??\n";
	return retVal;
}


}	//namespace advcpp
