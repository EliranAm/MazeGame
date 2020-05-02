#ifndef __COMMAND_MANAGER_H__
#define __COMMAND_MANAGER_H__

#include <map>
#include <vector>
#include <string>
#include "../Utils/command_factory.h"
#include "../Utils/uncopyable.h"
#include "default_action.h"


namespace advcpp
{

class ICommand;
class GameComunication;
class Maze;

class CommandManager : private Uncopyable
{
typedef std::tr1::shared_ptr<ICommand> SPCommand;
typedef std::map<const std::string, SPCommand> CommandMap;

public:
	CommandManager(std::vector<std::string> _commands, GameComunication& _gameCom);
	~CommandManager() {}
	
	const std::string ExecuteCommand(size_t _heroID, const std::string &_command, Maze &_maze);

private:
	class InitCommands 
	{
	public:
		explicit InitCommands(CommandMap& _map);
		void operator()(const std::string& _command);
	
	private:
		CommandMap& m_map;
		CommandFactory m_commandFactory;
	};

	CommandMap m_commandContainer;
	DefaultAction  m_defaultAct;
};

} //namespace advcpp

#endif /* __COMMAND_MANAGER_H__ */

