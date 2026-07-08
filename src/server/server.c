#include <netinet/in.h>
#include <server/server.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/* This function configures a socket TCP so it acts as a server
    * Parameters: Server *server, uint16_t server_port (pointer to a server, unsigned int of a server port)
    * Returns: int (0 succeed) (-1 error)
    *
    * All TCP servers in C are: socket -> bind -> listen -> accept
*/
int server_init(Server *server, uint16_t server_port) {
    if (!server) return -1;

    // Initializing the client count
    server->client_count = 0;

    // Creates the socket TCP
    server->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->fd == 1) return -1;

    // Configures the server address
    // IPv4, port, accept connections in all IPs of the PC
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(server_port);
    server->addr.sin_addr.s_addr = INADDR_ANY;

    // bind() tells the OS this socket will use this IP and this port
    // assigns an address to the socket
    if (bind(server->fd, (struct sockaddr *)&server->addr, sizeof(server->addr)) < 0) {
        return -1;
    }

    if (listen(server->fd, SOMAXCONN) < 0) return -1;
    printf("Server listening on port %d\n", server_port);

    return 0;
}

/* This function waits for a client to connect, obtains the information about the client, creates the client and returns it
    * Accepts incoming connection and returns a pointer to newly allocated client
    *
    * Parameters: Server *server (pointer to Server)
    * Returns: Client* (pointer to the newly created client)
*/
Client *server_accept(Server *server) {
    if (!server) return NULL;

    struct sockaddr_in address;
    socklen_t addr_len = sizeof(address);

    int sockfd = accept(
        server->fd,
        (struct sockaddr *)&address,
        &addr_len
    );
    if (sockfd == -1) return NULL;


    return create_client(sockfd, address);
}

/* This function adds a connected client to the servers list of clients
    * Parameters: Server *server, Client *client (pointer to server) (pointer to client) 
    * Returns: int (0 succeed) (-1 error)
*/
int server_add_client(Server *server, Client *client) {
    if (!server || !client) return -1;

    if (server->client_count >= MAX_CLIENTS) return -1;

    server->clients[server->client_count] = client;
    server->client_count++;

    return 0;
}

/* This function removes a client from the server list and update the client count
    * Parameters: Server *server, Client *client (pointer to server) (pointer to client)
    * Returns: int (0 succeed) (-1 error)
*/
int server_remove_client(Server *server, Client *client) {
    if (!server || !client) return -1;
    
    for (int i = 0; i < server->client_count; i++) {
        if (server->clients[i] == client) {
            // Move the last client into this pos
            server->clients[i] = server->clients[server->client_count -1];

            server->client_count--;

            return 0;
        }
    }

    // client not found
    return -1;
}

/* This function broadcast a message to all the clients in the server
    * Parameters: Server *server, Client *sender, const char *msg (pointer to the server) (pointer to a client) (string literal)
    * Returns: void
*/
void server_broadcast(Server *server, Client *sender, const char *msg) {
    if (!server || !sender || !msg) return;

    for (int i = 0; i < server->client_count; i++) {
        if (server->clients[i] == sender) {
            continue;
        } 

        send(server->clients[i]->sockfd, msg, strlen(msg), 0);
    }
}

/* This function closes the server, since the server will live in stack doesnt needs to free memory
    * Parameters: Server *server (pointer to the server)
    * Returns: void (nothing)
*/
void server_close(Server *server) {
    if (!server) return;   

    close(server->fd);
}
