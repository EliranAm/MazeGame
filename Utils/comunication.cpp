#include "comunication.h"
#include "../Commands/create_hero.h"

namespace advcpp
{

GameComunication::GameComunication(size_t _port) 
	: m_netCom(_port, PlayerCreator(), PlayerReleaser())
{ }

void GameComunication::Read(size_t *_connectionId, std::string &_inbuf)
{
	m_netCom.GetInput(_connectionId, &_inbuf);
}

void GameComunication::Write(size_t _connectionId, const std::string &_inbuf)
{
	m_netCom.PutOutput(_connectionId, _inbuf);
}

void GameComunication::ClosePlayerConnection(size_t _heroId)
{
	m_netCom.CloseConnection(_heroId);
}

}	//namespace advcpp
