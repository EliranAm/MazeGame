#ifndef __CREATE_HERO_H__
#define __CREATE_HERO_H__

#include "icommand.h"
#include "../Utils/uncopyable.h"
#include "../Objects/maze.h"


namespace advcpp
{

class CreateHero : public ICommand , private Uncopyable
{
public:
	const std::string Execute(size_t _heroID, Maze &_maze);
private:
	const std::string ShowEntranceScreen() const;	
};

}	//namespace advcpp

#endif /* __CREATE_HERO_H__ */

