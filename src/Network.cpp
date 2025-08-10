#include "Network.h"

#include <Windows.h>

#include "Config.h"


#pragma comment(lib, "Ws2_32.lib")


int startupWS2()
{
	WSAData wsa;
	return WSAStartup(MAKEWORD(2, 2), &wsa);
}

int PeerAddr::toSockaddrInet(sockaddr_in& pSain) const
{
	pSain.sin_family = AF_INET;
	pSain.sin_port = htons(port);
	return inet_pton(AF_INET, host.c_str(), &pSain.sin_addr);
}


Peer::Peer()
{
	mPAddr.host = "";
	mPAddr.port = -1;
	mServer = INVALID_SOCKET;
}
Peer& Peer::thisPeer()
{
	static Peer sPeer;
	return sPeer;
}

int Peer::init()
{
	mPAddr.host = getConfig(CONFIG_PSERVER_START_ON);
	mPAddr.port = (USHORT)std::stoi(getConfig(CONFIG_PSERVER_PORT));

	std::printf("Peer Addr initialized %s:%hu\n", mPAddr.host.c_str(), mPAddr.port);

	mServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mServer == SOCKET_ERROR)
	{
		std::printf("Creating socket failed\n");
		return 1;
	}

	int status = 0;
	
	sockaddr_in addr{};
	mPAddr.toSockaddrInet(addr);
	status = bind(mServer, (sockaddr*)&addr, sizeof(addr));
	if (status == SOCKET_ERROR)
	{
		std::printf("Bind failed\n");
		return 2;
	}

	status = listen(mServer, std::stoi(getConfig(CONFIG_PSERVER_BACKLOG)));
	if (status == SOCKET_ERROR)
	{
		std::printf("Listen failed\n");
		return 3;
	}

	std::printf("Peer listener (server side) initialized on %hu\n", mPAddr.port);

	return 0;
}
void Peer::run()
{
	//listening
	std::printf("Starting listening\n");

	//Amount of client to handle (temporary)
	int counter = 0;

	while (true)
	{
		if (counter > 10) break;
		counter++;

		sockaddr_in saddr{};
		int saddrlen = sizeof(saddr);
		SOCKET sock = accept(mServer, (sockaddr*)&saddr, &saddrlen);
		char fromConn[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &saddr.sin_addr, fromConn, INET_ADDRSTRLEN);
		std::printf("Connected from %s\n", fromConn);
	}
}
void Peer::close()
{
	closesocket(mServer);
	std::printf("Closing peer server\n");
}
