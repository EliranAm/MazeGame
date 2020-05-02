#include "monster.h"
#include <stdlib.h> //srand, rand
#include <time.h>

namespace advcpp
{

Monster::Monster(const std::string& _name, size_t _sword, size_t _shield, size_t _key, size_t _gold, size_t _potions)
	: Character(_sword, _shield, _key, _gold, _potions)
{
	SetName(_name);
	srand(time(0));
	SetHp(20 + rand() % 50); //20 - 70 HP	
}


}//namespace advcpp

