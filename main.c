#include <stdlib.h>
#include <string.h>
#include "ArgumentAnalizer.h"

#define NICK_NAME_SIZE 50
#define HOST_NAME_SIZE 150
#define DEFAULT_PORT 9696

typedef int FileDescriptor;
typedef struct sockaddr_in SocketAddress;
#define BUFFER_SIZE 256

#define DEBUG

enum mode
{
	NOT_SET
	SERVER,
	CLIENT
};
typedef enum mode Mode;

void Error(const char *msg)
{
	perror(msg);
	exit(1);
}

void Server(int port, char* nick)
{
	FileDescriptor serverSocketFD, socketConnectionFD;
	socklen_t clientSocketLenght;
	SocketAddress serverAddress, clientAddress;
	#ifdef DEBUG
	printf("Initializing socket\n");
	#endif
	serverSocketFD= socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocketFD < 0)
	{
		Error("[ERROR] Fail opening socket...\n");
	}
	#ifdef DEBUG
	printf("Socket initialize sucess!\n");
	#endif
	memset((char *) &serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family= AF_INET;
	serverAddress.sin_addr.s_addr= INADDR_ANY;
	serverAddress.sin_port = htons(serverPort);//htons = host to network endian
	#ifdef DEBUG
	printf("Biding socket to port\n");
	#endif
	if(0 > ( bind(serverSocketFD, (struct sockaddr *) &serverAddress, sizeof(serverAddress) ) ) )
	{
		Error("[ERROR] Binding failed\n");
	}
	#ifdef DEBUG
	printf("Biding socket sucess!\n");
	#endif
	#ifdef DEBUG
	printf("Socket now listening for incoming calls\n");
	#endif
	listen(serverSocketFD,5);
	#ifdef DEBUG
	printf("Waiting for contact...\n");
	#endif
	clientSocketLenght = sizeof(clientAddress);
	socketConnectionFD = accept(serverSocketFD, (struct sockaddr *) &clientAddress, &clientSocketLenght);
	if(socketConnectionFD < 0)
	{
		Error("[ERROR] Error on accept");
		continue;
	}
	#ifdef DEBUG
	printf("Contact sucess!\n");
	#endif
}
void Client(int port, char* nick)
{
	
}

int main(int argc, char **argv)
{
	int port= DEFAULT_PORT, aux;
	char *hostName, *userNick;
	Mode mode= NOT_SET;
	srand(time(NULL));
	if( SEARCH_FAILED == (aux = FindArgument("-n", argc, argv) ) )
	{
		printf("You need to specify your nick on the chat using -n [nickname].\n");
		return 0;
	}
	else
	{
		userNick= argv(aux+1);
	}
	if( SEARCH_FAILED == (aux = FindArgument("-S", argc, argv) ) )
	{
		//é servidor
		if(aux+1 < argc)
		{
			port = atoi(argv[aux+1]);
			Server(port, userNick);
		}
		else
		{
			printf("You need to specify the port after the '-C' or '-S'.\n");
			printf("Using default port.\n");
		}
		Server(port, userNick);
	}
	else if( SEARCH_FAILED == (aux = FindArgument("-C", argc, argv) ) )
	{
		//é cliente
		if(aux+1 < argc)
		{
			port = atoi(argv[aux+1]);
			Client(port, );
		}
		else
		{
			printf("You need to specify the port after the '-C' or '-S'.\n");
			printf("Using default port.\n");
		}
		Client(port, userNick);
	}
	else
	{
		printf("You need to specify if you are going to be a server or a client with -P or -C, respectively.\n");
	}

}
