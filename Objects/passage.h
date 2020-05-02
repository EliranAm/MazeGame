#ifndef __PASSAGE_H__
#define __PASSAGE_H__

#include <string>
#include <map>
#include <tr1/memory>
#include "../Utils/uncopyable.h"
#include "passageobj.h"

namespace advcpp
{

class Passage 
{

public:
enum PassageStatus { WALL = 0, DOOR_OPEN, DOOR_CLOSE, DOOR_LOCK, DOOR_UNLOCK, HOLEWAY };
typedef std::tr1::shared_ptr<IpassageObj> SPIpassageObj;
typedef std::map<PassageStatus,SPIpassageObj> PassageObjCon;
	
public:
	explicit Passage(PassageStatus _status);
	//~Passage(){} = default
	
	std::string DrawHorizontal() const;
	std::string DrawVertical() const;
	std::string StatusToStr() const;
	
	PassageStatus GetStatus() const { return m_status; }
	void SetStatus(PassageStatus _status) { m_status = _status; }
	
	const Passage& OpenPassage();
	const Passage& ClosePassage();
	const Passage& LockPassage();
	const Passage& UnlockPassage();

private:
	PassageStatus m_status;
	PassageObjCon m_PassageObj;
};

} //namespace advcpp

#endif /* __PASSAGE_H__ */
