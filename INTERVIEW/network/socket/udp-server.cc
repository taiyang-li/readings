#include <arpa/inet.h>

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

#define MAX_MSG 100
#define LINE_ARRAY_SIZE (MAX_MSG+1)

using namespace std;

int main()
{
  int listenSocket, i;
  unsigned short int listenPort;
  socklen_t clientAddressLength;
  struct sockaddr_in clientAddress, serverAddress;
  char line[LINE_ARRAY_SIZE];

  cout << "Enter port number to listen on (between 1500 and 65000): ";
  cin >> listenPort;

  // Create socket for listening for client connection requests.
  listenSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (listenSocket < 0) {
    cerr << "cannot create listen socket";
    exit(1);
  }
  
  // Bind listen socket to listen port.  First set various fields in
  // the serverAddress structure, then call bind().
  // htonl() and htons() convert long integers and short integers
  // (respectively) from host byte order (on x86 this is Least
  // Significant Byte first) to network byte order (Most Significant
  // Byte first).
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = htons(listenPort);
  
  if (bind(listenSocket,
           (struct sockaddr *) &serverAddress,
           sizeof(serverAddress)) < 0) {
    cerr << "cannot bind socket";
    exit(1);
  }

  // Wait for connections from clients.
  // This is a non-blocking call; i.e., it registers this program with
  // the system as expecting connections on this socket, and then
  // this thread of execution continues on.
  listen(listenSocket, 5);
  
  cout << "Waiting for request on port " << listenPort << "\n";

  while (1) {

    clientAddressLength = sizeof(clientAddress);

    // First set line to all zeroes, so we'll know where
    // the end of the string is.
    memset(line, 0x0, LINE_ARRAY_SIZE);
    if (recvfrom(listenSocket, line, MAX_MSG, 0,
                 (struct sockaddr *) &clientAddress,
                 &clientAddressLength) < 0) {
      cerr << "  I/O Problem";
      exit(1);
    }

    // show the client's IP address
    cout << "  from " << inet_ntoa(clientAddress.sin_addr);

    // Show the client's port number.
    cout << ":" << ntohs(clientAddress.sin_port) << "\n";

    // Show the line
    cout << "  Received: " << line << "\n";

    // Convert line to upper case.
    for (i = 0; line[i] != '\0'; i++)
      line[i] = toupper(line[i]);

    // Send converted line back to client.
    if (sendto(listenSocket, line, strlen(line) + 1, 0,
               (struct sockaddr *) &clientAddress,
               sizeof(clientAddress)) < 0)
      cerr << "Error: cannot send modified data";

    memset(line, 0x0, LINE_ARRAY_SIZE);  // set line to all zeroes
  }
}
