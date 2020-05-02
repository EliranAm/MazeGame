#include "default_action.h"
#include "insert_name.h"
#include "talking.h"
#include "shouting.h"
#include "quiting.h"
#include "raging.h"
#include "../Objects/room.h"
#include "../Objects/maze.h"


namespace advcpp
{

DefaultAction::DefaultAction(GameComunication& _gameCom)
	: m_gameCom(_gameCom)
{
	m_commandsMap.insert(std::pair<Hero::UserStatus, SPCommand>(Hero::NEW, SPCommand(new InsertName())));
	m_commandsMap.insert(std::pair<Hero::UserStatus, SPCommand>(Hero::TALKING, SPCommand(new Talking(m_gameCom))));
	m_commandsMap.insert(std::pair<Hero::UserStatus, SPCommand>(Hero::SHOUTING, SPCommand(new Shouting(m_gameCom))));
	m_commandsMap.insert(std::pair<Hero::UserStatus, SPCommand>(Hero::RAGE, SPCommand(new Raging(m_gameCom))));
	m_commandsMap.insert(std::pair<Hero::UserStatus, SPCommand>(Hero::QUIT, SPCommand(new Quiting(m_gameCom))));
}

void DefaultAction::SetCommand(const std::string& _command)
{
	m_command = _command;
}

const std::string DefaultAction::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
    Room::SPHero hero = room->GetHero(_heroID);
    
    OtherCommandMap::const_iterator itr = m_commandsMap.find(hero->GetStatus());
    if (itr != m_commandsMap.end())
    {
        return itr->second->ExecuteOther(_heroID, _maze, m_command);
    }
    
	return "ERROR\n";
}


} //namespace advcpp

