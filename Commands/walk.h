#ifndef __WALK_H__
#define __WALK_H__

#include <string>
#include "icommand.h"
#include "../Utils/uncopyable.h"


namespace advcpp
{

class Maze;

class Walk : public ICommand , private Uncopyable
{
public:
	const std::string Execute(size_t _heroID, Maze &_maze);

private:
	
};

} //namespace advcpp

#endif /* __WALK_H__ */

