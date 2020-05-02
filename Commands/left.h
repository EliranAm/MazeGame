#ifndef __LEFT_H__
#define __LEFT_H__

#include <string>
#include "icommand.h"
#include "../Utils/uncopyable.h"
#include "../Objects/maze.h"

namespace advcpp
{

class Left;

class Left : public ICommand , private Uncopyable
{
public:
	const std::string Execute(size_t _heroID, Maze &_maze);
	
private:

};

} //namespace advcpp

#endif /* __LEFT_H__ */

