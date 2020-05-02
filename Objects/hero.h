#ifndef __HERO_H__
#define __HERO_H__

#include <string>
#include "character.h"
#include "location.h"


namespace advcpp
{

class Hero : public Character
{
public:
enum UserStatus { NEW = 0, TALKING, SHOUTING, RAGE, QUIT, COMMAND };

	explicit Hero(unsigned int _id);
	virtual ~Hero();
	
	unsigned int GetID() const { return m_id; }
	UserStatus GetStatus() const { return m_status; }
	const std::string PrintHero() const;

	Location::Direction GetLocation() const { return m_location; }
	Location::Direction ReverseLocation() const;

	void SetStatus(UserStatus _status);
	void SetName(const std::string& _name);
	void Reset();
	
	void Left();
	void Right();

private:
/*  
	*Charecter data member*
	std::string m_name;
	unsigned int m_sword;
	unsigned int m_shield;
	unsigned int m_keys;
	unsigned int m_hp;
	unsigned int m_gold;
	unsigned int m_potions;
*/
	unsigned int m_id;
	Location::Direction m_location;
	UserStatus m_status;
};

}//advcpp

#endif /* __HERO_H__ */

