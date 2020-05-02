#include "hero.h"
#include <iostream>


namespace advcpp
{

Hero::Hero(unsigned int _id) 
	: Character(1,1,0,0,0)
	, m_id(_id)
	, m_location(Location::NORTH)
	, m_status(NEW)
{
	SetHp(100);
}

Hero::~Hero()
{
}
	
void Hero::SetName(const std::string& _name)
{
	Character::SetName(_name);
}

void Hero::SetStatus(UserStatus _status)
{
	m_status = _status;
}

Location::Direction Hero::ReverseLocation() const
{
	return Location::Direction((m_location + 2) % Location::LAST);
}

void Hero::Left()
{
	m_location = Location::Direction((m_location + 1) % Location::LAST);
}

void Hero::Right()
{
	m_location = Location::Direction((m_location + 3) % Location::LAST);
}

void Hero::Reset()
{
	Character::Reset();
	SetHp(100);
	SetSword(1);
	SetShield(1);
}

const std::string Hero::PrintHero() const
{
	std::string heroInfo = "Hero name: " + GetName() + "\n" + "Hp: " + std::to_string(GetHp()) + "\n" + "Gold: " + std::to_string(GetGold()) + "\n" + "Sword: " + std::to_string(GetSword()) + "\n" + "Shield: " + std::to_string(GetShield()) + "\n" + "Keys: " + std::to_string(GetNumOfKeys()) + "\n" + "Potions: " + std::to_string(GetNumOfPotions()) + "\n\n";
	return heroInfo;

}
}//namespace advcpp

