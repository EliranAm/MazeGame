#include "unlock.h"
#include "../Objects/maze.h"
#include "../Objects/room.h"
#include "../Objects/passage.h"


namespace advcpp
{

Unlock::Unlock()
{
	typedef std::pair< Passage::PassageStatus, std::string > PAIR;
	
	m_message.insert( PAIR(Passage::WALL, "There is a Wall!, No door here, go to optometrist and buy a new Glasses\n" ) );
	m_message.insert( PAIR(Passage::HOLEWAY, "There is no door. the way is open , u can go throw!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_CLOSE, "The Door Is close, go find a key!\n" ) ); 
	m_message.insert( PAIR(Passage::DOOR_OPEN, "U succeed to open the door , The Door Is Open now!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_LOCK, "The Door Is lock!\n" ) );
	m_message.insert( PAIR(Passage::DOOR_UNLOCK, "The Door Is unlock!\n" ) );
}

const std::string Unlock::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	Room::SPHero hero = room->GetHero(_heroID);
	if (!hero->RemoveKeys(1))
	{
		return "Cant unlock the door! not enough keys";
	}
	
	Passage passage = room->UnlockDoor(_heroID);
	std::string retVal;
	Passage::PassageStatus status = passage.GetStatus();

	return m_message.at(status) + room->Show(_heroID);		
}

} //namespace advcpp
