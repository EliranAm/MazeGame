#include "quiting.h"
#include "../Utils/comunication.h"
#include "../Objects/maze.h"
#include "../Objects/room.h"
#include "../Objects/hero.h"

namespace advcpp
{

Quiting::Quiting(GameComunication& _gameCom)
	: m_gameCom(_gameCom)
{
}


const std::string Quiting::ExecuteOther(size_t _heroId, Maze& _maze, const std::string& _command)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroId);
	Room::SPHero hero = room->GetHero(_heroId);
	hero->SetStatus(Hero::COMMAND);
	if(!_command.compare("y"))
	{
		room->ExitHero(_heroId);;
		_maze.RemovePosition(_heroId);
		m_gameCom.ClosePlayerConnection(_heroId);
		return "";
	}
	
	if(!_command.compare("n"))
	{
		return "Continue...\n";
	}
	
	return "Invalid choice\n";
}


}//namespace advcpp


