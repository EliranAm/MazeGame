#ifndef __TREASURE_H__
#define __TREASURE_H__

#include <string>
#include "../Utils/uncopyable.h"

namespace advcpp
{

class Hero;
class Treasure : private Uncopyable
{
public:
	Treasure(size_t _sword, size_t _shield, size_t _key, size_t _gold, size_t _potions);
	const std::string TakeTreasure(Hero& _hero);

private:
	size_t m_sword;
	size_t m_shield;
	size_t m_key;
	size_t m_gold;
	size_t m_potions;
};



}//namespace advcpp



#endif /* __TREASURE_H__ */

