#include "shouting.h"
#include "../Objects/maze.h"
#include "../Objects/room.h"
#include "../Objects/hero.h"

namespace advcpp
{

Shouting::Shouting(GameComunication& _gameCom)
	: m_gameCom(_gameCom)
{
}


const std::string Shouting::ExecuteOther(size_t _heroId, Maze& _maze, const std::string& _command)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroId);
	Room::SPHero hero = room->GetHero(_heroId);
	
	_maze.TalkToAllHeros(m_gameCom, hero->GetName(), _command);
	
	hero->SetStatus(Hero::COMMAND);
	return "";
}


}//namespace advcpp
