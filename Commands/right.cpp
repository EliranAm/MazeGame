#include "right.h"
#include "../Objects/room.h"
#include "../Objects/maze.h"


namespace advcpp
{


const std::string Right::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	room->Right(_heroID);
	return room->Show(_heroID);
}

} //namespace advcpp
