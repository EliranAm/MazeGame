#ifndef __COMMAND_FACTORY_H__
#define __COMMAND_FACTORY_H__

#include <string>
#include <map>
#include "../Commands/icommand.h"

namespace advcpp
{

class CommandFactory 
{
typedef std::tr1::shared_ptr<ICommand> SPCommand;
	
public:
	CommandFactory();
	SPCommand Create(const std::string &_commandType);

private:
	std::map<const std::string, SPCommand> m_commandsContainer;
};


} //namespace advcpp
#endif /* __COMMAND_FACTORY_H__ */

