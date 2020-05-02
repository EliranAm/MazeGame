#include "room_factory.h"
#include <algorithm>

namespace advcpp
{
typedef std::map<ROOM_ID, RoomInfo>::const_iterator ItrMapIdInfo;
typedef std::map<ROOM_ID, RoomFactory::SPRoom>::const_iterator ItrMapIdSPRoom;

std::map<ROOM_ID, RoomFactory::SPRoom> RoomFactory::CreateAllRooms(const std::map<ROOM_ID, RoomInfo> &_roomInfosContainer)
{
	std::map<ROOM_ID, SPRoom> retVal;
	BuildRoomMap(_roomInfosContainer, &retVal);
	UpdateRoomNeighbors(&retVal);
	return retVal;
}

void RoomFactory::BuildRoomMap(const std::map<ROOM_ID, RoomInfo> &_roomInfosContainer, std::map<ROOM_ID, SPRoom>* _retVal)
{
	ItrMapIdInfo itrEnd = _roomInfosContainer.end();
	for (ItrMapIdInfo itrBegin = _roomInfosContainer.begin(); itrBegin != itrEnd ; ++itrBegin)
	{
		_retVal->insert( std::pair<ROOM_ID, SPRoom>( itrBegin->first, SPRoom( new Room( itrBegin->second ) ) ) );
	}	
}

void RoomFactory::UpdateRoomNeighbors(std::map<ROOM_ID, SPRoom>* _retVal)
{
	ItrMapIdSPRoom itrEnd = _retVal->end();
	for (ItrMapIdSPRoom itrBegin = _retVal->begin(); itrBegin != itrEnd ; ++itrBegin)
	{
		SPRoom roomate = _retVal->at(itrBegin->second->m_roomInfo.m_neighborRooms[Location::NORTH].second);
		itrBegin->second->SetNeighbor(Location::NORTH, roomate);

		roomate = _retVal->at(itrBegin->second->m_roomInfo.m_neighborRooms[Location::WEST].second);
		itrBegin->second->SetNeighbor(Location::WEST, roomate);

		roomate = _retVal->at(itrBegin->second->m_roomInfo.m_neighborRooms[Location::SOUTH].second);
		itrBegin->second->SetNeighbor(Location::SOUTH, roomate);
		
		roomate = _retVal->at(itrBegin->second->m_roomInfo.m_neighborRooms[Location::EAST].second);
		itrBegin->second->SetNeighbor(Location::EAST, roomate);
	}
}

}	//namespace advcpp
