#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "../Utils/uncopyable.h"
#include <string>


namespace advcpp
{

class Character : private Uncopyable
{
public:
	Character(size_t _sword, size_t _shield, size_t _key, size_t _gold, size_t _potions);
	virtual ~Character() {}
	
	const std::string GetAttacked(size_t _attackerSwordLevel, size_t _attackStregnth);
	bool IsDead() const { return m_hp == 0; }
	
	const std::string GetName() const { return m_name; }
	size_t GetSword() const { return m_sword; }
	size_t GetShield() const { return m_shield; }
	size_t GetNumOfKeys() const { return m_keys; }
	size_t GetNumOfPotions() const { return m_potions; }
	size_t GetGold() const { return m_gold; }
	size_t GetHp() const { return m_hp; }
	
	void SetSword(size_t _sword) { m_sword = _sword; }
	void SetShield(size_t _shield) { m_shield = _shield; }
	
	void AddKeys(size_t _numOfKeys) { m_keys += _numOfKeys; }
	void AddPotions(size_t _numOfPotions) { m_potions += _numOfPotions; }
	void AddGold(size_t _gold) { m_gold += _gold; }
	void AddHp(size_t _hp);

	bool RemoveKeys(size_t _numOfkeys = 1);
	bool RemovePotions(size_t _numOfPotions = 1);
	bool RemoveGold(size_t _gold);
	void Reset();
	
protected:
	void SetName(const std::string& _name) { m_name = _name; }
	void SetHp(size_t _hp) { m_hp = _hp; }

private:
	std::string m_name;
	size_t m_sword;
	size_t m_shield;
	size_t m_keys;
	size_t m_hp;
	size_t m_gold;
	size_t m_potions;
};

} //namespace advcpp

#endif /* __CHARACTER_H__ */
