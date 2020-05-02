#include <algorithm>
#include "command_manager.h"
#include "icommand.h"
#include "../Objects/room.h"
#include "../Objects/maze.h"
#include "../Utils/command_factory.h"

namespace advcpp
{

CommandManager::CommandManager(std::vector<std::string> _commands, GameComunication& _gameCom)
	: m_defaultAct(DefaultAction(_gameCom))
{
	std::for_each(_commands.begin(), _commands.end(), InitCommands(m_commandContainer));
}

CommandManager::InitCommands::InitCommands(CommandMap& _map)
	: m_map(_map)
{
}

void CommandManager::InitCommands::operator()(const std::string& _command)
{
	m_map.insert(std::pair<const std::string, SPCommand>(_command, m_commandFactory.Create(_command)));
}

const std::string CommandManager::ExecuteCommand(size_t _heroID, const std::string &_command, Maze &_maze)
{
    CommandMap::iterator itr = m_commandContainer.find(_command);
    if (itr != m_commandContainer.end())
	{
		return itr->second->Execute(_heroID, _maze);
	}

	m_defaultAct.SetCommand(_command);
    return m_defaultAct.Execute(_heroID, _maze);
}

} //namespace advcpp
