#ifndef __RAGE_H__
#define __RAGE_H__

#include "icommand.h"
#include "../Utils/uncopyable.h"
#include "../Objects/maze.h"


namespace advcpp
{

class Rage : public ICommand , private Uncopyable
{
public:
	const std::string Execute(size_t _heroID, Maze &_maze);
private:
		
};

}	


#endif /* __RAGE_H__ */
