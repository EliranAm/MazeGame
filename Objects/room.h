#ifndef __ROOM_H__
#define __ROOM_H__

#include <map>
#include <tr1/memory>
#include <deque>
#include "hero.h"
#include "passage.h"
#include "room_info.h"
#include "colors.h"
#include "location.h"
#include "../Utils/room_factory.h"
#include "monster.h"
#include "treasure.h"
#include "../Utils/uncopyable.h"


#define UNIQUE_ID size_t

namespace advcpp
{

class GameComunication;
class Character;

class Room : private Uncopyable
{
public:
typedef std::tr1::shared_ptr<Room> SPRoom;
typedef std::tr1::shared_ptr<Hero> SPHero;
typedef std::tr1::shared_ptr<Monster> SPMonster;
typedef std::tr1::shared_ptr<Treasure> SPTreasure;
typedef std::tr1::shared_ptr<Character> SPCharacter;
typedef std::deque<std::pair<Passage::PassageStatus, ROOM_ID> > NeighborCont;
friend class RoomFactory;

public:
	explicit Room(const RoomInfo& _roomInfo);
	
	SPHero ExitHero(size_t _heroID);
	void InsertHero(size_t _heroID, SPHero _hero);	
	const std::string Show(size_t _heroID) const;
	
	size_t GetRoomID() const;
	Location::Direction GetLocation(size_t _heroID) const;
	Location::Direction ReverseLocation(size_t _heroID) const;
	std::pair<bool, Room*> GetNearByRoom(Location::Direction _location) const;
	UNIQUE_ID GetRandomHeroID() const;
	SPHero GetHero(size_t _heroID);

	const Passage& OpenDoor(size_t _heroID);
	const Passage& CloseDoor(size_t _heroID);
	const Passage& UnlockDoor(size_t _heroID);
	const Passage& LockDoor(size_t _heroID);
	
	void Left(size_t _heroID);
	void Right(size_t _heroID);
	const std::string AttackMonster(size_t _heroID, size_t _attackeStregnth, size_t _attackBackStregnth);
	const std::string AttackHero(size_t _attacker, size_t _attacked, size_t _attackeStregnth, size_t _attackBackStregnth);
	
	const std::string TakeTreasure(size_t _heroID);
	void TalkToHeros(GameComunication& _gameCom, const std::string& _heroName, const std::string& _chat);
	const std::string GetRoomInfo() const;
	const std::string ShowHerosInRoom() const;
	
private:
	void SetNeighbor(Location::Direction _location, SPRoom _nRoom);
	const std::string PrintNorth() const;
	const std::string PrintIfMonster() const;
	const std::string PrintBody(size_t _heroID) const;
	char PrintLocation(Location::Direction _location) const;
	const std::string PrintIfTressure() const;
	const std::string PrintSouth() const;
	const std::string ShowFoundLassieScreen() const;
	void TransformMonsterToTreasure();
	const std::string AttackEnemy(SPCharacter _attacker, SPCharacter _attacked, size_t _attackeStregnth, size_t _attackBackStregnth);
	SPMonster CreateMonster() const;
	SPTreasure CreateTreasure() const;
	
	RoomInfo m_roomInfo;
	std::deque<SPMonster> m_monsterContainer;
	std::deque<SPTreasure> m_treasureContainer;
	std::deque<Passage> m_passage;
	std::deque<SPRoom> m_neighborRooms;  
	std::map<UNIQUE_ID, SPHero> m_heroContainer;
};

inline size_t Room::GetRoomID() const
{
	return m_roomInfo.m_id;
}

inline void Room::Left(size_t _heroID)
{
	m_heroContainer.at(_heroID)->Left();
}

inline void Room::Right(size_t _heroID)
{
	m_heroContainer.at(_heroID)->Right();
}

inline void Room::InsertHero(size_t _heroID, SPHero _hero)
{
	m_heroContainer.insert(std::pair<size_t,SPHero>(_heroID,_hero));
}

inline Location::Direction Room::GetLocation(size_t _heroID) const
{
	return m_heroContainer.at(_heroID)->GetLocation();
}

inline Location::Direction Room::ReverseLocation(size_t _heroID) const
{
	return m_heroContainer.at(_heroID)->ReverseLocation();
}


}//namespace advcpp
#endif //__ROOM_H__

