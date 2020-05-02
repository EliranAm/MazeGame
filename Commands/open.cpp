#include "open.h"
#include "../Objects/maze.h"
#include "../Objects/room.h"


namespace advcpp
{

Open::Open()
{
	typedef std::pair< Passage::PassageStatus, std::string > PAIR;
	
	m_message.insert( PAIR(Passage::WALL, "There is a Wall! find another way!\n" ) );
	m_message.insert( PAIR(Passage::HOLEWAY, "There is no door. the way is open , you can go throw!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_LOCK, "The Door Is Lock, go find a key!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_OPEN, "The Door Is Open!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_CLOSE, "The Door Is close!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_UNLOCK, "The Door Is unlock!\n" ) );
}

const std::string Open::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	Passage passage = room->OpenDoor(_heroID);
	std::string retVal;
	Passage::PassageStatus status = passage.GetStatus();
	
	return m_message.at(status) + room->Show(_heroID);
}

} //namespace advcpp




