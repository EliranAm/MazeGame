#ifndef __OPEN_H__
#define __OPEN_H__

#include "icommand.h"
#include "../Objects/passage.h"
#include "../Utils/uncopyable.h"
#include <string>
#include <map>


namespace advcpp
{

class maze;

class Open : public ICommand , private Uncopyable
{

public:
	typedef std::map<Passage::PassageStatus,std::string> messageCon;

public:
	Open();
	const std::string Execute(size_t _heroID, Maze &_maze);
	
private:
	messageCon m_message;
};

}//namespace advcpp

#endif /* __OPEN_H__ */

