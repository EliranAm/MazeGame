#include "treasure.h"
#include "hero.h"

namespace advcpp
{

Treasure::Treasure(size_t _sword, size_t _shield, size_t _key, size_t _gold, size_t _potions)
	: m_sword(_sword)
	, m_shield(_shield)
	, m_key(_key)
	, m_gold(_gold)
	, m_potions(_potions)	
{ }

const std::string Treasure::TakeTreasure(Hero& _hero)
{
	std::string newInfo = "You Took:\n";
	if(_hero.GetShield() < m_shield)
	{
		size_t newShield = _hero.GetShield();
		_hero.SetShield(m_shield);
		m_shield = newShield;
		newInfo += "New Shield: " + std::to_string(_hero.GetShield()) + "\n";
	}
	
	if(_hero.GetSword() < m_sword)
	{
		size_t newSword = _hero.GetSword();	
		_hero.SetSword(m_sword);
		m_sword = newSword;
		newInfo += "New Sword: " + std::to_string(_hero.GetSword()) + "\n";
	}
	
	_hero.AddGold(m_gold);
	_hero.AddKeys(m_key);
	_hero.AddPotions(m_potions);
	
	newInfo += "Gold: " + std::to_string(m_gold) + "\n";
	newInfo += "Keys: " + std::to_string(m_key) + "\n";
	newInfo += "Potions: " + std::to_string(m_potions) + "\n\n";
	
	m_gold = 0;
	m_key = 0;
	m_potions = 0;

	return newInfo;
}
		
	
}//namespace advcpp
