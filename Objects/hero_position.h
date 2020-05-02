#ifndef __HERO_POSITION__
#define __HERO_POSITION__

#include <map>
#include "stddef.h"
#include "../Utils/uncopyable.h"

#define UNIQUE_ID size_t 
#define ROOM_NUM size_t 
namespace advcpp
{

class HeroPosition : private Uncopyable
{
public:
 	int  GetRoomNumber(size_t _heroID) const;
 	bool InsertNewHero(size_t _heroID);
 	void UpdateHeroPosition(size_t _heroID, size_t _newRoomNumber);
 	void RemoveHero(size_t _heroID);
 	
private:

	std::map<UNIQUE_ID, ROOM_NUM> m_heroPosition;
};



}//namespace advcpp
#endif /* __HERO_POSITION__ */
