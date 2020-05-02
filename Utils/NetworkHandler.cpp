#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <arpa/inet.h>
#include "NetworkHandler.h"
 
 
// Prototypes

namespace advcpp
{


void NetworkHandler::InitWsa()
{
#ifdef WIN32
	static bool s_alreadyDone = false;
	if (!s_alreadyDone)
	{
		WSADATA wsaData;
		int ret = WSAStartup(0x0202,&wsaData);
		if (ret != 0)
		{
			printf("WSAStartup() failed with error %d\n", ret);
			WSACleanup();
			throw std::bad_alloc();
		}
		s_alreadyDone = true;
	}
#endif
}

#ifndef WIN32
#define WSASocket(A, B, C, D, E, F) socket(A, B , C)
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define SOCKADDR_IN sockaddr_in
#define PSOCKADDR sockaddr*
#define closesocket close
#define WSAEWOULDBLOCK EWOULDBLOCK
#define ioctlsocket(S,X1,X2) fcntl((S), F_SETFL, fcntl((S),F_GETFL,0) | O_NONBLOCK)
inline int WSAGetLastError()
{
	return errno;
}
#endif

void NetworkHandler::InitListener(SOCKET *_socket, unsigned short _port)
{
	if ((*_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		printf("WSASocket() failed with error %d\n", WSAGetLastError());
		throw std::bad_alloc();
	}
	else
		printf("WSASocket() is OK!\n");

	SOCKADDR_IN internetAddr;
	internetAddr.sin_family = AF_INET;
	internetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	internetAddr.sin_port = htons(_port);

   if (bind(*_socket, (PSOCKADDR) &internetAddr, sizeof(internetAddr)) == SOCKET_ERROR)
   {
		printf("bind() failed with error %d\n", WSAGetLastError());
		throw std::runtime_error("bind() failed");
   }
   else
		printf("bind() is OK!\n");

   if (listen(*_socket, 5))
   {
      printf("listen() failed with error %d\n", WSAGetLastError());
	  throw std::runtime_error("listen() failed");
   }
   else
       printf("listen() is OK!\n");

   // Change the socket mode on the listening socket from blocking to
   // non-block so the application will not block waiting for requests
   ULONG nonBlock = 1;
   if (ioctlsocket(*_socket, FIONBIO, &nonBlock) == SOCKET_ERROR)
   {
      printf("ioctlsocket() failed with error %d\n", WSAGetLastError());
	  throw std::runtime_error("ioctlsocket() failed");
   }
   else
      printf("ioctlsocket() is OK!\n");
}

NetworkHandler::~NetworkHandler()
{
	close(m_listenSocket[USERS_LISTENER]);
	close(m_listenSocket[REMOTE_SERVER_LISTENER]);
}

void NetworkHandler::Init()
{
	InitWsa();
	memset(m_socketArray, 0, sizeof(m_socketArray));
	if (m_numListeners > USERS_LISTENER)
	{
		InitListener(&m_listenSocket[USERS_LISTENER], m_usersPort);
	}
	if (m_numListeners > REMOTE_SERVER_LISTENER)
	{
		InitListener(&m_listenSocket[REMOTE_SERVER_LISTENER], m_remoteServerPort);
	}
}

void NetworkHandler::GetInput(size_t *_socketid, std::string *_input)
{
	printf("FD_SETSIZE[%d]", FD_SETSIZE);
	while (true)
	{
		if (!m_totalSocketsReady)
		{
			FD_SET_TYPE writeSet;
			FD_ZERO(&writeSet);
			FD_ZERO(&m_lastReadSet);
			m_nextReadSocketToTraverse = 0;

			// Always look for connection attempts
			for (int i = 0 ; i < m_numListeners ; ++i)
			{
				FD_SET(m_listenSocket[i], &m_lastReadSet);
			}

			// Set Read and Write notification for each socket based on the
			// current state the buffer.  If there is data remaining in the
			// buffer then set the Write set otherwise the Read set
			for (int i = 0 ; i < FD_SETSIZE ; i++)
			{
				if (m_socketArray[i])
				{
					if (m_socketArray[i]->writeLen)
						FD_SET(m_socketArray[i]->Socket, &writeSet);
					else
						FD_SET(m_socketArray[i]->Socket, &m_lastReadSet);
				}
			}

			timeval t;
			t.tv_sec = 0;
			t.tv_usec = 1000;
			m_totalSocketsReady = select(FD_SETSIZE, &m_lastReadSet, &writeSet, NULL, &t) ;
			if (m_totalSocketsReady == SOCKET_ERROR)
			{
				m_totalSocketsReady = 0;
				printf("select() returned with error %d\n", WSAGetLastError());
				throw std::runtime_error("select() returned with error");
			}
			else if (m_totalSocketsReady)
				printf("select() is OK! %d\n", m_totalSocketsReady);

			//**************************************************************SEND*******************
			// Check each socket for WRITE notification until the number
			for (int i = 0 ; m_totalSocketsReady && i < FD_SETSIZE ; i++)
			{
				SOCKET_INFORMATION *socketInfo = m_socketArray[i];
				if (!socketInfo)
				{
					continue; // skip
				}

				// If the WriteSet is marked on this socket then this means the internal
				// data buffers are available for more data
				if (FD_ISSET(socketInfo->Socket, &writeSet))
				{
					--m_totalSocketsReady;

					DWORD sendBytes = send(socketInfo->Socket, socketInfo->writeBuffer, socketInfo->writeLen, 0);
					if (sendBytes == SOCKET_ERROR)
					{
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							printf("WSASend() failed with error %d\n", WSAGetLastError());
							FreeSocketInformation(i);
						}
						else
							printf("WSASend() is OK!\n");

						continue;
					}
					else
					{
						assert(sendBytes);
						if (sendBytes < socketInfo->writeLen)
						{
							memcpy(socketInfo->writeBuffer, socketInfo->writeBuffer + sendBytes, socketInfo->writeLen - sendBytes);
							socketInfo->writeLen -= sendBytes;
						}
						else
						{
							socketInfo->writeLen = 0;
						}
					}
				}
			}

			//**************************************************************ACCEPT*******************
			// Check for arriving connections on the listening socket.
			for (int i = 0 ; i < m_numListeners ; ++i)
			{
				if (FD_ISSET(m_listenSocket[i], &m_lastReadSet))
				{
					--m_totalSocketsReady;
					SOCKET newSocket = accept(m_listenSocket[i], NULL, NULL);
					if (newSocket != INVALID_SOCKET)
					{
						// Set the accepted socket to non-blocking mode so the server will
						// not get caught in a blocked condition on WSASends
						ULONG NonBlock = 1;
						if (ioctlsocket(newSocket, FIONBIO, &NonBlock) == SOCKET_ERROR)
						{
							printf("ioctlsocket(FIONBIO) failed with error %d\n", WSAGetLastError());
							throw std::runtime_error("ioctlsocket(FIONBIO) failed with error");
						}
						else
							printf("ioctlsocket(FIONBIO) is OK!\n");

						if (REMOTE_SERVER_LISTENER == i)
						{
							CreateSocketInformation(newSocket, i);
						}
						else
						{
							*_socketid = CreateSocketInformation(newSocket, i);
							_input->clear();
							return;
						}
					}
					else
					{
						if (WSAGetLastError() != WSAEWOULDBLOCK)
						{
							printf("accept() failed with error %d\n", WSAGetLastError());
							throw std::runtime_error("accept() failed with error");
						}
						else
							printf("accept() is fine!\n");
					}
				}
			}
		}
		//**************************************************************RECV*******************
		for ( ; m_totalSocketsReady ; ++m_nextReadSocketToTraverse)
		{
			SOCKET_INFORMATION *socketInfo = m_socketArray[m_nextReadSocketToTraverse];
			if (!socketInfo)
			{
				continue;
			}
			assert(socketInfo);

			// If the ReadSet is marked for this socket then this means data
			// is available to be read on the socket
			if (FD_ISSET(socketInfo->Socket, &m_lastReadSet))
			{
				--m_totalSocketsReady;

				DWORD recvBytes = recv(socketInfo->Socket, &socketInfo->readBuffer[socketInfo->BytesRECV], READ_DATA_BUFSIZE - socketInfo->BytesRECV, 0);
				if (recvBytes == -1)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						printf("WSARecv() failed with error %d\n", WSAGetLastError());
						FreeSocketInformation(m_nextReadSocketToTraverse);
					}
					else
						printf("WSARecv() is OK!\n");
					continue;
				}
				else
				{
					// If zero bytes are received, this indicates the peer closed the connection.
					if (recvBytes == 0)
					{
						FreeSocketInformation(m_nextReadSocketToTraverse);
						continue;
					}

					socketInfo->BytesRECV += recvBytes;
					assert(socketInfo->BytesRECV);
					if (socketInfo->readBuffer[socketInfo->BytesRECV - 1] == '\n' || socketInfo->readBuffer[socketInfo->BytesRECV - 1] == '\r')
					{
						*_socketid = m_nextReadSocketToTraverse;
						_input->assign(socketInfo->readBuffer, socketInfo->readBuffer + socketInfo->BytesRECV);
						socketInfo->BytesRECV = 0;
						_input->erase(_input->find_last_not_of(" \n\r\t")+1);
						++m_nextReadSocketToTraverse;
						return;
					}
				}
			}
		}
		assert(!m_totalSocketsReady);
	}
}

