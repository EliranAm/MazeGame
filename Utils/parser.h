#ifndef __PARSER_H__
#define __PARSER_H__

#include <fstream> 
#include <map>

#include "../Objects/location.h"
#include "tokenizer.h"
#include "../Objects/room_info.h"
#include "../Objects/colors.h"
#define ROOM_ID size_t

namespace advcpp
{

class Parser
{
public:
	struct OpenFileFailed : public std::exception
	{
		virtual const char* what() const throw();
	};	

	explicit Parser(const char* _filePath) throw (OpenFileFailed);

	std::map<ROOM_ID, RoomInfo>& Start();

private:
	void InitRoomInfo(RoomInfo *_roomInfo);
	void CaseOfMonsterOrTreasure(RoomInfo *_roomInfo);
	void MoveFPToMap();
	void ParseMapHorizontal();
	void RestoreFPToMap(std::streamoff _currPos);
	void ParseMapVertical(std::string& _line);
	void ParseHorizontal();
	void ParseVertical(const std::string &_line1, const std::string &_line2, const std::string &_line3);	
	void PlaceWallByDirection(const std::string &_line, Location::Direction _location);
	COLOR ParseColor(const std::string &_color);
	void InsertTreasureInfo(RoomInfo *_roomInfo);
	void InsertMonsterInfo(RoomInfo *_roomInfo);
	void SetEastAndWestWalls(unsigned int _curRoomId, unsigned int _index, Passage::PassageStatus _passage);

	Tokenizer m_tokenizer;
	std::ifstream m_fp;
	std::string m_line;
	std::map<ROOM_ID, RoomInfo> m_roomsInfo;
	
};

}	//namespace advcpp

#endif /* __PARSER_H__ */

