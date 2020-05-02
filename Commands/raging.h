#ifndef __RAGING_H__
#define __RAGING_H__

#include <string>
#include <tr1/memory>
#include "../Objects/hero.h"
#include "../Objects/room.h"
#include "iother_commands.h"


namespace advcpp
{

class Maze;
class GameComunication;

class Raging: public IOtherCommands 
{
typedef std::tr1::shared_ptr<Hero> SPHero;
typedef std::tr1::shared_ptr<Room> SPRoom;

public:
	Raging(GameComunication& _gameCom);
	const std::string ExecuteOther(size_t _heroId, Maze& _maze, const std::string& _command);
	
private:
	const std::string Rage(size_t _heroID, Maze &_maze);
	void ResetHero(size_t _heroID, Maze &_maze, SPRoom _room);
	
	GameComunication& m_gameCom;
	
};

}//namespace advcpp



#endif /* __RAGING_H__ */

