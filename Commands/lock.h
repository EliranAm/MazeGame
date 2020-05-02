#ifndef __LOCK_H__
#define __LOCK_H__

#include "icommand.h"
#include "../Objects/passage.h"
#include "../Utils/uncopyable.h"
#include <string>
#include <map>


namespace advcpp
{

class Maze;

class Lock : public ICommand , private Uncopyable
{
public:
	typedef std::map<Passage::PassageStatus,std::string> messageCon;

public:
	Lock();
	const std::string Execute(size_t _heroID, Maze &_maze);
	
private:
	messageCon m_message;
};

} //namespace advcpp

#endif /* __LOCK_H__ */
