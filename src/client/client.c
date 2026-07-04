#include "client/client.h"

#include <netinet/in.h>
#include <stdlib.h>

/* This function creates a new client without username
    * Parameters: 
    * Returns:
*/
Client *create_client(int sockfd, struct sockaddr_in address) {
    Client *client = malloc(sizeof(Client));
    if (!client) return NULL;

    client->sockfd = sockfd;
    client->address = address;
    client->name[0] = '\0';

    return client;
}

