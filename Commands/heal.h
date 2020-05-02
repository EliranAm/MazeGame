#ifndef __HEAL_H__
#define __HEAL_H__

#include "icommand.h"
#include "../Utils/uncopyable.h"
#include "../Objects/maze.h"


namespace advcpp
{

class Heal : public ICommand , private Uncopyable
{
public:
	const std::string Execute(size_t _heroID, Maze &_maze);
private:
		
};

}	


#endif /* __HEAL_H__ */

