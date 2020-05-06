#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

#define MAX_LINE 100
#define LINE_ARRAY_SIZE (MAX_LINE+1)

using namespace std;

int main()
{
  int socketDescriptor;
  unsigned short int serverPort;
  struct sockaddr_in serverAddress;
  struct hostent *hostInfo;
  char buf[LINE_ARRAY_SIZE], c;

  cout << "Enter server host name or IP address: ";
  cin.get(buf, MAX_LINE, '\n');

  // gethostbyname() takes a host name or ip address in "numbers and
  // dots" notation, and returns a pointer to a hostent structure,
  // which we'll need later.  It's not important for us what this
  // structure is actually composed of.
  hostInfo = gethostbyname(buf);
  if (hostInfo == NULL) {
    cout << "problem interpreting host: " << buf << "\n";
    exit(1);
  }

  cout << "Enter server port number: ";
  cin >> serverPort;
  cin.get(c); // dispose of the newline

  // Create a socket.  "AF_INET" means it will use the IPv4 protocol.
  // "SOCK_STREAM" means it will be a reliable connection (i.e., TCP;
  // for UDP use SOCK_DGRAM), and I'm not sure what the 0 for the last
  // parameter means, but it seems to work.
  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socketDescriptor < 0) {
    cerr << "cannot create socket\n";
    exit(1);
  }

  // Connect to server.  First we have to set some fields in the
  // serverAddress structure.  The system will assign me an arbitrary
  // local port that is not in use.
  serverAddress.sin_family = hostInfo->h_addrtype;
  memcpy((char *) &serverAddress.sin_addr.s_addr,
         hostInfo->h_addr_list[0], hostInfo->h_length);
  serverAddress.sin_port = htons(serverPort);
				
  if (connect(socketDescriptor,
              (struct sockaddr *) &serverAddress,
              sizeof(serverAddress)) < 0) {
    cerr << "cannot connect\n";
    exit(1);
  }

  cout << "\nEnter some lines, and the server will modify them and\n";
  cout << "send them back.  When you are done, enter a line with\n";
  cout << "just a dot, and nothing else.\n";
  cout << "If a line is more than " << MAX_LINE << " characters, then\n";
  cout << "only the first " << MAX_LINE << " characters will be used.\n\n";

  // Prompt the user for input, then read in the input, up to MAX_LINE
  // charactars, and then dispose of the rest of the line, including
  // the newline character.
  cout << "Input: ";
  cin.get(buf, MAX_LINE, '\n');
  while (cin.get(c) && c != '\n')
    ;

  // Stop when the user inputs a line with just a dot.
  while (strcmp(buf, ".")) {
    // Send the line to the server.
    if (send(socketDescriptor, buf, strlen(buf) + 1, 0) < 0) {
      cerr << "cannot send data ";
      close(socketDescriptor);
      exit(1);
    }

    // Zero out the buffer.
    memset(buf, 0x0, LINE_ARRAY_SIZE);

    // Read the modified line back from the server.
    if (recv(socketDescriptor, buf, MAX_LINE, 0) < 0) {
      cerr << "didn't get response from server?";
      close(socketDescriptor);
      exit(1);
    }

    cout << "Modified: " << buf << "\n";

    // Prompt the user for input, then read in the input, up to MAX_LINE
    // charactars, and then dispose of the rest of the line, including
    // the newline character.  As above.
    cout << "Input: ";
    cin.get(buf, MAX_LINE, '\n');
    while (cin.get(c) && c != '\n')
      ;
  }

  close(socketDescriptor);
  return 0;
}
