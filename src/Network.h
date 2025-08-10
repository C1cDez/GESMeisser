#pragma once

#include <string>

#include <WinSock2.h>
#include <WS2tcpip.h>


int startupWS2();

//IPv4
struct PeerAddr
{
	std::string host;
	USHORT port;

	int toSockaddrInet(sockaddr_in& pSain) const;
};


class Peer
{
public:
	static Peer& thisPeer();

	Peer(const Peer&) = delete;
	Peer& operator=(const Peer&) = delete;

	int init();
	void run();
	void close();

private:
	PeerAddr mPAddr;
	SOCKET mServer;

	Peer();
};
