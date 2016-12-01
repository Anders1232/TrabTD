#include <stdlib.h>
#include <string.h>
#include "ArgumentAnalizer.h"

#define NICK_NAME_SIZE 50
#define HOST_NAME_SIZE 150
#define DEFAULT_PORT 9696

void Server(int port, char* nick)
{

}
void Client(int port, char* nick)
{

}


enum mode
{
	NOT_SET
	SERVER,
	CLIENT
};
typedef enum mode Mode;

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
