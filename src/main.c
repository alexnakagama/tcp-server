#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "client/client.h"
#include "server/server.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

int main(void) {
    Server server;

    // Starts the server on the stack
    if (server_init(&server, SERVER_PORT) != 0) {
        printf("Server couldnt be started\n");
        return EXIT_FAILURE;
    }

    while (1) {
        // 1. Wait for the client
        Client *client = server_accept(&server);
        if (!client) continue;

        // 2. Save it
        if (server_add_client(&server, client) != 0) {
            delete_client(client);
            continue;
        } 

        // 3. Receive username
        if (client_receive_username(client) != 0) {
            server_remove_client(&server, client);
            delete_client(client);
            continue;
        }

        printf("%s joined the server\n", client->name);

        // 4. Chat
        char buffer[1024];

        while (1) {
            int bytes = recv(client->sockfd, buffer, sizeof(buffer) - 1, 0);
            if (bytes <= 0) break;

            buffer[bytes] = '\0';

            printf("%s: %s\n", client->name, buffer);

            server_broadcast(&server, client, buffer);
        }

        // 5. Client disconnected
        server_remove_client(&server, client);
        delete_client(client);
    }

    server_close(&server);
    return EXIT_SUCCESS;
}

