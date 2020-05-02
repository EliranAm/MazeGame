#ifndef __I_COMMAND_H__
#define __I_COMMAND_H__

#include "../Objects/maze.h"


namespace advcpp
{

class ICommand 
{
public:
	ICommand(){}
	virtual ~ICommand(){}

	virtual const std::string Execute(size_t _heroID, Maze &_maze) = 0;
};

} //namespace advcpp
#endif /* __I_COMMAND_H__ */

