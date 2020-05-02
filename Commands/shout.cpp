#include "shout.h"
#include "../Objects/maze.h"
#include "../Objects/room.h"
#include "../Objects/hero.h"

namespace advcpp
{

const std::string Shout::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	Room::SPHero hero =  room->GetHero(_heroID);
	hero->SetStatus(Hero::SHOUTING);
	std::string retVal = "What do yo want to shout??\n";
	return retVal;
}


}//namespace advcpp
