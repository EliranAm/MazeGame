#ifndef __MAZE_H__
#define __MAZE_H__

#include <map>
#include <tr1/memory>
#include <vector>


#include "hero.h"
#include "../Utils/uncopyable.h"
#include "hero_position.h"
#include "room_info.h"


#define ROOM_ID size_t

namespace advcpp
{

class GameComunication;
class Room;

class Maze : private Uncopyable
{
typedef std::tr1::shared_ptr<Hero> SPHero;
typedef std::tr1::shared_ptr<Room> SPRoom;

public:
	explicit Maze(std::map<ROOM_ID, RoomInfo> &_roomContainer);

	void InsertNewHero(SPHero _newHero);
	const SPRoom GetRoom(size_t _heroID) const;
	void ChangePosition(size_t _heroID, size_t _newPos);
	bool IsUserExist(size_t _heroID) const;
	void RemovePosition(size_t _heroID);
	void TalkToAllHeros(GameComunication& _gameCom, const std::string& _heroName, const std::string& _chat);

	void SetCommands(std::vector<std::string>& _commands);
	const std::string GetAllCommands() const;
	
private:
	std::vector<std::string> m_commands;
	HeroPosition m_herosPos;
	std::map<ROOM_ID, SPRoom> m_roomContainer;
};

} //namespace advcpp
#endif //__MAZE_H__