void NetworkHandler::PutOutput(size_t _socketid, const std::string &_output)
{
	if (_socketid >= sizeof(m_socketArray) / sizeof(*m_socketArray))
	{
		assert(_socketid < m_virtualSocketIdToRealSocketId.size());
		size_t virtualSocketId = _socketid;
		_socketid = m_virtualSocketIdToRealSocketId[virtualSocketId];

		//char buf[30];
		//itoa(virtualSocketId, buf, 10);
		//strcat(buf, ",");
		//_itoa(_output.size(), &buf[strlen(buf)], 10);
		//strcat(buf, ",");
		//size_t prefixLen = strlen(buf);
		//memcpy(&m_socketArray[_socketid]->writeBuffer[m_socketArray[_socketid]->writeLen], buf, prefixLen);
		//m_socketArray[_socketid]->writeLen += prefixLen;
	}

	if(m_socketArray[_socketid])
	{
#ifdef WIN32
		for (int i = 0 ; i < _output.size() ; ++i)
		{
			if (_output[i] == '\n')
			{
				m_socketArray[_socketid]->writeBuffer[m_socketArray[_socketid]->writeLen++] = '\r';
				m_socketArray[_socketid]->writeBuffer[m_socketArray[_socketid]->writeLen++] = '\n';
			}
			else
			{
				m_socketArray[_socketid]->writeBuffer[m_socketArray[_socketid]->writeLen++] = _output[i];
			}
		}
#else
		memcpy(&m_socketArray[_socketid]->writeBuffer[m_socketArray[_socketid]->writeLen], _output.c_str(), _output.size());
		m_socketArray[_socketid]->writeLen += _output.size();
#endif
	}
}

size_t NetworkHandler::CreateSocketInformation(SOCKET s, size_t _listenerIdx)
{
 
   printf("Accepted socket number %d\n", s);
 
   SOCKET_INFORMATION *SI = new SOCKET_INFORMATION(s, m_closedConnectionFunc[_listenerIdx].get());

   size_t socketIdx = 0;
	for ( ; (socketIdx < FD_SETSIZE) && m_socketArray[socketIdx] ; ++socketIdx)
		;

	m_socketArray[socketIdx] = SI;

	m_newConnectionFunc[_listenerIdx]->Call(socketIdx);
	return socketIdx;
}

void NetworkHandler::CloseConnection(size_t _Index)
{
	FreeSocketInformation(_Index);
}

void NetworkHandler::FreeSocketInformation(DWORD Index)
{
	SOCKET_INFORMATION *SI = m_socketArray[Index];
	m_socketArray[Index] = NULL;

	closesocket(SI->Socket);
	printf("Closing socket number %d\n", SI->Socket);

	SI->m_connectionClosedCallback->Call(Index);
	delete SI;
}

}//namespace advcpp
