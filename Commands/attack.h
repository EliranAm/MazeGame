#ifndef __ATTACK_H__
#define __ATTACK_H__

#include "icommand.h"
#include "../Utils/uncopyable.h"



namespace advcpp
{

class Maze;

class Attack : public ICommand , private Uncopyable
{
public:
	const std::string Execute(size_t _heroID, Maze &_maze);

};

} //namespace advcpp

#endif /* __ATTACK_H__ */
