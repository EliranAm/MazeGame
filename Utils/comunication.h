#ifndef __GAME_COMUNICATION_H__
#define __GAME_COMUNICATION_H__

#include "NetworkHandler.h"
#include "../Objects/maze.h"
#include "../Utils/uncopyable.h"
#include <iostream>
#include <string>
namespace advcpp
{

class GameComunication : private Uncopyable
{
	struct PlayerCreator
	{
		void operator()(size_t _connectionId)
		{
			std::cout << _connectionId << " connected!\n";
		}
	};
	
	struct PlayerReleaser
	{
		void operator()(size_t _connectionId)
		{
			std::cout << _connectionId << " disconnected!\n";
		}
	};

public:
	GameComunication(size_t _port);
	void ClosePlayerConnection(size_t _heroId);
	void Read(size_t *_connectionId, std::string &_inbuf);
	void Write(size_t _connectionId, const std::string &_inbuf);
private:
	NetworkHandler m_netCom;
};

}//namespace advcpp
#endif /* __GAME_COMUNICATION_H__ */

