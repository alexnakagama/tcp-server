#include <stdio.h>
#include <sys/socket.h>

#include "server/server.h"

#define SERVER_PORT 8080

int main(void) {
    Server server;

    // Starts the server on the stack
    if (server_init(&server, SERVER_PORT) != 0) {
        printf("Server couldnt be started\n");
        return -1;
    }

    return 0;
}
