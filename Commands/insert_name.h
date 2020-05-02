#ifndef __INSERT_NAME_H__
#define __INSERT_NAME_H__

#include <string>
#include <tr1/memory>
#include "../Objects/hero.h"
#include "iother_commands.h"

namespace advcpp
{

class Maze;

class InsertName: public IOtherCommands 
{
typedef std::tr1::shared_ptr<Hero> SPHero;
public:

	const std::string ExecuteOther(size_t _heroId, Maze& _maze, const std::string& _command);
	
};

}//namespace advcpp

#endif /* __INSERT_NAME_H__ */

