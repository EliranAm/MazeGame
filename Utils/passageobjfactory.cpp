#include "passageobjfactory.h"
#include <algorithm>


namespace advcpp
{

Passage::PassageObjCon passageObjFactory::CreateAllObj()
{
	Passage::PassageObjCon retVal;
	
	retVal.insert(std::pair< Passage::PassageStatus, Passage::SPIpassageObj>(Passage::WALL,  Passage::SPIpassageObj( new Wall )));
	retVal.insert(std::pair< Passage::PassageStatus, Passage::SPIpassageObj>(Passage::DOOR_OPEN, Passage::SPIpassageObj( new DoorOpen )));
	retVal.insert(std::pair< Passage::PassageStatus, Passage::SPIpassageObj>(Passage::DOOR_CLOSE, Passage::SPIpassageObj( new DoorClose )));
	retVal.insert(std::pair< Passage::PassageStatus, Passage::SPIpassageObj>(Passage::DOOR_LOCK, Passage::SPIpassageObj( new DoorLock )));
	retVal.insert(std::pair< Passage::PassageStatus, Passage::SPIpassageObj>(Passage::DOOR_UNLOCK, Passage::SPIpassageObj( new DoorUnlock )));
	retVal.insert(std::pair< Passage::PassageStatus, Passage::SPIpassageObj>(Passage::HOLEWAY, Passage::SPIpassageObj( new HoleWay )));
	
	return retVal;
}


}	//namespace advcpp
