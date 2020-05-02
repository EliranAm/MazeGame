#ifndef __IOTHER_COMMANDS_H__
#define __IOTHER_COMMANDS_H__

#include <string>
#include "../Utils/uncopyable.h"

namespace advcpp
{

class Maze;

class IOtherCommands : private Uncopyable
{
public:
	virtual ~IOtherCommands(){}
	virtual const std::string ExecuteOther(size_t _heroId, Maze& _maze, const std::string& _command) = 0;  

};



}//namespace advcpp


#endif /* __IOTHER_COMMANDS_H__ */

