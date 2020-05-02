#ifndef __QUIT_H__
#define __QUIT_H__

#include <string>
#include "icommand.h"
#include "../Utils/uncopyable.h"


namespace advcpp
{

class Maze;

class Quit : public ICommand , private Uncopyable
{
public:
	const std::string Execute(size_t _heroID, Maze &_maze);

private:
	
};

} //namespace advcpp

#endif /* __QUIT_H__ */

