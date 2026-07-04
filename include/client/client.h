#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

typedef struct Client {
    int sockfd; // socket (connection id)
    struct sockaddr_in address; // ip + port of that client
    char name[32]; // username
} Client;

Client *create_client(void);
void delete_client(Client *client);
void accept_client(Client *client);
void broadcast_message(char *msg);
