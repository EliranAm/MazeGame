#ifndef __MONSTER_H__
#define __MONSTER_H__

#include <string>
#include "character.h"
#include "../Utils/uncopyable.h"

namespace advcpp
{

class Monster : public Character 
{
public:
	Monster(const std::string& _name, size_t _sword, size_t _shield, size_t _key, size_t _gold, size_t _potions);
	virtual ~Monster(){}

private:

// uncopyable
/*
	std::string m_name;
	size_t m_sword;
	size_t  m_shield;
	size_t  m_key;
	size_t  m_hp;
	size_t  m_gold;
*/
};

}//namespace advcpp

#endif /* __MONSTER_H__ */
