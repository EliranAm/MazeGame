#include "room.h"
#include "../Utils/comunication.h"
#include "character.h"
#include <iostream>
#include <algorithm>
#include <assert.h>

#define COLOR_RESET	"\x1b[0m"
#define COLOR_BOLD	"\x1b[01m"
#define COLOR_RED	"\x1b[31m"
#define COLOR_GREEN	"\x1b[32m"
#define COLOR_CYAN	"\x1b[36m"


namespace advcpp
{

struct RandomFunctor
{
	void operator()(const std::pair<UNIQUE_ID, Room::SPHero>& _heroPair)
	{
		m_ids.push_back(_heroPair.first);
	}
	
	UNIQUE_ID GetRandId() const
	{
		return m_ids[rand() % m_ids.size()];
	}
	
private:
	std::vector<UNIQUE_ID> m_ids;
};


Room::Room(const RoomInfo& _roomInfo)
	: m_roomInfo(_roomInfo)
	, m_neighborRooms(4)
{
	m_passage.push_back(Passage(_roomInfo.m_neighborRooms[Location::NORTH].first));
	m_passage.push_back(Passage(_roomInfo.m_neighborRooms[Location::WEST].first));
	m_passage.push_back(Passage(_roomInfo.m_neighborRooms[Location::SOUTH].first));
	m_passage.push_back(Passage(_roomInfo.m_neighborRooms[Location::EAST].first));
	
	if(m_roomInfo.m_nameOfMonster.first)
	{
		m_monsterContainer.push_back(CreateMonster());
	}
	
	if(m_roomInfo.m_kindOfRoom == 't')
	{
		m_treasureContainer.push_back(CreateTreasure());
	}
}

const std::string Room::PrintNorth() const
{
	return m_passage[Location::NORTH].DrawHorizontal();
}

const std::string Room::PrintIfMonster() const
{
	if (!m_monsterContainer.empty())
	{
		return "|          (" COLOR_BOLD COLOR_RED "-^|^-" COLOR_RESET ")                                                                      |\n";
	}
	return "|                                                                                       |\n";
}

char Room::PrintLocation(Location::Direction _location) const
{
	switch (_location)
	{
		case Location::NORTH:
			return '^';
		case Location::WEST:
			return '<';
		case Location::SOUTH:
			return 'v';
		case Location::EAST:
			return '>';
		default:
			return '*';
	};
}

void Room::SetNeighbor(Location::Direction _location, SPRoom _nRoom)
{
	m_neighborRooms[_location] = _nRoom;
}

const std::string Room::PrintBody(size_t _heroID) const
{
	std::string west = m_passage[Location::WEST].DrawVertical();
	std::string east = m_passage[Location::EAST].DrawVertical();
	size_t length = west.size();
	std::string retVal;
	for (size_t index = 0; index < length-1; ++index)
	{
		retVal += west[index];
		for(size_t innerIndex = 0; innerIndex < (length - 2) * 3; ++innerIndex)
		{
			retVal += " ";
		}
		retVal += east[index];
		retVal += '\n';
	}
	//insert the location of the Hero in the middle of the retVal
	//retVal.size()/2 - middle row, PrintNorth().size()/2 middle collom
	retVal[retVal.size()/2 + PrintNorth().size()/2] = PrintLocation(m_heroContainer.at(_heroID)->GetLocation()); 
	return retVal;
}


const std::string Room::PrintIfTressure() const
{
	if (!m_treasureContainer.empty())
	{
		return "|                                                                      /" COLOR_BOLD COLOR_GREEN "$$$$$" COLOR_RESET "/          |\n";
	}
	return 	"|                                                                                       |\n";
}

const std::string Room::PrintSouth() const
{
	return m_passage[Location::SOUTH].DrawHorizontal();
}

const std::string Room::Show(size_t _heroID) const
{
	if (m_roomInfo.m_kindOfRoom == 'l')
	{
		return ShowFoundLassieScreen();
	}
	
	std::string retVal = PrintNorth();
	retVal += PrintIfMonster();
	retVal += PrintBody(_heroID);
	retVal += PrintIfTressure();
	retVal += PrintSouth();
	return retVal;
}

const std::string Room::ShowFoundLassieScreen() const
{
	return std::string(COLOR_CYAN COLOR_BOLD
	"                .\"\";._   _.---._   _.-\"\".\n"
	"               /_.'_  '-'      /`-` \\_   \\ \n"
	"             .'   / `\\         \\   /` \\   '.\n"
	"           .'    /    ;    _ _  '-;    \\   ;'.\n"
	"        _.'     ;    /\\   / \\ \\    \\    ;  '._;._\n"
	"     .-'.--.    |   /  |  \\0|0/     \\   |        '-.\n"
	"    / /`    \\   |  /  .'             \\  | .---.     \\ \n"
	"   | |       |  / /--'   .-\"\"\"-.      \\ \\/     \\     |\n"
	"   \\ \\      /  / /      (  , ,  )     /\\ \\      |    /\n"
	"    \\ '----' .' |        '-(_)-'     |  | '.   /    /\n"
	"     `'----'`   |                    '. |   `'----'`\n"
	"                \\                      `/\n"
	"                 '.         ,         .'\n"
	"                   `-.____.' '.____.-'\n"
	"                          \\   /\n"
	"                           '-'\n"
	COLOR_RESET);
}


const std::string Room::GetRoomInfo() const
{
	return COLOR_BOLD "Room: " + m_roomInfo.m_name + "\nDescription: " + m_roomInfo.m_description + "\n" COLOR_RESET; 
}

UNIQUE_ID Room::GetRandomHeroID() const
{
	RandomFunctor randFunc;
	randFunc = std::for_each(m_heroContainer.begin(), m_heroContainer.end(), randFunc);
	return randFunc.GetRandId();
}

const std::string Room::AttackMonster(size_t _heroID, size_t _attackeStregnth, size_t _attackBackStregnth)
{
	if (!m_monsterContainer.empty())
	{
		std::string retVal = AttackEnemy(m_heroContainer.at(_heroID), m_monsterContainer.front(), _attackeStregnth, _attackBackStregnth);
		
		if (m_monsterContainer.front()->IsDead())
		{
			TransformMonsterToTreasure();
		}
		
		return retVal + "\n";
	}
	
	return "No Monster In this room!\n";
}

const std::string Room::AttackEnemy(SPCharacter _attacker, SPCharacter _attacked, size_t _attackeStregnth, size_t _attackBackStregnth)
{
	size_t sword = _attacker->GetSword();
	std::string retVal = _attacked->GetAttacked(sword, _attackeStregnth);
	if (!_attacked->IsDead() && _attacker != _attacked)
	{
		sword = _attacked->GetSword();
		retVal += _attacker->GetAttacked(sword, _attackBackStregnth);
	}
	
	return retVal + "\n";
}

const std::string Room::AttackHero(size_t _attacker, size_t _attacked, size_t _attackeStregnth, size_t _attackBackStregnth)
{
	if (m_heroContainer.size() > 1)
	{
		std::string retVal = AttackEnemy(m_heroContainer.at(_attacker), m_heroContainer.at(_attacked), _attackeStregnth, _attackBackStregnth);
		return retVal + "\n";
	}

	return "No Hero In this room!\n";
}

void Room::TransformMonsterToTreasure()
{
	m_treasureContainer.push_back(CreateTreasure());	
	m_monsterContainer.pop_front();
}

Room::SPHero Room::ExitHero(size_t _heroID)
{
	Room::SPHero retVal = m_heroContainer.at(_heroID);
	m_heroContainer.erase(_heroID);
	return retVal;
}

std::pair<bool, Room*> Room::GetNearByRoom(Location::Direction _location) const
{
	Passage::PassageStatus status = m_passage[_location].GetStatus();
	if (status == Passage::DOOR_OPEN || status == Passage::HOLEWAY || status == Passage::DOOR_UNLOCK)
	{
		return std::pair<bool, Room*>(true, m_neighborRooms[_location].get());
	}
	return std::pair<bool, Room*>(false, const_cast<Room*>(this));
}

const Passage& Room::OpenDoor(size_t _heroID)
{
	Location::Direction loc = m_heroContainer.at(_heroID)->GetLocation();
	Location::Direction revLoc = m_heroContainer.at(_heroID)->ReverseLocation();
	m_neighborRooms[loc]->m_passage[revLoc].OpenPassage();
	return m_passage[loc].OpenPassage();
}

const Passage& Room::CloseDoor(size_t _heroID)
{
	Location::Direction loc = m_heroContainer.at(_heroID)->GetLocation();
	Location::Direction revLoc = m_heroContainer.at(_heroID)->ReverseLocation();
	m_neighborRooms[loc]->m_passage[revLoc].ClosePassage();
	return m_passage[loc].ClosePassage();
}

const Passage& Room::UnlockDoor(size_t _heroID)
{
	Location::Direction loc = m_heroContainer.at(_heroID)->GetLocation();
	Location::Direction revLoc = m_heroContainer.at(_heroID)->ReverseLocation();
	m_neighborRooms[loc]->m_passage[revLoc].UnlockPassage();
	return m_passage[loc].UnlockPassage();
}

const Passage& Room::LockDoor(size_t _heroID)
{
	Location::Direction loc = m_heroContainer.at(_heroID)->GetLocation();
	Location::Direction revLoc = m_heroContainer.at(_heroID)->ReverseLocation();
	m_neighborRooms[loc]->m_passage[revLoc].LockPassage();
	return m_passage[loc].LockPassage();
}

Room::SPHero Room::GetHero(size_t _heroID)
{
	assert(m_heroContainer.find(_heroID) != m_heroContainer.end());
	return m_heroContainer.at(_heroID);
}

const std::string Room::TakeTreasure(size_t _heroID)
{
	if(m_treasureContainer.empty())
	{
		return "No Treasure in this room\n";
	}
	SPTreasure treasure = m_treasureContainer.front();
	return treasure->TakeTreasure(*m_heroContainer.at(_heroID));	
}

void Room::TalkToHeros(GameComunication& _gameCom, const std::string& _heroName, const std::string& _chat)
{
	std::map<UNIQUE_ID, Room::SPHero>::iterator itrend =  m_heroContainer.end();
	for(std::map<UNIQUE_ID, Room::SPHero>::iterator itrBegin = m_heroContainer.begin(); itrBegin != itrend; itrBegin++)
	{
		_gameCom.Write(itrBegin->second->GetID(),_heroName + ": " + _chat + "\n");
	}
}

const std::string Room::ShowHerosInRoom() const
{
	std::string retVal = "Heros in Room: ";
	std::map<UNIQUE_ID, Room::SPHero>::const_iterator itrend =  m_heroContainer.end();
	for(std::map<UNIQUE_ID, Room::SPHero>::const_iterator itrBegin = m_heroContainer.begin(); itrBegin != itrend; itrBegin++)
	{
		retVal +=  itrBegin->second->GetName() + ",";
	}
	retVal[retVal.size() - 1] = '.';
		
	return retVal + "\n";
}

Room::SPMonster Room::CreateMonster() const
{
	return SPMonster( new Monster(m_roomInfo.m_nameOfMonster.second, m_roomInfo.m_sword, m_roomInfo.m_shield, m_roomInfo.m_keys, m_roomInfo.m_gold, m_roomInfo.m_potions) );
}

Room::SPTreasure Room::CreateTreasure() const
{
	return SPTreasure( new Treasure(m_roomInfo.m_sword, m_roomInfo.m_shield, m_roomInfo.m_keys, m_roomInfo.m_gold, m_roomInfo.m_potions) );
}


} //namespace advcpp


