#include "take.h"
#include "../Objects/maze.h"
#include "../Objects/room.h"
#include "../Objects/hero.h"

namespace advcpp
{

const std::string Take::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	return room->TakeTreasure(_heroID);
}


}//namespace advcpp
