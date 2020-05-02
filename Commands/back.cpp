#include <iostream>
#include "back.h"
#include "../Objects/maze.h"
#include "../Objects/room.h"


namespace advcpp
{

const std::string Back::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	Location::Direction location = room->ReverseLocation(_heroID);
	std::pair<bool, Room*> res = room->GetNearByRoom(location);
	std::string retVal;
	if (res.first)
	{
		Room::SPHero hero = room->ExitHero(_heroID);
		res.second->InsertHero(_heroID, hero);
		_maze.ChangePosition(_heroID, res.second->GetRoomID());
		return "You have entered to a new room!\n" + res.second->GetRoomInfo() + res.second->ShowHerosInRoom() + res.second->Show(_heroID);
	}
	
	return "Can't Pass Throw!\n";
}

} //namespace advcpp




