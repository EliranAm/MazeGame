#include "room_info.h"


namespace advcpp
{

RoomInfo::RoomInfo()
	: m_gold(0)
	, m_sword(0)
	, m_shield(0)
	, m_keys(0)
	, m_potions(0)
	, m_neighborRooms(4)
{}

void RoomInfo::ResetInfo()
{
	m_gold = 0;
	m_sword = 0;
	m_shield = 0;
	m_keys = 0;
	m_potions = 0;
	m_nameOfMonster.first = false;
}
	
} //namespace advcpp

