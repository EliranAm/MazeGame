#include "command_factory.h"

#include "../Commands/look.h"
#include "../Commands/left.h"
#include "../Commands/right.h"
#include "../Commands/walk.h"
#include "../Commands/back.h"
#include "../Commands/open.h"
#include "../Commands/close.h"
#include "../Commands/attack.h"
#include "../Commands/take.h"
#include "../Commands/talk.h"
#include "../Commands/shout.h"
#include "../Commands/unlock.h"
#include "../Commands/lock.h"
#include "../Commands/help.h"
#include "../Commands/heal.h"
#include "../Commands/quit.h"
#include "../Commands/rage.h"
#include "../Commands/create_hero.h"


namespace advcpp
{

CommandFactory::CommandFactory()
{
	m_commandsContainer[""] = SPCommand(new CreateHero);
	m_commandsContainer["look"] = SPCommand(new Look);
	m_commandsContainer["walk"] = SPCommand(new Walk);
	m_commandsContainer["right"] = SPCommand(new Right);
	m_commandsContainer["left"] = SPCommand(new Left);
	m_commandsContainer["open"] = SPCommand(new Open);
	m_commandsContainer["close"] = SPCommand(new Close);
	m_commandsContainer["back"] = SPCommand(new Back);
	m_commandsContainer["attack"] = SPCommand(new Attack);
	m_commandsContainer["take"] = SPCommand(new Take);
	m_commandsContainer["talk"] = SPCommand(new Talk);
	m_commandsContainer["shout"] = SPCommand(new Shout);
	m_commandsContainer["unlock"] = SPCommand(new Unlock);
	m_commandsContainer["lock"] = SPCommand(new Lock);
	m_commandsContainer["help"] = SPCommand(new Help);
	m_commandsContainer["heal"] = SPCommand(new Heal);
	m_commandsContainer["rage"] = SPCommand(new Rage);
	m_commandsContainer["quit"] = SPCommand(new Quit);

}


CommandFactory::SPCommand CommandFactory::Create(const std::string &_commandType)
{
	return m_commandsContainer[_commandType];
}

} //namespace advcpp
