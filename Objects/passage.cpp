#include "passage.h"
#include "../Utils/passageobjfactory.h"

namespace advcpp
{

Passage::Passage(PassageStatus _status) 
	: m_status(_status)
	, m_PassageObj( passageObjFactory::CreateAllObj() )
{
	
}

std::string Passage::DrawHorizontal() const
{
	return m_PassageObj.at(m_status)->DrawHorizontal();
}

std::string Passage::DrawVertical() const
{
	return m_PassageObj.at(m_status)->DrawVertical();
}

std::string Passage::StatusToStr() const
{
	return m_PassageObj.at(m_status)->StatusToStr();
}

const Passage& Passage::OpenPassage()
{
	if (m_status == DOOR_CLOSE)
	{
		m_status = DOOR_OPEN;
	}
	
	return *this;
}

const Passage& Passage::ClosePassage()
{
	if (m_status == DOOR_OPEN)
	{
		m_status = DOOR_CLOSE;
	}
	
	return *this;
}

const Passage& Passage::UnlockPassage()
{
	if (m_status == DOOR_LOCK)
	{
		m_status = DOOR_UNLOCK;
	}
	
	return *this;
}

const Passage& Passage::LockPassage()
{
	if (m_status == DOOR_UNLOCK)
	{
		m_status = DOOR_LOCK;
	}
	
	return *this;
}


} //namespace advcpp

