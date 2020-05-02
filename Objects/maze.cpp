#include "maze.h"
#include "room.h"

#define LOBBY (1)

namespace advcpp
{
Maze::Maze(std::map<ROOM_ID, RoomInfo> &_roomContainer)
	: m_roomContainer(RoomFactory::CreateAllRooms(_roomContainer))
{
}

void Maze::InsertNewHero(SPHero _newHero)
{
	m_roomContainer.at(LOBBY)->InsertHero(_newHero->GetID(), _newHero);
	m_herosPos.InsertNewHero(_newHero->GetID());
}

void Maze::ChangePosition(size_t _heroID, size_t _newPos)
{
	m_herosPos.UpdateHeroPosition(_heroID, _newPos);
}

void Maze::TalkToAllHeros(GameComunication& _gameCom, const std::string& _heroName, const std::string& _chat)
{
	std::map<ROOM_ID, SPRoom>::iterator itrend =  m_roomContainer.end();
	for(std::map<ROOM_ID, SPRoom>::iterator itrBegin = m_roomContainer.begin(); itrBegin != itrend; itrBegin++)
	{
		itrBegin->second->TalkToHeros(_gameCom,_heroName,_chat);
	}
}

const Maze::SPRoom Maze::GetRoom(size_t _heroID) const
{
	int roomNum = m_herosPos.GetRoomNumber(_heroID);
	return (roomNum == -1) ? m_roomContainer.at(LOBBY) : m_roomContainer.at(roomNum);
}

bool Maze::IsUserExist(size_t _heroID) const
{
	return (m_herosPos.GetRoomNumber(_heroID) != -1);
}

void Maze::RemovePosition(size_t _heroID)
{
	m_herosPos.RemoveHero(_heroID);
}

void Maze::SetCommands(std::vector<std::string>& _commands)	
{
	m_commands = _commands;
}

const std::string Maze::GetAllCommands() const
{
	std::string retVal = "Command List:\n";
	std::vector<std::string>::const_iterator itrEnd = m_commands.end();
	for(std::vector<std::string>::const_iterator itrBegin = m_commands.begin(); itrBegin != itrEnd; ++itrBegin)
	{
		retVal += *itrBegin + "\n";
	}
	return retVal;
}

}//namespace advcpp

