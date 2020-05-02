#ifndef __TALKING_H__
#define __TALKING_H__

#include <string>
#include <tr1/memory>
#include "../Objects/hero.h"
#include "iother_commands.h"

namespace advcpp
{

class Maze;
class GameComunication;

class Talking: public IOtherCommands
{
typedef std::tr1::shared_ptr<Hero> SPHero;

public:
	explicit Talking(GameComunication& _gameCom);
	const std::string ExecuteOther(size_t _heroId, Maze& _maze, const std::string& _command);
	
private:
	GameComunication& m_gameCom;
	
};

}//namespace advcpp



#endif /* __TALKING_H__ */

