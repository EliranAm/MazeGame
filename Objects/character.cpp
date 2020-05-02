#include "character.h"
#include <stdlib.h>
#include <time.h>

#define MAX_HELTH (100)


namespace advcpp
{

Character::Character(size_t _sword, size_t _shield, size_t _key, size_t _gold, size_t _potions)
	: m_sword(_sword)
	, m_shield(_shield)
	, m_keys(_key)
	, m_hp(0)
	, m_gold(_gold)
	, m_potions(_potions)
{ }

bool Character::RemoveKeys(size_t _numOfKeys)
{
	if (m_keys >= _numOfKeys)
	{
		m_keys -= _numOfKeys;
		return true;
	}

	return false;
}

bool Character::RemovePotions(size_t _numOfPotions)
{
	if (m_potions >= _numOfPotions)
	{
		m_potions -= _numOfPotions;
		return true;
	}

	return false;
}

bool Character::RemoveGold(size_t _gold)
{
	if (m_gold >= _gold)
	{
		m_gold -= _gold;
		return true;
	}

	return false;
}
	
const std::string Character::GetAttacked(size_t _attackerSwordLevel, size_t _attackStregnth)
{
	if (_attackerSwordLevel > m_shield)
	{
		_attackStregnth += (rand() % (_attackerSwordLevel - m_shield));
	}
	
	if(_attackStregnth >= m_hp)
	{
		m_hp = 0;
		return m_name + " killed!\n";
	}
	
	m_hp -= _attackStregnth;
	return m_name + " lost " + std::to_string(_attackStregnth) + " HP.\n" + m_name + " have " + std::to_string(m_hp) + " HP now.\n";
}

void Character::AddHp(size_t _hp)
{	
	if(m_hp + _hp >= MAX_HELTH)
	{
		m_hp = MAX_HELTH;
	}
	else
	{
		m_hp += _hp;
	}
}

void Character::Reset()
{
	m_sword = 0;
	m_shield = 0;
	m_keys = 0;
	m_hp = 0;
	m_gold = 0;
	m_potions = 0;
}


} //namespace advcpp

