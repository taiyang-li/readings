/* socket.h
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
/*** socket.h                                                              ***/
/***                                                                       ***/
/*** Defines the C++ socket framework.                                     ***/
/*****************************************************************************/

#include <sys/socket.h>
#include <resolv.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <errno.h>

typedef enum { eIPv4=PF_INET, eIPv6=PF_INET6 } ENetwork;
typedef enum { eStream=SOCK_STREAM, eDatagram=SOCK_DGRAM } EProtocol;

///////////////////////////////////////////////////////////////////////////////
/// SimpleString
//
//----------------------------------------------------------------------------
//---This class is separated and different from TextMessage, because exception
//---management must have the minimal number points of failure.  It would be
//---*very*bad* to have an exception within an exception.
//----------------------------------------------------------------------------
class SimpleString
{
	private:
		char *Buffer;
		int  Length;

	public:
		SimpleString(const char* s);
		SimpleString(const SimpleString& s);
		virtual ~SimpleString(void);

	protected:
		void Append(const char* s);
		void Append(const SimpleString& s);

	public:
		SimpleString& operator +(const char* s)		{ Append(s); return *this; }
		SimpleString& operator +(SimpleString s)	{ Append(s); return *this; }

	public:
		const char* GetString(void) const			{ return Buffer; }
		int GetLength(void) const					{ return Length; }
};

///////////////////////////////////////////////////////////////////////////////
/// Exception
class Exception
{
	private:
		int ErrNo;
		SimpleString Msg;

	public:
		Exception(const SimpleString M, int Err=0): Msg(M), ErrNo(Err) {}
		virtual ~Exception(void) {}

	public:
		int GetError(void) const						{ return ErrNo; }
		virtual void PrintException(void) const;
};

///////////////////////////////////////////////////////////////////////////////
/// RangeException
class RangeException: public Exception
{
	public:
		RangeException(const SimpleString M): Exception(M, ERANGE) {}
		virtual ~RangeException(void){}
};

///////////////////////////////////////////////////////////////////////////////
/// FileException
class FileException: public Exception
{
	public:
		FileException(const SimpleString M): Exception(M, errno) {}
		virtual ~FileException(void){}
};

///////////////////////////////////////////////////////////////////////////////
/// NetException
class NetException: public Exception
{
	public:
		NetException(const SimpleString M): Exception(M, errno) {}
		virtual ~NetException(void){}
};

///////////////////////////////////////////////////////////////////////////////
/// NetConversionException
class NetConversionException: public NetException
{
	public:
		NetConversionException(const SimpleString M): NetException(M) {}
		virtual ~NetConversionException(void){}
};

///////////////////////////////////////////////////////////////////////////////
/// NetDNSException
class NetDNSException: public NetException
{
	public:
		NetDNSException(const SimpleString M): NetException(M) {}
		virtual ~NetDNSException(void){}
};

///////////////////////////////////////////////////////////////////////////////
/// NetIOException
class NetIOException: public NetException
{
	public:
		NetIOException(const SimpleString M): NetException(M) {}
		virtual ~NetIOException(void){}
};

///////////////////////////////////////////////////////////////////////////////
/// NetConnectException
class NetConnectException: public NetException
{
	public:
		NetConnectException(const SimpleString M): NetException(M) {}
		virtual ~NetConnectException(void){}
};

///////////////////////////////////////////////////////////////////////////////
/// NetConfigException
class NetConfigException: public NetException
{
	public:
		NetConfigException(const SimpleString M): NetException(M) {}
		virtual ~NetConfigException(void){}
};

///////////////////////////////////////////////////////////////////////////////
/// HostAddress
class HostAddress
{
	private:
		static const int MaxHostName=50;
		ENetwork Network;
		char HostName[MaxHostName];
		struct sockaddr *Addr;

	public:
		HostAddress(const char* Name=0, ENetwork Network=eIPv4);
		HostAddress(HostAddress& Address);
		virtual ~HostAddress(void);

	public:
		void SetPort(int Port);
		int GetPort(void) const;
		ENetwork GetNetwork(void) const			{ return Network; }
		struct sockaddr* GetAddress(void) const	{ return Addr; }
		int GetSize(void) const;
		int operator ==(HostAddress& Address) const;
		int operator !=(HostAddress& Address) const	{ return !(operator ==(Address)); }
		const char* GetHost(bool byName=1);
};

///////////////////////////////////////////////////////////////////////////////
/// Message
class Message
{
	public:
		virtual ~Message(void){}

	public:
		virtual char* Wrap(int& Bytes) const=0;
		virtual bool  Unwrap(char* package, int Bytes, int MsgNum)=0;
};

///////////////////////////////////////////////////////////////////////////////
/// TextMessage
class TextMessage: public Message
{
	private:
		char *Buffer;
		unsigned short Available;
		unsigned short Size;

	public:
		TextMessage(unsigned short Bytes);
		TextMessage(const char *Msg, unsigned short Len=0);
		virtual ~TextMessage(void);

	private:
		void SetString(const char* str, int len=-1);
		void SetString(const TextMessage& s)				{ SetString(s.Buffer, s.Size); }
		void Append(const char* str, int len=-1);
		void Append(const TextMessage& s)					{ Append(s.Buffer, s.Size-1); }

	public:
		TextMessage& operator =(const char* str)			{ SetString(str); return *this; }
		TextMessage& operator =(const TextMessage& s)		{ SetString(s); return *this; }
		TextMessage& operator +=(const char* str)			{ Append(str); return *this; }
		TextMessage& operator +=(const TextMessage& s)		{ Append(s); return *this; }

