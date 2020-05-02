#ifndef __UNLOCK_H__
#define __UNLOCK_H__

#include "icommand.h"
#include "../Objects/passage.h"
#include "../Utils/uncopyable.h"
#include <string>
#include <map>


namespace advcpp
{

class Maze;

class Unlock : public ICommand , private Uncopyable
{
public:
	typedef std::map<Passage::PassageStatus,std::string> messageCon;

public:
	Unlock();
	const std::string Execute(size_t _heroID, Maze &_maze);

private:
	messageCon m_message;
};

} //namespace advcpp

#endif /* __UNLOCK_H__ */
