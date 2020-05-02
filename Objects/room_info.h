#ifndef __ROOM_INFO_H__
#define __ROOM_INFO_H__

#include <vector>
#include <exception>
#include "passage.h"
#include "colors.h"


#define POTION_TYPE size_t
#define ROOM_ID size_t

namespace advcpp
{

struct RoomInfo 
{
	typedef std::vector<std::pair<Passage::PassageStatus, ROOM_ID> > NeighborCont;

	RoomInfo();
	void ResetInfo();

	size_t m_id;
	char m_kindOfRoom;
	COLOR m_roomColor;
	COLOR m_doorColor;
	std::string m_name;
	std::string m_description;
	size_t m_gold;
	size_t m_sword;
	size_t m_shield;
	size_t m_keys;
	size_t m_potions;
	std::pair<bool, std::string> m_nameOfMonster;
	NeighborCont m_neighborRooms;
};




}	//namespace advcpp

#endif /* __ROOM_INFO_H__ */

