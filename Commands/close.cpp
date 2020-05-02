#include "close.h"
#include "../Objects/maze.h"
#include "../Objects/room.h"


namespace advcpp
{

Close::Close()
{
	typedef std::pair< Passage::PassageStatus, std::string > PAIR;
	
	m_message.insert( PAIR(Passage::WALL, "There is a Wall!, No door here dude\n" ) );
	m_message.insert( PAIR(Passage::HOLEWAY, "There is no door. the way is open , u can go throw!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_LOCK, "The Door Is Lock, go find a key!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_CLOSE, "The Door Is Close!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_UNLOCK, "The Door Is unlock!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_OPEN, "dude, The Door Is open!\n" ) );
}

const std::string Close::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	Passage passage = room->CloseDoor(_heroID);
	std::string retVal;
	Passage::PassageStatus status = passage.GetStatus();
	

	return m_message.at(status) + room->Show(_heroID);
}

} //namespace advcpp




