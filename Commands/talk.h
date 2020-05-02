#ifndef __TALK_H__
#define __TALK_H__

#include "icommand.h"
#include "../Objects/maze.h"
#include "../Utils/uncopyable.h"


namespace advcpp
{

class Talk : public ICommand , private Uncopyable
{
public:
	const std::string Execute(size_t _heroID, Maze &_maze);
private:
		
};

}	


#endif /* __TALK_H__ */

