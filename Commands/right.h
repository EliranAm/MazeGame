#ifndef __RIGHT_H__
#define __RIGHT_H__

#include "icommand.h"
#include "../Utils/uncopyable.h"
#include <string>


namespace advcpp
{

class Maze;

class Right : public ICommand , private Uncopyable
{
public:
	const std::string Execute(size_t _heroID, Maze &_maze);
	
private:

};

} //namespace advcpp

#endif /* __RIGHT_H__ */

