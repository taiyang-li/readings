/* socket.cpp
 *
 * Copyright (c) 2000 Sean Walton and Macmillan Publishers.  Use may be in
 * whole or in part in accordance to the General Public License (GPL).
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
*/

/*****************************************************************************/
/*** socket.cpp                                                            ***/
/***                                                                       ***/
/*** Implements the C++ socket framework.                                  ***/
/*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <errno.h>
#include <signal.h>
#include "socket.h"

///////////////////////////////////////////////////////////////////////////////
/// SimpleString
//-----------------------------------------------------------------------------
//--- Constructors & Destructors
SimpleString::SimpleString(const char* s)
{
	Length = strlen(s);
	Buffer = new char[Length+1];
	strcpy(Buffer, s);
}

SimpleString::SimpleString(const SimpleString& s)
{
	Length = s.GetLength();
	Buffer = new char[Length+1];
	strcpy(Buffer, s.GetString());
}

SimpleString::~SimpleString(void)
{
	delete Buffer;
}

//-----------------------------------------------------------------------------
//--- Operator overload support
void SimpleString::Append(const char* s)
{
	Length += strlen(s);
	char *tmps=new char[Length+1];
	strcpy(tmps, Buffer);
	strcat(tmps, s);
	delete Buffer;
	Buffer = tmps;
}

void SimpleString::Append(const SimpleString& s)
{
	Length += s.GetLength();
	char *tmps=new char[Length+1];
	strcpy(tmps, Buffer);
	strcat(tmps, s.GetString());
	delete Buffer;
	Buffer = tmps;
}

///////////////////////////////////////////////////////////////////////////////
/// Exception
//-----------------------------------------------------------------------------
//--- Specific Implementation
void Exception::PrintException(void) const
{
	fprintf(stderr, "%s", Msg.GetString());
	if ( ErrNo != 0 )
	{
		errno = ErrNo;
		perror("-- Error");
	}
	else
		printf("\n");
}

///////////////////////////////////////////////////////////////////////////////
/// HostAddress
//-----------------------------------------------------------------------------
//--- Constructors & Destructors
HostAddress::HostAddress(const char* Name, ENetwork network)
{
	switch ( network )
	{
		case eIPv4:
		{	long s_addr;
			int port = 0;

			if ( Name != 0 )
			{
				char *portname = strrchr(Name, ':');
				if ( portname != 0  &&  (port = atoi(portname+1)) > 0 )
					*portname = 0;
				struct hostent *host = gethostbyname(Name);
				if ( host == NULL )
					throw NetDNSException(SimpleString("gethostbyname [") + Name + "]");
				s_addr = *reinterpret_cast<long*>(host->h_addr);
			}
			else
				s_addr = INADDR_ANY;
			struct sockaddr_in *addr = new struct sockaddr_in();
			addr->sin_family = network;
			addr->sin_port = htons(port);
			addr->sin_addr.s_addr = s_addr;
			Addr = reinterpret_cast<struct sockaddr*>(addr);
			break;
		}
		case eIPv6:
		{
			struct sockaddr_in6 *addr = new struct sockaddr_in6();
			addr->sin6_family = network;
			addr->sin6_port = 0;
			if ( Name == 0 )
				Name = "0::0";
			if ( inet_pton(eIPv6, Name, &addr->sin6_addr) == 0 )
				throw NetConversionException(SimpleString("inet_pton failed [") + Name + "]");
			Addr = reinterpret_cast<struct sockaddr*>(addr);
			break;
		}
		default :
			throw Exception("Network type not supported", ENOTSUP);
	}
	Network = network;
}

HostAddress::HostAddress(HostAddress& Address)
{
	switch ( Network )
	{
		case eIPv4:
		{
			Network = Address.Network;
			struct sockaddr_in *addr = new struct sockaddr_in();
			memcpy(addr, Address.Addr, sizeof(*addr));
			Addr = reinterpret_cast<struct sockaddr*>(addr);
			break;
		}
		case eIPv6:
		{
			Network = Address.Network;
			struct sockaddr_in6 *addr = new struct sockaddr_in6();
			memcpy(addr, Address.Addr, sizeof(*addr));
			Addr = reinterpret_cast<struct sockaddr*>(addr);
			break;
		}
	}
}

HostAddress::~HostAddress(void)
{
	delete Addr;
}

//-----------------------------------------------------------------------------
//--- Specific Implementation
void HostAddress::SetPort(int Port)
{
	switch ( Network )
	{
		case eIPv4:
		{
			struct sockaddr_in *inet = reinterpret_cast<struct sockaddr_in*>(Addr);
			inet->sin_port = htons(Port);
			break;
		}
		case eIPv6:
		{
			struct sockaddr_in6 *inet6 = reinterpret_cast<struct sockaddr_in6*>(Addr);
			inet6->sin6_port = htons(Port);
			break;
		}
	}
}

int HostAddress::GetPort(void) const
{
	switch ( Network )
	{
		case eIPv4: return (reinterpret_cast<struct sockaddr_in*>(Addr))->sin_port;
		case eIPv6: return (reinterpret_cast<struct sockaddr_in6*>(Addr))->sin6_port;
	}
}

int HostAddress::GetSize(void) const
{
	switch ( Network )
	{
		case eIPv4: return sizeof(struct sockaddr_in);
		case eIPv6: return sizeof(struct sockaddr_in6);
	}
}

int HostAddress::operator ==(HostAddress& Address) const
{
	if ( Network != Address.Network )
		return 0;
	switch ( Network )
	{
		case eIPv4:
		case eIPv6: return (memcmp(Addr, Address.Addr, GetSize()) == 0);
		default: return 0;
	}
}

const char* HostAddress::GetHost(bool byName)
{
	switch ( Network )
	{
		case eIPv4:
		{
			char *name;
			struct sockaddr_in *inet = reinterpret_cast<struct sockaddr_in*>(Addr);

			if ( byName )
			{
				char *addr = reinterpret_cast<char*>(&(inet->sin_addr.s_addr));
				int size = sizeof(inet->sin_addr.s_addr);
				struct hostent *host = gethostbyaddr(addr, size, GetNetwork());
				if ( host == NULL )
					throw NetDNSException(SimpleString("gethostbyaddr failed for [") +
						inet_ntoa(inet->sin_addr) + "]");
				name = host->h_name;
			}
			else
				name = inet_ntoa(inet->sin_addr);
			sprintf(HostName, "%s:%d", name, (inet->sin_port));
			break;
		}
		case eIPv6:
		{
			struct sockaddr_in6 *inet6 = reinterpret_cast<struct sockaddr_in6*>(Addr);
			inet_ntop(GetNetwork(), Addr, HostName, MaxHostName);
			char TempS[10];
			sprintf(TempS, ":%d", inet6->sin6_port);
			strncat(HostName, TempS, MaxHostName);
			break;
		}
		default: strncpy(HostName, "<unsupported>", MaxHostName); break;
	}
	HostName[MaxHostName-1] = 0;
	return HostName;
}

///////////////////////////////////////////////////////////////////////////////
/// TextMessage
//-----------------------------------------------------------------------------
//--- Constructors & Destructors
TextMessage::TextMessage(unsigned short Bytes)
{
	Buffer = new char[Bytes];
	Available = Size = Bytes;
}

TextMessage::TextMessage(const char* Msg, unsigned short Len)
{
	if ( Len == 0 )
		Len = strlen(Msg)+1;
	Buffer = new char[Len];
	memcpy(Buffer, Msg, Len);
	Available = Size = Len;
}

TextMessage::~TextMessage(void)
{
	delete Buffer;
}

//-----------------------------------------------------------------------------
//--- Operator overload support
void TextMessage::SetString(const char* str, int len)
{
	if ( len <= 0 )
		len = strlen(str)+1;
	if ( len >= Available )
	{
		delete Buffer;
		Buffer = new char[len];
		Available = len;
	}
	Size = len;
	strcpy(Buffer, str);
}

void TextMessage::Append(const char* str, int len)
{
	if ( len <= 0 )
		len = strlen(str);
	if ( Size+len > Available )
	{
		char *B = new char[Size+len];
		strcpy(B, Buffer);
		delete Buffer;
		Buffer = B;
		Available = Size+len;
	}
	Size += len;
	strcat(Buffer, str);
}

//-----------------------------------------------------------------------------
//--- Specific Implementation
char *TextMessage::Wrap(int& Bytes) const
{
	Bytes = Size;
	char *data = new char[Size];
	strcpy(data, Buffer);
	return data;
}

bool TextMessage::Unwrap(char *Data, int Bytes, int MsgNum)
{
	if ( MsgNum > 1 )
		Append(Data, Bytes-1);
	else
		SetString(Data, Bytes);
	return reinterpret_cast<bool>(Data[Bytes-1] == 0);
}

///////////////////////////////////////////////////////////////////////////////
/// Socket
//-----------------------------------------------------------------------------
//--- Constructors & Destructors
Socket::Socket(ENetwork Network, EProtocol Protocol)
{
	SD = socket(Network, Protocol, 0);
	if ( SD < 0 )
		throw NetException("Could not create socket");
}

Socket::Socket(Socket& sock)
{
	int err;
	socklen_t size=sizeof(err);
	if ( getsockopt(SD, SOL_SOCKET, SO_ERROR, &err, &size) != 0 )
		throw NetException("Socket error");
	if ( (SD = dup(sock.SD)) < 0 )
		throw FileException("Can't copy socket");
}

Socket::~Socket(void)
{
	if ( close(SD) != 0 )
		throw FileException("Can't close socket");
}

//-----------------------------------------------------------------------------
//--- Specific Implementation
void Socket::Bind(HostAddress& Addr)
{
	if ( bind(SD, Addr.GetAddress(), Addr.GetSize()) != 0 )
		throw NetConnectException("Could not bind socket");
}

int  Socket::Send(Message& Msg, int Options) const
{
	int bytes;
	char *buf = Msg.Wrap(bytes);
	bytes = send(SD, buf, bytes, Options);
	delete buf;
	if ( bytes < 0 )
		throw NetIOException("Could not send message");
	return bytes;
}

int  Socket::Send(HostAddress& Addr, Message& Msg, int Options) const
{
	int bytes;
	char *buf = Msg.Wrap(bytes);
	bytes = sendto(SD, buf, bytes, Options, Addr.GetAddress(), Addr.GetSize());
	delete buf;
	if ( bytes < 0 )
		throw NetIOException("Could not send directed message");
	return bytes;
}

int  Socket::Receive(Message& Msg, int Options) const
{	const int BufferSize = 65536;
	bool done;
	int bytes, cnt=0;
	char *buf = new char[BufferSize];
	do
	{
		bytes = recv(SD, buf, BufferSize, Options);
		if ( bytes < 0 )
		{
			delete buf;
			throw NetIOException("Could could get message");
		}
		cnt++;
		done = Msg.Unwrap(buf, bytes, cnt);
	}
	while ( !done );
	delete buf;
	return bytes;
}

int  Socket::Receive(HostAddress& Addr, Message& Msg, int Options) const
{	const int BufferSize = 65536;
	socklen_t len = Addr.GetSize();
	bool done;
	int bytes, cnt=0;
	char *buf = new char[BufferSize];
	do
	{
		bytes = recvfrom(SD, buf, BufferSize, Options, Addr.GetAddress(), &len);
		if ( bytes < 0 )
		{
			delete buf;
			throw NetIOException("Could could get message");
		}
		cnt++;
		done = Msg.Unwrap(buf, bytes, cnt);
	}
	while ( !done );
	delete buf;
	return bytes;
}

//-----------------------------------------------------------------------------
//--- Class configuration (CRUD)
void Socket::PermitRoute(bool Setting)
{
	int val = (Setting == 0);
	if ( setsockopt(SD, SOL_SOCKET, SO_DONTROUTE, &val, sizeof(val)) != 0 )
		throw NetConfigException("Socket Option: set DONTROUTE");
}

void Socket::KeepAlive(bool Setting)
{
	int val = (Setting != 0);
	if ( setsockopt(SD, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof(val)) != 0 )
		throw NetConfigException("Socket Option: set KEEPALIVE");
}

void Socket::ShareAddress(bool Setting)
{
	int val = (Setting != 0);
	if ( setsockopt(SD, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) != 0 )
		throw NetConfigException("Socket Option: set REUSEADDR");
}

int  Socket::GetReceiveSize(void)
{
	int val;
	socklen_t size=sizeof(val);
	if ( getsockopt(SD, SOL_SOCKET, SO_RCVBUF, &val, &size) != 0 )
		throw NetConfigException("Socket Option: get RCVBUF");
	return val;
}

void Socket::SetReceiveSize(int Bytes)
{
	if ( setsockopt(SD, SOL_SOCKET, SO_RCVBUF, &Bytes, sizeof(Bytes)) != 0 )
		throw NetConfigException("Socket Option: set RCVBUF");
}

int  Socket::GetSendSize(void)
{
	int val;
	socklen_t size=sizeof(val);
	if ( getsockopt(SD, SOL_SOCKET, SO_SNDBUF, &val, &size) != 0 )
		throw NetConfigException("Socket Option: get SNDBUF");
	return val;
}

void Socket::SetSendSize(int Bytes)
{
	if ( setsockopt(SD, SOL_SOCKET, SO_SNDBUF, &Bytes, sizeof(Bytes)) != 0 )
		throw NetConfigException("Socket Option: set SNDBUF");
}

int  Socket::GetMinReceive(void)
{
	int val;
	socklen_t size=sizeof(val);
	if ( getsockopt(SD, SOL_SOCKET, SO_RCVLOWAT, &val, &size) != 0 )
		throw NetConfigException("Socket Option: get RCVLOWAT");
	return val;
}

void Socket::SetMinReceive(int Bytes) //---Not yet implemented in Linux
{
	if ( setsockopt(SD, SOL_SOCKET, SO_RCVLOWAT, &Bytes, sizeof(Bytes)) != 0 )
		throw NetConfigException("Socket Option: set RCVLOWAT");
}

int  Socket::GetMinSend(void)
{
	int val;
	socklen_t size=sizeof(val);
	if ( getsockopt(SD, SOL_SOCKET, SO_SNDLOWAT, &val, &size) != 0 )
		throw NetConfigException("Socket Option: get SNDLOWAT");
	return val;
}

void Socket::SetMinSend(int Bytes) //---Not yet implemented in Linux
{
	if ( setsockopt(SD, SOL_SOCKET, SO_SNDLOWAT, &Bytes, sizeof(Bytes)) != 0 )
		throw NetConfigException("Socket Option: set SNDLOWAT");
}

struct timeval Socket::GetReceiveTimeout(void)
{
	struct timeval val;
	socklen_t size=sizeof(val);
	if ( getsockopt(SD, SOL_SOCKET, SO_RCVTIMEO, &val, &size) != 0 )
		throw NetConfigException("Socket Option: get RCVTIMEO");
	return val;
}

void Socket::SetReceiveTimeout(struct timeval& val) //---Not yet implemented in Linux
{
	if ( setsockopt(SD, SOL_SOCKET, SO_RCVTIMEO, &val, sizeof(val)) != 0 )
		throw NetConfigException("Socket Option: set RCVTIMEO");
}

struct timeval Socket::GetSendTimeout(void)
{
	struct timeval val;
	socklen_t size=sizeof(val);
	if ( getsockopt(SD, SOL_SOCKET, SO_SNDTIMEO, &val, &size) != 0 )
		throw NetConfigException("Socket Option: get SNDTIMEO");
	return val;
}

void Socket::SetSendTimeout(struct timeval& val) //---Not yet implemented in Linux
{
	if ( setsockopt(SD, SOL_SOCKET, SO_SNDTIMEO, &val, sizeof(val)) != 0 )
		throw NetConfigException("Socket Option: set SNDTIMEO");
}

ENetwork Socket::GetType(void)
{
	int val;
	socklen_t size=sizeof(val);
	if ( getsockopt(SD, SOL_SOCKET, SO_TYPE, &val, &size) != 0 )
		throw NetConfigException("Socket Option: get TYPE");
	return (ENetwork)val;
}

int  Socket::GetTTL(void)
{
	int val;
	socklen_t size=sizeof(val);
	if ( GetType() == eIPv4 )
	{
		if ( getsockopt(SD, SOL_IP, IP_TTL, &val, &size) != 0 )
			throw NetConfigException("IP Option: get TTL");
	}
	else if ( GetType() == eIPv6 )
	{
		if ( getsockopt(SD, SOL_IPV6, IPV6_UNICAST_HOPS, &val, &size) != 0 )
			throw NetConfigException("IP Option: get MULTICAST_TTL");
	}
	return val;
}

void Socket::SetTTL(int Hops)
{
	if ( GetType() == eIPv4 )
	{
		if ( setsockopt(SD, SOL_IP, IP_TTL, &Hops, sizeof(Hops)) != 0 )
			throw NetConfigException("IP Option: set TTL");
	}
	else if ( GetType() == eIPv6 )
	{
		if ( setsockopt(SD, SOL_IPV6, IPV6_UNICAST_HOPS, &Hops, sizeof(Hops)) != 0 )
			throw NetConfigException("IP Option: set MULTICAST_TTL");
	}
}

int  Socket::GetError(void)
{
	int val;
	socklen_t size=sizeof(val);
	if ( getsockopt(SD, SOL_SOCKET, SO_ERROR, &val, &size) != 0 )
		throw NetConfigException("Socket Option: get ERROR");
	return val;
}

///////////////////////////////////////////////////////////////////////////////
/// SocketStream
//-----------------------------------------------------------------------------
//--- Class configuration (CRUD)

int  SocketStream::GetMaxSegmentSize(void)
{
	int val;
	socklen_t size=sizeof(val);
	if ( getsockopt(SD, SOL_TCP, TCP_MAXSEG, &val, &size) != 0 )
		throw NetConfigException("Socket Option: get TCP_MAXSEG");
	return val;
}

void SocketStream::SetMaxSegmentSize(short Bytes)
{
	if ( setsockopt(SD, SOL_TCP, TCP_MAXSEG, &Bytes, sizeof(Bytes)) != 0 )
		throw NetConfigException("Socket Option: set TCP_MAXSEG");
}

void SocketStream::DontDelay(bool Setting)
{
	if ( setsockopt(SD, SOL_TCP, TCP_NODELAY, &Setting, sizeof(Setting)) != 0 )
		throw NetConfigException("Socket Option: DONTDELAY ");
}

///////////////////////////////////////////////////////////////////////////////
/// SocketServer
//-----------------------------------------------------------------------------
//--- Constructors & Destructors
SocketServer::SocketServer(int Port, ENetwork Network, int QLen): SocketStream(Network)
{
	type = eNone;
	task_fn = 0;
	HostAddress Addr(0);
	Addr.SetPort(Port);
	Bind(Addr);
	if ( listen(SD, QLen) != 0 )
		throw NetConnectException("Listen");
	struct sigaction act;
	memset(&act, 0 , sizeof(act));
	act.sa_handler = SigChild;
	act.sa_flags = SA_NOCLDSTOP;
	if ( sigaction(SIGCHLD, &act, 0) != 0 )
		throw Exception("Sigaction -- processes");
}

SocketServer::SocketServer(HostAddress& Me, int QLen): SocketStream(Me.GetNetwork())
{
	type = eNone;
	task_fn = 0;
	Bind(Me);
	if ( listen(SD, QLen) != 0 )
		throw NetConnectException("Could not convert to listening socket");
	struct sigaction act;
	memset(&act, 0 , sizeof(act));
	act.sa_handler = SigChild;
	act.sa_flags = SA_NOCLDSTOP;
	if ( sigaction(SIGCHLD, &act, 0) != 0 )
		throw Exception("Sigaction -- processes");
}

SocketServer::~SocketServer(void)
{
}

//-----------------------------------------------------------------------------
//--- Specific Implementation
void SocketServer::Accept(void (*Server)(const Socket&))
{
	int client = accept(SD, 0, 0);
	if ( client < 0 )
		throw NetConnectException("Problems with accepting a connection");
	switch ( type )
	{
		case eCallback:
		case eProcess:
		case eThread: break;
	}
	(*Server)(Socket(client));
}

void SocketServer::Accept(HostAddress& Addr, void (*Server)(const Socket&))
{
	socklen_t size=Addr.GetSize();
	int client = accept(SD, Addr.GetAddress(), &size);
	if ( client < 0 )
		throw NetConnectException("Problems with accepting a connection");
	switch ( type )
	{
		case eCallback:
		case eProcess:
		case eThread: break;
	}
	(*Server)(Socket(client));
}

//-----------------------------------------------------------------------------
//--- Class configuration (CRUD)
void SocketServer::RegTask(void (*FN)(Socket& socket, HostAddress& addr))
{
}


///////////////////////////////////////////////////////////////////////////////
/// SocketClient
//-----------------------------------------------------------------------------
//--- Constructors & Destructors
SocketClient::SocketClient(HostAddress& Host, ENetwork Network): SocketStream(Network)
{
	Connect(Host);
}

//-----------------------------------------------------------------------------
//--- Specific Implementation
void SocketClient::Connect(HostAddress& Address)
{
	if ( connect(SD, Address.GetAddress(), Address.GetSize()) != 0 )
		throw NetConnectException("Connect");
}


///////////////////////////////////////////////////////////////////////////////
/// Datagram
//-----------------------------------------------------------------------------
//--- Constructors & Destructors

Datagram::Datagram(HostAddress& Me, ENetwork Network, EProtocol Protocol): Socket(Network, Protocol)
{
	Bind(Me);
}

Datagram::Datagram(ENetwork Network, EProtocol Protocol): Socket(Network, Protocol)
{}

//-----------------------------------------------------------------------------
//--- Private class configuration (CRUD)

void Datagram::SetTOS(bool Setting, int Val)
{
	int tos;
	socklen_t size=sizeof(tos);
	if ( getsockopt(SD, SOL_IP, IP_TOS, &tos, &size) != 0 )
		throw NetConfigException("Socket Option: get IP_TOS");
	if ( Setting != 0 )
		tos |= Val;
	else
		tos &= ~Val;
	if ( setsockopt(SD, SOL_IP, IP_TOS, &tos, sizeof(tos)) != 0 )
		throw NetConfigException("Socket Option: set IP_TOS");
}

//-----------------------------------------------------------------------------
//--- Class configuration (CRUD)

void Datagram::MinimizeDelay(bool Setting)
{
	SetTOS(Setting, IPTOS_LOWDELAY);
}

void Datagram::MaximizeThroughput(bool Setting)
{
	SetTOS(Setting, IPTOS_THROUGHPUT);
}

void Datagram::MaximizeReliability(bool Setting)
{
	SetTOS(Setting, IPTOS_RELIABILITY);
}

void Datagram::MinimizeCost(bool Setting)
{
	SetTOS(Setting, IPTOS_LOWCOST);
}

void Datagram::PermitFragNegotiation(EFrag Setting)
{
	if ( setsockopt(SD, SOL_IP, IP_MTU_DISCOVER, &Setting, sizeof(Setting)) != 0 )
		throw NetConfigException("Socket Option: set MTU_DISCOVER");
}

///////////////////////////////////////////////////////////////////////////////
/// Broadcast
//-----------------------------------------------------------------------------
//--- Constructors & Destructors
Broadcast::Broadcast(HostAddress& Me): Datagram(Me)
{
	const int on=1;
	if ( setsockopt(SD, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) != 0 )
		throw NetConfigException("Socket Option: set BROADCAST");
}

///////////////////////////////////////////////////////////////////////////////
/// MessageGroup
//-----------------------------------------------------------------------------
//--- Constructors & Destructors
MessageGroup::~MessageGroup(void)
{
	HostAddress NoAddr(0, GetType());
	for ( int i = 0; i < MAXGROUPS; i++ )
		if ( Addr[i] != NoAddr )
			Drop(Addr[i]);
}

//-----------------------------------------------------------------------------
//--- Specific Implementation
void MessageGroup::Connect(HostAddress& Address)
{
	if ( connect(SD, Address.GetAddress(), Address.GetSize()) != 0 )
		throw NetConnectException("Connect");
}

int MessageGroup::FindSlot(HostAddress& Host)
{	int slot=-1;

	for ( int i = 0; i < MAXGROUPS  &&  slot < 0; i++ )
		if ( Addr[i] == Host )
			slot = i;
	return slot;
}

void MessageGroup::Join(HostAddress& Address, int IFIndex)
{	int slot=-1;
	HostAddress NoAddr(0, Address.GetNetwork());

	slot = FindSlot(NoAddr);
	if ( slot < 0 )
		throw RangeException("Multicast table full");
	if ( GetType() == eIPv4 )
	{	struct ip_mreqn mreq;

		bzero(&mreq, sizeof(mreq));
		void* src = &(reinterpret_cast<struct sockaddr_in *>(Address.GetAddress())->sin_addr);
		memcpy(&mreq.imr_multiaddr, src, sizeof(mreq.imr_multiaddr));
		mreq.imr_ifindex = IFIndex;
		if ( setsockopt(SD, SOL_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) != 0 )
			throw NetConfigException("Socket Option: Join Multicast");
	}
	else if ( GetType() == eIPv6 )
	{	struct ipv6_mreq mreq;

		bzero(&mreq, sizeof(mreq));
		void* src = &(reinterpret_cast<struct sockaddr_in *>(Address.GetAddress())->sin_addr);
		memcpy(&mreq.ipv6mr_multiaddr, src, sizeof(mreq.ipv6mr_multiaddr));
		mreq.ipv6mr_interface = IFIndex;
		if ( setsockopt(SD, SOL_IPV6, IPV6_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) != 0 )
			throw NetConfigException("Socket Option: Join Multicast");
	}
	Addr[slot] = Address;
}

void MessageGroup::Drop(HostAddress& Address)
{	int slot=-1;

	for ( int i = 0; i < MAXGROUPS  &&  slot < 0; i++ )
		if ( Addr[i] == Address )
			slot = i;
	if ( slot == -1 )
		throw RangeException("Group not joined");
	if ( GetType() == eIPv4 )
	{	struct ip_mreq mreq;
		struct sockaddr_in *inet = reinterpret_cast<struct sockaddr_in *>(Addr[slot].GetAddress());

		mreq.imr_multiaddr = inet->sin_addr;
		mreq.imr_interface.s_addr = INADDR_ANY;
		if ( setsockopt(SD, SOL_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq)) != 0 )
			throw NetConfigException("Socket Option: Drop Multicast");
	}
	else if ( GetType() == eIPv6 )
	{	struct ipv6_mreq mreq;
		struct sockaddr_in6 *inet6 = reinterpret_cast<struct sockaddr_in6 *>(Addr[slot].GetAddress());
		mreq.ipv6mr_multiaddr = inet6->sin6_addr;
		mreq.ipv6mr_interface = INADDR_ANY;
		if ( setsockopt(SD, SOL_IPV6, IPV6_DROP_MEMBERSHIP, &mreq, sizeof(mreq)) != 0 )
			throw NetConfigException("Socket Option: Drop Multicast");
	}
	Addr[slot] = HostAddress();
}

//-----------------------------------------------------------------------------
//--- Class configuration (CRUD)

void MessageGroup::Loopback(bool Setting)
{
	int val = (Setting != 0);
	if ( GetType() == eIPv4 )
	{
		if ( setsockopt(SD, SOL_IP, IP_MULTICAST_LOOP, &val, sizeof(val)) != 0 )
			throw NetConfigException("IP Option: set MULTICAST_TTL");
	}
	else if ( GetType() == eIPv6 )
	{
		if ( setsockopt(SD, SOL_IPV6, IPV6_MULTICAST_LOOP, &val, sizeof(val)) != 0 )
			throw NetConfigException("IP Option: set MULTICAST_TTL");
	}
}

int  MessageGroup::GetTTL(void)
{
	int val;
	socklen_t size=sizeof(val);
	if ( GetType() == eIPv4 )
	{
		if ( getsockopt(SD, SOL_IP, IP_MULTICAST_TTL, &val, &size) != 0 )
			throw NetConfigException("IP Option: get MULTICAST_TTL");
	}
	else if ( GetType() == eIPv6 )
	{
		if ( getsockopt(SD, SOL_IPV6, IPV6_MULTICAST_HOPS, &val, &size) != 0 )
			throw NetConfigException("IP Option: get MULTICAST_TTL");
	}
	return val;
}

void MessageGroup::SetTTL(int Hops)
{
	if ( GetType() == eIPv4 )
	{
		if ( setsockopt(SD, SOL_IP, IP_MULTICAST_TTL, &Hops, sizeof(Hops)) != 0 )
			throw NetConfigException("IP Option: set MULTICAST_TTL");
	}
	else if ( GetType() == eIPv6 )
	{
		if ( setsockopt(SD, SOL_IPV6, IPV6_MULTICAST_HOPS, &Hops, sizeof(Hops)) != 0 )
			throw NetConfigException("IP Option: set MULTICAST_TTL");
	}
}