	public:
		virtual char* GetBuffer(void) const					{ return Buffer; }
		virtual char* Wrap(int& Bytes) const;
		virtual bool  Unwrap(char* package, int Bytes, int MsgNum);
		virtual int   GetSize(void) const					{ return Size; }
		virtual void  SetSize(int Bytes)					{ Size = Bytes; }
		virtual int   GetAvailable(void) const				{ return Available; }
};


///////////////////////////////////////////////////////////////////////////////
/// Socket
class Socket
{
	protected:
		int SD;

	public:
		Socket(void) { SD = -1; }
		Socket(int sd): SD(sd) {}
		Socket(ENetwork Network, EProtocol Protocol);
		Socket(Socket& sock);

	public:
		virtual ~Socket(void);

	public:
		void Bind(HostAddress& Addr);
		int  Send(Message& Msg, int Options=0) const;
		int  Send(HostAddress& Addr, Message& Msg, int Options=0) const;
		int  Receive(Message& Msg, int Options=0) const;
		int  Receive(HostAddress& Addr, Message& Msg, int Options=0) const;
		void CloseInput(void) const						{ shutdown(SD, 0); }
		void CloseOutput(void) const					{ shutdown(SD, 1); }

	public:
		void PermitRoute(bool Setting);
		void KeepAlive(bool Setting);
		void ShareAddress(bool Setting);
		int  GetReceiveSize(void);
		void SetReceiveSize(int Bytes);
		int  GetSendSize(void);
		void SetSendSize(int Bytes);
		int  GetMinReceive(void);
		void SetMinReceive(int Bytes);		//---Not yet implemented in Linux
		int  GetMinSend(void);
		void SetMinSend(int Bytes);			//---Not yet implemented in Linux
		struct timeval GetReceiveTimeout(void);
		void SetReceiveTimeout(struct timeval& val); //---Not yet implemented in Linux
		struct timeval GetSendTimeout(void);
		void SetSendTimeout(struct timeval& val); //---Not yet implemented in Linux
		ENetwork GetType(void);
		virtual int  GetTTL(void);
		virtual void SetTTL(int Hops);
		int  GetError(void);
};

///////////////////////////////////////////////////////////////////////////////
/// SocketStream
class SocketStream: public Socket
{
	private:
		void (*Urg_FN)(char *Msg);

	public:
		SocketStream(void);
		SocketStream(int sd): Urg_FN(0), Socket(sd){}
		SocketStream(ENetwork Network): Socket(Network, eStream){}
		SocketStream(SocketStream& sock): Urg_FN(sock.Urg_FN), Socket(sock) {}
		virtual ~SocketStream(void){}

	public:
		int  GetMaxSegmentSize(void);
		void SetMaxSegmentSize(short Bytes);
		void DontDelay(bool Setting);
};

///////////////////////////////////////////////////////////////////////////////
/// SocketServer
class SocketServer: public SocketStream
{
	public:
		typedef enum { eNone, eCallback, eProcess, eThread } ETask;

	private:
		ETask type;
		void (*task_fn)(Socket& socket, HostAddress& addr);

	public:
		SocketServer(int port, ENetwork Network=eIPv4, int QLen=15);
		SocketServer(HostAddress& Addr, int QLen=15);
		virtual ~SocketServer(void);

	private:
		static void SigChild(int sig)	{ wait(0); }

	public:
		void Accept(void (*Server)(const Socket& Client));
		void Accept(HostAddress& Addr, void (*Server)(const Socket& Client));
		void RegTask(void (*FN)(Socket& socket, HostAddress& addr));
};

///////////////////////////////////////////////////////////////////////////////
/// SocketClient
class SocketClient: public SocketStream
{
	public:
		SocketClient(ENetwork Network=eIPv4): SocketStream(Network){}
		SocketClient(HostAddress& Host, ENetwork Network=eIPv4);
		virtual ~SocketClient(void){}

	public:
		void Connect(HostAddress& Addr);
};

///////////////////////////////////////////////////////////////////////////////
/// Datagram
class Datagram: public Socket
{
	public:
		typedef enum { eJustSend, eHints, eNegotiate } EFrag;

	public:
		Datagram(HostAddress& Me, ENetwork Network=eIPv4, EProtocol Protocol=eDatagram);
		Datagram(ENetwork Network=eIPv4, EProtocol Protocol=eDatagram);
		virtual ~Datagram(void){}

	private:
		void SetTOS(bool Setting, int Val);

	public:
		void MinimizeDelay(bool Setting);
		void MaximizeThroughput(bool Setting);
		void MaximizeReliability(bool Setting);
		void MinimizeCost(bool Setting);
		void PermitFragNegotiation(EFrag Setting);
};

///////////////////////////////////////////////////////////////////////////////
/// Broadcast
class Broadcast: public Datagram
{
	private:
		HostAddress Address;

	public:
		Broadcast(HostAddress& Me);
		virtual ~Broadcast(void){}
};

///////////////////////////////////////////////////////////////////////////////
/// MessageGroup
class MessageGroup: public Datagram
{
	private:
		static const int MAXGROUPS=10;
		HostAddress Addr[MAXGROUPS];

	public:
		MessageGroup(HostAddress& Me, ENetwork Network=eIPv4): Datagram(Me, Network) {}
		virtual ~MessageGroup(void);

	private:
		int  FindSlot(HostAddress& Host);

	public:
		void Connect(HostAddress& Address);
		void Join(HostAddress& Address, int IFIndex=0);
		void Drop(HostAddress& Address);

	public:
		void Loopback(bool Setting);
		int  GetTTL(void);
		void SetTTL(int Hops);
};

