#ifndef __LOOK_H__
#define __LOOK_H__

#include "icommand.h"
#include "../Utils/uncopyable.h"


namespace advcpp
{

class Maze;

class Look : public ICommand , private Uncopyable
{
public:
	const std::string Execute(size_t _heroID, Maze &_maze);

};

} //namespace advcpp

#endif /* __LOOK_H__ */

