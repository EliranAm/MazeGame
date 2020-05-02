#include "help.h"
#include "../Objects/maze.h"
#include "../Objects/room.h"

namespace advcpp
{

const std::string Help::Execute(size_t _heroID, Maze &_maze)
{
	return _maze.GetAllCommands();
}

} //namespace advcpp




