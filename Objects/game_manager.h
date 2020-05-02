#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__


#include <tr1/memory>
#include <string>
#include <map>
#include <signal.h> /*handler*/
#include "hero.h"
#include "../Utils/uncopyable.h"
#include "maze.h"
#include "../Utils/comunication.h"
#include "../Commands/command_manager.h"

namespace advcpp
{

class Parser;
class HeroPosition;

class GameManager : private Uncopyable
{
private:
typedef std::tr1::shared_ptr<Room> SPRoom;
typedef std::tr1::shared_ptr<Hero> SPHero;
typedef std::tr1::shared_ptr<CommandManager> SPCommMan;

static bool s_runFlag;

public:
	GameManager(Parser& _parser, size_t _port = 5100);
	void Start();
	
	
private:
	static void InitSignalHandler();
	static void ServerSigHandler(int _sigNum, siginfo_t *_info, void *_contex);
	const std::string ShowEntranceScreen() const;
	SPCommMan CreateCommands();

	Maze m_maze;
	GameComunication m_gameCom;
	SPCommMan m_commandManager;
};

} //namespace advcpp 
#endif /* __GAME_MANAGER_H__ */

