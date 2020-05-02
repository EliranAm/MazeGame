#include "left.h"
#include "../Objects/room.h"


namespace advcpp
{

const std::string Left::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	room->Left(_heroID);
	return room->Show(_heroID);
}

} //namespace advcpp
