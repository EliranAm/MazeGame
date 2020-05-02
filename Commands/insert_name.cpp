#include "insert_name.h"
#include "../Objects/maze.h"
#include "../Objects/room.h"
#include "../Objects/hero.h"

#define COLOR_RESET	"\x1b[0m"
#define COLOR_BOLD	"\x1b[01m"
#define COLOR_GREEN	"\x1b[32m"

namespace advcpp
{


const std::string InsertName::ExecuteOther(size_t _heroId, Maze& _maze, const std::string& _command)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroId);
	SPHero hero = room->GetHero(_heroId);
	hero->SetName(_command);
	hero->SetStatus(Hero::COMMAND);
	return COLOR_BOLD COLOR_GREEN "Welcome " + _command + "\n" COLOR_RESET + room->GetRoomInfo() + room->ShowHerosInRoom() + room->Show(_heroId);
}


}//namespace advcpp


