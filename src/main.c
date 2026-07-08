#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "client/client.h"
#include "server/server.h"

#define SERVER_PORT 8080

int main(void) {
    Server server;

    // Starts the server on the stack
    if (server_init(&server, SERVER_PORT) != 0) {
        printf("Server couldnt be started\n");
        return EXIT_FAILURE;
    }

    while (1) {
        Client *client = server_accept(&server);

        if (!client) continue;

        if (server_add_client(&server, client) != 0) {
            delete_client(client);
            continue;
        } 

        char username[32];

        int bytes = recv(client->sockfd, username, sizeof(username) - 1, 0);

        if (bytes <= 0) {
            server_remove_client(&server, client);
            delete_client(client);
            continue;
        } 

        username[bytes] = '\0';

        assign_username(client, username);

        printf("%s joined the server\n", client->name);

        // Receive username
        // Receive messages
        // Broadcast messages
        //Client disconnects

        server_remove_client(&server, client);

        delete_client(client);
    }

    server_close(&server);

    return EXIT_SUCCESS;
}

