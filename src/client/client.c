#include "client/client.h"

#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

/* This function allocates memory for a Client
    * Parameters: int sockfd, struct sockaddr_in address 
    * Returns: Client* (pointer that points to a Client)
*/
Client *create_client(int sockfd, struct sockaddr_in address) {
    Client *client = malloc(sizeof(Client));
    if (!client) return NULL;

    client->sockfd = sockfd;
    client->address = address;
    client->name[0] = '\0';

    return client;
}

/* This function frees the memory allocated in the heap for the Client
    * Parameters: Client *client (pointer to the client)
    * Returns: void (nothing)
*/
void delete_client(Client *client) {
    if (!client) return;
    free(client);
}

/* This function assings the username, copies the chars into client->name
    * Parameters: Client *client, char *u (pointer to client) (string literal)
    * Returns: void (nothing)
*/
void assign_username(Client *client, char *u) {
    if (!client || !u) return;

    strncpy(client->name, u, sizeof(client->name) - 1);

    client->name[31] = '\0';
}

