#include "hero_position.h"
#include <assert.h>


namespace advcpp
{

int HeroPosition::GetRoomNumber(size_t _heroID) const
{
	std::map<UNIQUE_ID, ROOM_NUM>::const_iterator it = m_heroPosition.find(_heroID);
	if(it == m_heroPosition.end())
	{
		return -1;
	}
	return m_heroPosition.at(_heroID);
}

bool HeroPosition::InsertNewHero(size_t _heroID)
{
	std::pair<std::map<UNIQUE_ID, ROOM_NUM>::iterator,bool> result;
 	result = m_heroPosition.insert(std::pair<UNIQUE_ID, ROOM_NUM>(_heroID, 1));
 	return result.second;
}

void HeroPosition::UpdateHeroPosition(size_t _heroID, size_t _newRoomNumber)
{
	std::map<UNIQUE_ID, ROOM_NUM>::iterator it;
	it = m_heroPosition.find(_heroID);
	assert(it != m_heroPosition.end());
	m_heroPosition[_heroID] = _newRoomNumber;
}

void HeroPosition::RemoveHero(size_t _heroID)
{
	m_heroPosition.erase(_heroID); 	
}


}//namespace advcpp

