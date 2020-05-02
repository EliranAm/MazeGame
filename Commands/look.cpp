#include "look.h"
#include "../Objects/maze.h"
#include "../Objects/room.h"
#include "../Objects/hero.h"


namespace advcpp
{

const std::string Look::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	Room::SPHero hero  = room->GetHero(_heroID);
	return hero->PrintHero() + room->GetRoomInfo() + room->ShowHerosInRoom() + room->Show(_heroID);
}

} //namespace advcpp

