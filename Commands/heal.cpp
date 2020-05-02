#include "heal.h"
#include "../Objects/hero.h"
#include "../Objects/room.h"
#include <tr1/memory>
#include <string>

namespace advcpp
{

const std::string Heal::Execute(size_t _heroID, Maze &_maze)
{
	std::string retVal;
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	Room::SPHero hero =  room->GetHero(_heroID);
	if(hero->GetNumOfPotions() > 0)
	{
		if(hero->GetHp() != 100)
		{
			hero->AddHp(10);
			hero->RemovePotions();
			retVal += "You Used potions, your HP is: " + std::to_string(hero->GetHp()) + "\n";
		}
		else
		{
			retVal += "You HP is allready full\n";	
		}
	}
	else
	{
		retVal += "You don't have any potions\n";	
	}

	return retVal;
}


}	//namespace advcpp
