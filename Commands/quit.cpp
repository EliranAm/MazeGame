#include "quit.h"
#include "../Objects/maze.h"
#include "../Objects/room.h"

namespace advcpp
{

const std::string Quit::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	Room::SPHero hero =  room->GetHero(_heroID);
	hero->SetStatus(Hero::QUIT);
	
	return "Are you sure you Want to quit (y for Yes, n for NO)\n";
}

} //namespace advcpp




