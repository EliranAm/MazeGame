#ifndef __HELP_H__
#define __HELP_H__

#include <string>
#include "../Utils/uncopyable.h"
#include "icommand.h"


namespace advcpp
{

class Maze;

class Help : public ICommand , private Uncopyable
{
public:
	const std::string Execute(size_t _heroID, Maze &_maze);

private:
	
};

} //namespace advcpp

#endif /* __HELP_H__ */

