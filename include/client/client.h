#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAX_NAME_LENGHT 32

typedef struct Client {
    int sockfd; // socket (connection id)
    struct sockaddr_in address; // ip + port of that client
    char name[MAX_NAME_LENGHT]; // username
} Client;

Client *create_client(int sockfd, struct sockaddr_in address);
void delete_client(Client *client);
void assign_username(Client *client, const char *u);

