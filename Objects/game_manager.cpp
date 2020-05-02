#include "game_manager.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include "../Utils/parser.h"
#include "room.h"

namespace advcpp
{

bool GameManager::s_runFlag = false;

GameManager::GameManager(Parser& _parser, size_t _port) 
	: m_maze(_parser.Start())
	, m_gameCom(_port)
	, m_commandManager(CreateCommands())
{
    InitSignalHandler();
}

GameManager::SPCommMan GameManager::CreateCommands()
{
	std::vector<std::string> commands;
	commands.push_back("");
	commands.push_back("look");
	commands.push_back("walk");
	commands.push_back("back");
	commands.push_back("left");
	commands.push_back("right");
	commands.push_back("open");
	commands.push_back("close");
	commands.push_back("attack");
	commands.push_back("take");
	commands.push_back("talk");
	commands.push_back("shout");
	commands.push_back("unlock");
	commands.push_back("lock");
	commands.push_back("help");
	commands.push_back("heal");
	commands.push_back("rage");
	commands.push_back("quit");
	
    m_maze.SetCommands(commands);
	return SPCommMan(new CommandManager(commands, m_gameCom));
}

/* Signal handler - ctrl + c */
void GameManager::ServerSigHandler(int _sigNum, siginfo_t *_info, void *_contex)
{
	
	GameManager::s_runFlag = false;
}

void GameManager::InitSignalHandler()
{
	struct sigaction serverSignal;
	serverSignal.sa_sigaction = ServerSigHandler;
	serverSignal.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &serverSignal, NULL);
}


void GameManager::Start()
{
	s_runFlag = true;
	std::string command;

	while (s_runFlag)
	{
		size_t id;
		m_gameCom.Read(&id, command);
		command = m_commandManager->ExecuteCommand(id, command, m_maze);
		command += "\n(type help for command list)->";
		m_gameCom.Write(id, command);
	}
}


} //namespace advcpp








