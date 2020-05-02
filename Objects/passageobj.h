#ifndef __PASSAGE_OBJ_H__
#define __PASSAGE_OBJ_H__

#include <string>
#include "../Utils/uncopyable.h"

namespace advcpp
{

class IpassageObj : private Uncopyable
{
public:

	virtual ~IpassageObj(){};
	virtual std::string DrawHorizontal() const = 0;
	virtual std::string DrawVertical() const = 0;
	virtual std::string StatusToStr() const = 0;

};


class Wall : public IpassageObj
{

public:

	std::string DrawHorizontal() const { return "-----------------------------------------------------------------------------------------\n"; }
	std::string DrawVertical() const { return "||||||||||||||||||||||||||||||\n"; }
	std::string StatusToStr() const { return "WALL"; }
};

class DoorClose: public IpassageObj
{

public:

	std::string DrawHorizontal() const { return "--------------------------------=========================--------------------------------\n"; }
	std::string DrawVertical() const { return "||||||||||||888888||||||||||||\n";}
	std::string StatusToStr() const { return "DOOR_CLOSE"; }
};

class DoorOpen: public IpassageObj
{

public:
	
	std::string DrawHorizontal() const { return "--------------------------------\\                       /--------------------------------\n"; }
	std::string DrawVertical() const { return "||||||||||||\\    /||||||||||||\n"; }
	std::string StatusToStr() const { return "DOOR_OPEN"; }
};

class DoorLock: public IpassageObj
{

public:

	std::string DrawHorizontal() const { return "--------------------------------===========&&&===========--------------------------------\n"; }
	std::string DrawVertical() const { return "||||||||||||LLLLLL||||||||||||\n"; }
	std::string StatusToStr() const { return "DOOR_LOCK"; }
};

class DoorUnlock: public IpassageObj
{

public:

	std::string DrawHorizontal() const { return "--------------------------------U                       U--------------------------------\n"; }
	std::string DrawVertical() const { return "||||||||||||U    U||||||||||||\n"; }
	std::string StatusToStr() const { return "DOOR_UNLOCK"; }
};


class HoleWay: public IpassageObj
{

public:

	std::string DrawHorizontal() const { return "--------------------------------|                       |--------------------------------\n"; }
	std::string DrawVertical() const { return "||||||||||||      ||||||||||||\n"; }
	std::string StatusToStr() const { return "HOLEWAY"; }
};






} //namespace advcpp

#endif /* __PASSAGE_OBJ_H_*/
