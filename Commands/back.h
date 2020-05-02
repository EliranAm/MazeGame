#ifndef __BACK_H__
#define __BACK_H__

#include "icommand.h"
#include "../Utils/uncopyable.h"
#include <string>


namespace advcpp
{

class Maze;

class Back : public ICommand , private Uncopyable
{
public:
	const std::string Execute(size_t _heroID, Maze &_maze);

private:
	
};

}//namespace advcpp

#endif /* __BACK_H__ */

