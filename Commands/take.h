#ifndef __TAKE_H__
#define __TAKE_H__

#include <string>
#include "icommand.h"
#include "../Utils/uncopyable.h"

namespace advcpp
{

class Maze;

class Take : public ICommand , private Uncopyable
{
public:
	const std::string Execute(size_t _heroID, Maze &_maze);

private:
	
};

} //namespace advcpp



#endif /* __TAKE_H__ */

