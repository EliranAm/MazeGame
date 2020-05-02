#ifndef __ROOM_FACTORY_H__
#define __ROOM_FACTORY_H__

#include <tr1/memory>
#include <map>

#include "../Objects/room_info.h"
#include "uncopyable.h"
#include "../Objects/room.h"

#define ROOM_ID size_t

namespace advcpp
{

class Room;

class RoomFactory : private Uncopyable
{


public:
typedef std::tr1::shared_ptr<Room> SPRoom;

	static std::map<ROOM_ID, SPRoom> CreateAllRooms(const std::map<ROOM_ID, RoomInfo> &_roomInfosContainer);

private:
	RoomFactory();
	~RoomFactory();
	
	static void BuildRoomMap(const std::map<ROOM_ID, RoomInfo> &_roomInfosContainer, std::map<ROOM_ID, SPRoom>* _retVal);
	static void UpdateRoomNeighbors(std::map<ROOM_ID, SPRoom>* _retVal);
};


}	//namespace advcpp

#endif /* __ROOM_FACTORY_H__ */

