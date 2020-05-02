#include "raging.h"
#include "../Utils/comunication.h"
#include "../Objects/maze.h"
#include <stdlib.h>
#include <time.h>

#define PRECENTS (100)
#define ATT_MONST_PREC (34)
#define ATTACK_STRENGTH (40)

namespace advcpp
{

Raging::Raging(GameComunication& _gameCom)
	: m_gameCom(_gameCom)
{
}


const std::string Raging::ExecuteOther(size_t _heroId, Maze& _maze, const std::string& _command)
{
	std::tr1::shared_ptr<Room> room = _maze.GetRoom(_heroId);
	Room::SPHero hero = room->GetHero(_heroId);
	hero->SetStatus(Hero::COMMAND);
	if(!_command.compare("y"))
	{
		return Rage(_heroId, _maze);
	}
	
	if(!_command.compare("n"))
	{
		return "Continue...\n";
	}
	
	return "Invalid choice\n";
}

const std::string Raging::Rage(size_t _heroID, Maze &_maze)
{
	SPRoom room = _maze.GetRoom(_heroID);
	srand( time(0) );
	std::string retVal;

	//33% to hit a monster, the rest is for hitting other
	if (rand() % PRECENTS < ATT_MONST_PREC)
	{
		retVal = room->AttackMonster(_heroID, rand() % ATTACK_STRENGTH, rand() % ATTACK_STRENGTH);
	}
	else
	{
		size_t chosenHeroID = room->GetRandomHeroID();
		retVal = room->AttackHero(_heroID, chosenHeroID, rand() % ATTACK_STRENGTH, rand() % ATTACK_STRENGTH);

		if (room->GetHero(_heroID)->IsDead())
		{
			ResetHero(_heroID, _maze, room);
		}

		if (_heroID != chosenHeroID)
		{
			m_gameCom.Write(chosenHeroID, "You'v been attacked by other hero!\n");
			if (room->GetHero(chosenHeroID)->IsDead())
			{
				m_gameCom.Write(chosenHeroID, "You'v been killed by other hero!\n");
				ResetHero(chosenHeroID, _maze, room);
			}
			
		}

	
	}
	
	return retVal;
}

void Raging::ResetHero(size_t _heroID, Maze &_maze, SPRoom _room)
{
	Room::SPHero hero = _room->ExitHero(_heroID);
	_maze.RemovePosition(_heroID);
	_maze.InsertNewHero(hero);
	hero->Reset();	
}


}//namespace advcpp


