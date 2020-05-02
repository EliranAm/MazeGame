#ifndef __SHOUT_H__
#define __SHOUT_H__


#include <string>
#include "icommand.h"
#include "../Utils/uncopyable.h"


namespace advcpp
{

class Maze;

class Shout : public ICommand , private Uncopyable
{
public:
	const std::string Execute(size_t _heroID, Maze &_maze);

private:
	
};

} //namespace advcpp



#endif /* __SHOUT_H__ */

