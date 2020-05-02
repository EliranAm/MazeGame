#include "attack.h"
#include "../Objects/maze.h"
#include "../Objects/room.h"
#include <stdlib.h>
#include <time.h>

#define ATTACK_STRENGTH (20)

namespace advcpp
{

const std::string Attack::Execute(size_t _heroID, Maze &_maze)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroID);
	srand( time(0) );
	std::string retVal = room->AttackMonster(_heroID, rand() % ATTACK_STRENGTH, rand() % ATTACK_STRENGTH);
	if (room->GetHero(_heroID)->IsDead())
	{
		Room::SPHero hero = room->ExitHero(_heroID);
		_maze.RemovePosition(_heroID);
		_maze.InsertNewHero(hero);
		hero->Reset();
	}
	
	return retVal;
}


} //namespace advcpp
