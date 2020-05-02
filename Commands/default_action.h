#ifndef __DEFAULT_ACTION_H__
#define __DEFAULT_ACTION_H__

#include <string>
#include "icommand.h"
#include "iother_commands.h"


namespace advcpp
{

class GameComunication;
class Maze;

class DefaultAction : public ICommand
{
public:
typedef std::tr1::shared_ptr<IOtherCommands> SPCommand;
typedef std::map<Hero::UserStatus, SPCommand> OtherCommandMap;

public:
	explicit DefaultAction(GameComunication& _gameCom);
	const std::string Execute(size_t _heroID, Maze &_maze);
	void SetCommand(const std::string& _command);

private:
	std::string m_command;
	OtherCommandMap	  m_commandsMap;
	GameComunication& m_gameCom;
};

} //namespace advcpp


#endif /* __DEFAULT_ACTION_H__ */
