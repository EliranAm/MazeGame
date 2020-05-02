#include "lock.h"
#include "../Objects/maze.h"
#include "../Objects/room.h"



namespace advcpp
{

Lock::Lock()
{
	typedef std::pair< Passage::PassageStatus, std::string > PAIR;
	
	m_message.insert( PAIR(Passage::WALL, "There is a Wall!, No door here dude\n" ) );
	m_message.insert( PAIR(Passage::HOLEWAY, "There is no door. the way is open , u can go throw!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_CLOSE, "The Door Is Close, but there is no locker!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_OPEN, "The Door Is open and cant be locked!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_LOCK, "The Door Is lock!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_UNLOCK, "The Door Is unlock!\n" ) );
	
}


const std::string Lock::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	Room::SPHero hero = room->GetHero(_heroID);
	if (!hero->GetNumOfKeys())
	{
		return "Cant lock the door! not enough keys";
	}
	
	Passage passage = room->LockDoor(_heroID);
	std::string retVal;
	Passage::PassageStatus status = passage.GetStatus();


	return m_message.at(status) + room->Show(_heroID);	
}

} //namespace advcpp
