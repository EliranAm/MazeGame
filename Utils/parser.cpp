#include "parser.h"
#include "../Objects/passage.h"

#include <stdlib.h>	//atoi

#define NUM_OF_ROOM_DIGIT (3)

namespace advcpp
{

Parser::Parser(const char* _filePath) throw (OpenFileFailed)
	:	m_tokenizer("|,+")
{
	m_fp.open(_filePath);
	if (m_fp.fail())
	{
		throw OpenFileFailed();
	}
}

std::map<ROOM_ID, RoomInfo>& Parser::Start()
{
	RoomInfo roomInfo;
	getline(m_fp, m_line);
	while (!m_fp.eof() && m_line != "\r" && m_line != "\n" && m_line != "")
	{
		if (m_line[0] != '#')
		{
			m_tokenizer.TokenizeLine(m_line);
			InitRoomInfo(&roomInfo);
			CaseOfMonsterOrTreasure(&roomInfo);
			m_roomsInfo.insert(std::pair<ROOM_ID, RoomInfo>(roomInfo.m_id, roomInfo));
		}
		getline(m_fp, m_line);
		roomInfo.ResetInfo();
	}

	MoveFPToMap();
	std::string savedLine = m_line;

	std::streamoff currPos = m_fp.tellg();
	ParseMapHorizontal();
	RestoreFPToMap(currPos);

	ParseMapVertical(savedLine);

	return m_roomsInfo;
}

void Parser::ParseMapVertical(std::string& _line)
{
	std::string line2;
	std::string line3;
	PlaceWallByDirection(_line, Location::NORTH); //place NORTH to all the northest rooms
	while (!m_fp.eof())
	{
		getline(m_fp, line2);
		getline(m_fp, line3);
		ParseVertical(_line, line2, line3);
		_line = line3;
	}
	PlaceWallByDirection(_line, Location::SOUTH); //place SOUTH to all the southest rooms
}

void Parser::RestoreFPToMap(std::streamoff _currPos)
{
	m_fp.clear();
	m_fp.seekg(_currPos, m_fp.beg);
}

void Parser::ParseMapHorizontal()
{
	while(!m_fp.eof())
	{
		ParseHorizontal();
		getline(m_fp, m_line);
		getline(m_fp, m_line);
	}
}

void Parser::MoveFPToMap()
{
	while (m_line == "" || m_line[0] == '\n' || m_line[0] == '#' )
	{
		getline(m_fp, m_line);
	}
}

void Parser::CaseOfMonsterOrTreasure(RoomInfo *_roomInfo)
{
	if  (_roomInfo->m_kindOfRoom == 't')
	{
		InsertTreasureInfo(_roomInfo);
	}
	else if (_roomInfo->m_kindOfRoom == 'm')
	{
		InsertMonsterInfo(_roomInfo);
	}
}

void Parser::InitRoomInfo(RoomInfo *_roomInfo)
{
	_roomInfo->m_id = atoi(m_tokenizer.PopToken().c_str());
	_roomInfo->m_kindOfRoom = m_tokenizer.PopToken()[0];
	_roomInfo->m_roomColor = ParseColor(m_tokenizer.PopToken());
	_roomInfo->m_doorColor = ParseColor(m_tokenizer.PopToken());
	_roomInfo->m_name = m_tokenizer.PopToken();
	_roomInfo->m_description = m_tokenizer.PopToken();
	_roomInfo->m_nameOfMonster.first = false;
}

void Parser::InsertMonsterInfo(RoomInfo *_roomInfo)
{
	_roomInfo->m_nameOfMonster.first = true;
	_roomInfo->m_nameOfMonster.second = m_tokenizer.PopToken();
	InsertTreasureInfo(_roomInfo);
}

void Parser::InsertTreasureInfo(RoomInfo *_roomInfo)
{
	std::string token = m_tokenizer.PopToken();
	_roomInfo->m_gold = atoi(token.c_str());
	try
	{
		while (1)
		{
			token = m_tokenizer.PopToken();
			unsigned int numToAdd = atoi(m_tokenizer.PopToken().c_str());
			if (token == "key")
			{
				_roomInfo->m_keys = numToAdd;
			}
			else if (token == "life")
			{
				_roomInfo->m_potions = numToAdd;
			}
			else if (token == "sword")
			{
				_roomInfo->m_sword = numToAdd;
			}
			else if (token == "shield")
			{
				_roomInfo->m_shield = numToAdd;
			}
			else if (token == "gold")
			{
				_roomInfo->m_gold = numToAdd;
			}
		}
	}
	catch(const Tokenizer::NoMoreTokens&)
	{
	}
}

void Parser::ParseVertical(const std::string &_line1, const std::string &_line2, const std::string &_line3)
{
	unsigned int index = 0;
	while (index + NUM_OF_ROOM_DIGIT <= _line1.size())
	{
		while(_line1[index] == ' ')
		{
			++index;
			if (index + NUM_OF_ROOM_DIGIT >= _line3.size())
			{
				return;
			}
		}

		unsigned int curRoomId = atoi(_line1.substr(index, NUM_OF_ROOM_DIGIT).c_str());
		if (_line2[index] == '|')
		{
			unsigned int nextRoomId = atoi(_line3.substr(index, NUM_OF_ROOM_DIGIT).c_str());
			m_roomsInfo[curRoomId].m_neighborRooms[Location::SOUTH].second = nextRoomId;
			m_roomsInfo[nextRoomId].m_neighborRooms[Location::NORTH].second = curRoomId;

			switch (_line2[index+1])
			{
				case '@':
				{
					m_roomsInfo[curRoomId].m_neighborRooms[Location::SOUTH].first = Passage::DOOR_LOCK;
					m_roomsInfo[nextRoomId].m_neighborRooms[Location::NORTH].first = Passage::DOOR_LOCK;
					break; //if we wanna make each door in different collor so we will make a func
				}
				case '*':
				{
					m_roomsInfo[curRoomId].m_neighborRooms[Location::SOUTH].first = Passage::DOOR_CLOSE;
					m_roomsInfo[nextRoomId].m_neighborRooms[Location::NORTH].first = Passage::DOOR_CLOSE;
					break;
				}
				default:
				{
					m_roomsInfo[curRoomId].m_neighborRooms[Location::SOUTH].first = Passage::HOLEWAY;
					m_roomsInfo[nextRoomId].m_neighborRooms[Location::NORTH].first = Passage::HOLEWAY;
					break;
				}
			}
		}
		else
		{
			m_roomsInfo[curRoomId].m_neighborRooms[Location::SOUTH].first = Passage::WALL;
		}

		index += NUM_OF_ROOM_DIGIT + 1;
	}
}

void Parser::PlaceWallByDirection(const std::string &_line, Location::Direction _location)
{
	unsigned int index = 0;
	while(index < _line.size())
	{
		while(_line[index] == ' ')
		{
			++index;
		}
		unsigned int curRoomId = atoi(_line.substr(index, NUM_OF_ROOM_DIGIT).c_str());
		m_roomsInfo[curRoomId].m_neighborRooms[_location].first = Passage::WALL;
		index += NUM_OF_ROOM_DIGIT + 1;
	}
}

void Parser::ParseHorizontal()
{
	unsigned int index = 0;

	while(m_line[index] == ' ')
	{
		++index;
	}

	unsigned int curRoomId = atoi(m_line.substr(index, NUM_OF_ROOM_DIGIT).c_str());
	m_roomsInfo[curRoomId].m_neighborRooms[Location::WEST].first = Passage::WALL;

	while (index + NUM_OF_ROOM_DIGIT < m_line.size())
	{
		curRoomId = atoi(m_line.substr(index, NUM_OF_ROOM_DIGIT).c_str());
		index += NUM_OF_ROOM_DIGIT;

		switch(m_line[index])
		{
			case '=':
				SetEastAndWestWalls(curRoomId, index, Passage::HOLEWAY);
				break;
			case '*':
				SetEastAndWestWalls(curRoomId, index, Passage::DOOR_CLOSE);
				break;
			case '@':
				SetEastAndWestWalls(curRoomId, index, Passage::DOOR_LOCK);
				break;
			default:
				m_roomsInfo[curRoomId].m_neighborRooms[Location::EAST].first = Passage::WALL;
				break;
		}

		while(m_line[++index] == ' ')
		{ }
	}
}

void Parser::SetEastAndWestWalls(unsigned int _curRoomId, unsigned int _index, Passage::PassageStatus _passage)
{
	m_roomsInfo[_curRoomId].m_neighborRooms[Location::EAST].first = _passage;
	unsigned int nextRoomId = atoi(m_line.substr(_index + 1, NUM_OF_ROOM_DIGIT).c_str());
	m_roomsInfo[_curRoomId].m_neighborRooms[Location::EAST].second = nextRoomId;
	m_roomsInfo[nextRoomId].m_neighborRooms[Location::WEST].second = _curRoomId;
	m_roomsInfo[nextRoomId].m_neighborRooms[Location::WEST].first = _passage;
}

COLOR Parser::ParseColor(const std::string &_color)
{
	if (_color == "red")
	{
		return RED;
	}
	if (_color == "green")
	{
		return GREEN;
	}
	if (_color == "blue")
	{
		return BLUE;
	}
	return WHITE;	//white is default
}

const char* Parser::OpenFileFailed::what() const throw()
{
	return "Please, try check file path.";
}


} //namespace advcpp


